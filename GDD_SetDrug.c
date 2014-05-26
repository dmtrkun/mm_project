/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_SETDRUG_PUB
#include "include.h"

// Strings
const XCHAR Setdrug_OBJ_STATICTEXT_0_text[] = "DRUG NAME";

#if 0
const XCHAR Setdrug_OBJ_BUTTON_0_text[] = "SET PROGRAM";
const XCHAR Setdrug_OBJ_BUTTON_1_text[] = "SET PARAMETER";
const XCHAR Setdrug_OBJ_BUTTON_2_text[] = "CHECKUP";
const XCHAR Setdrug_OBJ_BUTTON_3_text[] = "SET DATE";
const XCHAR Setdrug_OBJ_BUTTON_4_text[] = "DRUGS PROTOCOL";
const XCHAR Setdrug_OBJ_BUTTON_5_text[] = "FACTORY DEFAULT";
const XCHAR Setdrug_OBJ_BUTTON_6_text[] = "PRESS CALIBRATION";
#endif
//const XCHAR Setdrug_OBJ_BUTTON_7_text[] = "EXIT";
const XCHAR Setdrug_OBJ_BUTTON_8_text[] = "AL";
const XCHAR Setdrug_OBJ_BUTTON_9_text[] = "AR";

#define Setdrug_OBJ_BUTTON_0   		0
#define Setdrug_OBJ_BUTTON_1  		1
#define Setdrug_OBJ_BUTTON_2   		2
#define Setdrug_OBJ_BUTTON_3   		3
#define Setdrug_OBJ_BUTTON_4   		4
#define Setdrug_OBJ_BUTTON_5   		5
#define Setdrug_OBJ_BUTTON_6   		6
#define Setdrug_OBJ_BUTTON_7   		7
#define Setdrug_OBJ_BUTTON_8   		8
#define Setdrug_OBJ_BUTTON_9   		9
#define Setdrug_OBJ_STATICTEXT_0	10

GFX_IMAGE_HEADER const* drug_images[6] = {
&drug_NoName,
&drug_Morph_Midaz,
&drug_Remitentanil,
&drug_Midazolam,
&drug_Adrenaline,
&drug_Noradrenaline,
};


void CreateSetdrug(void)
{
	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();

	BtnCreate(Setdrug_OBJ_BUTTON_0,7,		46,		116,	117,	10,BTN_DRAW,(void*)drug_images[0],NULL,defscheme);
	BtnCreate(Setdrug_OBJ_BUTTON_1,125,	46,		234,	117,	10,BTN_DRAW,(void*)drug_images[1],NULL,defscheme);
	BtnCreate(Setdrug_OBJ_BUTTON_2,7,		124,	116,	195,	10,BTN_DRAW,(void*)drug_images[2],NULL,defscheme);
	BtnCreate(Setdrug_OBJ_BUTTON_3,125,	124,	234,	195,	10,BTN_DRAW,(void*)drug_images[3],NULL,defscheme);
	BtnCreate(Setdrug_OBJ_BUTTON_4,7,		201,	116,	272,	10,BTN_DRAW,(void*)drug_images[4],NULL,defscheme);
	BtnCreate(Setdrug_OBJ_BUTTON_5,125,	201,	234,	272,	10,BTN_DRAW,(void*)drug_images[5],NULL,defscheme);

	 
	BtnCreate(Setdrug_OBJ_BUTTON_7,5,		277,	66,		313,	5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
//	BtnCreate(Setdrug_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,NULL,(XCHAR*)Setdrug_OBJ_BUTTON_8_text,botbar);
//	BtnCreate(Setdrug_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,NULL,(XCHAR*)Setdrug_OBJ_BUTTON_9_text,botbar);


	StCreate(Setdrug_OBJ_STATICTEXT_0,1,0,238,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Setdrug_OBJ_STATICTEXT_0_text,topbar);

}
void CreatePrimitivesForSetdrug(void){
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

WORD msgSetdrug(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
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
		case Setdrug_OBJ_BUTTON_0:
		case Setdrug_OBJ_BUTTON_1:
		case Setdrug_OBJ_BUTTON_2:
		case Setdrug_OBJ_BUTTON_3:
		case Setdrug_OBJ_BUTTON_4:
		case Setdrug_OBJ_BUTTON_5:
			if (objMsg == BTN_MSG_RELEASED) {
					vol_para.drug_type = GetObjID(pObj);
					GDDPrevScreen();
			}	
			return 1;
		case Setdrug_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) {
				GDDPrevScreen();
			}	
			return 1;
		
		default:
			break;
	}	

	return 1;	
} 
