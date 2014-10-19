/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_SETDRUG_PUB
#include "include.h"

// Strings
const GFX_XCHAR Setdrug_OBJ_STATICTEXT_0_text[] = "DRUG NAME";

#if 0
const GFX_XCHAR Setdrug_OBJ_BUTTON_0_text[] = "SET PROGRAM";
const GFX_XCHAR Setdrug_OBJ_BUTTON_1_text[] = "SET PARAMETER";
const GFX_XCHAR Setdrug_OBJ_BUTTON_2_text[] = "CHECKUP";
const GFX_XCHAR Setdrug_OBJ_BUTTON_3_text[] = "SET DATE";
const GFX_XCHAR Setdrug_OBJ_BUTTON_4_text[] = "DRUGS PROTOCOL";
const GFX_XCHAR Setdrug_OBJ_BUTTON_5_text[] = "FACTORY DEFAULT";
const GFX_XCHAR Setdrug_OBJ_BUTTON_6_text[] = "PRESS CALIBRATION";
#endif
//const GFX_XCHAR Setdrug_OBJ_BUTTON_7_text[] = "EXIT";
const GFX_XCHAR Setdrug_OBJ_BUTTON_8_text[] = "AL";
const GFX_XCHAR Setdrug_OBJ_BUTTON_9_text[] = "AR";

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

GFX_RESOURCE_HDR const* drug_images[6] = {
&drug_NoName,
&drug_Morph_Midaz,
&drug_Remitentanil,
&drug_Midazolam,
&drug_Adrenaline,
&drug_Noradrenaline,
};

#if 0 //todo
void CreateSetdrug(void)
{
	GFX_GOL_ObjectListFree();
	GFX_ColorSet(BLUE_LIGHT);
	GFX_ScreenClear();

	GFX_GOL_ButtonCreate(Setdrug_OBJ_BUTTON_0,7,		46,		116,	117,	10,BTN_DRAW,(void*)drug_images[0],NULL,defscheme);
	GFX_GOL_ButtonCreate(Setdrug_OBJ_BUTTON_1,125,	46,		234,	117,	10,BTN_DRAW,(void*)drug_images[1],NULL,defscheme);
	GFX_GOL_ButtonCreate(Setdrug_OBJ_BUTTON_2,7,		124,	116,	195,	10,BTN_DRAW,(void*)drug_images[2],NULL,defscheme);
	GFX_GOL_ButtonCreate(Setdrug_OBJ_BUTTON_3,125,	124,	234,	195,	10,BTN_DRAW,(void*)drug_images[3],NULL,defscheme);
	GFX_GOL_ButtonCreate(Setdrug_OBJ_BUTTON_4,7,		201,	116,	272,	10,BTN_DRAW,(void*)drug_images[4],NULL,defscheme);
	GFX_GOL_ButtonCreate(Setdrug_OBJ_BUTTON_5,125,	201,	234,	272,	10,BTN_DRAW,(void*)drug_images[5],NULL,defscheme);

	 
	GFX_GOL_ButtonCreate(Setdrug_OBJ_BUTTON_7,5,		277,	66,		313,	5,BTN_DRAW,NULL,(GFX_XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
//	GFX_GOL_ButtonCreate(Setdrug_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setdrug_OBJ_BUTTON_8_text,botbar);
//	GFX_GOL_ButtonCreate(Setdrug_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setdrug_OBJ_BUTTON_9_text,botbar);


	GFX_GOL_StaticTextCreate(Setdrug_OBJ_STATICTEXT_0,1,0,238,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Setdrug_OBJ_STATICTEXT_0_text,GFX_ALIGN_CENTER,topbar);

}
void CreatePrimitivesForSetdrug(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		GFX_ColorSet(BLUE_DARK);
//		while(!GFX_BarDraw(0,279,239,319));
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

WORD msgSetdrug(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
//	GFX_GOL_OBJ_HEADER* pSetPoint;
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
	
	switch (GFX_GOL_ObjectIDGet(pObj)) {
		case Setdrug_OBJ_BUTTON_0:
		case Setdrug_OBJ_BUTTON_1:
		case Setdrug_OBJ_BUTTON_2:
		case Setdrug_OBJ_BUTTON_3:
		case Setdrug_OBJ_BUTTON_4:
		case Setdrug_OBJ_BUTTON_5:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
					vol_para.drug_type = GFX_GOL_ObjectIDGet(pObj);
					GDDPrevScreen();
			}	
			return 1;
		case Setdrug_OBJ_BUTTON_7:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				GDDPrevScreen();
			}	
			return 1;
		
		default:
			break;
	}	

	return 1;	
} 
#endif //todo