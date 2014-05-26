/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_TEST_PUB
#include "include.h"

// Strings
const XCHAR Test_OBJ_STATICTEXT_0_text[] = "TEST";
const XCHAR Test_OBJ_EDITBOX_1_text[] = "TEST";

//const XCHAR Test_OBJ_BUTTON_0_text[] = "SET PROGRAM";
const XCHAR Test_OBJ_BUTTON_1_text[] = "SET PARAMETER";
const XCHAR Test_OBJ_BUTTON_2_text[] = "CHECKUP";
const XCHAR Test_OBJ_BUTTON_3_text[] = "SET DATE";
const XCHAR Test_OBJ_BUTTON_4_text[] = "BUTTON_4";
const XCHAR Test_OBJ_BUTTON_5_text[] = "BUTTON_5";
const XCHAR Test_OBJ_BUTTON_6_text[] = "BUTTON_6";
//const XCHAR Test_OBJ_BUTTON_7_text[] = "EXIT";
const XCHAR Test_OBJ_BUTTON_8_text[] = "RUN";
const XCHAR Test_OBJ_BUTTON_9_text[] = "STOP";

#define Test_OBJ_STATICTEXT_0		  100
#define Test_OBJ_DIGITALMETER_0   101
#define Test_OBJ_DIGITALMETER_1		102
#define Test_OBJ_DIGITALMETER_2   103
#define Test_OBJ_DIGITALMETER_3   104
#define Test_OBJ_BUTTON_4   105
#define Test_OBJ_BUTTON_5   106
#define Test_OBJ_BUTTON_6   107
#define Test_OBJ_BUTTON_7   108
#define Test_OBJ_BUTTON_8   109
#define Test_OBJ_BUTTON_9   110
#define Test_OBJ_EDITBOX_1		  111

#define Test_OBJ_EDITBOX_2	112
#define Test_OBJ_EDITBOX_3  113
#define Test_OBJ_EDITBOX_4  114
#define Test_OBJ_STATICTEXT_1		  115

static CONTROL_MSG cMsg;
XCHAR	bat_str[17];
XCHAR	test_str[100];
XCHAR	press1_str[30];
static XCHAR	press2_str[30];
static XCHAR	calib_str[87];

void CreateTest(void)
{         
	
	strcpy(test_str,Test_OBJ_EDITBOX_1_text);
	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();
	xTimerStart( xTimers[ 1 ], 0 );


//	DmCreate(Test_OBJ_DIGITALMETER_0, 150, 48, 236, 86, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 5, 1, botbar);
	EbCreate(Test_OBJ_EDITBOX_4,120,106,236,146, EB_DRAW,(XCHAR*)bat_str, 16 ,botbar);
//	DmCreate(Test_OBJ_DIGITALMETER_1, 150, 94, 236, 132, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 5, 0, botbar);
//	DmCreate(Test_OBJ_DIGITALMETER_2, 150, 140, 236, 178, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 5, 0, botbar);
	EbCreate(Test_OBJ_EDITBOX_2,120,150,236,208, EB_DRAW,(XCHAR*)press1_str, 29 ,botbar);
//	DmCreate(Test_OBJ_DIGITALMETER_3, 150, 186, 236, 224, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 5, 0, botbar);
	EbCreate(Test_OBJ_EDITBOX_3,120,212,236,270, EB_DRAW,(XCHAR*)press2_str, 29 ,blackScheme);
	 
	BtnCreate(Test_OBJ_BUTTON_7,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
	BtnCreate(Test_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,NULL,(XCHAR*)Test_OBJ_BUTTON_8_text,botbar);
	BtnCreate(Test_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,NULL,(XCHAR*)Test_OBJ_BUTTON_9_text,botbar);

	StCreate(Test_OBJ_STATICTEXT_0,0,0,239,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Test_OBJ_STATICTEXT_0_text,topbar);
//	StCreate(Test_OBJ_STATICTEXT_1,2,48,150,140,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)test_str,blackScheme);

	EbCreate(Test_OBJ_EDITBOX_1,2,48,236,88, EB_DRAW,(XCHAR*)test_str, 50 ,blackScheme);
//	sprintf(calib_str,"Z1=%d\r\nZ2=%d\r\nS1=%d\r\nS1=%d\r\nC1=%d\r\nC2=%d",zero_press1,zero_press2,set_press1,set_press2,scale_press1,scale_press2);
	sprintf(calib_str,"max=%d\r\nmin=%d\r\nlast=%d\r\ncurr=%d",rotate_debug_max,rotate_debug_min,rotate_debug_last,rotate_det_cntr);
	StCreate(Test_OBJ_STATICTEXT_0,2,124,110,268,ST_DRAW,(XCHAR*)calib_str,blackScheme);



}
void CreatePrimitivesForTest(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		SetColor(BLUE_DARK);
//		while(!Bar(0,279,239,319));
}
void UpdateTest(void)
{
	OBJ_HEADER* pObj;
	time_t time_val;

	 
	pObj = GOLFindObject(Test_OBJ_EDITBOX_4);
	if (pObj) {
//			sprintf(str," = %.2fV", BAT_RAW2VOLT(batt_raw));
		sprintf(bat_str,"Bat %.1fV",BAT_RAW2VOLT(batt_raw));
		EbSetText((EDITBOX*)pObj,bat_str);        //
		SetState((EDITBOX*) pObj, EB_DRAW);
	}
//	pObj = GOLFindObject(Test_OBJ_DIGITALMETER_1);
//	if (pObj) {
//		DmSetValue((DIGITALMETER*)pObj,air_raw);
//		SetState((DIGITALMETER*) pObj, DRAW_UPDATE);
//	}
	pObj = GOLFindObject(Test_OBJ_EDITBOX_2);
	if (pObj) {
		sprintf(press1_str,"P1 %d mmHg\r\n(%d)",press1_mmHg,press1_raw);
		EbSetText((EDITBOX*)pObj,press1_str);   
		SetState((EDITBOX*) pObj, EB_DRAW);
	}
	pObj = GOLFindObject(Test_OBJ_EDITBOX_3);
	if (pObj) {
		sprintf(press2_str,"P2 %d mmHg\r\n(%d)", press2_mmHg,press2_raw);
		EbSetText((EDITBOX*)pObj,press2_str);   
 		SetState((EDITBOX*) pObj, EB_DRAW);
	}
	pObj = GOLFindObject(Test_OBJ_EDITBOX_1);
	if (pObj) {
		time_val = clock();
//		sprintf(test_str,"%s", ctime(&time_val));
		strftime(test_str, 100, "%H:%M:%S %d.%m.%Y", localtime(&time_val));

//		sprintf(test_str,"Time %02d:%02d:%02d \r\n Infused %d ml", hour, min, sec, (unsigned int)vol_para.infsd);
		EbSetText((EDITBOX*)pObj,test_str); 
 		SetState((EDITBOX*) pObj, EB_DRAW);
//		StSetText(pObj,test_str); 
// 		SetState((STATICTEXT*) pObj, ST_DRAW);
// 		SetState((STATICTEXT*) pObj, ST_UPDATE);
	}
	pObj = GOLFindObject(Test_OBJ_STATICTEXT_0);
	if (pObj) {
		sprintf(calib_str,"max=%d\r\nmin=%d\r\nlast=%d\r\ncurr=%d",rotate_debug_max,rotate_debug_min,rotate_debug_last,rotate_det_cntr);
		StSetText((STATICTEXT*)pObj,calib_str);   
 		SetState((STATICTEXT*) pObj, ST_DRAW);
	}

	
	
	



}


/*********************************************************************
 * Function:        WORD msgMain(WORD objMsg, OBJ_HEADER* pObj)
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

WORD msgTest(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_STOP_ID:			   
				if(pMsg->param2 == INP_SET)
				{
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
				}	
				break;
			case INP_KVO_ID:			
				if(pMsg->param2 == INP_SET)
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,KVO_ALRM_SCR,NULL);
				}	
				break;
#if 0			
			case INP_AIR_ID:			   
				if(pMsg->param2 == INP_SET)
				{
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					GDDSetScreen(CREATE_SCREEN_ALARM,AIR_ALRM_SCR,NULL);
				}	
				//Stop infusion and alarm				
				break;
			case INP_MOTOR_ID:			
				if(pMsg->param2 == INP_SET)
				{
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					GDDSetScreen(CREATE_SCREEN_ALARM,MOTOR_ALRM_SCR,NULL);
				}	
				break;
			case INP_KVO_ID:			
				if(pMsg->param2 == INP_SET)
				{
					GDDSetScreen(CREATE_SCREEN_ALARM,MOTOR_ALRM_SCR,NULL);
				}	
				break;
			case INP_UPACC_ID:			 
					GDDSetScreen(CREATE_SCREEN_ALARM,UPOCC_ALRM_SCR,NULL);
			case INP_DOWNACC_ID:			 
					GDDSetScreen(CREATE_SCREEN_ALARM,DOWNOCC_ALRM_SCR,NULL);
			case INP_PARAOCC_ID:			
				if(pMsg->param2 == INP_SET)
				{                                        
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					GDDSetScreen(CREATE_SCREEN_ALARM,PARAOCC_ALRM_SCR,NULL);
				}	
				//Stop infusion and alarm				
				break;
#endif			
			case INP_TIMER1_ID:			 
				//Timer expired
				xTimerStart( xTimers[ 1 ], 0 );
				UpdateTest();
				break;
			default:
				break;
		}
		return 1;	
	}
	switch (GetObjID(pObj)) {
		case Test_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) {
				cMsg.cmd = MSG_CONTROL_STOP_INFUS;
				xQueueSend(hCONTROLQueue, &cMsg, 0);
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDPrevScreen();
			}	
			return 1;
		case Test_OBJ_BUTTON_8:
			if (objMsg == BTN_MSG_RELEASED) 
			{
				if(GetDoorState())
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,DOOR_ALRM_SCR,NULL);
					return 1;
				}
				steps = 0;
				if(stmotor_stat()== STMTR_STOP)
				{
					vol_para.rate = 600;
					vol_para.vtbi = 9999;
					cMsg.cmd = MSG_CONTROL_START_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
				}
			}	
			return 1;
		case Test_OBJ_BUTTON_9:
			if (objMsg == BTN_MSG_RELEASED) {
				cMsg.cmd = MSG_CONTROL_STOP_INFUS;
				xQueueSend(hCONTROLQueue, &cMsg, 0);
			}	
			return 1;
		
		default:
			break;
	}	

	return 1;	
} 
