/*****************************************************************************
 *****************************************************************************/
#define PWRDOWN_PUB
#include "include.h"

// Strings
const GFX_XCHAR Pwrdown_OBJ_STATICTEXT_0_text[] = "POWER DOWN?";
const GFX_XCHAR Pwrdown_OBJ_STATICTEXT_1_text[] = "error description";
static GFX_XCHAR str[30];


//const GFX_XCHAR Pwrdown_OBJ_BUTTON_7_text[] = "EXIT";

#define Pwrdown_OBJ_STATICTEXT_0		  0
#define Pwrdown_OBJ_STATICTEXT_1		  1
#define Pwrdown_OBJ_DIGITALMETER_0   2
#define Pwrdown_OBJ_DIGITALMETER_1		3
#define Pwrdown_OBJ_DIGITALMETER_2   4
#define Pwrdown_OBJ_DIGITALMETER_3   5
#define Pwrdown_OBJ_BUTTON_4   6
//#define Pwrdown_OBJ_BUTTON_5   7
#define Pwrdown_OBJ_BUTTON_6   8
#define Pwrdown_OBJ_BUTTON_7   9
#define Pwrdown_OBJ_BUTTON_8   10
#define Pwrdown_OBJ_BUTTON_9   11

static unsigned char pwrdown_cnt;

static GFX_GOL_OBJ_SCHEME*	pScheme;
void PwrdownShemes(void)
{
	pScheme = CreateScheme();
	memcpy(pScheme, defscheme, sizeof(GFX_GOL_OBJ_SCHEME));
	pScheme->Color0 = RED;
	pScheme->TextColor0 = BLACK;
	pScheme->Color1 = RED;
	pScheme->EmbossDkColor = YELLOW;
	pScheme->EmbossLtColor = YELLOW;
}

void CreatePwrdown(void)
{
	xTimerStart( xTimers[ 1 ], 0 );
	pwrdown_cnt = 6;
	
	if(page_create == INP_NOBAT_ID)
	{
			PwrDownCmd();					//Power down command
			while(1);
	}

	GFX_GOL_ObjectListFree();
	GFX_ColorSet(BLUE_LIGHT);
	GFX_ScreenClear();


	sprintf(str,"HOLD BUTTON\r\n3 SECONDS");
	GFX_GOL_StaticTextCreate(Pwrdown_OBJ_STATICTEXT_1,38,55,192,145,GFX_GOL_STATICTEXT_DRAW_STATE,str,GFX_ALIGN_CENTER,pScheme);

//	DmCreate(Pwrdown_OBJ_DIGITALMETER_0, 150, 48, 236, 86, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
//	DmCreate(Pwrdown_OBJ_DIGITALMETER_1, 150, 94, 236, 132, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
//	DmCreate(Pwrdown_OBJ_DIGITALMETER_2, 150, 140, 236, 178, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
//	DmCreate(Pwrdown_OBJ_DIGITALMETER_3, 150, 186, 236, 224, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
	 
//	GFX_GOL_ButtonCreate(Pwrdown_OBJ_BUTTON_7,5,277,66,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Pwrdown_OBJ_BUTTON_7_text,botbar);
//	GFX_GOL_ButtonCreate(Pwrdown_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,&Larrow,(GFX_XCHAR*)Test_OBJ_BUTTON_8_Pwrdown,botbar);
//	GFX_GOL_ButtonCreate(Pwrdown_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,&Rarrow,(GFX_XCHAR*)Test_OBJ_BUTTON_9_Pwrdown,botbar);

	GFX_GOL_StaticTextCreate(Pwrdown_OBJ_STATICTEXT_0,1,0,238,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Pwrdown_OBJ_STATICTEXT_0_text,GFX_ALIGN_CENTER,topbar);

}

display_graf(unsigned char height)
{
	unsigned char i;
		SetLineType(0);
		SetLineThickness(0);
		GFX_ColorSet(BLUE_LIGHT);
		while(!GFX_BarDraw(20,299-9*15,219,309));
		GFX_ColorSet(GREEN);
		for(i = 0;i<height;i++ )
		{
//			while(!GFX_BarDraw(20,279,219,319));
			while(!GFX_BarDraw(20,299-i*15,219,309-i*15));
		}
	
}

void CreatePrimitivesForPwrdown(void){
	display_graf(6);
}

void UpdatePwrdown(void)
{
//	GFX_GOL_OBJ_HEADER* pObj;

}


/*********************************************************************
 * Function:        WORD msgPwrdown(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
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

WORD msgPwrdown(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_ONOFF_ID:			
				if(pMsg->param2 == INP_RELEASE){
						//Go to back to previous screen
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDPrevScreen();
				}
				break;
			case INP_TIMER1_ID:			
				//Timer expired
				xTimerStart( xTimers[ 1 ], 0 );
				if(pwrdown_cnt%2)
					Beep(20);
				pwrdown_cnt--;
				display_graf(pwrdown_cnt);
				if(pwrdown_cnt == 0)
				{
					PwrDownCmd();					//Power down command
					while(1);	
				}
				break;
			default:
				break;
		}
		return 1;	
	}
	
	switch (GFX_GOL_ObjectIDGet(pObj)) {
		case Pwrdown_OBJ_BUTTON_7:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
//				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDPrevScreen();

			}	
			return 1;
		case Pwrdown_OBJ_BUTTON_8:
		case Pwrdown_OBJ_BUTTON_9:
//			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
//				GDDDemoNextScreen();
//			}	
			return 1;
		
		default:
			break;
	}	

	return 1;	
} 

