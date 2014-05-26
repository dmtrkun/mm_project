/*****************************************************************************
*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_CLEAR_PUB
#include "include.h"
#include "Graphics Resources\new.h"


// Strings
XCHAR Clear_OBJ_STATICTEXT_0_text[] = "CLEAR SETUP?";
XCHAR Clear_OBJ_STATICTEXT_1_text[] = "NEW INFUSION";
XCHAR Clear_OBJ_BUTTON_7_text[] = "CLEAR";
const XCHAR Clear_OBJ_BUTTON_8_text[] = "OPTIONS";
const XCHAR Clear_OBJ_BUTTON_9_text[] = "NO";
//const XCHAR Clear_OBJ_BUTTON_10_text[] = "EXIT";
const XCHAR Clear_OBJ_BUTTON_11_text[] = "OK";

PARA_SPECS_t Step_Para_Specs = {"STEP",		(void*)&vol_para.prog_stepsnum,				PARA_CHAR,	TYPE_GEN,		NULL,			0};
PARA_SPECS_t Rate_Para_Specs = {"RATE",		(void*)&vol_para.prog_steps[0].rate,	PARA_FLOAT,	TYPE_RATE,		NULL,			0};
PARA_SPECS_t Vol_Para_Specs =  {"VOLUME",	(void*)&vol_para.prog_steps[0].vol,		PARA_FLOAT,	TYPE_VOLUME,	NULL,			0};




#define Clear_OBJ_STATICTEXT_0   0
#define Clear_OBJ_STATICTEXT_1   1
#define Clear_OBJ_BUTTON_0   2
#define Clear_OBJ_BUTTON_1   3
#define Clear_OBJ_BUTTON_2   4
#define Clear_OBJ_BUTTON_3   5
#define Clear_OBJ_BUTTON_4   6
#define Clear_OBJ_BUTTON_5   7
#define Clear_OBJ_BUTTON_6   8
#define Clear_OBJ_BUTTON_7   9
#define Clear_OBJ_BUTTON_8   10
#define Clear_OBJ_BUTTON_9   11
#define Clear_OBJ_BUTTON_10   12
#define Clear_OBJ_BUTTON_11   13
#define Clear_OBJ_PICTURE_0		14

WORD msgClear_prog1(WORD objMsg, OBJ_HEADER* pObj, int objID);
WORD msgClear_prog2(WORD objMsg, OBJ_HEADER* pObj, int objID);
WORD msgClear_prog3(WORD objMsg, OBJ_HEADER* pObj, int objID);
WORD msgClear_prog4(WORD objMsg, OBJ_HEADER* pObj, int objID);
WORD msgClear_prog5(WORD objMsg, OBJ_HEADER* pObj, int objID);
void CreateClear_prog1(void);
void CreateClear_prog2(void);
void CreateClear_prog3(void);
void CreateClear_prog4(void);
void CreateClear_prog5(void);
static char	str1[30];
static char	str2[30];
static char	str3[30];
char page_nums; 


void CreateClear(void)
{
	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();
	xTimerStart( xTimers[ 1 ], 0 );

	switch(prog_num)
	{
		default:
		case 0:
			CreateClear_prog1();
			page_nums = 2;
			break;
		case 1:
			CreateClear_prog2();
			page_nums = 2;
			break;
		case 2:
			CreateClear_prog3();
			page_nums = 4;
			break;
		case 3:
			CreateClear_prog4();
			page_nums = 4;
			break;
		case 4:
		case 5:
			CreateClear_prog5();
			page_nums = 2;
			break;
			
	}

	if(page_create < (page_nums/2))
	{
		BtnCreate(Clear_OBJ_BUTTON_7,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)Clear_OBJ_BUTTON_7_text,botbar);
		BtnCreate(Clear_OBJ_BUTTON_9,174,277,235,313,5,BTN_DRAW,NULL,(XCHAR*)Clear_OBJ_BUTTON_9_text,botbar);
		StCreate(Clear_OBJ_STATICTEXT_0,0,0,239,30,ST_DRAW,(XCHAR*)Clear_OBJ_STATICTEXT_0_text,topbar);
	}
	else
	{
		BtnCreate(Clear_OBJ_BUTTON_10,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
		BtnCreate(Clear_OBJ_BUTTON_11,174,277,235,313,5,BTN_DRAW,NULL,(XCHAR*)Clear_OBJ_BUTTON_11_text,botbar);
		StCreate(Clear_OBJ_STATICTEXT_0,0,0,239,30,ST_DRAW,(XCHAR*)Clear_OBJ_STATICTEXT_1_text,topbar);
	}
	BtnCreate(Clear_OBJ_BUTTON_8,74,277,166,313,5,BTN_DRAW,NULL,(XCHAR*)Clear_OBJ_BUTTON_8_text,botbar);
	PictCreate(Clear_OBJ_PICTURE_0,215,0,239,30, PICT_DRAW, IMAGE_NORMAL, getBatImg(batlevel), topbar);

}
void CreatePrimitivesForClear(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		SetColor(BLUE_DARK);
//		while(!Bar(0,279,239,319));
}

void UpdateClear(void)
{
	OBJ_HEADER* pObj;
	
	pObj = GOLFindObject(Clear_OBJ_PICTURE_0);
	if (pObj) {
		PictSetBitmap(pObj, getBatImg(batlevel));
		SetState((PICTURE*) pObj, DRAW_UPDATE);
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

WORD msgClear(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
int objID;	
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_TIMER1_ID:			
				//Timer expired
				xTimerStart( xTimers[ 1 ], 0 );
				UpdateClear();
				break;
			default:
				break;
		}
		return 1;	
	}

	objID = GetObjID(pObj);

	switch(prog_num)
	{
		default:
		case 0:
			if(msgClear_prog1(objMsg, pObj, objID) == 1)
				return 1;
			break;
		case 1:
			if(msgClear_prog2(objMsg, pObj, objID) == 1)
				return 1;
			break;
		case 2:
			if(msgClear_prog3(objMsg, pObj, objID) == 1)
				return 1;
			break;
		case 3:
			if(msgClear_prog4(objMsg, pObj, objID) == 1)
				return 1;
			break;
		case 4:
		case 5:
			if(msgClear_prog5(objMsg, pObj, objID) == 1)
				return 1;
			break;
	}
	switch(objID)
	{
		case Clear_OBJ_BUTTON_3:
			//Goto programms
			if (objMsg == BTN_MSG_RELEASED){ 
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_SETPROG,0,NULL);
			}
			return 1;
		case Clear_OBJ_BUTTON_4:
			//Goto drugs
			if (objMsg == BTN_MSG_RELEASED) {
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_SETDRUG,0,NULL);
			}
			return 1;
		case Clear_OBJ_BUTTON_8:
			if (objMsg == BTN_MSG_RELEASED) {
				//Goto options
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				pswrd = 0;
				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
			}	
			return 1;
		default:
			break;	
	}
	
	return 1;	
} 

WORD msgClear_prog1(WORD objMsg, OBJ_HEADER* pObj, int objID)
{
	 
	switch (objID) {
		case Clear_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap(pObj, (char*)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap(pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED)
				{
					page_display = 1;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_RATE,NULL);
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					page_display = 1;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_VTBI,NULL);
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_2:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					page_display = 1;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_INFUSED,NULL);
				}
			}	
			return 1;
#if 0		
		case Clear_OBJ_BUTTON_3:
			//Goto programms
			if (objMsg == BTN_MSG_RELEASED){ 
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_SETPROG,0,NULL);
			}
			return 1;
		case Clear_OBJ_BUTTON_4:
			//Goto drugs
			if (objMsg == BTN_MSG_RELEASED) {
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_SETDRUG,0,NULL);
			}
			return 1;
#endif		
		case Clear_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) 
			{
				//Clear and Goto priming
				ClearParams();
				vol_para.rate = max_rate;
				vol_para.vtbi = 600.0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_PRIME,0,NULL);
			}
			return 1;
#if 0		
		case Clear_OBJ_BUTTON_8:
			if (objMsg == BTN_MSG_RELEASED) {
				//Goto options
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
			}	
			return 1;
#endif		
		case Clear_OBJ_BUTTON_9:
		case Clear_OBJ_BUTTON_11:
			if (objMsg == BTN_MSG_RELEASED) {
			//Goto please confirm
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				
				if((vol_para.rate > 0.01))//&&(vol_para.vtbi > 0.1))
					GDDSetScreen(CREATE_SCREEN_CONFIRM,0,NULL);
				else
					GDDSetScreen(CREATE_SCREEN_ALARM,RATEZERO_ALRM_SCR,NULL);
			}	  
			return 1;
		
		case Clear_OBJ_BUTTON_10:
			if (objMsg == BTN_MSG_RELEASED) {
				//EXIT - Goto Clear setup
				page_display = 0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(0);
//				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
			}	
			return 1;
		default:
			break;
	}	
	return 0;
}
WORD msgClear_prog2(WORD objMsg, OBJ_HEADER* pObj, int objID)
{
	 
	switch (objID) {
		case Clear_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap(pObj, (char*)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap(pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED)
				{
					page_display = 1;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_VTBI,NULL);
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					page_display = 1;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_INFTIME,NULL);
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_2:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					page_display = 1;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_INFUSED,NULL);
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) 
			{
				//Clear and Goto priming
				ClearParams();
				estim_infusetime = 0L;
				vol_para.rate = max_rate;
				vol_para.vtbi = 600.0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_PRIME,0,NULL);
			}
			return 1;
		case Clear_OBJ_BUTTON_9:
		case Clear_OBJ_BUTTON_11:
			if (objMsg == BTN_MSG_RELEASED) {
			//Goto please confirm
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				if((estim_infusetime > 0))//&&(vol_para.vtbi > 0.1))
					GDDSetScreen(CREATE_SCREEN_CONFIRM,0,NULL);
				else
					GDDSetScreen(CREATE_SCREEN_ALARM,RATEZERO_ALRM_SCR,NULL);
			}	  
			return 1;
		
		case Clear_OBJ_BUTTON_10:
			if (objMsg == BTN_MSG_RELEASED) {
				//EXIT - Goto Clear setup
				page_display = 0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(0);
//				GDDSetScreen(CREATE_SCREEN_OPTIONS,0,NULL);
			}	
			return 1;
		default:
			break;
	}	
	return 0;
}






WORD msgClear_prog3(WORD objMsg, OBJ_HEADER* pObj, int objID)
{
	 
	switch (objID) {
		case Clear_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap(pObj, (char*)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap(pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED)
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					if((page_display == 0)||(page_display == 2))
					{
						GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_BAGVOL,NULL);
						page_display = 2;
					}
					else
					{
						GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_INTERVALTIME,NULL);
						page_display = 3;
					}
				
				}
			}	
			return 1;
		
		case Clear_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					if((page_display == 0)||(page_display == 2))
					{
						GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_DOSEVOL,NULL);
						page_display = 2;
					}
					else
					{
						GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_KVORATE,NULL);
						page_display = 3;
					}
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_2:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_DOSERATE,NULL);
					page_display = 2;
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) 
			{
				//Clear and Goto priming
				ClearParams();
				vol_para.rate = max_rate;
				vol_para.vtbi = 600.0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_PRIME,0,NULL);
			}
			return 1;
		case Clear_OBJ_BUTTON_9: //NO
		case Clear_OBJ_BUTTON_11://OK
			if (objMsg == BTN_MSG_RELEASED) {
			//Goto please confirm
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				page_display++;
				if(page_display < (objID == Clear_OBJ_BUTTON_9 ? 2 : 4))
					GDDShiftScreen(page_display);
				else if((vol_para.dose_rate > 0.1)&&(vol_para.bag_vol > 0.1)&&(vol_para.dose_vol > 0.1)&&(vol_para.dose_interval != 0))
					GDDSetScreen(CREATE_SCREEN_CONFIRM,0,NULL);
				else
					GDDSetScreen(CREATE_SCREEN_ALARM,RATEZERO_ALRM_SCR,NULL);
			}	  
			return 1;
		
		case Clear_OBJ_BUTTON_10:
			if (objMsg == BTN_MSG_RELEASED) {
				//EXIT - Goto Clear setup
				page_display = 0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(0);
			}	
			return 1;
		default:
			break;
	}	
	return 0;
}

WORD msgClear_prog4(WORD objMsg, OBJ_HEADER* pObj, int objID)
{
	 
	switch (objID) {
		case Clear_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap(pObj, (char*)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap(pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED)
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					if((page_display == 0)||(page_display == 2))
					{
						GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_BAGVOL,NULL);
						page_display = 2;
					}
					else
					{
						GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_INTERVALTIME,NULL);
						page_display = 3;
					}
				
				}
			}	
			return 1;
		
		case Clear_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					if((page_display == 0)||(page_display == 2))
					{
						GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_DOSEVOL,NULL);
						page_display = 2;
					}
					else
					{
						GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_KVORATE,NULL);
						page_display = 3;
					}
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_2:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_DOSETIME,NULL);
					page_display = 2;
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) 
			{
				//Clear and Goto priming
				ClearParams();
				vol_para.rate = max_rate;
				vol_para.vtbi = 600.0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_PRIME,0,NULL);
			}
			return 1;
		case Clear_OBJ_BUTTON_9: //NO
		case Clear_OBJ_BUTTON_11://OK
			if (objMsg == BTN_MSG_RELEASED) {
			//Goto please confirm
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				page_display++;
				if(page_display < (objID == Clear_OBJ_BUTTON_9 ? 2 : 4))
					GDDShiftScreen(page_display);
				else if((vol_para.dose_time != 0)&&(vol_para.bag_vol > 0.1)&&(vol_para.dose_vol > 0.1)&&(vol_para.dose_interval != 0))
					GDDSetScreen(CREATE_SCREEN_CONFIRM,0,NULL);
				else
					GDDSetScreen(CREATE_SCREEN_ALARM,RATEZERO_ALRM_SCR,NULL);
			}	  
			return 1;
		
		case Clear_OBJ_BUTTON_10:
			if (objMsg == BTN_MSG_RELEASED) {
				//EXIT - Goto Clear setup
				page_display = 0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(0);
			}	
			return 1;
		default:
			break;
	}	
	return 0;
}



WORD msgClear_prog5(WORD objMsg, OBJ_HEADER* pObj, int objID)
{
unsigned char i;
		 
	switch (objID) {
		case Clear_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap(pObj, (char*)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap(pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED)
				{
					page_display = 1;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );

					if(vol_para.prog_stepsnum < 25)
						vol_para.prog_stepsnum++;
					Step_Para_Specs.pset_var = (void*)&vol_para.prog_stepsnum ;
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_INT,(void*)&Step_Para_Specs);
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					page_display = 1;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					Rate_Para_Specs.pset_var = (void*)&vol_para.prog_steps[vol_para.prog_stepsnum-1].rate;
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_RATE,(void*)&Rate_Para_Specs);
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_2:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, (char *)&Param_btn);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					page_display = 1;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					Vol_Para_Specs.pset_var =  (void*)&vol_para.prog_steps[vol_para.prog_stepsnum-1].vol;
					GDDSetScreen(CREATE_SCREEN_ADJUST,ADJUST_VTBI,(void*)&Vol_Para_Specs);
				}
			}	
			return 1;
		case Clear_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) 
			{
				//Clear and Goto priming
				ClearParams();
				vol_para.rate = max_rate;
				vol_para.vtbi = 600.0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_PRIME,0,NULL);
			}
			return 1;
		case Clear_OBJ_BUTTON_9:
		case Clear_OBJ_BUTTON_11:
			if (objMsg == BTN_MSG_RELEASED) {
			//Goto please confirm
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				
				for(i = 0; i<vol_para.prog_stepsnum;i++)
				{
					if((vol_para.prog_steps[i].rate < 0.1)||(vol_para.prog_steps[i].vol < 0.1))
						GDDSetScreen(CREATE_SCREEN_ALARM,RATEZERO_ALRM_SCR,NULL);
				}
				GDDSetScreen(CREATE_SCREEN_CONFIRM,0,NULL);
			}	  
			return 1;
		
		case Clear_OBJ_BUTTON_10:
			if (objMsg == BTN_MSG_RELEASED) {
				//EXIT - Goto Clear setup
				page_display = 0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     		xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(0);
			}	
			return 1;
		default:
			break;
	}	
	return 0;
}




void CreateClear_prog1(void)
{
	if(vol_para.rate < 100.0)
		sprintf(str1,"RATE  = %.1fml/hr",(double)vol_para.rate);
	else
		sprintf(str1,"RATE  = %.0fml/hr",(double)vol_para.rate);
	BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str1,defscheme);
	
	
	if(no_limit == 1)
		sprintf(str2,"NO LIMIT");
	else if(vol_para.vtbi < 100.0)
		sprintf(str2,"VTBI  = %.1fml",(double)vol_para.vtbi);
	else
		sprintf(str2,"VTBI  = %.0fml",(double)vol_para.vtbi);
	BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str2,defscheme);
	
	
	BtnCreate(Clear_OBJ_BUTTON_3,6,193,115,264,10,BTN_DRAW,(void *)prog_images[prog_num],NULL,defscheme);
	BtnCreate(Clear_OBJ_BUTTON_4,131,203,235,263,1,BTN_DRAW, (void *)drug_images[vol_para.drug_type],NULL,defscheme);

	 
	if((page_create == 0) && (vol_para.infsd > 0.01))
	{
		if(vol_para.infsd < 100.0)
			sprintf(str3,"INFUSED = %.1fml",(double)vol_para.infsd);
		else
			sprintf(str3,"INFUSED = %.0fml",(double)vol_para.infsd);
		BtnCreate(Clear_OBJ_BUTTON_2,3,140,236,178,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str3,defscheme);
	}
	else
	{
	}
}

void CreateClear_prog2(void)
{
	if(no_limit == 1)
		sprintf(str1,"NO LIMIT");
	else
	{
		sprintf(str1,"VTBI  = ");
		ValToStr(TYPE_VOLUME,0, vol_para.vtbi,NULL, str1 + strlen(str1));
	}
	
	BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str1,defscheme);
	
	sprintf(str2,"TIME  = ");
	ValToStr(TYPE_TIMEINTERVAL,estim_infusetime, 0,NULL, str2 + strlen(str2));
	sprintf(str2 + strlen(str2)," Hr:Min");
	BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str2,defscheme);
	
	BtnCreate(Clear_OBJ_BUTTON_3,6,193,115,264,10,BTN_DRAW,(void *)prog_images[prog_num],NULL,defscheme);
	BtnCreate(Clear_OBJ_BUTTON_4,131,203,235,263,1,BTN_DRAW, (void *)drug_images[vol_para.drug_type],NULL,defscheme);
	 
	if((page_create == 0) && (vol_para.infsd > 0.01))
	{
		if(vol_para.infsd < 100.0)
			sprintf(str3,"INFUSED = %.1fml",(double)vol_para.infsd);
		else
			sprintf(str3,"INFUSED = %.0fml",(double)vol_para.infsd);
		BtnCreate(Clear_OBJ_BUTTON_2,3,140,236,178,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str3,defscheme);
	}
	else
	{
	}
}

void CreateClear_prog3(void)
{
	 
	if((page_create == 0)||(page_create == 2))
	{
		sprintf(str1,"BAG VOL = ");
		ValToStr(TYPE_VOLUME,0, vol_para.bag_vol,NULL, str1 + strlen(str1));
		BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str1,defscheme);
	
		sprintf(str2,"DOSE VOL = ");
		ValToStr(TYPE_VOLUME, 0, vol_para.dose_vol, NULL, str2 + strlen(str2));
		BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str2,defscheme);
		
		sprintf(str3,"D/RATE = ");
		ValToStr(TYPE_RATE,0, vol_para.dose_rate,NULL, str3 + strlen(str3));
		BtnCreate(Clear_OBJ_BUTTON_2,3,140,236,178,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str3,defscheme);
		
		BtnCreate(Clear_OBJ_BUTTON_3,6,193,115,264,10,BTN_DRAW,(void *)prog_images[prog_num],NULL,defscheme);
		BtnCreate(Clear_OBJ_BUTTON_4,131,203,235,263,1,BTN_DRAW, (void *)drug_images[vol_para.drug_type],NULL,defscheme);
	}
	else
	{
		sprintf(str1,"T.INTERVAL = ");
		ValToStr(TYPE_TIMEINTERVAL,vol_para.dose_interval, 0,NULL, str1 + strlen(str1));
//		sprintf(str1 + strlen(str1)," Hr:Min");
		BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str1,defscheme);
	
		sprintf(str2,"KVO = ");
		ValToStr(TYPE_RATE,0, vol_para.kvo_rate,NULL, str2 + strlen(str2));
		BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str2,defscheme);
	}
}
void CreateClear_prog4(void)
{
	 
	if((page_create == 0)||(page_create == 2))
	{
		sprintf(str1,"BAG VOL = ");
		ValToStr(TYPE_VOLUME,0, vol_para.bag_vol,NULL, str1 + strlen(str1));
		BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str1,defscheme);
	
		sprintf(str2,"DOSE VOL = ");
		ValToStr(TYPE_VOLUME, 0, vol_para.dose_vol, NULL, str2 + strlen(str2));
		BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str2,defscheme);
		
		sprintf(str3,"DOSE TIME = ");
		ValToStr(TYPE_TIMEINTERVAL,vol_para.dose_time, 0,NULL, str3 + strlen(str3));
		BtnCreate(Clear_OBJ_BUTTON_2,3,140,236,178,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str3,defscheme);
		
		BtnCreate(Clear_OBJ_BUTTON_3,6,193,115,264,10,BTN_DRAW,(void *)prog_images[prog_num],NULL,defscheme);
		BtnCreate(Clear_OBJ_BUTTON_4,131,203,235,263,1,BTN_DRAW, (void *)drug_images[vol_para.drug_type],NULL,defscheme);
	}
	else
	{
		sprintf(str1,"T.INTERVAL = ");
		ValToStr(TYPE_TIMEINTERVAL,vol_para.dose_interval, 0,NULL, str1 + strlen(str1));
//		sprintf(str1 + strlen(str1)," Hr:Min");
		BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str1,defscheme);
	
		sprintf(str2,"KVO = ");
		ValToStr(TYPE_RATE,0, vol_para.kvo_rate,NULL, str2 + strlen(str2));
		BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str2,defscheme);
	}
}
#if 0
void CreateClear_prog4(void)
{
	 
	if((page_create == 0)||(page_create == 2))
	{
		sprintf(str1,"BAG VOL = ");
		ValToStr(TYPE_VOLUME,0, vol_para.bag_vol,NULL, str1 + strlen(str1));
		BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str1,defscheme);
	
		sprintf(str2,"DOSE VOL = ");
		ValToStr(TYPE_VOLUME, 0, vol_para.dose_vol, NULL, str2 + strlen(str2));
		BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str2,defscheme);
		
		sprintf(str3,"DOSE TIME = ");
		ValToStr(TYPE_TIMEINTERVAL,vol_para.dose_time, 0,NULL, str3 + strlen(str3));
		sprintf(str3 + strlen(str3)," Hr:Min");
		BtnCreate(Clear_OBJ_BUTTON_2,3,140,236,178,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str3,defscheme);
		
		BtnCreate(Clear_OBJ_BUTTON_3,6,193,115,264,10,BTN_DRAW,(void *)prog_images[prog_num],NULL,defscheme);
		BtnCreate(Clear_OBJ_BUTTON_4,131,203,235,263,1,BTN_DRAW, (void *)drug_images[vol_para.drug_type],NULL,defscheme);
	}
	else
	{
		sprintf(str1,"INTERVAL TIME = ");
		ValToStr(TYPE_TIMEINTERVAL,vol_para.dose_interval, 0,NULL, str2 + strlen(str2));
		sprintf(str2 + strlen(str2)," Hr:Min");
		BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str1,defscheme);
	
		sprintf(str2,"KVO RATE = ");
		ValToStr(TYPE_RATE,0, vol_para.kvo_rate,NULL, str2 + strlen(str2));
		BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str2,defscheme);
	}
}
#endif

void CreateClear_prog5(void)
{
	
	sprintf(str1,"STEP  = %d",vol_para.prog_stepsnum);
	BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str1,defscheme);
	
	if(vol_para.rate < 100.0)
		sprintf(str2,"RATE  = %.1fml/hr",(double)vol_para.prog_steps[vol_para.prog_stepsnum-1].rate);
	else
		sprintf(str2,"RATE  = %.0fml/hr",(double)vol_para.prog_steps[vol_para.prog_stepsnum-1].rate);
	BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str2,defscheme);
	
	BtnCreate(Clear_OBJ_BUTTON_3,6,193,115,264,10,BTN_DRAW,(void *)prog_images[prog_num],NULL,defscheme);
	BtnCreate(Clear_OBJ_BUTTON_4,131,203,235,263,1,BTN_DRAW, (void *)drug_images[vol_para.drug_type],NULL,defscheme);
	 
	if(vol_para.infsd < 100.0)
		sprintf(str3,"VOLUME = %.1fml",(double)vol_para.prog_steps[vol_para.prog_stepsnum-1].vol);
	else
		sprintf(str3,"VOLUME = %.0fml",(double)vol_para.prog_steps[vol_para.prog_stepsnum-1].vol);
	BtnCreate(Clear_OBJ_BUTTON_2,3,140,236,178,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(XCHAR*)str3,defscheme);
}


