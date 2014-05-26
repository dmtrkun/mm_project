/*****************************************************************************
 *****************************************************************************/
#define TASKSPI_PUB
#include "include.h"

extern volatile SHORT prevX;
extern volatile SHORT prevY;
extern volatile SHORT x, y;


// semaphore to regulate access to the FLASH to read calibration
// constants and one for accessing the QVGA display
extern xSemaphoreHandle FLASHSemaphore;
//extern xSemaphoreHandle QVGAMutSemaphore;

// this semaphore is used to indicate when there is new data to be 
// processed by the touch screen task

/*********************************************************************
* Function: void TouchLoadCalibration(void)
*
* PreCondition: EEPROMInit() must be called before
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: loads calibration parameters from EEPROM
*
* Note: none
*
********************************************************************/

#define SAMPLE_PERIOD 500		// us
#define TIME_BASE (((GetPeripheralClock() / 1000) * SAMPLE_PERIOD) / 8000)

/*********************************************************************
 * Function:        Timer 4 ISR
 *
 * PreCondition:    None
 *
 * Input:           None
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Touchscreen ISR. Routine reads the analog inputs
 *					in succession and if it detects a touch event it
 *					then signals via a queue a new event to the
 *					touchscreen handling task
 *
 * Note:            
 ********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)
{
	static portBASE_TYPE ticks;
	portBASE_TYPE taskWoken = pdFALSE;

		ProcessADCSamples(NULL);


	/*read keypad*/
	ticks++;
	if(ticks%40 == 0) /*every 20 ms*/
	{
		ticks = 0;
		xSemaphoreGiveFromISR(hSPISemaphore, &taskWoken);	  

//		xQueueSendToBackFromISR(hCONTROLQueue, &cMsg, &xTaskWoken);
//		cMsg.cmd = MSG_INPUT_EVENT;
//		xQueueSendToBackFromISR(hCONTROLQueue, &cMsg, taskWoken);

//		event_man();
	}
	
	IFS1bits.T4IF = 0;       /* clear interrupt flag     */
	if( taskWoken != pdFALSE )
		portEND_SWITCHING_ISR(taskWoken);		   
}


/*********************************************************************
 * Function:        void taskSPI(void* pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *                  
 * Output:          Does not return
 *
 * Side Effects:    None
 *
 * Overview:        
 *
 * Note:            
 ********************************************************************/
void taskSPI(void* pvParameter)
{
	static GRAPHICS_MSG msg;

//	vTaskSetApplicationTaskTag( NULL, ( void * ) 's' );	

#ifndef SIM_DEBUG
	        
	TouchHardwareInit(0);
#endif	
	ANSCbits.ANSC13 = 0;   //RC13 set as digital
//	LATCbits.LATC13 = 0;
	TRISCbits.TRISC13 = 1; //Set as input	   

	
	// we initialize TMR4 here to control the sampling of the Analog and Digital Inputs
	// channels. 
	TMR4 = 0;
	PR4 = TIME_BASE - 1;
	T4CONbits.TCKPS = 1;	// prescale 1:8    //2Mhz
	IFS1bits.T4IF = 0;
	IEC1bits.T4IE = 1;
	IPC6bits.T4IP = 1;
	T4CONbits.TON = 1;
	
	
	   
	// create the semaphore used to signal touch activity from the ADC ISR
//	vSemaphoreCreateBinary(hSPISemaphore);
	xSemaphoreTake(hSPISemaphore, portMAX_DELAY);
	ucExpGPO = MCP23S08Read(GPIO);
	// any messages that we send will always be of this type
	msg.cmd = MSG_TOUCH_EVENT;
	msg.data.golMsg.type = TYPE_TOUCHSCREEN;
	
	while (1) {
		///////////////////////////////////////////////////////////
		// use a semaphore to wait for updates from the ISR
		// block forever waiting for hADCSemaphore to arrive
//		xSemaphoreTake(hSPISemaphore, portMAX_DELAY);
		if( xSemaphoreTake( hSPISemaphore, portMAX_DELAY ) != pdTRUE )
			continue;
#ifndef SIM_DEBUG
	    if(TouchScreenPacketReady())
		{
			TouchDetectPosition();
		// convert the reading and signal the semaphore if an action detected
			x = TouchGetX(); y = TouchGetY();
 			if ((x == -1) || (y == -1)) 
 			{
 				x = -1; y = -1;
 			}
 //			else
 //			{
			if ((x != prevX) && (y != prevY)) 
			{
		///////////////////////////////////////////////////////////
		// change since last cycle so send wake-up to touchscreen task
		// we use the hADCSemaphore to signal the touchscreen task
		// that it needs to do some processing
//		xSemaphoreGiveFromISR(hADCSemaphore, &taskWoken);	
//	}
		
		   
		// analyze the current screen state and send an update to the
		// graphics task
		// something has changed (press, release or move)
				if ((prevX == -1) && (prevY == -1)) {
			// screen pressed
					msg.data.golMsg.uiEvent = EVENT_PRESS;
					msg.data.golMsg.param1 = x;
					msg.data.golMsg.param2 = y;
				} else if ((x == -1) && (y== -1)) {
			// screen released
					msg.data.golMsg.uiEvent = EVENT_RELEASE;
					msg.data.golMsg.param1 = prevX;
					msg.data.golMsg.param2 = prevY;
				} else {
			// screen moved
					msg.data.golMsg.uiEvent = EVENT_MOVE;
					msg.data.golMsg.param1 = x;
					msg.data.golMsg.param2 = y;				
				}
		
		// send a message to update the graphics task
				xQueueSend(hQVGAQueue, &msg, portMAX_DELAY);
				prevX = x; prevY = y;		
			}
		}
		ucExpGPIO = ChkKeyPad();/*every 20 ms*/
#endif	
		new_event_man();
		if( xSemaphoreTake( hIOSemaphore, 0 ) == pdTRUE )
		{
			if(ucExpGPIO != ucExpGPO){
				MCP23S08Write(OLAT,ucExpGPO);
//				ucExpGPIO = ucExpGPO;
			}
			xSemaphoreGive( hIOSemaphore);
		}
	}	

}
void setExpGPO(unsigned char val, unsigned char bit)
{
#if 1		
		while( xSemaphoreTake( hIOSemaphore, portMAX_DELAY ) != pdTRUE );
		{
//				if(ucExpGPIO != ucExpGPO)
//					xSemaphoreGive( hIOSemaphore);
//				else
//				{
					
					if(val == 0)
						setBit(ucExpGPO,bit);
					else				
						clearBit(ucExpGPO,bit);
					xSemaphoreGive( hIOSemaphore);
//					break;
//				}
		}
#endif
}
void toggleExpGPO(unsigned char bit)
{
#if 1		
		while( xSemaphoreTake( hIOSemaphore, portMAX_DELAY ) != pdTRUE );

//		{
//				if(ucExpGPIO != ucExpGPO)
//					xSemaphoreGive( hIOSemaphore);
//				else
//				{
//					if(setBit(ucExpGPO,bit) == 0)
//						setBit(ucExpGPO,bit);
//					else				
//						clearBit(ucExpGPO,bit);
					toggleBit(ucExpGPO,bit);
					xSemaphoreGive( hIOSemaphore);
//					break;
//				}
//		}
#endif
}


