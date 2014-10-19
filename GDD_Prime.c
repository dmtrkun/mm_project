/*****************************************************************************
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_PRIME_PUB
#include "include.h"
#include "Graphics Resources\new.h"

// Strings
const GFX_XCHAR Prime_OBJ_STATICTEXT_0_text[] = "PRIME?";
const GFX_XCHAR Prime_OBJ_STATICTEXT_1_text[] = "PRIME";
const GFX_XCHAR Prime_OBJ_STATICTEXT_2_text[] = "WARNING!!!";
const GFX_XCHAR Prime_OBJ_STATICTEXT_3_text[] = "Ensure the set\r\nis not connected\r\nto patient!";
const GFX_XCHAR Prime_OBJ_STATICTEXT_4_text[] = "PRIMING";
//const GFX_XCHAR Prime_OBJ_STATICTEXT_5_text[] = "to patient!";
//const GFX_XCHAR Prime_OBJ_BUTTON_0_text[] = "PRIME VOL = 236 ml/hr";
const GFX_XCHAR Prime_OBJ_BUTTON_1_text[] = "START PRIME";
const GFX_XCHAR Prime_OBJ_BUTTON_2_text[] = "NO PRIME";
const GFX_XCHAR Prime_OBJ_BUTTON_3_text[] = "STOP PRIME";

#define Prime_OBJ_STATICTEXT_0   0
#define Prime_OBJ_STATICTEXT_1   1
#define Prime_OBJ_STATICTEXT_2   2
#define Prime_OBJ_STATICTEXT_3   3
#define Prime_OBJ_STATICTEXT_4   4
#define Prime_OBJ_STATICTEXT_5   5
#define Prime_OBJ_BUTTON_0   6
#define Prime_OBJ_BUTTON_1   7
#define Prime_OBJ_BUTTON_2   8
#define Prime_OBJ_BUTTON_3   9
#define Prime_OBJ_BUTTON_4   10
#define Prime_OBJ_BUTTON_5   11
#define Prime_OBJ_BUTTON_6   12
#define Prime_OBJ_BUTTON_7   13
#define Prime_OBJ_BUTTON_8   14
#define Prime_OBJ_BUTTON_9   15
#define Prime_OBJ_BUTTON_10   16
#define Prime_OBJ_BUTTON_11   17
#define Prime_OBJ_PICTURE_0		18
#define Prime_OBJ_PROGRESSBAR_0	19

static CONTROL_MSG cMsg;

static GFX_GOL_OBJ_SCHEME* pScheme;	
static GFX_GOL_OBJ_SCHEME* pScheme1;	
static GFX_GOL_OBJ_SCHEME* pScheme2;	

void PrimeShemes(void)
{
	pScheme = CreateScheme();
	memcpy(pScheme, defscheme, sizeof(GFX_GOL_OBJ_SCHEME));
	pScheme->Color0 = RED;
	pScheme->Color1 = RED;
	pScheme->CommonBkColor = RED;

	pScheme1 = CreateScheme();
	memcpy(pScheme1, defscheme, sizeof(GFX_GOL_OBJ_SCHEME));
	pScheme1->CommonBkColor = RED;
	pScheme1->pFont = (void*)&Arial_Narrow_24;

	pScheme2 = CreateScheme();
	memcpy(pScheme2, defscheme, sizeof(GFX_GOL_OBJ_SCHEME));
	pScheme2->CommonBkColor = RED;
	pScheme2->TextColor0 = BLACK;
//	pScheme2->pFont = (void*)&arial_narrow_0_0_0_14;
	pScheme2->pFont = (void*)&Arial_Narrow_14;
}

void CreatePrime(void)
{
static char	str1[30];

	GFX_GOL_ObjectListFree();
	GFX_ColorSet(RED);
	GFX_ScreenClear();
	
	if(page_create == 0)
	{
		if(vol_para.vtbi < 100.0)
			sprintf(str1,"PRIME VOL  = %.1f ml",(double)vol_para.vtbi);
		else
			sprintf(str1,"PRIME VOL  = %.0f ml",(double)vol_para.vtbi);
	//	pPrime_OBJ_BUTTON_0 = GFX_GOL_ButtonCreate(Prime_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW,NULL,(GFX_XCHAR*)Prime_OBJ_BUTTON_0_text,defscheme);
		GFX_GOL_ButtonCreate(Prime_OBJ_BUTTON_0,3,206,236,244,10,BTN_DRAW|BTN_TEXTLEFT,(void*)&Param_btn,(GFX_XCHAR*)str1,pScheme1);
		
		GFX_GOL_ButtonCreate(Prime_OBJ_BUTTON_1,5,277,118,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Prime_OBJ_BUTTON_1_text,botbar);
		GFX_GOL_ButtonCreate(Prime_OBJ_BUTTON_2,152,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Prime_OBJ_BUTTON_2_text,botbar);
		GFX_GOL_StaticTextCreate(Prime_OBJ_STATICTEXT_0,0,0,239,39,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Prime_OBJ_STATICTEXT_0_text,GFX_ALIGN_CENTER,topbar);
		
		GFX_GOL_StaticTextCreate(Prime_OBJ_STATICTEXT_2,0,50,239,83,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Prime_OBJ_STATICTEXT_2_text,GFX_ALIGN_CENTER,pScheme);
		GFX_GOL_StaticTextCreate(Prime_OBJ_STATICTEXT_3,0,85,239,196,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Prime_OBJ_STATICTEXT_3_text,GFX_ALIGN_CENTER,pScheme);
//		GFX_GOL_StaticTextCreate(Prime_OBJ_STATICTEXT_4,0,120,239,153,GFX_GOL_STATICTEXT_DRAW_STATE|ST_CENTER_ALIGN,(GFX_XCHAR*)Prime_OBJ_STATICTEXT_4_text,pScheme);
//		GFX_GOL_StaticTextCreate(Prime_OBJ_STATICTEXT_5,0,155,239,188,GFX_GOL_STATICTEXT_DRAW_STATE|ST_CENTER_ALIGN,(GFX_XCHAR*)Prime_OBJ_STATICTEXT_5_text,pScheme);
	}
	else
	{
		xTimerStart( xTimers[ 1 ], 0 );
		
//		if(no_limit == 1)
//			sprintf(str1,"NO LIMIT");
		if(vol_para.vtbi < 100.0)
			sprintf(str1,"%.1f ml",(double)vol_para.vtbi);
		else
			sprintf(str1,"%.0f ml",(double)vol_para.vtbi);
 //		sprintf(str1 + strlen(str1),", %.0f ml/h",(double)vol_para.rate);
		GFX_GOL_StaticTextCreate(Prime_OBJ_STATICTEXT_5,40,140,200,180,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_CENTER,pScheme1);
		GFX_GOL_ButtonCreate(Prime_OBJ_BUTTON_3,70,277,185,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Prime_OBJ_BUTTON_3_text,botbar);
		GFX_GOL_StaticTextCreate(Prime_OBJ_STATICTEXT_0,0,0,239,39,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Prime_OBJ_STATICTEXT_1_text,GFX_ALIGN_CENTER,topbar);
		GFX_GOL_PictureControlCreate(Prime_OBJ_PICTURE_0, 210,0,239,30, GFX_GOL_PICTURECONTROL_DRAW_STATE, IMAGE_NORMAL, getWaitImg(), topbar);
	  PbCreate( Prime_OBJ_PROGRESSBAR_0, 10, 206, 229, 244, PB_DRAW, 0,(int)vol_para.vtbi,"ml",pScheme1);
		GFX_GOL_StaticTextCreate(Prime_OBJ_STATICTEXT_4,0,85,239,136,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Prime_OBJ_STATICTEXT_4_text,GFX_ALIGN_CENTER,pScheme1);
	}
}
void CreatePrimitivesForPrime(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		SetColor(BLUE_DARK);
//		while(!GFX_BarDraw(0,279,239,319));
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

WORD msgPrime(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
	
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_KVO_ID:			   
			case INP_STOP_ID:			
				if(pMsg->param2 == INP_SET)
				{
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					clearBit( alarm_st, KVO_ALRM);
					GDDSetScreen(CREATE_SCREEN_CLEAR,1,NULL);
					ClearParams();
					steps = 0;
//					kvo_stat = 0;
				}	
				break;
			case INP_TIMER1_ID:			
				//Timer expired
				xTimerStart( xTimers[ 1 ], 0 );
				UpdatePrime();
				break;
			default:
				break;
		}
		return 1;	
	}
	
	switch (GFX_GOL_ObjectIDGet(pObj)) {
		
		case Prime_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap(pObj, &Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap(pObj, &Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
				{
					/*Adjust priming volume*/
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_PRIME,NULL);
				}
			}	
			return 1;
		case Prime_OBJ_BUTTON_1:
			/*Start priming*/
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
				steps = 0;
				if(stmotor_stat()== STMTR_STOP)
				{
//					vol_para.rate = max_rate;
					vol_para.rate = 600.0;
					no_limit = 0;
//					new_calc_rate(1800.0);
					cMsg.cmd = MSG_CONTROL_START_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
				}
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(1);
			}
			return 1;
		
		case Prime_OBJ_BUTTON_2:
			/*Back to prev screen*/
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				if(prog_num == 2 || prog_num == 3)
					GDDSetScreen(CREATE_SCREEN_CLEAR,2,NULL);
				else
					GDDSetScreen(CREATE_SCREEN_CLEAR,1,NULL);
				ClearParams();
//				kvo_stat = 0;
				steps = 0;
//				GDDPrevScreen();
			}
			return 1;

		case Prime_OBJ_BUTTON_3:
			/*Stop priming and back to prev screen*/
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
				cMsg.cmd = MSG_CONTROL_STOP_INFUS;
				xQueueSend(hCONTROLQueue, &cMsg, 0);
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_CLEAR,1,NULL);
//				GDDPrevScreen();
				ClearParams();
//				kvo_stat = 0;
				steps = 0;
			}
			return 1;

#if 0		 
		case Prime_OBJ_BUTTON_3:
			//Goto programms
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
				GDDSetScreen(CREATE_SCREEN_SETPROG,0,NULL);
			return 1;
		case Prime_OBJ_BUTTON_4:
			//Goto drugs
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
				GDDSetScreen(CREATE_SCREEN_SETDRUG,0,NULL);
			return 1;
		case Prime_OBJ_BUTTON_7:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
				//Prime and Goto priming
				memset((unsigned char)&vol_para,0,sizeof((unsigned char)&vol_para));
//				GDDSetScreen(CREATE_SCREEN_PRIME,0,NULL);
			}
			return 1;
		case Prime_OBJ_BUTTON_8:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				//Goto options
				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
			}	
			return 1;
		case Prime_OBJ_BUTTON_9:
		case Prime_OBJ_BUTTON_11:
			//Goto please confirm
			return 1;
		
		case Prime_OBJ_BUTTON_10:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				//Goto Prime setup
				page_display = 0;
				GDDShiftScreen(0);
//				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
			}	
			return 1;
#endif
		default:
			break;
	}	
	return 1;	
} 


void UpdatePrime(void)
{
	GFX_GOL_OBJ_HEADER* pObj;
	static unsigned long lastClock;
	unsigned int elapsedTime;
	
	elapsedTime += clock_ms() - lastClock;
	lastClock = clock_ms();
	if (page_display == 1)
	{
		pObj = GOLFindObject(Prime_OBJ_PICTURE_0);
		if (pObj) {
			PictSetBitmap(pObj, getWaitImg());
			SetState((PICTURE*) pObj, DRAW_UPDATE);
		}
		pObj = GOLFindObject(Prime_OBJ_PROGRESSBAR_0);
		if (pObj) {
			PbSetPos((PROGRESSBAR*) pObj, (WORD)vol_para.infsd);
			SetState((PROGRESSBAR*) pObj, DRAW_UPDATE);
		}
	}

//	pObj = GOLFindObject(Prime_OBJ_BUTTON_0);
//	if (pObj) {
//		SetState((BUTTON*) pObj, BTN_DRAW|BTN_DISABLED);
//	}

}



