/*****************************************************************************
 *****************************************************************************/
#define ALARM_PUB
#include "include.h"

// Strings

//const XCHAR Alarm_OBJ_BUTTON_0_text[] = "EXIT";
const XCHAR Alarm_OBJ_BUTTON_1_text[] = "RESTART INFUSION";
const XCHAR Alarm_OBJ_BUTTON_2_text[] = "MUTE";

#define Alarm_OBJ_STATICTEXT_0		0
#define Alarm_OBJ_STATICTEXT_1		1
#define Alarm_OBJ_STATICTEXT_2		2
#define Alarm_OBJ_STATICTEXT_3		3
#define Alarm_OBJ_DIGITALMETER_0	4
#define Alarm_OBJ_DIGITALMETER_1	5
#define Alarm_OBJ_DIGITALMETER_2	6
#define Alarm_OBJ_DIGITALMETER_3	7
#define Alarm_OBJ_BUTTON_0			8
#define Alarm_OBJ_BUTTON_1			9
#define Alarm_OBJ_BUTTON_2			10
#define Alarm_OBJ_PICTURE_0			11
#define Alarm_OBJ_PICTURE_1			12
#define Alarm_OBJ_PICTURE_2			13

static unsigned char time_halfsec;
static unsigned char mute;
static WORD  bk_color;
static GOL_SCHEME*	pScheme_alarm1;
static GOL_SCHEME*	pScheme_alarm2;
static GOL_SCHEME*	pScheme_alarm3;
static CONTROL_MSG cMsg;
static unsigned char hrdwr_err;
static unsigned long batt_live_time;


void AlarmShemes(void)
{
	pScheme_alarm1 = GOLCreateScheme();
	memcpy(pScheme_alarm1, defscheme, sizeof(GOL_SCHEME));
	pScheme_alarm1->CommonBkColor = RED;
	pScheme_alarm1->TextColor0 = BLACK;
	pScheme_alarm1->Color1 = RED;
	pScheme_alarm1->pFont = (void*)&Arial_Narrow_36;
	
	pScheme_alarm2 = GOLCreateScheme();
	memcpy(pScheme_alarm2, pScheme_alarm1, sizeof(GOL_SCHEME));
	pScheme_alarm2->pFont = (void*)&Arial_Narrow_Bold_18;

	pScheme_alarm3 = GOLCreateScheme();
	memcpy(pScheme_alarm3, defscheme, sizeof(GOL_SCHEME));
	pScheme_alarm3->CommonBkColor = WHITE;
	pScheme_alarm3->TextColor0 = BLACK;
	pScheme_alarm3->Color1 = YELLOW;
	pScheme_alarm3->pFont = (void*)&Arial_Narrow_Bold_18;
}          

void CreateAlarm(void)
{
	GOL_SCHEME*	pScheme;
	_prog_addressT p;
	XCHAR *p_add;

	if(page_create != ACFAIL_ALRM_SCR)
		Beep(500);
	
	time_halfsec = 0;
	mute = 0;
	xTimerStart( xTimers[ 1 ], 0 );

	GOLFree();
	bk_color = Alarm_Specs[page_create].bckgr_color;
	SetColor(bk_color);
	ClearDevice();

	pScheme_alarm1->CommonBkColor = bk_color;
	pScheme_alarm1->Color1 = bk_color;
	
	pScheme_alarm2->CommonBkColor = bk_color;
	pScheme_alarm2->Color1 = bk_color;
	
	/*Build title*/
	
	if(Alarm_Specs[page_create].title != NULL)
		StCreate(Alarm_OBJ_STATICTEXT_0,0,0,239,30,ST_DRAW|ST_CENTER_ALIGN,Alarm_Specs[page_create].title,topbar);
	/*Build alarm name */
	if(Alarm_Specs[page_create].name != NULL)
		StCreate(Alarm_OBJ_STATICTEXT_1,10,38,230,115,ST_DRAW|ST_CENTER_ALIGN,Alarm_Specs[page_create].name,pScheme_alarm1);
	
	if(page_create == ACFAIL_ALRM_SCR)
	{
		if(Alarm_Specs[page_create].descr != NULL)
		{
//			p_add = Alarm_Specs[page_create].descr;
//			_init_prog_address(p, p_add);
//			_strncpy_p2d16(str_buf1,p,128);
//			StCreate(Alarm_OBJ_STATICTEXT_2,10,150,140,200,ST_DRAW,str_buf1,pScheme_alarm2);
			StCreate(Alarm_OBJ_STATICTEXT_2,10,150,140,200,ST_DRAW,Alarm_Specs[page_create].descr,pScheme_alarm2);
		}
		PictCreate(Alarm_OBJ_PICTURE_2,162,150,195,273,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&BBat_img,pScheme_alarm2);
		/*Build battery time meter */
		
		batt_live_time = /*6h max*/(6L*3600L *(unsigned long)batlevel)/10L;
		strftime(gStr1, 100, "%HHr : %MMin", localtime(&batt_live_time));
		memcpy(basicscheme, defscheme, sizeof(GOL_SCHEME));
		basicscheme->CommonBkColor = GREEN;
		basicscheme->TextColor0 = BLACK;
		basicscheme->Color1 = YELLOW;
		basicscheme->pFont = (void*)&Arial_Narrow_26;

		StCreate(Alarm_OBJ_STATICTEXT_3,10,207,140,240,ST_DRAW,gStr1,basicscheme);
	
	}
	
	else if (page_create == KVO_ALRM_SCR)
	{
		/*Build alarm description */
		if(Alarm_Specs[page_create].descr != NULL)
			StCreate(Alarm_OBJ_STATICTEXT_2,10,116,230,200,ST_DRAW,Alarm_Specs[page_create].descr,pScheme_alarm2);
		
		
		/*Build alarm solution */
		if(Alarm_Specs[page_create].solut != NULL)
		{
			sprintf(gStr1,"%s %dml/hr",Alarm_Specs[page_create].solut,(int)vol_para.rate);
			StCreate(Alarm_OBJ_STATICTEXT_3,10,207,230,267,ST_DRAW,gStr1,pScheme_alarm3);
		}
		
	}
	else
	{
		/*Build alarm description */
		if(Alarm_Specs[page_create].descr != NULL)
			StCreate(Alarm_OBJ_STATICTEXT_2,10,116,230,200,ST_DRAW,Alarm_Specs[page_create].descr,pScheme_alarm2);
		/*Build alarm solution */
		if(Alarm_Specs[page_create].solut != NULL)
			StCreate(Alarm_OBJ_STATICTEXT_3,10,207,230,267,ST_DRAW,Alarm_Specs[page_create].solut,pScheme_alarm3);
	}
	if(Alarm_Specs[page_create].btns & RESTART_BTN)
	{
		if(page_create == AIR_ALRM_SCR)
			BtnCreate(Alarm_OBJ_BUTTON_1,7,277,160,313,5,BTN_DRAW|BTN_DISABLED ,NULL,(XCHAR*)Alarm_OBJ_BUTTON_1_text,botbar);
		else
			BtnCreate(Alarm_OBJ_BUTTON_1,7,277,160,313,5,BTN_DRAW ,NULL,(XCHAR*)Alarm_OBJ_BUTTON_1_text,botbar);
	}
	if(Alarm_Specs[page_create].btns & MUTE_BTN)	 
		BtnCreate(Alarm_OBJ_BUTTON_2,175,277,230,313,5,BTN_DRAW,NULL,(XCHAR*)Alarm_OBJ_BUTTON_2_text,botbar);
	if(Alarm_Specs[page_create].btns & EXIT_BTN)	 
		BtnCreate(Alarm_OBJ_BUTTON_0,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);

	if(Alarm_Specs[page_create].btns & WAIT_ICON)	 
		PictCreate(Alarm_OBJ_PICTURE_0, 210,0,239,30, PICT_DRAW, IMAGE_NORMAL, getWaitImg(), topbar);
	if(Alarm_Specs[page_create].btns & BAT_ICON)	 
		PictCreate(Alarm_OBJ_PICTURE_1, 186,0,209,30, PICT_DRAW, IMAGE_NORMAL, getBatImg(batlevel), topbar);
}
int bar_level_tmp;

void CreatePrimitivesForAlarm(void){

	if(page_create == ACFAIL_ALRM_SCR)
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(WHITE);
		while(!Bar(164,154,193,271));
		 
		SetColor(GREEN);
		if(batlevel == 10)
			bar_level_tmp = 154L;
		else
			bar_level_tmp = 271L - ((int)batlevel*(271L-154L))/10L;
		
		while(!Bar(164,bar_level_tmp,193,271));
	}

}

void UpdateAlarm(void)
{
	OBJ_HEADER* pObj;
	pObj = GOLFindObject(Alarm_OBJ_PICTURE_0);
	if (pObj) {
		PictSetBitmap(pObj, getWaitImg());
		SetState((PICTURE*) pObj, DRAW_UPDATE);
	}
	pObj = GOLFindObject(Alarm_OBJ_PICTURE_1);
	if (pObj) {
		PictSetBitmap(pObj, getBatImg(batlevel));
		SetState((PICTURE*) pObj, DRAW_UPDATE);
	}
	if(page_display == ACFAIL_ALRM_SCR)
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(WHITE);
		while(!Bar(164,154,193,271));
		SetColor(GREEN);
//		SetColor(GREEN);
		if(batlevel == 10)
			bar_level_tmp = 154L;
		else
			bar_level_tmp = 271L - ((int)batlevel*(271L-154L))/10L;
		while(!Bar(164,bar_level_tmp,193,271));
	}
	else	if(page_display == AIR_ALRM_SCR)
	{
		if(GetDoorState() == 1)
		{
			pObj = GOLFindObject(Alarm_OBJ_BUTTON_1);
			if (pObj) 
			{
				if(GetState(pObj, BTN_DISABLED))
				{
					ClrState(pObj, BTN_DISABLED);
					SetState((BUTTON*) pObj, BTN_DRAW);
				}
			}
		}
	}
}


/*********************************************************************
 * Function:        WORD msgAlarm(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
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
WORD msgAlarm(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_STOP_ID:			   
				if(pMsg->param2 == INP_SET)
				{
					alarm_st = 0;
					if(page_display == AIR_ALRM_SCR)
						air_alarm = FALSE;
					else if(page_display == MOTOR_ALRM_SCR)
						motor_alarm = FALSE;
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
					xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
				}	
				break;
			case INP_BATLOW_ID:			 
			case INP_NOAC_ID:			 
				alarm_st = 0;
				break;
			case INP_KVO_ID:			
				if(pMsg->param2 == INP_SET)
				{
					clearBit( alarm_st, Alarm_Specs[page_display].statbit_forclear);
				}	
				break;
			case INP_TIMER1_ID:			 
				//Timer expired
				UpdateAlarm();
				time_halfsec++;
				if(Alarm_Specs[page_display].tout != 0)
				{
        				if((time_halfsec >= Alarm_Specs[page_display].tout*2) || \
                                                ( page_display == KVO_ALRM_SCR&& testBit(kvo_stat, KVO_STAT)==0))
					{
						alarm_st = 0;
                                                xTimerStop( xTimers[ 1 ], 0 );
							GDDPrevScreen();
							break;
						}
				}
				else				 
				{
						if(mute)
							mute--;
						if(time_halfsec >= 5)
						{
							if(mute == 0)
							{
								Beep(500);
							}
							time_halfsec = 0;
						}
				}
				xTimerStart( xTimers[ 1 ], 0 );
				break;
			default:
				break;
		}
		return 1;	
	}
	
	switch (GetObjID(pObj)) {
		case Alarm_OBJ_BUTTON_0:
		case Alarm_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_RELEASED) {
//				clearBit( alarm_st, Alarm_Specs[page_display].statbit_forclear);
				alarm_st = 0;				
				if(page_display == AIR_ALRM_SCR)
					air_alarm = FALSE;
				else if(page_display == MOTOR_ALRM_SCR)
					motor_alarm = FALSE;
   				xTimerStop( xTimers[ 1 ], 0 );
//				if(page_display == DOOR_ALRM_SCR)
//					GDDPrevScreen();
//				else
					GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
			}	  
			return 1;
		case Alarm_OBJ_BUTTON_2:
			if (objMsg == BTN_MSG_RELEASED) {
				mute = 120;
			}	
			return 1;
		
		default:
			break;
	}	

	return 1;	
} 

void SetError(unsigned char err, unsigned char type)
{
	static GRAPHICS_MSG msg;	 
	if(type == HARWARE_ALRM_SCR)
		hrdwr_err |= 1 << err; /*Save err in eeprom*/ 
	
	// any messages that we send will always be of this type
	msg.cmd = MSG_ERROR;
	msg.data.bVal[0] = type;
 	xQueueSend(hQVGAQueue, &msg, portMAX_DELAY);
}

unsigned char GetError(void)
{
	return hrdwr_err;
}
void ClearError(void)
{
	hrdwr_err = 0;
}

void CriticalError(unsigned char *str)
{
//	lcd_clear();

//	select_font((FONT_INFO *)&arialNarrow10ptFontInfo);
//	draw_text( 0, LCD_TXTLINE1, (uchar*)"ERROR!!", LCD_PIXEL_ON,0);
//	draw_text( 0, LCD_TXTLINE3, str, LCD_PIXEL_ON,0);
//	RTclock.timer = 1000; //1sec
	
	while(1)
	{
 //		if(get_evnt_queue() == WE_ONOFF)
 //				wait_off();
 //		if(RTclock.timer == 0)
 //		{
			Beep(2000);
// 			beep(30,1);
 //			RTclock.timer = 1000; //1sec
 //		}
	}
}
#if 1
//  Create Error Flash (Blue Screen)
void CreateErr(char* string)
{
	// Blue Screen Error
	SetColor(119);
	ClearDevice();
	SetColor(-1);
// Flash Error Message
	if(string == NULL)
		{OutTextXY(0, 0, "Runtime Error.");}
	else{OutTextXY(0,0, string);}
}
#endif

