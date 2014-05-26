/*****************************************************************************
 *****************************************************************************/

#ifndef __TASK_CONTROL_H
#define __TASK_CONTROL_H

#ifdef TASK_CONTROL_PUB
#define TASK_CONTROLPUB
#else
#define TASK_CONTROLPUB extern
#endif

#define ACHAN_NUM 4

#define BAT_PIN	19//AN19 bat
#define PR1_PIN	21//AN21 PR1
#define PR2_PIN	22//AN22 PR2
//#define AIR_PIN	5//AN5 Air
#define AIR_PIN	16//AN16 Air

#define BATT_VAL			0
#define PRESS1_VAL		1
#define PRESS2_VAL		2
#define AIR_VAL				3

TASK_CONTROLPUB volatile unsigned int adc_inp[ACHAN_NUM];
TASK_CONTROLPUB volatile unsigned int adc_inp_filtered[ACHAN_NUM];
TASK_CONTROLPUB volatile unsigned int adc_inp_sum[ACHAN_NUM];
TASK_CONTROLPUB volatile unsigned int adc_inp_buf[ACHAN_NUM][64];




#ifdef TASK_CONTROL_PUB
//unsigned int chan_order[4] = {ADC_CH0_POS_SAMPLEA_AN2 ,ADC_CH0_POS_SAMPLEA_AN3, ADC_CH0_POS_SAMPLEA_AN1 ,ADC_CH0_POS_SAMPLEA_AN4};
unsigned char chan_order[(ACHAN_NUM-1)*2] = {BAT_PIN, AIR_PIN, PR1_PIN, AIR_PIN, PR2_PIN, AIR_PIN};
#else
extern unsigned char chan_order[];
#endif

#if 0
//#define press1_raw		adc_inp[PRESS1_VAL]
//#define press2_raw		adc_inp[PRESS2_VAL]
//#define air_raw				adc_inp[AIR_VAL]
//#define batt_raw			adc_inp[BATT_VAL]

#else
#define press1_raw		adc_inp_filtered[PRESS1_VAL]
#define press2_raw		adc_inp_filtered[PRESS2_VAL]
#define air_raw				adc_inp[AIR_VAL]
#define batt_raw			adc_inp_filtered[BATT_VAL]
#endif

#if 0
// definition of the home meter object used to store information
// about the gas and electricity in this application
typedef struct {
	DWORD	electric_units;		// electricity units used
	DWORD	electric_total;		// electricity total cost
	DWORD	electric_cost;		// electricty cost per unit ($0.01)
	DWORD	gas_units;			// gas units used
	DWORD	gas_total;			// gas total cost
	DWORD	gas_cost;			// gas cost per unit		($0.01)
	WORD	electric_on;		// electricity supply enabled
	WORD	gas_on;				// gas supply enabled
	WORD	setpoint;			// thermometer setpoint
	WORD	temperature;		// current temperature (0.1C)
} structMeter;

// the one global meter object
extern structMeter gMeter;
#endif







// structure used to pass updates to the meter task
// other task send messages of this type on a queue
typedef struct {
	WORD	cmd;
	union {
		BYTE		bVal[4];
		WORD		wVal[2];
		DWORD		dVal;
	} data;
} CONTROL_MSG;

#define CONTROL_QUEUE_SIZE	4

// types of meter messages
#define MSG_CONTROL_UPDATE_TEMPERATURE		1	// new temperature reading
#define MSG_CONTROL_UPDATE_SETPOINT			2	// new setpoint value
#define MSG_CONTROL_UPDATE_ELECTRIC			3	// electric used update
#define MSG_CONTROL_UPDATE_GAS				4	// gas used update
#define MSG_CONTROL_UPDATE_ELECTRIC_STATE		5	// electric state change
#define MSG_CONTROL_UPDATE_GAS_STATE			6	// gas state change
#define MSG_CONTROL_UPDATE_ELECTRIC_COST	7	// cost per unit
#define MSG_CONTROL_START_INFUS						8	// Start infusion
#define MSG_CONTROL_STOP_INFUS						9	// Stop infusion
#define MSG_CONTROL_SHDWN									10 //Shutdown


#define INP_NOEVENT        	0 /* No event */
#define INP_RELEASE        	1 /* Release event */
#define INP_SET        			2 /* Set event */

#define INP_STOP_ID     	20  /* STOP key event ID */
#define INP_ONOFF_ID   		19  /* ONOFF key event ID */
#define INP_TIMER0_ID  		18  /* Timer0 event ID */
#define INP_TIMER1_ID  		17  /* Timer1 event ID */
#define INP_TIMER2_ID  		16  /* Timer2 event ID */
#define INP_NOBAT_ID			15  /* no battery event ID */
#define INP_BATEMPTY_ID		14 /* battery empty event ID */
#define INP_NOSET_ID			13 /* No Set event ID*/
#define INP_DOOR_ID   		12  /* Door sensor event ID */
#define INP_ZERORATE_ID		11 /* Rate is 0 event ID*/
#define INP_AIR_ID	   		10  /* Air sensor event ID */
#define INP_ACCAIR_ID	   	9  /* Air sensor event ID */
#define INP_DOWNOCC_ID 		8  /* down occlusion event ID */
#define INP_UPOCC_ID   		7  /* up occlusion event ID */
#define INP_PARAOCC_ID   	6  /* para occlusion event ID */
#define INP_MOTOR_ID   		5  /* motor sensor event ID */
#define INP_ONHOLD_ID	   	4  /* ON HOLD more then 2 min ID */

#define INP_KVO_ID		   	3  /* KVO event ID */
#define INP_BATLOW_ID  		2  /* battery low event ID */
#define INP_NOAC_ID				1 /* No AC event ID*/
#define INP_NOEVNT_ID			0 /* No AC event ID*/

// size of the stack for this task
#define STACK_SIZE_CONTROL		(configMINIMAL_STACK_SIZE * 2)
// handle for the task
TASK_CONTROLPUB xTaskHandle hCONTROLTask;
// queue to send incoming meter update messages
TASK_CONTROLPUB xQueueHandle hCONTROLQueue;
// semaphore to guard access to the meter object
TASK_CONTROLPUB xSemaphoreHandle CONTROLSemaphore;
// the calc task
TASK_CONTROLPUB void taskControl(void* pvParameter);
TASK_CONTROLPUB void init_adc(void);
TASK_CONTROLPUB void ProcessADCSamples(unsigned int *buf);
#endif // __TASK_CALC_H
