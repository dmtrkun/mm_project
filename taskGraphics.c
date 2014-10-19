/*****************************************************************************
 * FileName:        taskGraphics.c
 * Dependencies:    
 * Processor:       PIC24
 * Compiler:       	MPLAB C30 V3.30
 * Linker:          MPLAB LINK30
 *
 * Version  Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 1.0      DMK               03/24/12    Initial version   
 *****************************************************************************/
#define TASK_GRAPHICS_PUB
#include "include.h"

#include "taskTouchScreen.h"
#include "string.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////
// Flash images used by the application
//extern const FONT_FLASH GOLFontDefault;
//extern const FONT_FLASH GOLMediumFont;
//extern const FONT_FLASH GOLSmallFont;

extern BYTE update;
extern BYTE updateGPL;

// task handle
xTaskHandle hGRAPHICSTask;

///////////////////////////////////////////////////////////////////
// defines for the window and menu items
#define ID_WINDOW1					10
#define ID_WINDOW2					11
#define ID_WINDOW3					12
#define ID_WINDOW4					13
#define ID_BUTTON_GAS				20
#define ID_BUTTON_ELECTRIC			21
#define ID_BUTTON_TEMPERATURE		22
#define ID_ELECTRIC_TOTAL_COST		23
#define ID_GAS_TOTAL_COST			24
#define ID_PICTURE_WEATHER			25
#define ID_SETPOINT_DIAL			26
#define ID_SETPOINT_TEMPERATURE		27
#define ID_BUTTON_GAS_OFF			28
#define ID_BUTTON_GAS_ON			29
#define ID_GAS_SCREEN_TOTAL			30
#define ID_GAS_SCREEN_COST			31
#define ID_BUTTON_ELECTRIC_OFF		32
#define ID_BUTTON_ELECTRIC_ON		33
#define ID_ELECTRIC_SCREEN_TOTAL	34
#define ID_ELECTRIC_SCREEN_COST		35
#define ID_LABEL_COST				36
#define ID_LABEL_UNITS				37
#define ID_PICT_GAS					50
#define ID_PICT_ELECTRIC			51

///////////////////////////////////////////////////////////////////
// Colors
#define RED4					GFX_RGBConvert(139,   0,   0)
#define FIREBRICK1		GFX_RGBConvert(255,  48,  48)
#define DARKGREEN			GFX_RGBConvert(  0, 100,   0)
#define PALEGREEN			GFX_RGBConvert(152, 251, 152)

///////////////////////////////////////////////////////////////////
// local functions within this module
WORD ScreenUpdate(void);
WORD GOLMsgCallback(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg);
static CONTROL_MSG cMsg;
WORD GOLDrawCallback(void);

///////////////////////////////////////////////////////////////////
// The graphics display uses several strings to display data
// to save RAM we re-use the strings between the various screens
//static char qvgaBuff1[20];
//static char qvgaBuff2[20];
//static char qvgaBuff3[20];
//static char qvgaBuff4[20];

///////////////////////////////////////////////////////////////////
// All display update messages are sent to the graphics task
// using this queue. Messages include touch screen updates
// as well as updates to the displayed parameters
xQueueHandle hQVGAQueue;

// x position store when displaying graphs and last value
//WORD usage_xpos;
//WORD usage_last_value;

/*********************************************************************
 * Function:        void taskGraphics(void* pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           Pointer to optional parameter
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Graphics display task
 *
 * Note:            
 ********************************************************************/
 int pressx, pressy;
 
void taskGraphics(void* pvParameter)
{
	static GRAPHICS_MSG msg;
	GFX_GOL_MESSAGE* pMsg;
	GFX_GOL_OBJ_HEADER* pObj;
//	vTaskSetApplicationTaskTag( NULL, ( void * ) 'g' );	
	
    GFX_GOL_DrawCallbackSet(GOLDrawCallback);
    GFX_GOL_MessageCallbackSet(GOLMsgCallback);
	
	GDDSetScreen(CREATE_SCREEN_INTRO,0,NULL);
	// notify task started
//	UARTprintf("GRAPH: Task Started.\r\n");
	
	// this semaphore will initially be taken by the touchscreen task
	// in case it needs to perform calibration we use to pause
	// this task until the touchscreen has finished startup
	xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);

#ifndef SIM_DEBUG
	/*TODO*/	 
//	CheckExternalFlashHex();
#endif	
	// create the color and style schemes used by the various screens
	// and perform GOL startup
	CreateSchemes();
	xSemaphoreGive(QVGAMutSemaphore);

	// graphics task main loop
	while (1) {
		// gain access to the QVGA display and PMP
		xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
		// when drawing is complete GOLDraw will return TRUE
		while (GFX_GOL_ObjectListDraw() != TRUE);
		xSemaphoreGive(QVGAMutSemaphore);
		
		
		// block until we receive a new message from the graphics
		// queue. This message could be from the touchscreen or any
		// other task that may cause an update
		if (xQueueReceive(hQVGAQueue, &msg, portMAX_DELAY) == pdTRUE) {
			// perform message specific processing
			switch (msg.cmd) {
				case MSG_TIMER_EXPIRED:
					pMsg = &msg.data.golMsg;
					GOLMsgCallback(pMsg->param2, NULL, pMsg);
					
					break;
				case MSG_ERROR:
//DMK					GDDSetScreen(CREATE_SCREEN_ALARM,msg.data.wVal[0],NULL);
					break;
				case MSG_UPDATE_DISPLAY:
					// force a redraw of the screen, this allows for
					// periodic updates of the screen
#if 0					
					if (screenState == DISPLAY_SCREEN_RTOS) {
						xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
						UpdateRTOSScreen();
						xSemaphoreGive(QVGAMutSemaphore);
					} else if ((screenState == DISPLAY_SCREEN_ELECTRICITY) ||
							 (screenState == DISPLAY_SCREEN_GAS)) {
						xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
						UpdateUsageGraph();
						xSemaphoreGive(QVGAMutSemaphore);
					} else
#endif						
						xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
						ScreenUpdate();
						xSemaphoreGive(QVGAMutSemaphore);
//						GOLDrawCallback();
					break;
				case MSG_UPDATE_CURSOR:
					// force a redraw of the screen, this allows for
					// periodic updates of the screen
					if(screenState == DISPLAY_SCREEN_INTRO)
					{
						xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
						UpdateIntro();
						xSemaphoreGive(QVGAMutSemaphore);
					}
//TBD					else if(screenState == DISPLAY_SCREEN_BOLUS)
//					{
//						xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
//						UpdateBolus();
//						xSemaphoreGive(QVGAMutSemaphore);
//					}
//					else if(screenState == DISPLAY_SCREEN_RUN)
//					{
//						xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
//						UpdateRun();
//						xSemaphoreGive(QVGAMutSemaphore);
//					}
//					else if(screenState == DISPLAY_SCREEN_ALARM)
//					{
//						xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
//						UpdateAlarm();
//						xSemaphoreGive(QVGAMutSemaphore);
//					}

					break;
				case MSG_UPDATE_OFF:
				case MSG_UPDATE_STOP:
					break;

#if 0				 
				case MSG_UPDATE_TEMPERATURE:
					// update the real temperature display
					pObj = GFX_GOL_ObjectFind(ID_BUTTON_TEMPERATURE);
					if (pObj) {
						sprintf(qvgaBuff1, "%d.%01dC", msg.data.wVal[0] / 10,
							msg.data.wVal[0] % 10);
						GFX_GOL_ObjectStateSet((BUTTON*) pObj, DRAW_UPDATE);
					}
					break;
				case MSG_UPDATE_ELECTRIC_TOTAL:
					// update electricity total cost
					pObj = GFX_GOL_ObjectFind(ID_ELECTRIC_TOTAL_COST);
					if (pObj) {
						sprintf(qvgaBuff2, "$%d.%02d",
							msg.data.wVal[1], msg.data.wVal[0]);
						GFX_GOL_ObjectStateSet((BUTTON*) pObj, DRAW_UPDATE);
					}
					break;
				case MSG_UPDATE_ELECTRIC_UNITS:
					// update electricity total units used
					pObj = GFX_GOL_ObjectFind(ID_ELECTRIC_SCREEN_TOTAL);
					if (pObj) {
						sprintf(qvgaBuff1, "%ld", msg.data.dVal[0]);
						GFX_GOL_ObjectStateSet((BUTTON*) pObj, DRAW_UPDATE);							
					}
					break;
				case MSG_UPDATE_GAS_TOTAL:
					// update gas total cost
					pObj = GFX_GOL_ObjectFind(ID_GAS_TOTAL_COST);
					if (pObj) {
						sprintf(qvgaBuff3, "$%d.%02d",
							msg.data.wVal[1], msg.data.wVal[0]);
						GFX_GOL_ObjectStateSet((BUTTON*) pObj, DRAW_UPDATE);
					}
					break;
				case MSG_UPDATE_GAS_UNITS:
					// update gas total units used
					pObj = GFX_GOL_ObjectFind(ID_GAS_SCREEN_TOTAL);
					if (pObj) {
						sprintf(qvgaBuff1, "%ld", msg.data.dVal[0]);
						GFX_GOL_ObjectStateSet((BUTTON*) pObj, DRAW_UPDATE);							
					}
					break;
#endif				
				case MSG_TOUCH_EVENT:
					// process events from the touchscreen
					pMsg = &msg.data.golMsg;
					pressx = pMsg->param1;
					pressy = pMsg->param2;
					GFX_GOL_ObjectMessage(pMsg);
					break;
				case MSG_INPUT_EVENT:
					// process events from the calc task
					pMsg = &msg.data.golMsg;
//					pressx = pMsg->param1;
					/*pMsg->param2 - BTN_MSG_PRESSED */
					GOLMsgCallback(pMsg->param2, NULL, pMsg);
					break;
				
				default:
					break;
			}
		}	
	}
}


/*********************************************************************
 * Function:        WORD GOLMsgCallback(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, 
 *										GFX_GOL_MESSAGE* pMsg);
 *
 * PreCondition:    None
 *
 * Input:           objMsg full message, 
 *					pObj pointer to header,
 *					pMsg the message
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Process a screen specific message or call
 *					the default handler
 *
 * Note:            
 ********************************************************************/
WORD msg_redalarm(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
#if 0
        if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_ONHOLD_ID:			 
				if(pMsg->param2 == INP_SET)
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
						xTimerStop( xTimers[ 1 ], 0 );
//TBD					GDDSetScreen(CREATE_SCREEN_ALARM,HOLD_ALRM_SCR,NULL);
				}	
				break;
			case INP_DOOR_ID:			
				if(pMsg->param2 == INP_SET)
				{
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if(page_display != DOOR_ALRM_SCR)
					{					
						if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     				xTimerStop( xTimers[ 1 ], 0 );
						if( xTimerIsTimerActive( xTimers[ 0 ] ) != pdFALSE ) 
	   	     				xTimerStop( xTimers[ 0 ], 0 );
//TBD						GDDSetScreen(CREATE_SCREEN_ALARM,DOOR_ALRM_SCR,NULL);
					}
				}	
				//Stop infusion and alarm				
				break;
			case INP_AIR_ID:			 
				if(pMsg->param2 == INP_SET)
				{
//TBD					if(screenState == DISPLAY_SCREEN_PRIME)
//					{
//						air_alarm = FALSE;
//						clearBit( alarm_st, AIR_ALRM);
//			        	break;
//					}
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
						xTimerStop( xTimers[ 1 ], 0 );
//TBD					GDDSetScreen(CREATE_SCREEN_ALARM,AIR_ALRM_SCR,NULL);
				}	
				//Stop infusion and alarm				
				break;
			case INP_MOTOR_ID:			
				if(pMsg->param2 == INP_SET)
				{
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	         			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,MOTOR_ALRM_SCR,NULL);
				}	
				//Stop infusion and alarm				
				break;
			case INP_BATEMPTY_ID:			 
				if(pMsg->param2 == INP_SET)
				{                                        
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	         			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,BATEMPTY_ALRM_SCR,NULL);
				}	
				break;
			case INP_UPOCC_ID:			 
				if(pMsg->param2 == INP_SET)
				{                                        
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	         			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,UPOCC_ALRM_SCR,NULL);
				}	
				break;
			case INP_DOWNOCC_ID:			 
				if(pMsg->param2 == INP_SET)
				{                                        
					//Stop infusion				 
//					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
//					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	         			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,DOWNOCC_ALRM_SCR,NULL);
				}	
				break;
			case INP_PARAOCC_ID:			
				if(pMsg->param2 == INP_SET)
				{                                        
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	         			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,PARAOCC_ALRM_SCR,NULL);
				}	
				break;
			case INP_NOSET_ID:			
				if(pMsg->param2 == INP_SET)
				{                                        
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	         			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,NOSET_ALRM_SCR,NULL);
				}	
				break;
			default:
				return 0;	
		}
		
		return 1;	
	}
#endif
        return 0;
}

WORD msg_yellowalarm(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
#if 0
    if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_BATLOW_ID:			 
				if(pMsg->param2 == INP_SET)
				{                                        
					if(screenState == DISPLAY_SCREEN_ALARM)
					{
//				 		if(testBit( alarm_st, BATLOW_ALRM))
						clearBit( alarm_st, BATLOW_ALRM);
						break;
					}					          
					//Stop infusion				 
//					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
//					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	         			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,BATLOW_ALRM_SCR,NULL);
				}	
				break;
			case INP_NOAC_ID:			 
				if(pMsg->param2 == INP_SET)
				{                                        
					if(screenState == DISPLAY_SCREEN_ALARM || screenState == DISPLAY_SCREEN_PRIME || screenState == DISPLAY_SCREEN_RATECALIB || screenState == DISPLAY_SCREEN_CALIB)
					{
				 		clearBit( alarm_st, NOAC_ALRM);
						break;
					}					          
					//Stop infusion				 
//					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
//					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	         			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,ACFAIL_ALRM_SCR,NULL);
				}	
				break;
			
			default:
				return 0;	
		}
		
		return 1;	
	}
#endif
    return 0;
}



WORD GOLMsgCallback(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
	
	if(pObj != NULL)
	{
		// beep if button is pressed
		if(objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
		{
			Beep(20);
			clear_hold_tmr();
		}
		// beep if radio button is checked
		if(objMsg == GFX_GOL_RADIOBUTTON_ACTION_CHECKED)
		{
			Beep(20);
			clear_hold_tmr();
		}
	}
	else
	{
		// beep if button is pressed
		if(objMsg == INP_SET)
		{
			if(pMsg->param1 != INP_NOAC_ID)
				Beep(20);
			clear_hold_tmr();
			if(pMsg->param1 == INP_ONOFF_ID || pMsg->param1 == INP_NOBAT_ID){
//TBD				GDDSetScreen(CREATE_SCREEN_PWRDOWN,pMsg->param1,NULL);
				return 1;
			}
		}
	
	}
//TBD	if(screenState != DISPLAY_SCREEN_CHECKUP)
//	{
//		if(msg_redalarm(objMsg, pObj, pMsg) == 1)
//			return 1;
//	}

//	if(screenState != DISPLAY_SCREEN_ALARM)
//	{
//		if(msg_yellowalarm(objMsg, pObj, pMsg) == 1)
//			return 1;
//	}
	if(msg_yellowalarm(objMsg, pObj, pMsg) == 1)
		return 1;
	// process messages for the demo screens
	switch (screenState) {
		case DISPLAY_SCREEN_INTRO:
			return msgIntro(objMsg, pObj, pMsg);
		case DISPLAY_SCREEN_CLEAR:
			return msgClear(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_CONFIRM:
//			return msgConfirm(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_RUN:
//			return msgRun(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_SETPROG:
//			return msgSetprog(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_SETDRUG:
//			return msgSetdrug(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_ADJUST:
//			return msgAdjust(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_PRIME:
//			return msgPrime(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_OPTIONS:
//			return msgOptions(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_TEST:
//			return msgTest(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_ALARM:
//			return msgAlarm(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_PWRDOWN:
//			return msgPwrdown(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_CALIB:
//			return msgCalib(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_RATECALIB:
//			return msgRCalib(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_BOLUS:
//			return msgBolus(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_SETMENU:
//			return msgSetmenu(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_SETUP:
//			return msgSetup(objMsg, pObj, pMsg);
//		case DISPLAY_SCREEN_CHECKUP:
//			return msgCheckup(objMsg, pObj, pMsg);
		default:
			break;
	}
		
	return 1;	
}

WORD ScreenUpdate(void)
{
	// process the draw messages
	switch (screenState) {
		case CREATE_SCREEN_INTRO:
			return 1;
		case DISPLAY_SCREEN_INTRO:
//			UpdateIntro();
			return 1;
//		case DISPLAY_SCREEN_CHECKUP:
//			UpdateCheckup();
//			return 1;
//		case DISPLAY_SCREEN_TEST:
//			UpdateTest();
//			return 1;
//		case DISPLAY_SCREEN_ADJUST:
//			UpdateAdjust();
//			return 1;
//		case DISPLAY_SCREEN_RUN:
//			UpdateRun();
//			return 1;
//		case DISPLAY_SCREEN_CALIB:
//			return 1;
//		case DISPLAY_SCREEN_OPTIONS:
//			UpdateOptions();
//			return 1;
//		case DISPLAY_SCREEN_PRIME:
//			UpdatePrime();
//			return 1;
//TBD		case DISPLAY_SCREEN_ALARM:
//			UpdateAlarm();
//			return 1;
		case DISPLAY_SCREEN_CLEAR:
			UpdateClear();
			return 1;

//TBD		case DISPLAY_SCREEN_CONFIRM:
//			UpdateConfirm();
//			return 1;
//		case CREATE_SCREEN_NEXT:
//			return 1;
//		case DISPLAY_SCREEN_NEXT:
//			return 1;
		default:	
			return 1;
	}
}

/*********************************************************************
 * Function:        WORD GOLDrawCallback(void);
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Handle application specific drawing, returning
 *					non-zero to allow the GOL to handle drawing
 *
 * Note:            
 ********************************************************************/
WORD GOLDrawCallback(void)
{
SCREEN_MSG scr_msg;
	
	if (xQueueReceive(hSCREENQueue, &scr_msg, 0/*portMAX_DELAY*/) == pdTRUE);
	else
		return 1;
	screenState = scr_msg.cmd;
	if (screenState%2==0)
	{
		GDDCreateScreenCallback(screenState);
		screenState++;
	}
	return 1;	
}
#if 0



/*********************************************************************
 * Function:        void CreateRTOSScreen(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Create the RTOS summary screen
 *
 * Note:            
 ********************************************************************/
static const GFX_XCHAR ipStr[] = {'I','P',':',0};
static const GFX_XCHAR netmaskStr[] = {'M','A','S','K',':',0};
static const GFX_XCHAR gwStr[] = {'G','W',':',0};
void CreateRTOSScreen(void)
{
	short textHeight;
	short ypos;
	char sBuff[30];
	
	GOLFree();	
	SetColor(BLACK);
	ClearDevice();
	
	// display the title message
	BtnCreate(ID_WINDOW4,
		0, 0, GetMaxX(), 39, 0,
		BTN_DRAW, NULL, "RTOS Summary", blueScheme);
	
	// we will call the update function to perform drawing (saving code)
	UpdateRTOSScreen();

	// fill in the IP address information
	
	SetColor(WHITE);
	SetFont((void*) &GOLSmallFont);
	textHeight = GetTextHeight((void*) &GOLSmallFont);


	Line(0, 148, GetMaxX(), 148);
}
/*********************************************************************
 * Function:        WORD msgMain(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj)
 *
 * PreCondition:    None
 *
 * Input:           objMsg, message 
 *					pObj, object
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Handle messages from the main menu
 *
 * Note:            
 ********************************************************************/
WORD msgMain(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj)
{
	GFX_GOL_OBJ_HEADER* pSetPoint;
	SHORT dialVal;
	
	switch (GFX_GOL_ObjectIDGet(pObj)) {
		case ID_SETPOINT_DIAL:
			dialVal = RdiaGetVal((ROUNDDIAL*) pObj);
			
			// update the setpoint display text box
			xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
			pSetPoint = GFX_GOL_ObjectFind(ID_SETPOINT_TEMPERATURE);
			sprintf(qvgaBuff4, "%d.%01dC", dialVal / 10, dialVal % 10);
			StDraw((STATICTEXT*) pSetPoint);
			xSemaphoreGive(QVGAMutSemaphore);
			
			// update the meter object
			xSemaphoreTake(CONTROLSemaphore, portMAX_DELAY);
			gMeter.setpoint = dialVal;
			xSemaphoreGive(CONTROLSemaphore);
			
			// put limits on the rotation
			if ((objMsg == RD_MSG_CLOCKWISE) && (dialVal == 350))
				return 0;
			if ((objMsg == RD_MSG_CTR_CLOCKWISE) && (dialVal == 0))
				return 0;		
			break;
		default:
			break;
	}	

	return 1;	
}

/*********************************************************************
 * Function:        WORD msgGas(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj)
 *
 * PreCondition:    None
 *
 * Input:           objMsg, message 
 *					pObj, object
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Handle messages from the gas screen
 *
 * Note:            
 ********************************************************************/
WORD msgGas(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj)
{
	GFX_GOL_OBJ_HEADER* pOtherBtn;
	
	switch(GFX_GOL_ObjectIDGet(pObj)) {
		case ID_BUTTON_GAS_ON:
			if (objMsg == BTN_MSG_PRESSED) {
				if (!GetState(pObj, BTN_PRESSED)) {
					xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
					pOtherBtn = GFX_GOL_ObjectFind(ID_BUTTON_GAS_OFF);
					ClrState(pOtherBtn, BTN_PRESSED);
					GFX_GOL_ObjectStateSet(pOtherBtn, BTN_DRAW);
					GFX_GOL_ObjectStateSet(pObj, BTN_PRESSED | BTN_DRAW);
					xSemaphoreGive(QVGAMutSemaphore);
					// update the meter
					xSemaphoreTake(CONTROLSemaphore, portMAX_DELAY);
					gMeter.gas_on = 1;
					xSemaphoreGive(CONTROLSemaphore);
				}
			}
			return 0;
		case ID_BUTTON_GAS_OFF:
			if (objMsg == BTN_MSG_PRESSED) {
				if (!GetState(pObj, BTN_PRESSED)) {
					xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
					pOtherBtn = GFX_GOL_ObjectFind(ID_BUTTON_GAS_ON);
					ClrState(pOtherBtn, BTN_PRESSED);
					GFX_GOL_ObjectStateSet(pOtherBtn, BTN_DRAW);
					GFX_GOL_ObjectStateSet(pObj, BTN_PRESSED | BTN_DRAW);
					xSemaphoreGive(QVGAMutSemaphore);
					// update the meter
					xSemaphoreTake(CONTROLSemaphore, portMAX_DELAY);
					gMeter.gas_on = 0;
					xSemaphoreGive(CONTROLSemaphore);
				}
			}
			return 0;
		default:
			return 1;
	}	
}

/*********************************************************************
 * Function:        WORD msgElectric(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj)
 *
 * PreCondition:    None
 *
 * Input:           objMsg, message 
 *					pObj, object
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Handle messages from the Electric screen
 *
 * Note:            
 ********************************************************************/
WORD msgElectric(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj)
{
	GFX_GOL_OBJ_HEADER* pOtherBtn;
	
	switch(GFX_GOL_ObjectIDGet(pObj)) {
		case ID_BUTTON_ELECTRIC_ON:
			if (objMsg == BTN_MSG_PRESSED) {
				if (!GetState(pObj, BTN_PRESSED)) {
					xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
					pOtherBtn = GFX_GOL_ObjectFind(ID_BUTTON_ELECTRIC_OFF);
					ClrState(pOtherBtn, BTN_PRESSED);
					GFX_GOL_ObjectStateSet(pOtherBtn, BTN_DRAW);
					GFX_GOL_ObjectStateSet(pObj, BTN_PRESSED | BTN_DRAW);
					xSemaphoreGive(QVGAMutSemaphore);
					// update the meter
					xSemaphoreTake(CONTROLSemaphore, portMAX_DELAY);
					gMeter.electric_on = 1;
					xSemaphoreGive(CONTROLSemaphore);
				}
			}
			return 0;
		case ID_BUTTON_ELECTRIC_OFF:
			if (objMsg == BTN_MSG_PRESSED) {
				if (!GetState(pObj, BTN_PRESSED)) {
					xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
					pOtherBtn = GFX_GOL_ObjectFind(ID_BUTTON_ELECTRIC_ON);
					ClrState(pOtherBtn, BTN_PRESSED);
					GFX_GOL_ObjectStateSet(pOtherBtn, BTN_DRAW);
					GFX_GOL_ObjectStateSet(pObj, BTN_PRESSED | BTN_DRAW);
					xSemaphoreGive(QVGAMutSemaphore);
					// update the meter
					xSemaphoreTake(CONTROLSemaphore, portMAX_DELAY);
					gMeter.electric_on = 0;
					xSemaphoreGive(CONTROLSemaphore);
				}
			}
			return 0;
		default:
			return 1;
	}	
}

/*********************************************************************
 * Function:        WORD msgRTOS(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj)
 *
 * PreCondition:    None
 *
 * Input:           objMsg, message 
 *					pObj, object
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Handle messages from the RTOS screen
 *
 * Note:            
 ********************************************************************/
WORD msgRTOS(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj)
{
	switch(GFX_GOL_ObjectIDGet(pObj)) {
		case ID_WINDOW4:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
			}
			return 1;
		default:
			return 1;
	}	
}

/*********************************************************************
 * Function:        void UpdateRTOSScreen(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Repaint the stack usage info
 *
 * Note:            
 ********************************************************************/
static const GFX_XCHAR uartStr[] = {'U','A','R','T',':',0};
static const GFX_XCHAR meterStr[] = {'M','E','T','E','R',':',0};
static const GFX_XCHAR miwiStr[] = {'M','I','W','I',':',0};
static const GFX_XCHAR touchStr[] = {'T','O','U','C','H',':',0};
static const GFX_XCHAR graphicsStr[] = {'G','R','A','P','H',':',0};
static const GFX_XCHAR tcpipStr[] = {'T','C','P','I','P',':',0};
void UpdateRTOSScreen(void)
{
	unsigned portBASE_TYPE hw;
	short textHeight;
	short ypos;
	
	// display the RTOS task usage bargraph
//	textHeight = GetTextHeight((void*) &GOLSmallFont); 
	textHeight = GetTextHeight((void*) &GOLFontDefault); 
	
	// just erase the area of the bars and summary text
	SetColor(BLACK);
	GFX_BarDraw(60, 48, GFX_MaxXGet(), (6 * textHeight) + 48);
	
	// for each task display its stack usage as a bar graph and summary text
	ypos = 48;	
//	hw = (STACK_SIZE_UART - uxTaskGetStackHighWaterMark(hUARTTask)) * sizeof(portSTACK_TYPE);
//	DrawRTOSStack((GFX_XCHAR*) uartStr, ypos, hw, STACK_SIZE_UART * sizeof(portSTACK_TYPE));
	
//	ypos += textHeight;
	hw = (STACK_SIZE_CALC - uxTaskGetStackHighWaterMark(hCALCTask)) * sizeof(portSTACK_TYPE);
	DrawRTOSStack((GFX_XCHAR*) meterStr, ypos, hw, STACK_SIZE_CALC * sizeof(portSTACK_TYPE));
				
//	ypos += textHeight;
//	hw = (STACK_SIZE_MIWI - uxTaskGetStackHighWaterMark(hMIWITask)) * sizeof(portSTACK_TYPE);
//	DrawRTOSStack((GFX_XCHAR*) miwiStr, ypos, hw, STACK_SIZE_MIWI * sizeof(portSTACK_TYPE));

	ypos += textHeight;
	hw = (STACK_SIZE_TOUCHSCREEN - uxTaskGetStackHighWaterMark(hTOUCHTask)) * sizeof(portSTACK_TYPE);
	DrawRTOSStack((GFX_XCHAR*) touchStr, ypos, hw, STACK_SIZE_TOUCHSCREEN * sizeof(portSTACK_TYPE));

	ypos += textHeight;
	hw = (STACK_SIZE_GRAPHICS - uxTaskGetStackHighWaterMark(hGRAPHICSTask)) * sizeof(portSTACK_TYPE);
	DrawRTOSStack((GFX_XCHAR*) graphicsStr, ypos, hw, STACK_SIZE_GRAPHICS * sizeof(portSTACK_TYPE));

//	ypos += textHeight;
//	hw = (STACK_SIZE_TCPIP - uxTaskGetStackHighWaterMark(hTCPIPTask)) * sizeof(portSTACK_TYPE);
//	DrawRTOSStack((GFX_XCHAR*) tcpipStr, ypos, hw, STACK_SIZE_TCPIP * sizeof(portSTACK_TYPE));	
}

/*********************************************************************
 * Function:        void UpdateUsageGraph(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Draw the usage graph at the bottom of the screen
 *
 * Note:            
 ********************************************************************/
void UpdateUsageGraph(void)
{
	WORD currentVal, ypos;
	static WORD old_x, old_y;
	
	// calculate how many units used in the last time interval (2 seconds)
	xSemaphoreTake(CONTROLSemaphore, portMAX_DELAY);
	currentVal = gMeter.electric_units;
	xSemaphoreGive(CONTROLSemaphore);
	// subtract the previous reading (if valid)
	if (usage_last_value != 0xFFFF) {
		ypos = currentVal - usage_last_value;
	} else {
		ypos = 0;
	}
	usage_last_value = currentVal;

	// update the graph
	if (usage_xpos == 0xFFFF) {
		// redraw the graph
		SetColor(BLACK);	
//		GFX_BarDraw(80, 200, 239, GetMaxY());
		GFX_BarDraw(120, 280, 180, GetMaxY());
		SetColor(WHITE);
		Line(132, 280, 132, GetMaxY() - 2);
		Line(130, GetMaxY() - 4, 170, GetMaxY() - 4);
		
		usage_xpos = 0;
	}
	
	SetColor(GREEN);
	// scale the ypos result into the displayed pixel range
	ypos *= 3;
	ypos = GetMaxY() - 4 - ypos;
	
	// only draw if not the very first point of the line
	if (usage_xpos != 0)
		Line(old_x + 93, old_y, usage_xpos + 93, ypos);
	
	// record the previous points
	old_x = usage_xpos;
	old_y = ypos;
	
	usage_xpos += 4;
	
	// redraw graph next time if required
	if ((usage_xpos + 83) >= 220) {
		usage_xpos = 0xFFFF;
	}
}
#endif

