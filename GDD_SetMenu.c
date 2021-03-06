/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_SETMENU_PUB
#include "include.h"

extern USB_HANDLE USBGenericInHandle;
// Strings
const XCHAR Setmenu_OBJ_STATICTEXT_0_text[] = "SETUP";
const XCHAR Setmenu_OBJ_STATICTEXT_1_text[] = "To save parameters\r\n press \"Save\"";
//const XCHAR Setmenu_OBJ_STATICTEXT_2_text[] = "Wrong PASSWORD";

const XCHAR Setmenu_OBJ_BUTTON_0_text[] = "1. RATE MAX";
const XCHAR Setmenu_OBJ_BUTTON_1_text[] = "2. VTBI MAX";
const XCHAR Setmenu_OBJ_BUTTON_2_text[] = "3. BOLUS MODE";
const XCHAR Setmenu_OBJ_BUTTON_3_text[] = "4. BOLUS RATE MAX";
const XCHAR Setmenu_OBJ_BUTTON_4_text[] = "5. BOLUS VOL. MAX";

const XCHAR Setmenu_OBJ_BUTTON_5_text[] = "6. BOLUS RATE DEF. ";
const XCHAR Setmenu_OBJ_BUTTON_6_text[] = "7. BOLUS VTBI DEF.";
//const XCHAR Setmenu_OBJ_BUTTON_7_text[] = "8. OCC. LIMIT";
//const XCHAR Setmenu_OBJ_BUTTON_8_text[] = "9. OCC. HIGH";
//const XCHAR Setmenu_OBJ_BUTTON_9_text[] = "10. OCC. MED";
const XCHAR Setmenu_OBJ_BUTTON_7_text[] = "8. OCC. HIGH";
const XCHAR Setmenu_OBJ_BUTTON_8_text[] = "9. OCC. MED";
const XCHAR Setmenu_OBJ_BUTTON_9_text[] = "10. OCC. LOW";

//const XCHAR Setmenu_OBJ_BUTTON_10_text[] = "11. OCC. LOW";
const XCHAR Setmenu_OBJ_BUTTON_10_text[] = "11. AIL LIMIT MAX";
const XCHAR Setmenu_OBJ_BUTTON_11_text[] = "12. UPPER LIMIT";
const XCHAR Setmenu_OBJ_BUTTON_12_text[] = "13. PARA LIMIT";
const XCHAR Setmenu_OBJ_BUTTON_13_text[] = "14. BATTERY TYPE";
//const XCHAR Setmenu_OBJ_BUTTON_14_text[] = "16. DATE";

//const XCHAR Setmenu_OBJ_BUTTON_16_text[] = "SAVE";
//const XCHAR Setmenu_OBJ_BUTTON_17_text[] = "EXIT";
//const XCHAR Setmenu_OBJ_BUTTON_18_text[] = "AL";
//const XCHAR Setmenu_OBJ_BUTTON_19_text[] = "AR";


#define Setmenu_OBJ_STATICTEXT_0   0
#define Setmenu_OBJ_STATICTEXT_1   1
#define Setmenu_OBJ_STATICTEXT_2   2
#define Setmenu_OBJ_BUTTON_0   3
#define Setmenu_OBJ_BUTTON_1   4
#define Setmenu_OBJ_BUTTON_2   5
#define Setmenu_OBJ_BUTTON_3   6
#define Setmenu_OBJ_BUTTON_4   7
#define Setmenu_OBJ_BUTTON_5   8
#define Setmenu_OBJ_BUTTON_6   9
#define Setmenu_OBJ_BUTTON_7   10
#define Setmenu_OBJ_BUTTON_8   11
#define Setmenu_OBJ_BUTTON_9   12
#define Setmenu_OBJ_BUTTON_10   13
#define Setmenu_OBJ_BUTTON_11   14
#define Setmenu_OBJ_BUTTON_12   15
#define Setmenu_OBJ_BUTTON_13   16
#define Setmenu_OBJ_BUTTON_14   17
#define Setmenu_OBJ_BUTTON_16   18
#define Setmenu_OBJ_BUTTON_17   19
#define Setmenu_OBJ_BUTTON_18   20
#define Setmenu_OBJ_BUTTON_19   21
#define Setmenu_OBJ_PICTURE_0	22															 	
static unsigned char Setmenu_pg;


void CreateSetmenu(void)
{
	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();
	
	Setmenu_pg = page_create; 
	
//	if(pswrd != 12345)
//		Setmenu_pg = 4;	

	if(Setmenu_pg == 0)
	{
		BtnCreate(Setmenu_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_0_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_1_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_2,3,140,236,178,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_2_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_3,3,186,236,224,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_3_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_4,3,232,236,270,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_4_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_19,170,277,230,313,5,BTN_DRAW,(void *)&Rarrow,/*(XCHAR*)Setmenu_OBJ_BUTTON_19_text*/NULL,botbar);
	
	}
	else if(Setmenu_pg == 1)
	{
		BtnCreate(Setmenu_OBJ_BUTTON_5,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_5_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_6,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_6_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_7,3,140,236,178,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_7_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_8,3,186,236,224,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_8_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_9,3,232,236,270,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_9_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_18,92,277,152,313,5,BTN_DRAW,(void *)&Larrow,/*(XCHAR*)Setmenu_OBJ_BUTTON_18_text*/NULL,botbar);
		BtnCreate(Setmenu_OBJ_BUTTON_19,170,277,230,313,5,BTN_DRAW,(void *)&Rarrow,/*(XCHAR*)Setmenu_OBJ_BUTTON_19_text*/NULL,botbar);
	}
	else if(Setmenu_pg == 2)
	{
		BtnCreate(Setmenu_OBJ_BUTTON_10,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_10_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_11,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_11_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_12,3,140,236,178,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_12_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_13,3,186,236,224,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_13_text,defscheme);
//		BtnCreate(Setmenu_OBJ_BUTTON_14,3,232,236,270,10,BTN_DRAW|BTN_TEXTLEFT,NULL,(XCHAR*)Setmenu_OBJ_BUTTON_14_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_18,92,277,152,313,5,BTN_DRAW,(void *)&Larrow,/*(XCHAR*)Setmenu_OBJ_BUTTON_18_text*/NULL,botbar);
	}
	else if(Setmenu_pg == 3)
	{
		StCreate(Setmenu_OBJ_STATICTEXT_1,10,60,228,160,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Setmenu_OBJ_STATICTEXT_1_text,defscheme);
		BtnCreate(Setmenu_OBJ_BUTTON_16,92,277,152,313,5,BTN_DRAW,NULL,(XCHAR*)SAVE_OBJ_BUTTON_text,botbar);
	}
//	else
//	{
//		StCreate(Setmenu_OBJ_STATICTEXT_2,10,60,228,160,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Setmenu_OBJ_STATICTEXT_2_text,defscheme);
//	}
	BtnCreate(Setmenu_OBJ_BUTTON_17,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
	StCreate(Setmenu_OBJ_STATICTEXT_0,0,0,239,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Setmenu_OBJ_STATICTEXT_0_text,topbar);
	PictCreate(Setmenu_OBJ_PICTURE_0, 209,0,239,30, PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&setting, topbar);

}
void CreatePrimitivesForSetmenu(void){
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

WORD msgSetmenu(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
	
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
		
		case Setmenu_OBJ_BUTTON_17:
			if (objMsg == BTN_MSG_RELEASED) {
				if(Setmenu_pg != 3 && memcmp((unsigned char*)&E2pImage_tmp,(unsigned char*)&E2pImage,sizeof(E2pImage_t)))
					GDDShiftScreen(3); //4st screen
				else
				{
//					pswrd = 0;
					GDDPrevScreen();
				}
			}	  
			return 1;

		case Setmenu_OBJ_BUTTON_16:
			if (objMsg == BTN_MSG_RELEASED) {
				/* put checksum to the last halfword */
  				((unsigned int*)&E2pImage_tmp)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage_tmp, sizeof(E2pImage_t) - 2);
				vTaskSuspendAll();
				SST25SectorErase(PARAM_E2PIMG_BASE);
				if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage_tmp, sizeof(E2pImage_t)))
					/*CriticalError("eeprom err")*/;
				xTaskResumeAll();
				memcpy((unsigned char*)&E2pImage,(unsigned char*)&E2pImage_tmp,sizeof(E2pImage_t));
//				pswrd = 0;
				GDDPrevScreen();
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_18:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, &Larrow_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, &Larrow);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED)
				{
					if(Setmenu_pg-- == 0)
						Setmenu_pg = 2;
					GDDShiftScreen(Setmenu_pg); //1st screen
				}
			}	
			return 1;
			
		case Setmenu_OBJ_BUTTON_19:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, &Rarrow_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, &Rarrow);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					if(++Setmenu_pg >2)
						Setmenu_pg = 0;
					GDDShiftScreen(Setmenu_pg); 
				}
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_RELEASED) {
//				float maxrate
//				E2pImage_tmp.maxrate
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_RATE_MAX,NULL); //Rate maximum
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_RELEASED) {
//				float maxvolume
//				E2pImage_tmp.maxvolume
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_VTBI_MAX,NULL); //Volume maximum
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_2:  //Bolus mode
			if (objMsg == BTN_MSG_RELEASED) {
//				unsigned char mode;
//				E2pImage_tmp.bolus_init.mode
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_BOLUS_MODE,NULL);  //Bolus rate max
			}	  
			return 1;
		case Setmenu_OBJ_BUTTON_3:
			if (objMsg == BTN_MSG_RELEASED) {
//				float maxrate;
//				E2pImage_tmp.bolus_init.maxrate
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_BOLUS_RATEMAX,NULL);  //Bolus rate max
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_4:
			if (objMsg == BTN_MSG_RELEASED) {
//				float maxvolume;
//				E2pImage_tmp.bolus_init.maxvolume
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_BOLUS_VTBIMAX,NULL);  //Bolus volume max
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_5:
			if (objMsg == BTN_MSG_RELEASED) {
//				float rate;
//				E2pImage_tmp.bolus_init.rate
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_BOLUS_RATEDEF,NULL);  //Bolus rate default
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_6:
			if (objMsg == BTN_MSG_RELEASED) {
//				float volume;
//				E2pImage_tmp.bolus_init.volume
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_BOLUS_VTBIDEF,NULL);  //Bolus volume default
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) {
//		int occlus_lmts[3];
//				E2pImage_tmp.occlus_lmts
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_OCC_HIGH,NULL);  //Occlusion High
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_8:
			if (objMsg == BTN_MSG_RELEASED) {
//		int occlus_lmts[3];
//				E2pImage_tmp.occlus_lmts
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_OCC_MEDIUM,NULL);  //Occlusion High
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_9:
			if (objMsg == BTN_MSG_RELEASED) {
//		int occlus_lmts[3];
//				E2pImage_tmp.occlus_lmts
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_OCC_LOW,NULL);  //Occlusion Meduim
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_10:
//		 unsigned int	ail_limit;
//				E2pImage_tmp.ail_limit
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_AIL_LIMITMAX,NULL);  //Ail limit max
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_11:  //Upper occlusion limit
//		 unsigned char bzz_volume;
//				E2pImage_tmp.bzz_volume
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_UPPER_LIMIT,NULL);  //Upper occlusion
			}	
			return 1;                     
		case Setmenu_OBJ_BUTTON_12:  
//				E2pImage_tmp.                                      
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_PARA_LIMIT,NULL);  //Para limit      &bolus_rate
			}	
			return 1;
		case Setmenu_OBJ_BUTTON_13:   //Battery type     SETUP_BATTERY_TYPE
//		 unsigned char battype;
//				E2pImage_tmp.battype
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_BATTERY_TYPE,NULL);  //Para limit
//				GDDSetScreen(CREATE_SCREEN_TEST,0,NULL);
			}	
			return 1;
//		case Setmenu_OBJ_BUTTON_14:  
//				E2pImage_tmp.                                      
//			if (objMsg == BTN_MSG_RELEASED) {
//				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_DATE,NULL);  //data
//			}	
//			return 1;
		
		default:
			break;
	}	

	return 1;	
} 
