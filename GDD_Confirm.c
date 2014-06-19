/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_CONFIRM_PUB
#include "include.h"
#include "Graphics Resources\new.h"

// Strings
GFX_XCHAR Confirm_OBJ_STATICTEXT_0_text[] = "PLEASE CONFIRM";
GFX_XCHAR Confirm_OBJ_STATICTEXT_1_text[] = "TIME REMAIN";
GFX_XCHAR Confirm_OBJ_STATICTEXT_2_text[] = "RATE";

const GFX_XCHAR Confirm_OBJ_BUTTON_9_text[] = "CONFIRMED";
//const GFX_XCHAR Confirm_OBJ_BUTTON_10_text[] = "EXIT";
const GFX_XCHAR Confirm_OBJ_BUTTON_11_text[] = "START INFUSION";


#define Confirm_OBJ_STATICTEXT_0   0
#define Confirm_OBJ_STATICTEXT_1   1
#define Confirm_OBJ_STATICTEXT_2   2
#define Confirm_OBJ_STATICTEXT_3   3
#define Confirm_OBJ_STATICTEXT_4   4
#define Confirm_OBJ_STATICTEXT_5   5

#define Confirm_OBJ_PICTURE_0			 6
#define Confirm_OBJ_PICTURE_1      7
#define Confirm_OBJ_PICTURE_2      8
#define Confirm_OBJ_PICTURE_3      9

#define Confirm_OBJ_BUTTON_9   10
#define Confirm_OBJ_BUTTON_10   11
#define Confirm_OBJ_BUTTON_11   12
static CONTROL_MSG cMsg;
GFX_GOL_OBJ_SCHEME* confirmScheme;
static char	str1[30];
static char	str2[30];
static char	str3[30];

void CreateConfirm_prog1(void);
void CreateConfirm_prog2(void);
void CreateConfirm_prog5(void);


void ConfirmShemes(void)
{
	confirmScheme = CreateScheme();
	memcpy(confirmScheme, defscheme, sizeof(GFX_GOL_OBJ_SCHEME));
//	confirmScheme->Color0 = BLACK;
	confirmScheme->Color1 = BLACK;
	confirmScheme->pFont = (void*) &Arial_Narrow_26;
}

void CreateConfirm(void)
{
	
	GFX_GOL_ObjectListFree();
	GFX_ColorSet(BLUE_LIGHT);
	GFX_ScreenClear();
	xTimerStart( xTimers[ 1 ], 0 );


	switch(prog_num)
	{
		default:
		case 0:
			CreateConfirm_prog1();
			break;
		case 1:
			CreateConfirm_prog2();
			break;
		case 2:
			CreateConfirm_prog3();
			break;
		case 3:
			CreateConfirm_prog4();
			break;
		case 4:
		case 5:
			CreateConfirm_prog5();
			break;
	}
	
	if(page_create == 0)
	{
		GFX_GOL_PictureControlCreate(Confirm_OBJ_PICTURE_0,6,193,115,264,PICT_DRAW, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)prog_images[prog_num],defscheme);
	 	GFX_GOL_PictureControlCreate(Confirm_OBJ_PICTURE_1,131,203,235,263,PICT_DRAW, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)drug_images[vol_para.drug_type],defscheme);
	}
	
	BtnCreate(Confirm_OBJ_BUTTON_10,5,277,66,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
	GFX_GOL_PictureControlCreate(Confirm_OBJ_PICTURE_3,215,0,239,30, PICT_DRAW, IMAGE_NORMAL, getBatImg(batlevel), topbar);

}
void CreatePrimitivesForConfirm(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		GFX_ColorSet(BLUE_DARK);
//		while(!GFX_BarDraw(0,279,239,319));
}

void UpdateConfirm(void)
{
	GFX_GOL_OBJ_HEADER* pObj;
	
	pObj = GOLFindObject(Confirm_OBJ_PICTURE_3);
	if (pObj) {
		PictSetBitmap(pObj, getBatImg(batlevel));
		SetState((PICTURE*) pObj, DRAW_UPDATE);
	}
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

WORD msgConfirm(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
	if(pObj == NULL)
	{

		switch(pMsg->param1)
		{
			case INP_TIMER1_ID:			
				//Timer expired
				xTimerStart( xTimers[ 1 ], 0 );
				UpdateConfirm();
				break;
			default:
				break;
		}
		return 1;	
	}
	
	switch (GFX_GOL_ObjectIDGet(pObj)) {
		
		case Confirm_OBJ_BUTTON_10:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				//Go back
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDPrevScreen();
			}	
			return 1;
		case Confirm_OBJ_BUTTON_11:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				if(GetDoorState())
				{
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,DOOR_ALRM_SCR,NULL);
					return 1;
				}
//				cMsg.cmd = MSG_CONTROL_START_INFUS;
//				xQueueSend(hCONTROLQueue, &cMsg, 0);
				//Goto run
				GDDSetScreen(CREATE_SCREEN_RUN,0,NULL);
			}	
			return 1;
		
		case Confirm_OBJ_BUTTON_9:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				//Goto Time remain
//				page_display = 0;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(1);
			}	
			return 1;
		default:
			break;
	}	
	return 1;	
} 

void CreateConfirm_prog1(void)
{

	if(page_create == 0)
	{
		sprintf(str1,"RATE  = ");
		ValToStr(TYPE_RATE,0, vol_para.rate,NULL, str1 + strlen(str1));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_2,3,48,236,86,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_LEFT,confirmScheme);
	 	
		if(no_limit == 1)
			sprintf(str2,"NO LIMIT");
		else
		{
			sprintf(str2,"VTBI  = ");
			ValToStr(TYPE_VOLUME,0, vol_para.vtbi,NULL, str2 + strlen(str2));
	 	}
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_3,3,94,236,132,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str2,GFX_ALIGN_LEFT,confirmScheme);

		sprintf(str3,"INFUSED  = ");
		ValToStr(TYPE_VOLUME,0, vol_para.infsd,NULL, str3 + strlen(str3));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_4,3,140,236,178,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str3,GFX_ALIGN_LEFT,confirmScheme);
	 	
 		BtnCreate(Confirm_OBJ_BUTTON_9,124,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_9_text,botbar);
 		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_0_text,GFX_ALIGN_LEFT,topbar);
	}
	else
	{
	 	GFX_GOL_PictureControlCreate(Confirm_OBJ_PICTURE_2,55,40,183,168,PICT_DRAW, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)&clock_img,defscheme);
		run_prepare();
		calc_rem_infusetime();
		   
		if(no_limit)
			sprintf(str1,"NO LIMIT");
		else	
			strftime(str1, 100, "%Hhr/ %Mmin/ %Ssec", localtime(&remain_infusetime));
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_5,3,200,236,245,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_CENTER,confirmScheme);
		BtnCreate(Confirm_OBJ_BUTTON_11,95,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_11_text,botbar);
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_1_text,GFX_ALIGN_LEFT,topbar);
	}
}

void CreateConfirm_prog2(void)
{
	
	if(page_create == 0)
	{
		sprintf(str1,"VTBI  = ");
		ValToStr(TYPE_VOLUME,0, vol_para.vtbi,NULL, str1 + strlen(str1));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_2,3,48,236,86,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_LEFT,confirmScheme);
	 	
		sprintf(str2,"TIME  = ");
		ValToStr(TYPE_TIMEINTERVAL,estim_infusetime, 0,NULL, str2 + strlen(str2));
		sprintf(str2 + strlen(str2)," Hr:Min");
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_3,3,94,236,132,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str2,GFX_ALIGN_LEFT,confirmScheme);
	
		sprintf(str3,"INFUSED  = ");
		ValToStr(TYPE_VOLUME,0, vol_para.infsd,NULL, str3 + strlen(str3));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_4,3,140,236,178,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str3,GFX_ALIGN_LEFT,confirmScheme);
	 	
 		BtnCreate(Confirm_OBJ_BUTTON_9,124,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_9_text,botbar);
 		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_0_text,GFX_ALIGN_LEFT,topbar);
	}
	else
	{
		run_prepare();
		calc_rem_infusetime();
		
		sprintf(str1,"RATE  = ");
		ValToStr(TYPE_RATE,0, vol_para.rate,NULL, str1 + strlen(str1));
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_5,3,200,236,245,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_CENTER,confirmScheme);
		BtnCreate(Confirm_OBJ_BUTTON_11,95,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_11_text,botbar);
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_2_text,GFX_ALIGN_LEFT,topbar);
	}
}

void CreateConfirm_prog3(void)
{

		 
	if(page_create == 0)
	{
		sprintf(str1,"BAG VOL = ");
		ValToStr(TYPE_VOLUME,0, vol_para.bag_vol,NULL, str1 + strlen(str1));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_2,3,48,236,86,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_LEFT,confirmScheme);
	 	
		sprintf(str2,"DOSE VOL = ");
		ValToStr(TYPE_VOLUME, 0, vol_para.dose_vol,NULL, str2 + strlen(str2));
//		sprintf(str2 + strlen(str2)," Hr:Min");
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_3,3,94,236,132,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str2,GFX_ALIGN_LEFT,confirmScheme);
	
		sprintf(str3,"D/RATE = ");
		ValToStr(TYPE_RATE,0, vol_para.dose_rate,NULL, str3 + strlen(str3));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_4,3,140,236,178,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str3,GFX_ALIGN_LEFT,confirmScheme);
	 	
 		BtnCreate(Confirm_OBJ_BUTTON_9,124,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_9_text,botbar);
 		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_0_text,GFX_ALIGN_LEFT,topbar);
	}
	else
	{
		run_prepare();
		calc_rem_infusetime();
		
		sprintf(str1,"T.INTERVAL = ");
		ValToStr(TYPE_TIMEINTERVAL,vol_para.dose_interval, 0,NULL, str1 + strlen(str1));
//		sprintf(str1 + strlen(str1)," Hr:Min");
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_2,3,48,236,86,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_LEFT,confirmScheme);
//		BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(GFX_XCHAR*)str1,defscheme);
	
		sprintf(str2,"KVO = ");
		ValToStr(TYPE_RATE,0, vol_para.kvo_rate,NULL, str2 + strlen(str2));
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_3,3,94,236,132,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str2,GFX_ALIGN_LEFT,confirmScheme);
//		BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(GFX_XCHAR*)str2,defscheme);
	
		BtnCreate(Confirm_OBJ_BUTTON_11,95,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_11_text,botbar);
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_2_text,GFX_ALIGN_LEFT,topbar);
	}
}

void CreateConfirm_prog4(void)
{
	if(page_create == 0)
	{
		sprintf(str1,"BAG VOL = ");
		ValToStr(TYPE_VOLUME,0, vol_para.bag_vol,NULL, str1 + strlen(str1));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_2,3,48,236,86,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_LEFT,confirmScheme);
	 	
		sprintf(str2,"DOSE VOL = ");
		ValToStr(TYPE_VOLUME, 0, vol_para.dose_vol,NULL, str2 + strlen(str2));
//		sprintf(str2 + strlen(str2)," Hr:Min");
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_3,3,94,236,132,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str2,GFX_ALIGN_LEFT,confirmScheme);
	
		sprintf(str3,"DOSE TIME = ");
		ValToStr(TYPE_TIMEINTERVAL,vol_para.dose_time, 0,NULL, str3 + strlen(str3));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_4,3,140,236,178,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str3,GFX_ALIGN_LEFT,confirmScheme);
		  	 
 		BtnCreate(Confirm_OBJ_BUTTON_9,124,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_9_text,botbar);
 		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_0_text,GFX_ALIGN_LEFT,topbar);
	}
	else
	{
		run_prepare();
		calc_rem_infusetime();
		
		sprintf(str1,"T.INTERVAL = ");
		ValToStr(TYPE_TIMEINTERVAL,vol_para.dose_interval, 0,NULL, str1 + strlen(str1));
//		sprintf(str1 + strlen(str1)," Hr:Min");
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_2,3,48,236,86,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_LEFT,confirmScheme);
//		BtnCreate(Clear_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(GFX_XCHAR*)str1,defscheme);
	
		sprintf(str2,"KVO = ");
		ValToStr(TYPE_RATE,0, vol_para.kvo_rate,NULL, str2 + strlen(str2));
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_3,3,94,236,132,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str2,GFX_ALIGN_LEFT,confirmScheme);
//		BtnCreate(Clear_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW|BTN_TEXTLEFT,(void *)&Param_btn,(GFX_XCHAR*)str2,defscheme);
	
		BtnCreate(Confirm_OBJ_BUTTON_11,95,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_11_text,botbar);
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_2_text,GFX_ALIGN_LEFT,topbar);
	}
}


void CreateConfirm_prog5(void)
{

int i;
float tot_vol = 0.0;
unsigned long tot_time;
	
	if(page_create == 0)
	{
		sprintf(str1,"TOT. STEPS = ");
		ValToStr(TYPE_GEN,vol_para.prog_stepsnum, 0,NULL, str1 + strlen(str1));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_2,3,48,236,86,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_LEFT,confirmScheme);
	 	
		for(i = 0; i<vol_para.prog_stepsnum; i++)
			tot_vol += vol_para.prog_steps[i].vol;
		
		sprintf(str2,"TOT. VOL = ");
		ValToStr(TYPE_VOLUME,0, tot_vol,NULL, str2 + strlen(str2));
	 	GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_3,3,94,236,132,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str2,GFX_ALIGN_LEFT,confirmScheme);
	
		sprintf(str3,"INFUSED  = ");
		ValToStr(TYPE_VOLUME,0, vol_para.infsd,NULL, str3 + strlen(str3));
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_4,3,140,236,178,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str3,GFX_ALIGN_LEFT,confirmScheme);
	 	
 		BtnCreate(Confirm_OBJ_BUTTON_9,124,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_9_text,botbar);
 		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_0_text,GFX_ALIGN_LEFT,topbar);
	}
	else
	{
	 	GFX_GOL_PictureControlCreate(Confirm_OBJ_PICTURE_2,55,40,183,168,PICT_DRAW, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)&clock_img,defscheme);
		run_prepare();
		calc_rem_infusetime();

		
		if(no_limit)
			sprintf(str1,"NO LIMIT");
		else	
			strftime(str1, 100, "%Hhr/ %Mmin/ %Ssec", localtime(&remain_infusetime));
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_5,3,200,236,245,GFX_GOL_STATICTEXT_DRAW_STATE|GFX_GOL_STATICTEXT_FRAME_STATE,(GFX_XCHAR*)str1,GFX_ALIGN_CENTER,confirmScheme);
		BtnCreate(Confirm_OBJ_BUTTON_11,95,277,235,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Confirm_OBJ_BUTTON_11_text,botbar);
		GFX_GOL_StaticTextCreate(Confirm_OBJ_STATICTEXT_0,0,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Confirm_OBJ_STATICTEXT_1_text,GFX_ALIGN_LEFT,topbar);
	}
}

