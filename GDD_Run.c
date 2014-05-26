/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_RUN_PUB
#include "include.h"
#include "Graphics Resources\new.h"

// Strings
XCHAR Run_OBJ_STATICTEXT_0_text[] = "RUNNING";
XCHAR Run_OBJ_STATICTEXT_1_text[] = "ml/hr";

//const XCHAR Run_OBJ_STATICTEXT_2_text[] = "RATE";
//const XCHAR Run_OBJ_STATICTEXT_3_text[] = "VTBI";
//const XCHAR Run_OBJ_STATICTEXT_4_text[] = "INFUSED";
XCHAR Run_OBJ_STATICTEXT_5_text[] = "RATE=";

XCHAR Run_OBJ_STATICTEXT_6_text[] = "PUMPING\r\nPRESSURE";
const XCHAR Run_OBJ_STATICTEXT_7_text[] = "OCCLUSION\r\nLIMIT";
const XCHAR Run_OBJ_STATICTEXT_8_text[] = "RATE";

const XCHAR Run_OBJ_BUTTON_9_text[] = "MORE DISPLAY";
const XCHAR Run_OBJ_BUTTON_10_text[] = "BOLUS";

#define Run_OBJ_STATICTEXT_0   0
#define Run_OBJ_STATICTEXT_1   1

#define Run_OBJ_EDITBOX_2   2
#define Run_OBJ_EDITBOX_3   3
#define Run_OBJ_EDITBOX_4   	 4
#define Run_OBJ_STATICTEXT_5   5

#define Run_OBJ_STATICTEXT_6   6
#define Run_OBJ_STATICTEXT_7   7
#define Run_OBJ_STATICTEXT_8   8

#define Run_OBJ_PICTURE_0			 9
#define Run_OBJ_PICTURE_1      10
#define Run_OBJ_PICTURE_2      11

#define Run_OBJ_BUTTON_9   	12
#define Run_OBJ_BUTTON_10   13
#define Run_OBJ_BUTTON_11   14

#define Run_OBJ_EDITBOX_0   15
#define Run_OBJ_EDITBOX_1   16
#define Run_OBJ_PICTURE_3		17
#define Run_OBJ_PICTURE_4   18
#define Run_OBJ_PICTURE_5   19
#define Run_OBJ_PICTURE_6   20

void CreateRun_prog1(void);
void CreateRun_prog2(void);
void CreateRun_prog5(void);

static CONTROL_MSG cMsg;
static unsigned char run_display;
static char	str1[30];
static char	str2[30];
static char	str3[30];

		/*100%   from -300 to + 800  = 1100
		 * High max 260 - 66 pix = 194 
		 * bar_high = (press2_mmHg + 300) / (1100/194)  */
//#define press2hight(press) ((press + 300) / (1100/194))

static GOL_SCHEME* runScheme;
static GOL_SCHEME* runScheme1;
static GOL_SCHEME* runScheme2;
static GOL_SCHEME* runGrayScheme;

void RunShemes(void)
{
	runScheme = GOLCreateScheme();
	memcpy(runScheme, defscheme, sizeof(GOL_SCHEME));
	runScheme->Color1 = BLACK;
	runScheme->Color0 = GREEN;
	runScheme->pFont = (void*) &Arial_Narrow_Bold_28;
	runScheme->EmbossDkColor = BLACK;
	runScheme->EmbossLtColor = BLACK;
	runScheme->CommonBkColor = GREEN;

	runScheme1 = GOLCreateScheme();
	memcpy(runScheme1, runScheme, sizeof(GOL_SCHEME));
	runScheme1->pFont = (void*) &Arial_Narrow_Bold_86;
	
	runScheme2 = GOLCreateScheme();
	memcpy(runScheme2, runScheme, sizeof(GOL_SCHEME));
	runScheme2->pFont = (void*) &Arial_Narrow_24;
	 
	runGrayScheme = GOLCreateScheme();
	memcpy(runGrayScheme, defscheme, sizeof(GOL_SCHEME));
	runGrayScheme->Color1 = GRAY_RUN;
	runGrayScheme->Color0 = YELLOW_RUN;
	runGrayScheme->TextColor0 = BLACK;
	runGrayScheme->TextColorDisabled = YELLOW_RUN;
	runGrayScheme->pFont = (void*) &Arial_Narrow_Bold_18;
	runGrayScheme->EmbossDkColor = GRAY_RUN;
	runGrayScheme->EmbossLtColor = GRAY_RUN;
	runGrayScheme->CommonBkColor = GRAY_RUN;

}

void CreateRun(void)
{
	
	GOLFree();
	SetColor(GREEN);
	ClearDevice();
	xTimerStart( xTimers[ 1 ], 0 );
	
	if(stmotor_stat()== STMTR_STOP)
	{
		cMsg.cmd = MSG_CONTROL_START_INFUS;
		xQueueSend(hCONTROLQueue, &cMsg, 0);
	}

	   
	run_display = page_create;



	if(page_create == 0)
	{
		switch(prog_num)
		{
			default:
			case 0:
				CreateRun_prog1();
				break;
			case 1:
				CreateRun_prog2();
				break;
			case 2:
			case 3:
				CreateRun_prog3();
				break;
			case 4:
			case 5:
				CreateRun_prog5();
				break;
		}
	 	PictCreate(Run_OBJ_PICTURE_0,6,193,115,264,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)prog_images[prog_num],runScheme);
	 	PictCreate(Run_OBJ_PICTURE_1,131,203,235,263,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)drug_images[vol_para.drug_type],runScheme);
	 
	}
	else if(page_create == 1)
	{                           
	 	PictCreate(Run_OBJ_PICTURE_1,15,35,223,155,PICT_DRAW, IMAGE_X2, (GFX_IMAGE_HEADER *)drug_images[vol_para.drug_type],runScheme);
	 	if(vol_para.rate < 100.0)
	 		sprintf(str1,"%.1f",(double)vol_para.rate);
	 	else
	 		sprintf(str1,"%.0f",(double)vol_para.rate);
		StCreate(Run_OBJ_STATICTEXT_5,1,185,178,280,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)str1,runScheme1);
		StCreate(Run_OBJ_STATICTEXT_8,88,156,152,189,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Run_OBJ_STATICTEXT_8_text,runScheme);
		StCreate(Run_OBJ_STATICTEXT_1,174,240,239,278,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Run_OBJ_STATICTEXT_1_text,runScheme);
	}
	else
	{
		StCreate(Run_OBJ_STATICTEXT_6,42,54,135,92,ST_DRAW|ST_CENTER_ALIGN|ST_DISABLED,(XCHAR*)Run_OBJ_STATICTEXT_6_text,runGrayScheme);
		StCreate(Run_OBJ_STATICTEXT_7,42,198,135,236,ST_DRAW|ST_CENTER_ALIGN|ST_DISABLED,(XCHAR*)Run_OBJ_STATICTEXT_7_text,runGrayScheme);
	
		sprintf(str1,"%d mmHg",press2_mmHg);
		EbCreate(Run_OBJ_EDITBOX_0,42,96,135,122, EB_DRAW,(XCHAR*)str1, 50 ,runGrayScheme);
		sprintf(str2,"%d mmHg",occlus_lmt[occlusion_limit]);
		EbCreate(Run_OBJ_EDITBOX_1,42,240,135,266, EB_DRAW,(XCHAR*)str2, 50 ,runGrayScheme);
		
		PictCreate(Run_OBJ_PICTURE_3,148,260 - press2hight(occlus_lmt[occlusion_limit]) - 6,
							160,260 - press2hight(occlus_lmt[occlusion_limit])+6 ,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&Pointer_img,runGrayScheme);
		PictCreate(Run_OBJ_PICTURE_4,162,64,195,263,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&Pressbar_img,runGrayScheme);
	}
	
	BtnCreate(Run_OBJ_BUTTON_10,5,277,70,313,5,BTN_DRAW,NULL,(XCHAR*)Run_OBJ_BUTTON_10_text,botbar);
	BtnCreate(Run_OBJ_BUTTON_9,110,277,235,313,5,BTN_DRAW,NULL,(XCHAR*)Run_OBJ_BUTTON_9_text,botbar);
	StCreate(Run_OBJ_STATICTEXT_0,0,0,239,30,ST_DRAW,(XCHAR*)Run_OBJ_STATICTEXT_0_text,topbar);
	PictCreate(Run_OBJ_PICTURE_2, 210,0,239,30, PICT_DRAW, IMAGE_NORMAL, getWaitImg(), topbar);
	PictCreate(Run_OBJ_PICTURE_5, 186,0,209,30, PICT_DRAW, IMAGE_NORMAL, getBatImg(batlevel), topbar);
//	if(testBit(kvo_stat, KVO_STAT)/* kvo_stat*/ != 0)
	PictCreate(Run_OBJ_PICTURE_6, 145,0,185,30, PICT_DRAW|PICT_HIDE, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&KVO, topbar);


}
void CreatePrimitivesForRun(void){
	if(page_create == 1)
	{
		SetLineType(0);
		SetLineThickness(2);
		SetColor(BLACK);
		while(!Line(88,189,152,189));
	}
	else if(page_create == 2)
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(40,46,200,270));
	}
}

	 	

void UpdateRun(void)
{
	
	OBJ_HEADER* pObj;

#if 0	 
	pObj = GOLFindObject(Test_OBJ_DIGITALMETER_0);
	if (pObj) {
//			sprintf(str," = %.2fV", BAT_RAW2VOLT(batt_raw));
		DmSetValue((DIGITALMETER*)pObj,(long)(BAT_RAW2VOLT(batt_raw)*100.0));        //
		SetState((DIGITALMETER*) pObj, DRAW_UPDATE);
	}
	pObj = GOLFindObject(Test_OBJ_DIGITALMETER_1);
	if (pObj) {
		DmSetValue((DIGITALMETER*)pObj,air_raw);
		SetState((DIGITALMETER*) pObj, DRAW_UPDATE);
	}
	pObj = GOLFindObject(Test_OBJ_DIGITALMETER_2);
	if (pObj) {
		DmSetValue((DIGITALMETER*)pObj,press1_raw);
		SetState((DIGITALMETER*) pObj, DRAW_UPDATE);
	}
	pObj = GOLFindObject(Test_OBJ_DIGITALMETER_3);
	if (pObj) {
		DmSetValue((DIGITALMETER*)pObj,press2_raw);
 		SetState((DIGITALMETER*) pObj, DRAW_UPDATE);
	}
#endif	
	pObj = GOLFindObject(Run_OBJ_PICTURE_2);
	if (pObj) {
		PictSetBitmap(pObj, getWaitImg());
		SetState((PICTURE*) pObj, DRAW_UPDATE);
	}
	pObj = GOLFindObject(Run_OBJ_PICTURE_5);
	if (pObj) {
		PictSetBitmap(pObj, getBatImg(batlevel));
		SetState((PICTURE*) pObj, DRAW_UPDATE);
	}
				
	pObj = GOLFindObject(Run_OBJ_PICTURE_6);
	if (pObj) {
		if(testBit(kvo_stat, KVO_STAT)/* kvo_stat*/ != 0)
		{
			ClrState((PICTURE*) pObj, PICT_HIDE);
			SetState((PICTURE*) pObj, DRAW_UPDATE);
		}
		else
		{
			SetState((PICTURE*) pObj, PICT_HIDE|DRAW_UPDATE);
		}
//					SetState((PICTURE*) pObj, DRAW_UPDATE);
	}
	 

	if(page_display == 0)
	{
		switch(prog_num)
		{
			default:
			case 0:
//				UpdateRun_prog1();
				break;
			case 1:
//				UpdateRun_prog2();
				pObj = GOLFindObject(Run_OBJ_EDITBOX_3);
				if (pObj) {
					sprintf(str2,"TIME  = ");
					ValToStr(TYPE_TIMEINTERVAL,remain_infusetime, 0,NULL, str2 + strlen(str2));
					sprintf(str2 + strlen(str2)," Hr:Min");
					EbSetText((EDITBOX*)pObj,str2); 
			 		SetState((EDITBOX*) pObj, EB_DRAW);
				}
				pObj = GOLFindObject(Run_OBJ_EDITBOX_2);
				if (pObj) {
					
					if(no_limit == 1)
						sprintf(str1,"NO LIMIT");
					else
					{
						sprintf(str1,"VTBI = ");
						ValToStr(TYPE_VOLUME,0, vol_para.vtbi,NULL, str1 + strlen(str1));
				 	}
					EbSetText((EDITBOX*)pObj,str1); 
			 		SetState((EDITBOX*) pObj, EB_DRAW);
				}
				break;
			case 2:
			case 3:
				pObj = GOLFindObject(Run_OBJ_EDITBOX_3);
				if (pObj) {
					sprintf(str2,"PSD. TIME = ");
					ValToStr(TYPE_TIMEINTERVAL,(clock() - vol_para.dose_strt_time), 0,NULL, str2 + strlen(str2));
//					sprintf(str2,"TIME  = ");
//					ValToStr(TYPE_TIMEINTERVAL,remain_infusetime, 0,NULL, str2 + strlen(str2));
//					sprintf(str2 + strlen(str2)," Hr:Min");
					EbSetText((EDITBOX*)pObj,str2); 
			 		SetState((EDITBOX*) pObj, EB_DRAW);
				}
				pObj = GOLFindObject(Run_OBJ_EDITBOX_4);
				if (pObj) {
					sprintf(str3,"INFUSED = ");
					ValToStr(TYPE_VOLUME,0, vol_para.infsd,NULL, str3 + strlen(str3));
					EbSetText((EDITBOX*)pObj,str3); 
			 		SetState((EDITBOX*) pObj, EB_DRAW);
				}
				break;
			case 4:
			case 5:
//				UpdateRun_prog5();
				pObj = GOLFindObject(Run_OBJ_EDITBOX_2);
				if (pObj) {
					if(testBit(kvo_stat, KVO_STAT)/* kvo_stat*/ == 0)
					{
						sprintf(str1,"STEP = ");
						ValToStr(TYPE_GEN,vol_para.prog_step+1, 0,NULL, str1 + strlen(str1));
					}
					else
						sprintf(str1,"ALL STEPS DONE");
					EbSetText((EDITBOX*)pObj,str1); 
			 		SetState((EDITBOX*) pObj, EB_DRAW);
				}
				pObj = GOLFindObject(Run_OBJ_EDITBOX_3);
				if (pObj) {
					sprintf(str2,"RATE = ");
					ValToStr(TYPE_RATE,0, vol_para.rate,NULL, str2 + strlen(str2));
					EbSetText((EDITBOX*)pObj,str2); 
			 		SetState((EDITBOX*) pObj, EB_DRAW);
				}
				break;
		}
		pObj = GOLFindObject(Run_OBJ_EDITBOX_4);
		if (pObj) {
//			if(vol_para.infsd < 100.0)
//		 		sprintf(str3,"INFUSED = %.1f ml",(double)vol_para.infsd);
//	 		else
//	 			sprintf(str3,"INFUSED = %.0f ml",(double)vol_para.infsd);
			sprintf(str3,"INFUSED = ");
			ValToStr(TYPE_VOLUME,0, vol_para.infsd,NULL, str3 + strlen(str3));
			EbSetText((EDITBOX*)pObj,str3); 
	 		SetState((EDITBOX*) pObj, EB_DRAW);
		}
	
	}
	else if(page_display == 2)
	{
		pObj = GOLFindObject(Run_OBJ_EDITBOX_0);
		if (pObj) {
			sprintf(str1,"%d mmHg", press2_mmHg);
			EbSetText((EDITBOX*)pObj,str1);   
 			SetState((EDITBOX*) pObj, EB_DRAW);
		}
//		pObj = GOLFindObject(Run_OBJ_EDITBOX_1);
//		if (pObj) {
//	 		sprintf(run_str2,"%d mmHg", press2_mmHg);
//			EbSetText((EDITBOX*)pObj,run_str2);   
// 			SetState((EDITBOX*) pObj, EB_DRAW);
//		}
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(168,66,188,260));
		
		SetColor(YELLOW_RUN);
		while(!Bar(168, ((260 - press2hight(press2_mmHg)) < 66 ? 66 : (260 - press2hight(press2_mmHg))),188,260));
//		while(!Bar(168, 260 - press2hight(press2_mmHg)/*66*/,188,260));
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

WORD msgRun(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
//	OBJ_HEADER* pSetPoint;
//	SHORT dialVal;
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_STOP_ID:			
				if(pMsg->param2 == INP_SET)
				{
					//Stop infusion				 
					cMsg.cmd = MSG_CONTROL_STOP_INFUS;
					xQueueSend(hCONTROLQueue, &cMsg, 0);
         			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
				}	
				break;
			case INP_KVO_ID:			
				if(pMsg->param2 == INP_SET)
				{
   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDSetScreen(CREATE_SCREEN_ALARM,KVO_ALRM_SCR,NULL);
				}	
				break;


			case INP_TIMER1_ID:			
				//Timer expired
				xTimerStart( xTimers[ 1 ], 0 );
//				UpdateRun();
				break;
			default:
				break;
		}
		return 1;	
	}
	
	switch (GetObjID(pObj)) {
		case Run_OBJ_BUTTON_9:
			if (objMsg == BTN_MSG_RELEASED) {
				//Goto Time remain
//				page_display = 0;
				if(++run_display > 2)
					run_display = 0;
       			xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(run_display);
			}	
			return 1;
		case Run_OBJ_BUTTON_10:
			if (objMsg == BTN_MSG_RELEASED) {
				//Go to Bolus screen
				bolus_rate = bolus_init.rate;
				bolus_volume = bolus_init.volume;
       			xTimerStop( xTimers[ 1 ], 0 );
				GDDSetScreen(CREATE_SCREEN_BOLUS,SET_BOLUS,NULL);
			}	
			return 1;
		default:
			break;
		
	}	
	return 1;	
} 

void CreateRun_prog1(void)
{
		sprintf(str1,"RATE = ");
		ValToStr(TYPE_RATE,0, vol_para.rate,NULL, str1 + strlen(str1));
		EbCreate(Run_OBJ_EDITBOX_2,3,48,236,86,EB_DRAW,(XCHAR*)str1,50,runScheme);
	 	
		if(no_limit == 1)
			sprintf(str2,"NO LIMIT");
		else
		{
			sprintf(str2,"VTBI = ");
			ValToStr(TYPE_VOLUME,0, vol_para.vtbi,NULL, str2 + strlen(str2));
	 	}
		EbCreate(Run_OBJ_EDITBOX_3,3,94,236,132,EB_DRAW,(XCHAR*)str2,50,runScheme);
	
		sprintf(str3,"INFUSED = ");
		ValToStr(TYPE_VOLUME,0, vol_para.infsd,NULL, str3 + strlen(str3));
		EbCreate(Run_OBJ_EDITBOX_4,3,140,236,178, EB_DRAW,(XCHAR*)str3, 50 ,runScheme);
}

void CreateRun_prog2(void)
{
		if(no_limit == 1)
			sprintf(str1,"NO LIMIT");
		else
		{
			sprintf(str1,"VTBI = ");
			ValToStr(TYPE_VOLUME,0, vol_para.vtbi,NULL, str1 + strlen(str1));
	 	}
		EbCreate(Run_OBJ_EDITBOX_2,3,48,236,86,EB_DRAW,(XCHAR*)str1,50,runScheme);
		
		sprintf(str2,"TIME = ");
		ValToStr(TYPE_TIMEINTERVAL,remain_infusetime, 0,NULL, str2 + strlen(str2));
		sprintf(str2 + strlen(str2)," Hr:Min");
		EbCreate(Run_OBJ_EDITBOX_3,3,94,236,132,EB_DRAW,(XCHAR*)str2,50,runScheme);
	
		sprintf(str3,"INFUSED = ");
		ValToStr(TYPE_VOLUME,0, vol_para.infsd,NULL, str3 + strlen(str3));
		EbCreate(Run_OBJ_EDITBOX_4,3,140,236,178, EB_DRAW,(XCHAR*)str3, 50 ,runScheme);
}

void CreateRun_prog3(void)
{
		if(no_limit == 1)
			sprintf(str1,"NO LIMIT");
		else
		{
			sprintf(str1,"BAG VOL = ");
			ValToStr(TYPE_VOLUME,0, vol_para.bag_vol,NULL, str1 + strlen(str1));
	 	}
		EbCreate(Run_OBJ_EDITBOX_2,3,48,236,86,EB_DRAW,(XCHAR*)str1,50,runScheme);
		
		sprintf(str2,"PSD. TIME = ");
		ValToStr(TYPE_TIMEINTERVAL,(clock() - vol_para.dose_strt_time), 0,NULL, str2 + strlen(str2));
//		sprintf(str2 + strlen(str2)," Hr:Min");
		EbCreate(Run_OBJ_EDITBOX_3,3,94,236,132,EB_DRAW,(XCHAR*)str2,50,runScheme);
	
		sprintf(str3,"INFUSED = ");
		ValToStr(TYPE_VOLUME,0, vol_para.infsd,NULL, str3 + strlen(str3));
		EbCreate(Run_OBJ_EDITBOX_4,3,140,236,178, EB_DRAW,(XCHAR*)str3, 50 ,runScheme);
}

void CreateRun_prog5(void)
{
		if(testBit(kvo_stat, KVO_STAT)/* kvo_stat*/ == 0)
		{
			sprintf(str1,"STEP  = ");
			ValToStr(TYPE_GEN,vol_para.prog_step+1, 0,NULL, str1 + strlen(str1));
		}
		else
			sprintf(str1,"ALL STEPS DONE");
		EbCreate(Run_OBJ_EDITBOX_2,3,48,236,86,EB_DRAW,(XCHAR*)str1,50,runScheme);
	 	
		sprintf(str2,"RATE = ");
		ValToStr(TYPE_RATE,0, vol_para.rate,NULL, str2 + strlen(str2));
		EbCreate(Run_OBJ_EDITBOX_3,3,94,236,132,EB_DRAW,(XCHAR*)str2,50,runScheme);
	
		sprintf(str3,"INFUSED = ");
		ValToStr(TYPE_VOLUME,0, vol_para.infsd,NULL, str3 + strlen(str3));
		EbCreate(Run_OBJ_EDITBOX_4,3,140,236,178, EB_DRAW,(XCHAR*)str3, 50 ,runScheme);

}


