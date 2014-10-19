/*****************************************************************************
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_BOLUS_PUB
#include "include.h"
#include "Graphics Resources\new.h"

// Strings
//const GFX_XCHAR *Bolus_pages[] = {
//__psv__ const unsigned int *Bolus_pages[] __attribute__((space(psv))) = {
//"BOLUS",
//"BOLUS DELIVERY",
//"BOLUS COMPLETED",
//"BOLUS STOPPED",
//};

__psv__ const GFX_XCHAR Bolus_p0[] __attribute__((space(psv))) = {"BOLUS"};
__psv__ const GFX_XCHAR Bolus_p1[] __attribute__((space(psv))) = {"BOLUS DELIVERY"};
__psv__ const GFX_XCHAR Bolus_p2[] __attribute__((space(psv))) = {"BOLUS COMPLET"};
__psv__ const GFX_XCHAR Bolus_p3[] __attribute__((space(psv))) = {"BOLUS STOPPED"};

__psv__ const GFX_XCHAR *Bolus_pages[]= {
Bolus_p0,
Bolus_p1,
Bolus_p2,
Bolus_p3,
};
  
__psv__ GFX_XCHAR *pFLASH;

const __prog__ GFX_XCHAR __attribute__((space(prog))) Bolus_OBJ_STATICTEXT_5_text[] =
{
 "ATTENTION!!!\r\nBOLUS STOPPED\r\nDURING INJECTION"
};
const __prog__ GFX_XCHAR __attribute__((space(prog))) Bolus_OBJ_STATICTEXT_6_text[] =
{
 "THE PUMP WILL\r\nCONTINUE\r\nRUNNING"
};
const GFX_XCHAR Bolus_OBJ_BUTTON_3_text[] = "START BOLUS";
const GFX_XCHAR Bolus_OBJ_BUTTON_4_text[] = "STOP BOLUS";
const GFX_XCHAR Bolus_OBJ_BUTTON_5_text[] = "CONTINUE INFUSE";
const GFX_XCHAR Bolus_OBJ_BUTTON_6_text[] = "CONTINUE BOLUS";

const __prog__ GFX_XCHAR __attribute__((space(prog))) Bolus_OBJ_STATICTEXT_7_text[] = {
	"BOLUS OFF\r\nCONSULT\r\nA TECHNICIAN"
	};

#define Bolus_OBJ_STATICTEXT_0   0
#define Bolus_OBJ_STATICTEXT_1   1
#define Bolus_OBJ_STATICTEXT_2   2
#define Bolus_OBJ_STATICTEXT_3   3
#define Bolus_OBJ_STATICTEXT_4   4
#define Bolus_OBJ_STATICTEXT_5   5
#define Bolus_OBJ_STATICTEXT_6   6
#define Bolus_OBJ_STATICTEXT_7   7
#define Bolus_OBJ_BUTTON_0   8
#define Bolus_OBJ_BUTTON_1   9
#define Bolus_OBJ_BUTTON_2   10   
#define Bolus_OBJ_BUTTON_3   11
#define Bolus_OBJ_BUTTON_4   12
#define Bolus_OBJ_BUTTON_5   13
#define Bolus_OBJ_BUTTON_6   14
#define Bolus_OBJ_BUTTON_7   15
#define Bolus_OBJ_BUTTON_8   16
#define Bolus_OBJ_BUTTON_9   17
#define Bolus_OBJ_BUTTON_10   18
#define Bolus_OBJ_BUTTON_11   19
#define Bolus_OBJ_PICTURE_0		20
#define Bolus_OBJ_PROGRESSBAR_0	21
#define Bolus_OBJ_PICTURE_1		22

static CONTROL_MSG cMsg;
static float preinfused;
static float bolus_infused;
//static unsigned char occ_old;
//float rate_old;
static char	str1[30];
static char	str2[30];
static char	str3[30];
static GFX_GOL_OBJ_SCHEME* pScheme;	
static GFX_GOL_OBJ_SCHEME* pScheme1;
static unsigned char beep_cntr;
	 

void BolusShemes(void)
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
}

void CreateBolus(void)
{
	_prog_addressT p;
	int i;
	
	GFX_GOL_ObjectListFree();
	if (page_create == STOPPED_BOLUS)
	{
		GFX_ColorSet(RED);
		pScheme->Color0 = RED;
		pScheme->Color1 = RED;
		pScheme->CommonBkColor = RED;
	}
	else if(page_create == COMPLETED_BOLUS)
	{
		GFX_ColorSet(YELLOW_RUN);
		pScheme->Color0 = YELLOW_RUN;
		pScheme->Color1 = YELLOW_RUN;
		pScheme->CommonBkColor = YELLOW_RUN;

	}
	else
		GFX_ColorSet(BLUE_LIGHT);
	GFX_ScreenClear();
	
	memcpy(basicscheme, defscheme, sizeof(GFX_GOL_OBJ_SCHEME));
	basicscheme->Color1 = BLACK;
	basicscheme->TextColor0 = BLACK;
	basicscheme->CommonBkColor = WHITE;
	basicscheme->pFont = (void*)&Arial_Narrow_24;


//	occ_old = vol_para.occlusion_lmt;
	
	pFLASH = *(Bolus_pages+page_create);
	for(i=0;i<30;i++)
		*(str3+i) = *(pFLASH+i);

	GFX_GOL_StaticTextCreate(Bolus_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str3,GFX_ALIGN_LEFT,topbar);
//	GFX_GOL_StaticTextCreate(Bolus_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Bolus_pages[page_create],topbar);


//	GFX_GOL_PictureControlCreate(Bolus_OBJ_PICTURE_0, 209,0,239,30, GFX_GOL_PICTURECONTROL_DRAW_STATE, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)&Wait1, topbar);
	GFX_GOL_PictureControlCreate(Bolus_OBJ_PICTURE_1, 186,0,209,30, GFX_GOL_PICTURECONTROL_DRAW_STATE, IMAGE_NORMAL, getBatImg(batlevel), topbar);
	if(bolus_init.mode == 0)
	{
		_init_prog_address(p, Bolus_OBJ_STATICTEXT_7_text);
		_strncpy_p2d16(str_buf1,p,128);
 	 	GFX_GOL_StaticTextCreate(Bolus_OBJ_STATICTEXT_7,3,45,236,270,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str_buf1,GFX_ALIGN_CENTER,defscheme);
		GFX_GOL_ButtonCreate(Bolus_OBJ_BUTTON_2,5,277,60,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
		return;			 
	}
	beep_cntr = 8;


	switch (page_create)
	{
		case SET_BOLUS:
			bolus_infused	= 0.0;
			if(bolus_rate < 100.0)
				sprintf(str1,"RATE  = %.1f ml/hr",(double)bolus_rate);
			else
				sprintf(str1,"RATE  = %.0f ml/hr",(double)bolus_rate);
			GFX_GOL_ButtonCreate(Bolus_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(GFX_XCHAR*)str1,defscheme);
	
			if(bolus_volume < 100.0)
				sprintf(str2,"VTBI  = %.1f ml",(double)bolus_volume);
			else
				sprintf(str2,"VTBI  = %.0f ml",(double)bolus_volume);
			GFX_GOL_ButtonCreate(Bolus_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(GFX_XCHAR*)str2,defscheme);

			GFX_GOL_ButtonCreate(Bolus_OBJ_BUTTON_2,5,277,60,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
			GFX_GOL_ButtonCreate(Bolus_OBJ_BUTTON_3,115,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Bolus_OBJ_BUTTON_3_text,botbar);
		  break;
		case DELIVERED_BOLUS:
	 		if(bolus_rate < 100.0)
	 			sprintf(str1,"RATE  = %.1f ml/hr",(double)bolus_rate);
	 		else
	 			sprintf(str1,"RATE  = %.0f ml/hr",(double)bolus_rate);
		 	GFX_GOL_StaticTextCreate(Bolus_OBJ_STATICTEXT_1,3,48,236,86,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_LEFT,defscheme);

		 	if(bolus_volume < 100.0)
	 			sprintf(str2,"VTBI  = %.1f ml",(double)bolus_volume);
	 		else
	 			sprintf(str2,"VTBI  = %.0f ml",(double)bolus_volume);
		 	GFX_GOL_StaticTextCreate(Bolus_OBJ_STATICTEXT_2,3,94,236,132,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str2,GFX_ALIGN_LEFT,defscheme);
			
			GFX_GOL_ButtonCreate(Bolus_OBJ_BUTTON_4,5,277,116,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Bolus_OBJ_BUTTON_4_text,botbar);
			GFX_GOL_PictureControlCreate(Bolus_OBJ_PICTURE_0, 210,0,239,30, GFX_GOL_PICTURECONTROL_DRAW_STATE, IMAGE_NORMAL, getWaitImg(), topbar);
                        PbCreate( Bolus_OBJ_PROGRESSBAR_0, 10, 177, 229, 215, PB_DRAW, 0,(int)(bolus_volume*10.0),"ml",pScheme1);
			
			break;
		case COMPLETED_BOLUS:
			
			xTimerStart( xTimers[ 1 ], 0 );
		 	if(vol_para.infsd < 100.0)
		 		sprintf(str1,"BOLUS INFUSED\r\n%.1f ml",(double)(bolus_infused + (vol_para.infsd - preinfused)));               
		 	else
		 		sprintf(str1,"BOLUS INFUSED\r\n%.0f ml",(double)(bolus_infused + (vol_para.infsd - preinfused)));
		 	GFX_GOL_StaticTextCreate(Bolus_OBJ_STATICTEXT_3,3,100,236,168,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_CENTER,pScheme);
			_init_prog_address(p, Bolus_OBJ_STATICTEXT_6_text);
			_strncpy_p2d16(str_buf2,p,128);
			GFX_GOL_StaticTextCreate(Bolus_OBJ_STATICTEXT_6_text,10,220,229,313,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str_buf2,GFX_ALIGN_CENTER,basicscheme);
			 
//			GFX_GOL_ButtonCreate(Bolus_OBJ_BUTTON_5,46,277,196,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Bolus_OBJ_BUTTON_5_text,botbar);
			
			break;
		case STOPPED_BOLUS:
			xTimerStart( xTimers[ 1 ], 0 );
			_init_prog_address(p, Bolus_OBJ_STATICTEXT_5_text);
			_strncpy_p2d16(str_buf1,p,128);
			GFX_GOL_StaticTextCreate(Bolus_OBJ_STATICTEXT_5,0,55,239,170,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str_buf1,GFX_ALIGN_CENTER,pScheme);
    	PbCreate( Bolus_OBJ_PROGRESSBAR_0, 10, 177, 229, 215, PB_DRAW, (WORD)(10.0*(vol_para.infsd - preinfused)),(int)(bolus_volume*10.0),"ml",pScheme1);
			_init_prog_address(p, Bolus_OBJ_STATICTEXT_6_text);
			_strncpy_p2d16(str_buf2,p,128);
			GFX_GOL_StaticTextCreate(Bolus_OBJ_STATICTEXT_6_text,10,220,229,313,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str_buf2,GFX_ALIGN_CENTER,basicscheme);
			
//			GFX_GOL_ButtonCreate(Bolus_OBJ_BUTTON_5,46,277,196,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Bolus_OBJ_BUTTON_5_text,botbar);
//			GFX_GOL_ButtonCreate(Bolus_OBJ_BUTTON_6,46,234,196,270,5,BTN_DRAW,NULL,(GFX_XCHAR*)Bolus_OBJ_BUTTON_6_text,botbar);
			break;
		default:
			break;	 
	}


}
void CreatePrimitivesForBolus(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		GFX_ColorSet(BLUE_DARK);
//		while(!GFX_BarDraw(0,279,239,319));
}



/*********************************************************************
 * Function:        WORD msgBolus(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj)
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

WORD msgBolus(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
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
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
//					vol_para.occlusion_lmt = occ_old;
					GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
				}	
				break;
			case INP_KVO_ID:			
				if(pMsg->param2 == INP_SET)
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
//					vol_para.occlusion_lmt = occ_old;
					GDDSetScreen(CREATE_SCREEN_ALARM,KVO_ALRM_SCR,NULL);
				}	
				break;
			case INP_TIMER1_ID:			
				//Timer expired
				if(beep_cntr == 0)
				{
					if(vol_para.rate>200.0)
						occlusion_limit = 2;
					else
						occlusion_limit = vol_para.occlusion_lmt;
//					occlusion_limit = vol_para.occlusion_lmt;
					new_calc_rate(vol_para.rate);
					cMsg.cmd = MSG_CONTROL_START_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDPrevScreen();
				}
				else
				{
					if((beep_cntr < 7)&&(beep_cntr%2 == 0))
						Beep(700);
					beep_cntr--;
					xTimerStart( xTimers[ 1 ], 0 );
//				UpdateBolus();
				}
				break;
			default:
				break;
		}
		return 1;	
	}
	
	switch (GFX_GOL_ObjectIDGet(pObj)) {
		
		case Bolus_OBJ_BUTTON_0:
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
					/*Adjust bolus rate*/
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_BOLUS_RATE,NULL);
				}
			}	
			return 1;
		case Bolus_OBJ_BUTTON_1:
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
					/*Adjust bolus volume*/
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_BOLUS_VTBI,NULL);
				}
			}	
			return 1;
		case Bolus_OBJ_BUTTON_2:
			/*Back to prev screen*/
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
//				vol_para.occlusion_lmt = occ_old;
				GDDPrevScreen();
			}
			return 1;
		case Bolus_OBJ_BUTTON_3:
			/*Start bolus*/
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
//				cMsg.cmd = MSG_CONTROL_STOP_INFUS;
//				xQueueSend(hCONTROLQueue, &cMsg, 0);
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(DELIVERED_BOLUS);
				preinfused = vol_para.infsd;
//				occ_old = vol_para.occlusion_lmt;
//				vol_para.occlusion_lmt = 2;//occlus_lmt.high;
				occlusion_limit = 2;//occlus_lmt.high;
				new_calc_rate(vol_para.rate + bolus_rate);
			}
			return 1;
		case Bolus_OBJ_BUTTON_4:
			/*Stop bolus*/
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
				bolus_infused += vol_para.infsd - preinfused;
				cMsg.cmd = MSG_CONTROL_STOP_INFUS;
				xQueueSend(hCONTROLQueue, &cMsg, 0);
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(STOPPED_BOLUS);
			}
			return 1;
		case Bolus_OBJ_BUTTON_5:
			/*Continue infuse*/
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
//				vol_para.occlusion_lmt = occ_old;
//				vol_para.rate = rate_old;
//				new_calc_rate(vol_para.rate);
				if(vol_para.rate>200.0)
					occlusion_limit = 2;
				else
					occlusion_limit = vol_para.occlusion_lmt;
//				occlusion_limit = vol_para.occlusion_lmt;
				new_calc_rate(vol_para.rate);
				cMsg.cmd = MSG_CONTROL_START_INFUS;
				xQueueSend(hCONTROLQueue, &cMsg, 0);
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDPrevScreen();
			}
			return 1;
		case Bolus_OBJ_BUTTON_6:
			/*Continue bolus*/
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
				preinfused = vol_para.infsd;
				occlusion_limit = 2;//occlus_lmt.high;
				new_calc_rate(vol_para.rate + bolus_rate);
				cMsg.cmd = MSG_CONTROL_START_INFUS;
				xQueueSend(hCONTROLQueue, &cMsg, 0);
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(DELIVERED_BOLUS);
			}
			return 1;

#if 0		 
		case Bolus_OBJ_BUTTON_3:
			//Goto programms
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
				GDDSetScreen(CREATE_SCREEN_SETPROG,0,NULL);
			return 1;
		case Bolus_OBJ_BUTTON_4:
			//Goto drugs
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
				GDDSetScreen(CREATE_SCREEN_SETDRUG,0,NULL);
			return 1;
		case Bolus_OBJ_BUTTON_7:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
				//Prime and Goto priming
				memset((unsigned char)&vol_para,0,sizeof((unsigned char)&vol_para));
//				GDDSetScreen(CREATE_SCREEN_PRIME,0,NULL);
			}
			return 1;
		case Bolus_OBJ_BUTTON_8:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				//Goto options
				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
			}	
			return 1;
		case Bolus_OBJ_BUTTON_9:
		case Bolus_OBJ_BUTTON_11:
			//Goto please confirm
			return 1;
		
		case Bolus_OBJ_BUTTON_10:
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


void UpdateBolus(void)
{
	GFX_GOL_OBJ_HEADER* pObj;
//	static unsigned long lastClock;
//	unsigned int elapsedTime;
	
//	elapsedTime += clock_ms() - lastClock;
//	lastClock = clock_ms();
	if (page_display == DELIVERED_BOLUS)
	{
		pObj = GOLFindObject(Bolus_OBJ_PICTURE_0);
		if (pObj) {
			PictSetBitmap(pObj, getWaitImg());
			SetState((PICTURE*) pObj, DRAW_UPDATE);
		}
		pObj = GOLFindObject(Bolus_OBJ_PROGRESSBAR_0);
		if (pObj) {
			PbSetPos((PROGRESSBAR*) pObj, (WORD)(10.0*(bolus_infused + (vol_para.infsd - preinfused))));
			SetState((PROGRESSBAR*) pObj, DRAW_UPDATE);
		}

	  if((bolus_infused + (vol_para.infsd - preinfused)) > bolus_volume)
		{
			cMsg.cmd = MSG_CONTROL_STOP_INFUS;
			xQueueSend(hCONTROLQueue, &cMsg, 0);
 			if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
      			xTimerStop( xTimers[ 1 ], 0 );
			GDDShiftScreen(COMPLETED_BOLUS);
		}

	}
	pObj = GOLFindObject(Bolus_OBJ_PICTURE_1);
	if (pObj) {
		PictSetBitmap(pObj, getBatImg(batlevel));
		SetState((PICTURE*) pObj, DRAW_UPDATE);
	}

//	pObj = GOLFindObject(Bolus_OBJ_BUTTON_0);
//	if (pObj) {
//		SetState((BUTTON*) pObj, BTN_DRAW|BTN_DISABLED);
//	}

}



