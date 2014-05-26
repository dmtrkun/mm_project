/*****************************************************************************
 *****************************************************************************/
#define PWRDOWN_PUB
#include "include.h"

// Strings
const XCHAR Pwrdown_OBJ_STATICTEXT_0_text[] = "POWER DOWN?";
const XCHAR Pwrdown_OBJ_STATICTEXT_1_text[] = "error description";
static XCHAR str[30];


//const XCHAR Pwrdown_OBJ_BUTTON_7_text[] = "EXIT";

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

static GOL_SCHEME*	pScheme;
void PwrdownShemes(void)
{
	pScheme = GOLCreateScheme();
	memcpy(pScheme, defscheme, sizeof(GOL_SCHEME));
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

	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();


	sprintf(str,"HOLD BUTTON\r\n3 SECONDS");
	StCreate(Pwrdown_OBJ_STATICTEXT_1,38,55,192,145,ST_DRAW|ST_CENTER_ALIGN,str,pScheme);

//	DmCreate(Pwrdown_OBJ_DIGITALMETER_0, 150, 48, 236, 86, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
//	DmCreate(Pwrdown_OBJ_DIGITALMETER_1, 150, 94, 236, 132, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
//	DmCreate(Pwrdown_OBJ_DIGITALMETER_2, 150, 140, 236, 178, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
//	DmCreate(Pwrdown_OBJ_DIGITALMETER_3, 150, 186, 236, 224, DM_DRAW | DM_FRAME | DM_CENTER_ALIGN, 0, 4, 0, botbar);
	 
//	BtnCreate(Pwrdown_OBJ_BUTTON_7,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)Pwrdown_OBJ_BUTTON_7_text,botbar);
//	BtnCreate(Pwrdown_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,&Larrow,(XCHAR*)Test_OBJ_BUTTON_8_Pwrdown,botbar);
//	BtnCreate(Pwrdown_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,&Rarrow,(XCHAR*)Test_OBJ_BUTTON_9_Pwrdown,botbar);

	StCreate(Pwrdown_OBJ_STATICTEXT_0,1,0,238,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Pwrdown_OBJ_STATICTEXT_0_text,topbar);

}

display_graf(unsigned char height)
{
	unsigned char i;
		SetLineType(0);
		SetLineThickness(0);
		SetColor(BLUE_LIGHT);
		while(!Bar(20,299-9*15,219,309));
		SetColor(GREEN);
		for(i = 0;i<height;i++ )
		{
//			while(!Bar(20,279,219,319));
			while(!Bar(20,299-i*15,219,309-i*15));
		}
	
}

void CreatePrimitivesForPwrdown(void){
	display_graf(6);
}

void UpdatePwrdown(void)
{
//	OBJ_HEADER* pObj;

}


/*********************************************************************
 * Function:        WORD msgPwrdown(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
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

WORD msgPwrdown(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
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
	
	switch (GetObjID(pObj)) {
		case Pwrdown_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) {
//				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDPrevScreen();

			}	
			return 1;
		case Pwrdown_OBJ_BUTTON_8:
		case Pwrdown_OBJ_BUTTON_9:
//			if (objMsg == BTN_MSG_RELEASED) {
//				GDDDemoNextScreen();
//			}	
			return 1;
		
		default:
			break;
	}	

	return 1;	
} 

