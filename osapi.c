/*
    FreeRTOS V7.0.1 - Copyright (C) 2011 Real Time Engineers Ltd.
*/

#define OSAPI_PUB
#include "include.h"
/* Standard includes. */
#include <stdio.h>
#include "partest.h"
#include "SST39LF400.h"    


/* Demo task priorities. */
#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainCOM_TEST_PRIORITY				( 2 )

/* The check task may require a bit more stack as it calls sprintf(). */
#define mainCHECK_TAKS_STACK_SIZE			( configMINIMAL_STACK_SIZE * 2 )

/* The execution period of the check task. */
#define mainCHECK_TASK_PERIOD				( ( portTickType ) 3000 / portTICK_RATE_MS )

/* The number of flash co-routines to create. */
#define mainNUM_FLASH_COROUTINES			( 5 )

/* Baud rate used by the comtest tasks. */
#define mainCOM_TEST_BAUD_RATE				( 19200 )

/* The frequency at which the "fast interrupt test" interrupt will occur. */
#define mainTEST_INTERRUPT_FREQUENCY		( 20000 )

/* The number of processor clocks we expect to occur between each "fast
interrupt test" interrupt. */
#define mainEXPECTED_CLOCKS_BETWEEN_INTERRUPTS ( configCPU_CLOCK_HZ / mainTEST_INTERRUPT_FREQUENCY )

/* The number of nano seconds between each processor clock. */
#define mainNS_PER_CLOCK ( ( unsigned short ) ( ( 1.0 / ( double ) configCPU_CLOCK_HZ ) * 1000000000.0 ) )

/* Dimension the buffer used to hold the value of the maximum jitter time when
it is converted to a string. */
#define mainMAX_STRING_LENGTH				( 20 )


void	DA210DEVBOARD_SST39LF400WriteWord(WORD data, DWORD address);
WORD	DA210DEVBOARD_SST39LF400ReadWord(DWORD address);
void	DA210DEVBOARD_SST39LF400SectorErase(DWORD address);

BYTE DA210DEVBOARD_SST39LF400WriteArray(DWORD address, BYTE *pData, WORD nCount);
void DA210DEVBOARD_SST39LF400ReadArray(DWORD address, BYTE *pData, WORD nCount);
void DA210DEVBOARD_SST39LF400ChipErase(void);


///////////////////////////////////////////////////////////////////
// Semaphores used to guard access to the various hardware resources
// they are controlled because multiple tasks may access them

// global meter object
//structMeter gMeter;

 
 
 /* An array to hold a count of the number of times each timer expires. */
long lExpireCounters[ NUM_TIMERS ] = { 0 };

void SendTimerExpiredMsg(SHORT timer_id)
{
	static GRAPHICS_MSG gMsg;	
	// any messages that we send will always be of this type
//	gMsg.cmd = MSG_UPDATE_DISPLAY;
	gMsg.cmd = MSG_TIMER_EXPIRED;
	gMsg.data.golMsg.param1 = timer_id;             //input event id  
	gMsg.data.golMsg.param2 = INP_NOEVENT;     //input event status;
 	xQueueSend(hQVGAQueue, &gMsg, portMAX_DELAY);
//	xQueueSend(hQVGAQueue, &gMsg, 0);
}

/*-----------------------------------------------------------*/

/* The queue used to send messages to the LCD task. */
static xQueueHandle xLCDQueue;

/* Define a callback function that will be used by multiple timer instances.  
 The callback function does nothing but count the number of times the 
 associated timer expires, and stop the timer once the timer has expired
 10 times. */
 void vTimerCallback( xTimerHandle pxTimer )
 {
 long lArrayIndex;
 const long xMaxExpiryCountBeforeStopping = 1;
 
     /* Optionally do something if the pxTimer parameter is NULL. */
     configASSERT( pxTimer );
     
     /* Which timer expired? */
     lArrayIndex = ( long ) pvTimerGetTimerID( pxTimer );
     
     /* Increment the number of times that pxTimer has expired. */
     lExpireCounters[ lArrayIndex ] += 1;

     /* If the timer has expired 10 times then stop it from running. */
     if( lExpireCounters[ lArrayIndex ] == xMaxExpiryCountBeforeStopping )
     {
         lExpireCounters[ lArrayIndex ]=0;
		 /* Do not use a block time if calling a timer API function from a
         timer callback function, as doing so could cause a deadlock! */
         xTimerStop( pxTimer, 0 );
				 SendTimerExpiredMsg(INP_TIMER0_ID - lArrayIndex);
     }
 }





/*-----------------------------------------------------------*/

/*
 * Create the demo tasks then start the scheduler.
 */
void os_prepare( void )
{
	
	BeepInit();
	xTimers[ 0 ] = xTimerCreate(  (signed char*)"TMR0",        /* Just a text name, not used by the kernel. */
                                       ( 1000  ),    /* The timer period in ticks. */
                                       pdTRUE,         /* The timers will auto-reload themselves when they expire. */
                                       ( void * ) 0,   /* Assign each timer a unique id equal to its array index. */
                                       vTimerCallback  /* Each timer calls the same callback when it expires. */
                                     );
	xTimers[ 1 ] = xTimerCreate(  (signed char*)"TMR1",        /* Just a text name, not used by the kernel. */
                                       ( 100  ),    /* The timer period in ticks. */
                                       pdTRUE,         /* The timers will auto-reload themselves when they expire. */
                                       ( void * ) 1,   /* Assign each timer a unique id equal to its array index. */
                                       vTimerCallback  /* Each timer calls the same callback when it expires. */
                                     );
	
	
	// the QVGA Semaphore is normally controlled by the graphics
	// task however if calibration is required then it must take
	// control until the user has completed the calibration steps
	// we also use this on GFX2 boards to control access to the 
	// parallel FLASH device which is shared by graphics
	QVGAMutSemaphore = xSemaphoreCreateMutex();
	
	// semaphore to control access to the meter object
	vSemaphoreCreateBinary(CONTROLSemaphore);
	
	// messages to update the display are sent via the QVGAQueue
	hQVGAQueue = xQueueCreate(QVGA_QUEUE_SIZE, sizeof(GRAPHICS_MSG));
	
	// messages to update the display are sent via the QVGAQueue
	hSCREENQueue = xQueueCreate(SCREEN_QUEUE_SIZE, sizeof(SCREEN_MSG));
	
	
	// create the Background task
	xTaskCreate(taskBackground, (signed char*) "BGRND", STACK_SIZE_BACKGRND,
		NULL, tskIDLE_PRIORITY + 9, &hBACKGRNDTask);
	
	vSemaphoreCreateBinary(hSPISemaphore);
	vSemaphoreCreateBinary(hIOSemaphore);
	// create the SPI task
	xTaskCreate(taskSPI, (signed char*) "SPI", STACK_SIZE_SPI,
		NULL, tskIDLE_PRIORITY + 6, &hSPITask);
	
	
	// create the control task
	xTaskCreate(taskControl, (signed char*) "CTRL", STACK_SIZE_CONTROL,
		NULL, tskIDLE_PRIORITY + 5, &hCONTROLTask);
	hCONTROLQueue = xQueueCreate(CONTROL_QUEUE_SIZE, sizeof(CONTROL_MSG));

	// create the calc task
	xTaskCreate(taskCalc, (signed char*) "CALC", STACK_SIZE_CALC,
		NULL, tskIDLE_PRIORITY + 5, &hCALCTask);
//	hCONTROLQueue = xQueueCreate(CONTROL_QUEUE_SIZE, sizeof(CONTROL_MSG));
		   
	
	// touchscreen task
//	xTaskCreate(taskTouchScreen, (signed char*) "TOUCH", STACK_SIZE_TOUCHSCREEN, 
//		NULL, tskIDLE_PRIORITY + 4, &hTOUCHTask);

	// QVGA Graphics display task
	xTaskCreate(taskGraphics, (signed char*) "GRAPH", STACK_SIZE_GRAPHICS,
		NULL, tskIDLE_PRIORITY + 3, &hGRAPHICSTask);

	xTaskCreate(taskUSB, (signed char*) "USB", STACK_SIZE_USB, 
		NULL, tskIDLE_PRIORITY + 4, &hUSBTask);
	xTaskCreate(taskUART, (signed char*) "UART", STACK_SIZE_UART,
		NULL, tskIDLE_PRIORITY + 4, &hUARTTask);

		
//	vAltStartComTestTasks( tskIDLE_PRIORITY + 4, mainCOM_TEST_BAUD_RATE);
}
/*-----------------------------------------------------------*/


#if 0
/************************************************************************************
* Function: DA210DEVBOARD_SST39LF400SectorErase(DWORD address)
*
* Notes: Erase the sector specified by the address in the parallel flash.
*        The graphics module is locked out during this function but
*        since this function occurs fast enough and only called when 
*        calibrating the touch screen, it will not be noticeable.
*
*************************************************************************************/
void DA210DEVBOARD_SST39LF400SectorErase(DWORD address)
{
    // this function locks out the graphics module from accessing
    // external memory until the MSTSEL is reset back to Graphics

    // to minimize effects on the screen refresh 
    // wait until the VSYNC starts
    while(!_VMRGN); 

  	PMCON2bits.MSTSEL = 0;		// set CPU as Master
    SST39LF400SectorErase(address);
  	PMCON2bits.MSTSEL = 3;		// set Graphics as Master

}    

/************************************************************************************
* Function: DA210DEVBOARD_SST39LF400WriteWord(WORD data, DWORD address)
*
* Notes: Write a word to parallel flash with the given address.
*        The graphics module is locked out during this function but
*        since this function occurs fast enough and only called when 
*        calibrating the touch screen, it will not be noticeable.
*
*************************************************************************************/
void DA210DEVBOARD_SST39LF400WriteWord(WORD data, DWORD address)
{
    // this function locks out the graphics module from accessing
    // external memory until the MSTSEL is reset back to Graphics

    // to minimize effects on the screen refresh 
    // wait until the VSYNC starts
    while(!_VMRGN); 

  	PMCON2bits.MSTSEL = 0;		// set CPU as Master
    SST39LF400WriteWord(data, address);
  	PMCON2bits.MSTSEL = 3;		// set Graphics as Master
    
}
#endif

WORD DA210DEVBOARD_SST39LF400CheckID()
{
    WORD temp;
	// this function locks out the graphics module from accessing
    // external memory until the MSTSEL is reset back to Graphics

    // to minimize effects on the screen refresh 
    // wait until the VSYNC starts
    while(!_VMRGN); 

  	PMCON2bits.MSTSEL = 0;		// set CPU as Master
	temp = SST39LF400CheckID();
  	PMCON2bits.MSTSEL = 3;		// set Graphics as Master
    return temp;
}

BYTE DA210DEVBOARD_SST39LF400WriteArray(DWORD address, BYTE *pData, WORD nCount)
{
    BYTE temp;
    // this function locks out the graphics module from accessing
    // external memory until the MSTSEL is reset back to Graphics

    // to minimize effects on the screen refresh 
    // wait until the VSYNC starts
    while(!_VMRGN); 

  	PMCON2bits.MSTSEL = 0;		// set CPU as Master
	temp = SST39LF400WriteArray(address, pData, nCount);
  	PMCON2bits.MSTSEL = 3;		// set Graphics as Master
    return temp;
    
}

void DA210DEVBOARD_SST39LF400ReadArray(DWORD address, BYTE *pData, WORD nCount)
{
    // this function locks out the graphics module from accessing
    // external memory until the MSTSEL is reset back to Graphics

    // to minimize effects on the screen refresh 
    // wait until the VSYNC starts
    while(!_VMRGN); 

  	PMCON2bits.MSTSEL = 0;		// set CPU as Master
	SST39LF400ReadArray(address, pData, nCount);
  	PMCON2bits.MSTSEL = 3;		// set Graphics as Master
    
}

void DA210DEVBOARD_SST39LF400ChipErase(void)
{
    // this function locks out the graphics module from accessing
    // external memory until the MSTSEL is reset back to Graphics

    // to minimize effects on the screen refresh 
    // wait until the VSYNC starts
    while(!_VMRGN); 

  	PMCON2bits.MSTSEL = 0;		// set CPU as Master
	SST39LF400ChipErase();
  	PMCON2bits.MSTSEL = 3;		// set Graphics as Master
    
}



/*********************************************************************
 * Function:        void vApplicationTickHook(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called at each tick interval
 *
 * Note:            
 ********************************************************************/
void vApplicationTickHook(void)
{
	static unsigned int tickCount = 0, tickCount1 = 0;
	static CONTROL_MSG mMsg;
	static GRAPHICS_MSG gMsg;
	portBASE_TYPE xTaskWoken;
	
#if 0	
	tickCount2++;
	if (tickCount2 >= (configTICK_RATE_HZ/25)) {
		tickCount2 = 0;
		xSemaphoreGiveFromISR(hSPISemaphore, &xTaskWoken);	
	}
#endif	
	tickCount1++;
	if (tickCount1 >= (configTICK_RATE_HZ/8)) {
		tickCount1 = 0;
		gMsg.cmd = MSG_UPDATE_CURSOR;
 		xQueueSendToBackFromISR(hQVGAQueue, &gMsg, &xTaskWoken);
	}
	
	
#if 0		
	// update to the graphics task every 0.5 seconds
	tickCount++;
//	if (tickCount >= (2 * configTICK_RATE_HZ)) {
	if (tickCount >= (configTICK_RATE_HZ/2)) {
		tickCount = 0;
		
		// update the meters temperature reading
		mMsg.cmd = MSG_CONTROL_UPDATE_TEMPERATURE;
		mMsg.data.wVal[0] = adcTemp;
		xQueueSendToBackFromISR(hCONTROLQueue, &mMsg, &xTaskWoken);
		// also use this as an opportunity to update the display
		// with periodic data updates if required
		gMsg.cmd = MSG_UPDATE_DISPLAY;
		xQueueSendToBackFromISR(hQVGAQueue, &gMsg, &xTaskWoken);
	}	
#endif		
	
}


#if 0
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	static unsigned int tickCount = 0;
	static CONTROL_MSG mMsg;
	static GRAPHICS_MSG gMsg;
	portBASE_TYPE xTaskWoken;
#if 0		
	
	// send a temperature update to the graphics task every 2 seconds
	tickCount++;
	if (tickCount >= (2 * configTICK_RATE_HZ)) {
		tickCount = 0;
		
		// update the meters temperature reading
		mMsg.cmd = MSG_CONTROL_UPDATE_TEMPERATURE;
		mMsg.data.wVal[0] = adcTemp;
		xQueueSendToBackFromISR(hCONTROLQueue, &mMsg, &xTaskWoken);
		// also use this as an opportunity to update the display
		// with periodic data updates if required
		gMsg.cmd = MSG_UPDATE_DISPLAY;
		xQueueSendToBackFromISR(hQVGAQueue, &gMsg, &xTaskWoken);
	}	
#endif		
	
}
#endif
unsigned char int1stat;
unsigned char int2stat;
/*-----------------------------------------------------------*/

void EnterCriticalSPI( void )
{
//	portENTER_CRITICAL();
//  	int1stat = IEC1bits.INT1IE;
//  	int2stat = IEC0bits.T1IE;
//	IEC1bits.INT1IE = 0; //disable touch interrupt
//	IEC0bits.T1IE = 0; //disable clock interruipt
//	portEXIT_CRITICAL();
}
void ExitCriticalSPI( void )
{
//	portENTER_CRITICAL();
//	IEC1bits.INT1IE = int1stat; //enable touch interrupt
//  	IEC0bits.T1IE = int2stat; //enable clock interruipt
//	portEXIT_CRITICAL();
}

