/*****************************************************************************
 *****************************************************************************/
#define ERROR_PUB
#include "include.h"

// Strings
const XCHAR Error_OBJ_STATICTEXT_0_text[] = "ERROR";
const XCHAR Error_OBJ_STATICTEXT_1_text[] = "error description";


//const XCHAR Error_OBJ_BUTTON_0_text[] = "SET PROGRAM";
//const XCHAR Error_OBJ_BUTTON_1_text[] = "SET PARAMETER";
//const XCHAR Error_OBJ_BUTTON_2_text[] = "CHECKUP";
//const XCHAR Error_OBJ_BUTTON_3_text[] = "SET DATE";
//const XCHAR Error_OBJ_BUTTON_4_text[] = "DRUGS PROTOCOL";
//const XCHAR Error_OBJ_BUTTON_5_text[] = "FACTORY DEFAULT";
//const XCHAR Error_OBJ_BUTTON_6_text[] = "PRESS CALIBRATION";
//const XCHAR Error_OBJ_BUTTON_7_text[] = "EXIT";
//const XCHAR Error_OBJ_BUTTON_8_text[] = "AL";
//const XCHAR Error_OBJ_BUTTON_9_text[] = "AR";

#define Error_OBJ_STATICTEXT_0		  0
#define Error_OBJ_STATICTEXT_1		  1
#define Error_OBJ_DIGITALMETER_0   2
#define Error_OBJ_DIGITALMETER_1		3
#define Error_OBJ_DIGITALMETER_2   4
#define Error_OBJ_DIGITALMETER_3   5
#define Error_OBJ_BUTTON_4   6
#define Error_OBJ_BUTTON_5   7
#define Error_OBJ_BUTTON_6   8
#define Error_OBJ_BUTTON_7   9
#define Error_OBJ_BUTTON_8   10
#define Error_OBJ_BUTTON_9   11

void CreateError(void)
{
	GOL_SCHEME*	pScheme;
	XCHAR str[50] = "";

	GFX_GOL_ObjectListFree();
	GFX_ColorSet(BLUE_LIGHT);
	GFX_ScreenClear();




	pScheme = CreateScheme();
	memcpy(pScheme, defscheme, sizeof(GOL_SCHEME));
	pScheme->Color0 = RED;
	pScheme->Color1 = RED;
	pScheme->EmbossDkColor = YELLOW;
	pScheme->EmbossLtColor = YELLOW;

	switch(page_create)
	{
		case EEPROM_ERR:
			sprintf(str,"Eeprom error!!!");
			break;
		default:
			sprintf(str,"Uncknown error!!!");
			break;

				 
	}
	StCreate(Error_OBJ_STATICTEXT_1,10,80,230,130,ST_DRAW|ST_CENTER_ALIGN,str,pScheme);

//	DmCreate(Error_OBJ_DIGITALMETER_0, 150, 48, 236, 86, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
//	DmCreate(Error_OBJ_DIGITALMETER_1, 150, 94, 236, 132, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
//	DmCreate(Error_OBJ_DIGITALMETER_2, 150, 140, 236, 178, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
//	DmCreate(Error_OBJ_DIGITALMETER_3, 150, 186, 236, 224, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
	 
	GFX_GOL_ButtonCreate(Error_OBJ_BUTTON_7,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
//	GFX_GOL_ButtonCreate(Error_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,&Larrow,(XCHAR*)Test_OBJ_BUTTON_8_Error,botbar);
//	GFX_GOL_ButtonCreate(Error_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,&Rarrow,(XCHAR*)Test_OBJ_BUTTON_9_Error,botbar);

	StCreate(Error_OBJ_STATICTEXT_0,1,0,238,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Error_OBJ_STATICTEXT_0_text,topbar);

}

void CreatePrimitivesForError(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		GFX_ColorSet(BLUE_DARK);
//		while(!GFX_BarDraw(0,279,239,319));
}

void UpdateError(void)
{
//	OBJ_HEADER* pObj;

}


/*********************************************************************
 * Function:        WORD msgError(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
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

WORD msgError(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
	if(pObj == NULL)
	{
		
		return 1;	
	}
	
	switch (GFX_GOL_ObjectIDGet(pObj)) {
		case Error_OBJ_BUTTON_7:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
//				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
				GDDPrevScreen();

			}	
			return 1;
		case Error_OBJ_BUTTON_8:
		case Error_OBJ_BUTTON_9:
//			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
//				GDDDemoNextScreen();
//			}	
			return 1;
		
		default:
			break;
	}	

	return 1;	
} 















void SetError(unsigned char err, unsigned char type)
{
	static GRAPHICS_MSG msg;	 
	if(type == HW_ERRTYPE)
		/*Save err in eeprom*/ ;
	
	// any messages that we send will always be of this type
	msg.cmd = MSG_ERROR;
	msg.data.bVal[0] = err;
 	xQueueSend(hQVGAQueue, &msg, portMAX_DELAY);
}

unsigned int GetError(void)
{
	return 0;
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










