/*****************************************************************************
*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_SETPROG_PUB
#include "include.h"

// Strings
const XCHAR Setprog_OBJ_STATICTEXT_0_text[] = "SET PROGRAMM";

#if 0
const XCHAR Setprog_OBJ_BUTTON_0_text[] = "SET PROGRAM";
const XCHAR Setprog_OBJ_BUTTON_1_text[] = "SET PARAMETER";
const XCHAR Setprog_OBJ_BUTTON_2_text[] = "CHECKUP";
const XCHAR Setprog_OBJ_BUTTON_3_text[] = "SET DATE";
const XCHAR Setprog_OBJ_BUTTON_4_text[] = "DRUGS PROTOCOL";
const XCHAR Setprog_OBJ_BUTTON_5_text[] = "FACTORY DEFAULT";
const XCHAR Setprog_OBJ_BUTTON_6_text[] = "PRESS CALIBRATION";
#endif
//const XCHAR Setprog_OBJ_BUTTON_7_text[] = "EXIT";
//const XCHAR Setprog_OBJ_BUTTON_8_text[] = "AL";
//const XCHAR Setprog_OBJ_BUTTON_9_text[] = "AR";

#define Setprog_OBJ_BUTTON_0   0
#define Setprog_OBJ_BUTTON_1   1
#define Setprog_OBJ_BUTTON_2   2
#define Setprog_OBJ_BUTTON_3   3
#define Setprog_OBJ_BUTTON_4   4
#define Setprog_OBJ_BUTTON_5   5
#define Setprog_OBJ_BUTTON_6   6
#define Setprog_OBJ_BUTTON_7   7
#define Setprog_OBJ_BUTTON_8   8
#define Setprog_OBJ_BUTTON_9   9
#define Setprog_OBJ_STATICTEXT_0   1

GFX_IMAGE_HEADER const* prog_images[6] = {
&prog_ContROV,
&prog_ContVOT,
&prog_IntROV,
&prog_IntVOT,
&prog_Step,
&prog_PCA
};


void CreateSetprog(void)
{
	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();

	BtnCreate(Setprog_OBJ_BUTTON_0,7,46,116,117,10,BTN_DRAW,(void*)prog_images[0],NULL,defscheme);
	BtnCreate(Setprog_OBJ_BUTTON_1,125,46,234,117,10,BTN_DRAW,(void*)prog_images[1],NULL,defscheme);
	BtnCreate(Setprog_OBJ_BUTTON_2,7,124,116,195,10,BTN_DRAW,(void*)prog_images[2],NULL,defscheme);
	BtnCreate(Setprog_OBJ_BUTTON_3,125,124,234,195,10,BTN_DRAW,(void*)prog_images[3],NULL,defscheme);
	BtnCreate(Setprog_OBJ_BUTTON_4,7,201,116,272,10,BTN_DRAW,(void*)prog_images[4],NULL,defscheme);
	BtnCreate(Setprog_OBJ_BUTTON_5,125,201,234,272,10,BTN_DRAW,(void*)prog_images[5],NULL,defscheme);

	 
	BtnCreate(Setprog_OBJ_BUTTON_7,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
//	BtnCreate(Setprog_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,NULL,(XCHAR*)Setprog_OBJ_BUTTON_8_text,botbar);
//	BtnCreate(Setprog_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,NULL,(XCHAR*)Setprog_OBJ_BUTTON_9_text,botbar);


	StCreate(Setprog_OBJ_STATICTEXT_0,1,0,238,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Setprog_OBJ_STATICTEXT_0_text,topbar);

}
void CreatePrimitivesForSetprog(void){
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

WORD msgSetprog(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
//	OBJ_HEADER* pSetPoint;
//	SHORT dialVal;
	if(pObj == NULL)
	{

		switch(pMsg->param1)
		{
			case INP_TIMER1_ID:			
				//Timer expired
//				xTimerStart( xTimers[ 1 ], 0 );
//				UpdateConfirm();
				break;
			default:
				break;
		}
		return 1;	
	}
	
	switch (GetObjID(pObj)) {
		
		case Setprog_OBJ_BUTTON_0:
		case Setprog_OBJ_BUTTON_1:
		case Setprog_OBJ_BUTTON_2:
		case Setprog_OBJ_BUTTON_3:
		case Setprog_OBJ_BUTTON_4:
		case Setprog_OBJ_BUTTON_5:
			if (objMsg == BTN_MSG_RELEASED) {
				prog_num = GetObjID(pObj);
				GDDPrevScreen();
			}	
			return 1;
		case Setprog_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) {
				GDDPrevScreen();
			}	
			return 1;
		
		default:
			break;
	}	

	return 1;	
} 
