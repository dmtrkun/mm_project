/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_RCALIB_PUB
#include "include.h"




#define END_CLBR_PG				2
#define ERROR_CLBR_PG			3

#define PREPARE_RATE_CLBR	0
#define RATE_CLBR					1
#define ENTER_RATE_CLBR		2
#define END_RATE_CLBR			3

float scale_rate_tmp;
float vol_calibr_tmp;
static unsigned int calib_page;
static volatile unsigned char calib_status;
//static unsigned int elapsedTime;
static unsigned char time_halfsec;

static CONTROL_MSG cMsg;

// Strings
__prog__ XCHAR __attribute__((space(prog))) RCalib_OBJ_STATICTEXT_0_text[] = "RATE CALIBRAT.";

//const XCHAR RCalib_OBJ_BUTTON_0_text[] = "EXIT";
const XCHAR RCalib_OBJ_BUTTON_1_text[] = "CONTINUE";
//const XCHAR RCalib_OBJ_BUTTON_2_text[] = "SAVE";

const __prog__ XCHAR __attribute__((space(prog))) RCalib_msg_0[] = {
	"1. LOAD PRIMED IV SET\r\n2. PRESS CONTINUE\r\nAND WAIT UNTIL\r\n\VOLUME WILL BE\r\nDELIVERED."
	};
const __prog__ XCHAR __attribute__((space(prog))) RCalib_msg_1[] = {
	"ENTER THE VOLUME THAT\r\nAPPEARS ON THE SCALE\r\n(in 18.0 to 22.0 ml range)",
	};
const __prog__ XCHAR __attribute__((space(prog))) RCalib_msg_2[] = {
	"END OF\r\nRATE CALIBRATION.\r\nPRESS SAVE TO STORE\r\nCALIBRATION RESULTS.\r\nTHANKS",
	};
const __prog__ XCHAR __attribute__((space(prog))) RCalib_msg_3[] = {
	"ERROR CALIBRATION"
	};



PARA_SPECS_t Ratecalib_Para_Specs = {"INFUSED",		(void*)&scale_rate_tmp,				PARA_FLOAT,	TYPE_VOLUME,		NULL,			0};


#define RCalib_OBJ_STATICTEXT_0		0
#define RCalib_OBJ_BUTTON_0   		1
#define RCalib_OBJ_BUTTON_1				2
#define RCalib_OBJ_BUTTON_2				3
#define RCalib_OBJ_STATICTEXT_1		4
#define RCalib_OBJ_PICTURE_0				5
#define RCalib_OBJ_PROGRESSBAR_0		6

void CreateRCalib(void)
{
	static char	str1[30];
	_prog_addressT p;
	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();
	xTimerStart( xTimers[ 1 ], 0 );
	memcpy(basicscheme, defscheme, sizeof(GOL_SCHEME));
	basicscheme->pFont = (void*)&Arial_Narrow_Bold_18;
	 
	calib_page = page_create;
	
	if(calib_page == 0)
	{
		vol_calibr_tmp = vol_calibr;
		vol_calibr = 1.0;
		_init_prog_address(p, RCalib_msg_0);
		_strncpy_p2d16(str_buf1,p,128);
//		_strncpy_p2d16(str_buf1,(_prog_addressT)RCalib_msg[0],128);
		StCreate(RCalib_OBJ_STATICTEXT_1,5,40,238,200,ST_DRAW|ST_CENTER_ALIGN,str_buf1,basicscheme);
		BtnCreate(RCalib_OBJ_BUTTON_1,132,277,232,313,5,BTN_DRAW,NULL,(XCHAR*)RCalib_OBJ_BUTTON_1_text,botbar);
		calib_status = PREPARE_RATE_CLBR;  //Stop any calibration process
	}
	else if(calib_page == 1)
	{
		PbCreate(RCalib_OBJ_PROGRESSBAR_0, 10, 206, 229, 244, PB_DRAW, 0,(int)vol_para.vtbi,"ml",basicscheme);
//		BtnCreate(RCalib_OBJ_BUTTON_1,132,277,232,313,5,BTN_DRAW,NULL,(XCHAR*)RCalib_OBJ_BUTTON_1_text,botbar);
	}
	else if(calib_page == 2)
	{
		_init_prog_address(p, RCalib_msg_1);
		_strncpy_p2d16(str_buf1,p,128);
//		_strncpy_p2d16(str_buf1,(_prog_addressT)RCalib_msg[1],128);
		StCreate(RCalib_OBJ_STATICTEXT_1,5,40,238,200,ST_DRAW|ST_CENTER_ALIGN,str_buf1,basicscheme);
		sprintf(str1,"WEIGHT  = %.1f ml",(double)scale_rate_tmp);
		BtnCreate(RCalib_OBJ_BUTTON_2,3,206,236,244,10,BTN_DRAW|BTN_TEXTLEFT,(void*)&Param_btn,(XCHAR*)str1,basicscheme);
		if(scale_rate_tmp < 18.0 || scale_rate_tmp > 22.0 )
			BtnCreate(RCalib_OBJ_BUTTON_1,132,277,232,313,5,BTN_DRAW|BTN_DISABLED,NULL,(XCHAR*)RCalib_OBJ_BUTTON_1_text,botbar);
		else	
			BtnCreate(RCalib_OBJ_BUTTON_1,132,277,232,313,5,BTN_DRAW,NULL,(XCHAR*)RCalib_OBJ_BUTTON_1_text,botbar);
	}
	else
	{
		_init_prog_address(p, RCalib_msg_2);
		_strncpy_p2d16(str_buf1,p,128);
//		_strncpy_p2d16(str_buf1,RCalib_msg[2],128);
		StCreate(RCalib_OBJ_STATICTEXT_1,5,40,238,200,ST_DRAW|ST_CENTER_ALIGN,str_buf1,basicscheme);
		BtnCreate(RCalib_OBJ_BUTTON_1,132,277,232,313,5,BTN_DRAW,NULL,(XCHAR*)SAVE_OBJ_BUTTON_text,botbar);
	}	
	 
//	StCreate(RCalib_OBJ_STATICTEXT_1,5,40,238,200,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)RCalib_msg[calib_page],basicscheme);
 
	BtnCreate(RCalib_OBJ_BUTTON_0,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
	_init_prog_address(p, RCalib_OBJ_STATICTEXT_0_text);
	_strncpy_p2d16(gStr1,p,128);
	StCreate(RCalib_OBJ_STATICTEXT_0,1,0,238,30,ST_DRAW|ST_CENTER_ALIGN,gStr1,topbar);
//	StCreate(RCalib_OBJ_STATICTEXT_0,1,0,238,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)RCalib_OBJ_STATICTEXT_0_text,topbar);
	
	PictCreate(RCalib_OBJ_PICTURE_0, 210,0,239,30, PICT_DRAW|PICT_HIDE , IMAGE_NORMAL, getWaitImg(), topbar);
}

void CreatePrimitivesForRCalib(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		SetColor(BLUE_DARK);
//		while(!Bar(0,279,239,319));
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

WORD msgRCalib(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
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
					GDDSetScreen(CREATE_SCREEN_CLEAR,1,NULL);
					ClearParams();
					vol_calibr = vol_calibr_tmp;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDPrevScreen();
				}	
				break;
			case INP_KVO_ID:			
				if(pMsg->param2 == INP_SET)
				{
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					ClearParams();
					calib_page++;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					clearBit( alarm_st, KVO_ALRM);
					GDDShiftScreen(calib_page);
				}	
				break;
			
			case INP_TIMER1_ID:			 
				//Timer expired
				xTimerStart( xTimers[ 1 ], 0 );
				UpdateRCalib();
				break;
			default:
				break;
		}
		return 1;	
	}
	 
	switch (GetObjID(pObj)) {
		
		case RCalib_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_RELEASED) {
				vol_calibr = vol_calibr_tmp;
   				xTimerStop( xTimers[ 1 ], 0 );
				GDDPrevScreen();
			}	
			return 1;
		case RCalib_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_RELEASED) {
				if(calib_page < END_RATE_CLBR)
				{
					SetState((BUTTON*) pObj, BTN_DRAW|BTN_DISABLED);
					calib_page++;
					if(calib_page == 1)
					{
						steps = 0;
						if(stmotor_stat()== STMTR_STOP)
						{
							vol_para.rate = 600;
							vol_para.vtbi = 20;
							no_limit = 0;
							cMsg.cmd = MSG_CONTROL_START_INFUS;
							xQueueSend(hCONTROLQueue, &cMsg, 0);
						}
					}
	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDShiftScreen(calib_page);
				}
				else
				{
//					vol_calibr = 20.0/scale_rate_tmp;
					vol_calibr = scale_rate_tmp/20.0;
					vTaskSuspendAll();
					((unsigned int*)&Clbr_E2pImage)[sizeof(Clbr_E2pImage)/2 - 1] = crc16(&Clbr_E2pImage, sizeof(Clbr_E2pImage) - 2);
					SST25SectorErase(CLBR_E2PIMG_BASE);
					if(!SST25WriteArray(CLBR_E2PIMG_BASE, &Clbr_E2pImage, sizeof(Clbr_E2pImage)))
						/*CriticalError("eeprom err")*/;
					xTaskResumeAll();
		         	xTimerStop( xTimers[ 1 ], 0 );
					GDDPrevScreen();
				}
			}	
			break;
		case RCalib_OBJ_BUTTON_2:
			if (objMsg == BTN_MSG_RELEASED) {
		         	xTimerStop( xTimers[ 1 ], 0 );
//					adjust_val_ptr = &scale_rate_tmp;
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_INFUSED_CLBR,(void*)&Ratecalib_Para_Specs);
			}			
			break;
		
		default:
			break;
	}	

	return 1;	
} 
void UpdateRCalib(void)
{
	OBJ_HEADER* pObj;
//	static unsigned char i;
//	static unsigned int calibr_val;
	static unsigned long lastClock;
//	unsignedsigned int elapsedTime;
	
#if 0
	if(calib_status == PRESS1_ZERO_CLBR || calib_status == PRESS2_ZERO_CLBR || calib_status == SET_ZERO_CLBR || calib_status == SET_300_CLBR)
	{
			pObj = GOLFindObject(Calib_OBJ_PICTURE_0);
			if (pObj) {
				PictSetBitmap(pObj, getWaitImg());
				ClrState(pObj, PICT_HIDE);
				SetState((PICTURE*) pObj, DRAW_UPDATE);
			}
//			pObj = GOLFindObject(Calib_OBJ_BUTTON_1);
//			if (pObj) {
//				SetState((BUTTON*) pObj, BTN_DRAW|BTN_DISABLED);
//			}
			
			elapsedTime += clock_ms() - lastClock;
	}
	else
	{
			pObj = GOLFindObject(Calib_OBJ_PICTURE_0);
			if (pObj) {
				SetState((PICTURE*) pObj, DRAW_UPDATE|PICT_HIDE);
			}
			pObj = GOLFindObject(Calib_OBJ_BUTTON_1);
			if (pObj) {
				ClrState(pObj, BTN_DISABLED);
				SetState((BUTTON*) pObj, BTN_DRAW);
			}
			elapsedTime = 0;
	}
#endif
	
	lastClock = clock_ms();
	
	switch(calib_page)
	{
		case PREPARE_RATE_CLBR:
			break;
		case RATE_CLBR:
			time_halfsec++;
			if(time_halfsec >= 5)
			{
				Beep(250);
				time_halfsec = 0;
			}
			pObj = GOLFindObject(RCalib_OBJ_PROGRESSBAR_0);
			if (pObj) {
				PbSetPos((PROGRESSBAR*) pObj, (WORD)vol_para.infsd);
				SetState((PROGRESSBAR*) pObj, DRAW_UPDATE);
			}
			break;
		case ENTER_RATE_CLBR:
			break;
		case END_RATE_CLBR:
			break;
	}
}











