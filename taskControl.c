/*****************************************************************************
 *****************************************************************************/
#define TASK_CONTROL_PUB

#include "include.h"

#include "framework/gfx/gfx.h"
#include "taskGraphics.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
//#include "taskUART.h"
#include "taskControl.h"


//#define SAMPLE_PERIOD 1000		// us
//#define TIME_BASE (((GetPeripheralClock() / 1000) * SAMPLE_PERIOD) / 8000)

unsigned char chan_idx;

//unsigned int Buffer[4*16];
unsigned int Buffer[1];

/***************************************************************
 *    Fsam for Air - 2ms (ADC sample rate 1 ms)
 *		Fsam for rest of channels 8ms(fourfold from FsamAir - x4) 
 ***************************************************************/

void ProcessADCSamples(unsigned int *buf)
{
unsigned char i,j;
static unsigned char buf_idx,abuf_idx;
unsigned int sum;
	
	if (!AD1CON1bits.DONE)
		return;	
	if(chan_idx & 0x01)
	{
		adc_inp[AIR_VAL] = ADC1BUF0;
		adc_inp_buf[AIR_VAL][abuf_idx]= adc_inp[AIR_VAL];
		if (abuf_idx < 63 )        
			abuf_idx++; 
		else
			abuf_idx = 0;
	}
	else
	{
		adc_inp[chan_idx >> 1] = ADC1BUF0;
 		adc_inp_sum[chan_idx >> 1] -= adc_inp_buf[chan_idx >> 1][buf_idx];
		adc_inp_buf[chan_idx >> 1][buf_idx] = adc_inp[chan_idx >> 1];
		adc_inp_sum[chan_idx >> 1] += adc_inp_buf[chan_idx >> 1][buf_idx];
		adc_inp_filtered[chan_idx >> 1] = adc_inp_sum[chan_idx >> 1]>>6; /*divide by 64*/
	}
	
	if (chan_idx < (ACHAN_NUM-1)*2-1 ) 
		chan_idx++; 
	else
	{
		chan_idx = 0;
		if (buf_idx < 63 )        
			buf_idx++; 
		else
			buf_idx = 0;
	}

	AD1CHS = chan_order[chan_idx];
	AD1CON1bits.SAMP = 1;


#if 0
	
	if (buf_idx < 63 ) 
		buf_idx++; 
	else
		buf_idx = 0;
	
	for(i=0; i<ACHAN_NUM; i++)
	{
		sum = 0;
		for(j=0; j<16; j++)
			sum += buf[i + j*ACHAN_NUM];
		adc_inp[i] = sum/16;
		
 		adc_inp_sum[i] -= adc_inp_buf[i][buf_idx];
		adc_inp_buf[i][buf_idx] = adc_inp[i];
		adc_inp_sum[i] += adc_inp_buf[i][buf_idx];
		adc_inp_filtered[i] = adc_inp_sum[i]/64;
	}
#endif
}

#if 0
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
	portBASE_TYPE taskWoken = pdFALSE;

		ProcessADCSamples(Buffer);

	// this macro will allow a higher priority task than the one originally
	// interrupted to be woken after servicing the interrupt
	// clear the interrupt flag
	IFS1bits.T4IF = 0;
//	portEND_SWITCHING_ISR(taskWoken);		

}
#endif


/*********************************************************************
 * Function:        void taskControl(void* pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           void* pvParameter, any parameter from the creator
 *                  
 * Output:          Does not return
 *
 * Side Effects:    None
 *
 * Overview:        Calc handling task
 *
 * Note:            
 ********************************************************************/
void taskControl(void* pvParameter)
{
	static CONTROL_MSG msg;
	static GRAPHICS_MSG gMsg;

//	vTaskSetApplicationTaskTag( NULL, ( void * ) 'c' );	
	 
#if 1	
	chan_idx = 0;
	TRISAbits.TRISA7 = 1; //Set as inpit
	ANSAbits.ANSA7 = 1; //AN22 PR2_PIN
	//ANSBbits.ANSB5 = 1; //AN5 Air_PIN
	TRISCbits.TRISC4 = 1; //Set as inpit
	ANSCbits.ANSC4 = 1; //AN16 Air_PIN
	TRISEbits.TRISE9 = 1; //Set as inpit
	ANSEbits.ANSE9 = 1; //AN21 PR1_PIN
	TRISGbits.TRISG9 = 1; //Set as inpit
	ANSGbits.ANSG8 = 1; //AN19 bat_PIN
	// configure the ADC
	//AD1CON1 = 0x80E0; 
	AD1CON1 = 0x80E0; 
	AD1CON2 = 0x0000;
	AD1CON3 = 0x1F80;
	AD1CHS = chan_order[chan_idx];
	AD1CSSL = 0;
	AD1CON1bits.SAMP = 1;
	
//	ADPCFG_XPOS = 0;
//	ADPCFG_YPOS = 0;
#endif
	
#if 0	
	// we initialize TMR4 here to control the sampling of the ADC
	// channels. 
	TMR4 = 0;
	PR4 = TIME_BASE - 1;
	T4CONbits.TCKPS = 1;	// prescale 1:8    //2Mhz
	IFS1bits.T4IF = 0;
	IEC1bits.T4IE = 1;
	IPC6bits.T4IP = 4;
	T4CONbits.TON = 1;
#endif	
	
	
#if 0	
	// initialise the meter object
	xSemaphoreTake(CONTROLSemaphore, portMAX_DELAY);
	gMeter.setpoint = 190;		// 19.0 celsius
	gMeter.electric_cost = 12;	// 12 cents per unit
	gMeter.electric_units = 0;
	gMeter.electric_total = 0;
	gMeter.electric_on = 1;
	gMeter.gas_cost = 37;		// 37 cents per unit
	gMeter.gas_units = 0;
	gMeter.gas_total = 0;
	gMeter.gas_on = 1;
	gMeter.temperature = 0;	
	xSemaphoreGive(CONTROLSemaphore);
#endif
	 
	while (1) {
		
		// wait for an incoming message 
//		if(!xQueueReceive(hCONTROLQueue, &msg, 200/portTICK_RATE_MS))
//				continue;  //50ms timeout
		xQueueReceive(hCONTROLQueue, &msg, portMAX_DELAY);

		// take control of the meter information structure
		xSemaphoreTake(CONTROLSemaphore, portMAX_DELAY);
//		LATGbits.LATG2 = 1;
		switch(msg.cmd) {
#if 0			
			case MSG_CONTROL_UPDATE_TEMPERATURE:
				// update the meter
				gMeter.temperature = msg.data.wVal[0];
				// send an update to the QVGA display
				gMsg.cmd = MSG_UPDATE_TEMPERATURE;
				gMsg.data.wVal[0] = gMeter.temperature;
				xQueueSend(hQVGAQueue, &gMsg, 0);
				break;
		
			case MSG_CONTROL_UPDATE_ELECTRIC:
				// update the meter only if it is enabled
				if (gMeter.electric_on == 1) {
					gMeter.electric_units++;
					gMeter.electric_total += gMeter.electric_cost; 
				
					// send update to the QVGA display (Note preformatting)
					gMsg.cmd = MSG_UPDATE_ELECTRIC_UNITS;
					gMsg.data.dVal[0] = gMeter.electric_units;
					xQueueSend(hQVGAQueue, &gMsg, 0);
					gMsg.cmd = MSG_UPDATE_ELECTRIC_TOTAL;
					gMsg.data.wVal[0] = gMeter.electric_total % 100;
					gMsg.data.wVal[1] = gMeter.electric_total / 100;
					xQueueSend(hQVGAQueue, &gMsg, 0);				
				}
				break;
			
			case MSG_CONTROL_UPDATE_GAS:
				// update the meter only if it is enabled
				if (gMeter.gas_on == 1) {
					gMeter.gas_units++;
					gMeter.gas_total += gMeter.gas_cost;
					
					// send update to the display
					gMsg.cmd = MSG_UPDATE_GAS_UNITS;
					gMsg.data.dVal[0] = gMeter.gas_units;
					xQueueSend(hQVGAQueue, &gMsg, 0);
					gMsg.cmd = MSG_UPDATE_GAS_TOTAL;
					gMsg.data.wVal[0] = gMeter.gas_total % 100;
					gMsg.data.wVal[1] = gMeter.gas_total / 100;
					xQueueSend(hQVGAQueue, &gMsg, 0);			
				}
				break;
				
			case MSG_CONTROL_UPDATE_ELECTRIC_COST:
				// update the unit cost
				gMeter.electric_cost = msg.data.wVal[0];
				break;
				
			case MSG_CONTROL_START_INFUS:
				// update the unit cost
				gMeter.gas_cost = msg.data.wVal[0];
				break;
#endif				
			case MSG_CONTROL_START_INFUS:
				/*Calculate rate and run*/
				if (screenState != DISPLAY_SCREEN_BOLUS)
				{
					if(vol_para.rate>200.0)
						occlusion_limit = 2;
					else
						occlusion_limit = vol_para.occlusion_lmt;
					new_calc_rate(vol_para.rate);
				}
				//	beep(500,1);
				Beep(500);
				steps_cntr = 0;
				start_air_det();
				clearBit(kvo_stat, KVO_STAT);
				stmotor_cmd(STMTR_DIR_LEFT,STMTR_RUN);
				break;
			case MSG_CONTROL_STOP_INFUS:
//				new_calc_rate(vol_para.rate);
				//	beep(500,1);
				Beep(500);
					/*stop*/
				stop_air_det();
				stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_STOP);
				break;
#if 0			
			case MSG_CONTROL_SHDWN:
				/*Prepare device to shutdown*/
				Beep(2000);
					/*stop*/
				stop_air_det();
				stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_STOP);
				/*Turn of Back light*/
				/*Set Onn/Off interrupt and go to sleep*/
				while(1);
				break;
#endif			
			case MSG_INPUT_EVENT:
				
				break;
			default:
//				UARTprintf("METER: Unhandled message!\r\n");
				break;	
		}	
		// release the data
		xSemaphoreGive(CONTROLSemaphore);	
//		LATGbits.LATG2 = 0;
	
	}	  
}


