/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_CALIB_PUB
#include "include.h"

// Strings
const XCHAR Calib_OBJ_STATICTEXT_0_text[] = "CALIBRATION";

const XCHAR Calib_OBJ_BUTTON_0_text[] = "SET PROGRAM";
const XCHAR Calib_OBJ_BUTTON_1_text[] = "SET PARAMETER";
const XCHAR Calib_OBJ_BUTTON_2_text[] = "CHECKUP";
const XCHAR Calib_OBJ_BUTTON_3_text[] = "SET DATE";
const XCHAR Calib_OBJ_BUTTON_4_text[] = "DRUGS PROTOCOL";
const XCHAR Calib_OBJ_BUTTON_5_text[] = "FACTORY DEFAULT";
const XCHAR Calib_OBJ_BUTTON_6_text[] = "PRESS CALIBRATION";
const XCHAR Calib_OBJ_BUTTON_7_text[] = "EXIT";
const XCHAR Calib_OBJ_BUTTON_8_text[] = "AL";
const XCHAR Calib_OBJ_BUTTON_9_text[] = "AR";


#define Calib_OBJ_STATICTEXT_0   0
#define Calib_OBJ_BUTTON_0   1
#define Calib_OBJ_BUTTON_1   2
#define Calib_OBJ_BUTTON_2   3
#define Calib_OBJ_BUTTON_3   4
#define Calib_OBJ_BUTTON_4   5
#define Calib_OBJ_BUTTON_5   6
#define Calib_OBJ_BUTTON_6   7
#define Calib_OBJ_BUTTON_7   8
#define Calib_OBJ_BUTTON_8   9
#define Calib_OBJ_BUTTON_9   10
#define Calib_OBJ_BUTTON_10   11
#define Calib_OBJ_BUTTON_11   12




void CreateCalib(void)
{
	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();
	
	if(page_create == 0)
	{
		BtnCreate(Calib_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW,NULL,(XCHAR*)Calib_OBJ_BUTTON_0_text,defscheme);
		BtnCreate(Calib_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW,NULL,(XCHAR*)Calib_OBJ_BUTTON_1_text,defscheme);
		BtnCreate(Calib_OBJ_BUTTON_2,3,140,236,178,10,BTN_DRAW,NULL,(XCHAR*)Calib_OBJ_BUTTON_2_text,defscheme);
		BtnCreate(Calib_OBJ_BUTTON_3,3,186,236,224,10,BTN_DRAW,NULL,(XCHAR*)Calib_OBJ_BUTTON_3_text,defscheme);
		BtnCreate(Calib_OBJ_BUTTON_4,3,232,236,270,10,BTN_DRAW,NULL,(XCHAR*)Calib_OBJ_BUTTON_4_text,defscheme);
		BtnCreate(Calib_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,(void *)&Rarrow,/*(XCHAR*)Calib_OBJ_BUTTON_9_text*/NULL,botbar);
	
	}
	else
	{
		BtnCreate(Calib_OBJ_BUTTON_5,3,48,236,86,10,BTN_DRAW,NULL,(XCHAR*)Calib_OBJ_BUTTON_5_text,defscheme);
		BtnCreate(Calib_OBJ_BUTTON_6,3,94,236,132,10,BTN_DRAW,NULL,(XCHAR*)Calib_OBJ_BUTTON_6_text,defscheme);
		BtnCreate(Calib_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,(void *)&Larrow,/*(XCHAR*)Calib_OBJ_BUTTON_8_text*/NULL,botbar);
	}
 
	BtnCreate(Calib_OBJ_BUTTON_7,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)Calib_OBJ_BUTTON_7_text,botbar);

	StCreate(Calib_OBJ_STATICTEXT_0,1,0,238,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Calib_OBJ_STATICTEXT_0_text,topbar);

}
void CreatePrimitivesForCalib(void){
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

WORD msgCalib(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
	if(pObj == NULL)
	{
		
		return 1;	
	}
	
	switch (GetObjID(pObj)) {
		
		case Calib_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) {
				GDDPrevScreen();
			}	
			return 1;
		case Calib_OBJ_BUTTON_8:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, &Larrow_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, &Larrow);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
					GDDShiftScreen(0); //1st screen
			}	
			return 1;
			
		case Calib_OBJ_BUTTON_9:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, &Rarrow_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, &Rarrow);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
					GDDShiftScreen(1); //2nd screen
			}	
			return 1;
		case Calib_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_SETPROG,0,NULL);
			}	
			return 1;
		case Calib_OBJ_BUTTON_1:
		case Calib_OBJ_BUTTON_2:
		case Calib_OBJ_BUTTON_3:
		case Calib_OBJ_BUTTON_4:
//			if (objMsg == BTN_MSG_RELEASED) {
//				GDDDemoNextScreen();
//			}	
			return 1;
		case Calib_OBJ_BUTTON_5:
			if (objMsg == BTN_MSG_RELEASED) {
			
				GDDShiftScreen(0); // Refresh screen
			}	
			return 1;
		
		
		case Calib_OBJ_BUTTON_6:
//			if (objMsg == BTN_MSG_RELEASED) {
//				GDDDemoNextScreen();
//			}	
			return 1;
		default:
			break;
	}	

	return 1;	
} 
