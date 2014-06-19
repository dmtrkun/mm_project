/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define INTRO_PUB
#include "include.h"

// Strings
const GFX_XCHAR Intro_OBJ_STATICTEXT_3_1text[] = "PLEASE WAIT";

const __prog__ GFX_XCHAR __attribute__((space(prog))) VERSION_txt[] = VERSION_TXT;//   "Ver 1.8 rel. ";
const __prog__ GFX_XCHAR __attribute__((space(prog))) REL_txt[] = " rel. ";
const __prog__ GFX_XCHAR __attribute__((space(prog))) DATE_txt[] = __DATE__;
//const __prog__ GFX_XCHAR __attribute__((space(prog))) GFX_XCHAR TIME_txt[] = __TIME__;

//const GFX_XCHAR Intro_OBJ_STATICTEXT_3_2text[] = "SEND THE PUMP\r\n  TO TECHNICIAN\r\n  FOR CALIBRATION";
const GFX_XCHAR Intro_OBJ_STATICTEXT_3_3text[] = "ATTENTION !!";

const __prog__ GFX_XCHAR __attribute__((space(prog))) Intro_OBJ_STATICTEXT_3_2text[] = {
	"SEND THE PUMP\r\n  TO TECHNICIAN\r\n  FOR CALIBRATION"
	};


//const GFX_XCHAR Intro_OBJ_STATICTEXT_4_2text[] = "VOLUMETRIC PUMP";
//const GFX_XCHAR Intro_OBJ_STATICTEXT_5_2text[] = "VL667";

#define Intro_OBJ_STATICTEXT_3_1	 50
#define Intro_OBJ_STATICTEXT_3_2   51
#define Intro_OBJ_STATICTEXT_4_2   52
#define Intro_OBJ_STATICTEXT_5_2   53
#define Intro_OBJ_PICTURE_0				 54
#define Intro_OBJ_PICTURE_1				 55
#define Intro_OBJ_STATICTEXT_5_3   56
#define Intro_OBJ_STATICTEXT_5_4   57

static unsigned char keypad_ready = 0;
static unsigned char timer_ready = 0;
static unsigned char intro_first_time = 0;


void CreateIntro(void)
{
	_prog_addressT p;
	intro_first_time++;
	
//	timer_ready = 0;
	Beep(1000);
//	if(timer_ready)
//			GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
	GFX_GOL_ObjectListFree();
	if(page_create == 0)
	{
		GFX_ColorSet(GREEN);
		GFX_ScreenClear();
		xTimerStart( xTimers[ 0 ], 0 );
		memcpy(basicscheme, botbar, sizeof(GFX_GOL_OBJ_SCHEME));
		basicscheme->CommonBkColor = BLUE_DARK;
	
		GFX_GOL_StaticTextCreate(Intro_OBJ_STATICTEXT_3_1,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Intro_OBJ_STATICTEXT_3_1text,GFX_ALIGN_CENTER,topbar);

		GFX_GOL_PictureControlCreate(Intro_OBJ_PICTURE_0, 10,60,10+Intro_WIDTH,60+Intro_HEIGHT, PICT_DRAW, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)&Intro, green_sch);
		GFX_GOL_PictureControlCreate(Intro_OBJ_PICTURE_1, 210,0,239,30, PICT_DRAW, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)&Wait1, topbar);

                
                _init_prog_address(p, VERSION_txt);
		_strncpy_p2d16(str_buf1,p,strlen(VERSION_txt));
                _init_prog_address(p, REL_txt);
		_strncpy_p2d16(str_buf1 + strlen(VERSION_txt),p,strlen(REL_txt));
                _init_prog_address(p, DATE_txt);
		_strncpy_p2d16(str_buf1 + strlen(VERSION_txt) + strlen(REL_txt),p,strlen(DATE_txt));
		GFX_GOL_StaticTextCreate(Intro_OBJ_STATICTEXT_5_3,37,289,210,309,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str_buf1,GFX_ALIGN_RIGHT,basicscheme);
	}	
	else
	{
//		keypad_ready = 1;
		GFX_ColorSet(BLUE_LIGHT);
		GFX_ScreenClear();
		xTimerStart( xTimers[ 0], 0 );
		
		GFX_GOL_StaticTextCreate(Intro_OBJ_STATICTEXT_3_1,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Intro_OBJ_STATICTEXT_3_1text,GFX_ALIGN_CENTER,topbar);
		
		GFX_GOL_PictureControlCreate(Intro_OBJ_PICTURE_1, 210,0,239,30, PICT_DRAW, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)&Wait1, topbar);
	
		_init_prog_address(p, Intro_OBJ_STATICTEXT_3_2text);
		_strncpy_p2d16(str_buf1,p,128);
		GFX_GOL_StaticTextCreate(Intro_OBJ_STATICTEXT_5_3,9,45,229,269,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)str_buf1,GFX_ALIGN_CENTER,defscheme);
	
	}

}

void CreatePrimitivesForIntro(void){
//		SetLineType(0);
//		SetLineThickness(0);
		GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);
		GFX_ColorSet(BLUE_DARK);
		while(!GFX_BarDraw(0,279,239,319));
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

WORD msgIntro(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
	
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_ONOFF_ID:			   
				if(pMsg->param2 == INP_RELEASE)
				{
					//if timer is over Go to back to main screen
					keypad_ready = 1;
					if(timer_ready == 1)
					{
						if( xTimerIsTimerActive( xTimers[ 0 ] ) != pdFALSE ) 
		   	     			xTimerStop( xTimers[ 0 ], 0 );
						
						if((page_display == 0) && (mktime(&rtc_time) - calib_time >= 31536000L /*365*24*60*60*/))
							GDDShiftScreen(1);
						else
						{
//							if(GetDoorState())
//								GDDSetScreen(CREATE_SCREEN_ALARM,DOOR_ALRM_SCR,NULL);
//							else
								GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
						}
					}
				}
				break;
			case INP_TIMER0_ID:			
				//Timer of introduction is expired
				timer_ready = 1;
				if(keypad_ready == 1 || intro_first_time > 1)
				{
					if( xTimerIsTimerActive( xTimers[ 0 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 0 ], 0 );
					if((page_display == 0) && (mktime(&rtc_time) - calib_time >= 31536000L /*365*24*60*60*/))
						GDDShiftScreen(1);
					else
					{
//						if(GetDoorState())
//							GDDSetScreen(CREATE_SCREEN_ALARM,DOOR_ALRM_SCR,NULL);
//						else
							GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
					}
				}
				break;
			default:
				break;
		}
		return 1;	
	}
	
	switch (GFX_GOL_ObjectIDGet(pObj)) {
		case 33:
//			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
//			}	
			return 1;
		default:
			break;
	}	

	return 1;	
} 

void UpdateIntro(void)
{
	GFX_GOL_OBJ_HEADER* pObj;
	pObj = GFX_GOL_ObjectFind(Intro_OBJ_PICTURE_1);
	if (pObj) {
		GFX_GOL_PictureControlImageSet(pObj, getWaitImg());
                GFX_GOL_ObjectStateSet((PICTURE*) pObj, DRAW_UPDATE);

	}

//	pObj = GFX_GOL_ObjectFind(Intro_OBJ_PICTURE_0);
//	if (pObj) {
//		GFX_GOL_PictureControlImageSet(pObj, (GFX_RESOURCE_HDR *)&Intro);
//		GFX_GOL_ObjectStateSet((PICTURE*) pObj, DRAW_UPDATE);
//	}
}



