/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_OPTIONS_PUB
#include "include.h"


extern USB_HANDLE USBGenericInHandle;
// Strings
const XCHAR Options_OBJ_STATICTEXT_0_text[] = "OPTIONS";
const XCHAR Options_OBJ_STATICTEXT_1_text[] = "BUZZER VOLUME";
const XCHAR Options_OBJ_STATICTEXT_2_text[] = "OCC. LIMIT";
const XCHAR Options_OBJ_STATICTEXT_3_text[] = "Wrong PASSWORD";

const XCHAR Options_OBJ_BUTTON_0_text[] = "SET PROGRAM";
const XCHAR Options_OBJ_BUTTON_1_text[] = "SET PARAMETER";
const XCHAR Options_OBJ_BUTTON_2_text[] = "PUMP TESTING";
const XCHAR Options_OBJ_BUTTON_3_text[] = "SET DATE";
const XCHAR Options_OBJ_BUTTON_4_text[] = "SET TIME";
const XCHAR Options_OBJ_BUTTON_5_text[] = "FACTORY DEFAULT";
const XCHAR Options_OBJ_BUTTON_6_text[] = "PRESS CALIBRATION";
const XCHAR Options_OBJ_BUTTON_10_text[] = "DRUGS PROTOCOL";
//const XCHAR Options_OBJ_BUTTON_11_text[] = "EXTERN FLASH";
const XCHAR Options_OBJ_BUTTON_11_text[] = "RATE CALIBRATION";
const XCHAR Options_OBJ_BUTTON_15_text[] = "HIGH";
const XCHAR Options_OBJ_BUTTON_16_text[] = "MED";
const XCHAR Options_OBJ_BUTTON_17_text[] = "LOW";
const XCHAR Options_OBJ_BUTTON_18_text[] = "TEST";


#define Options_OBJ_STATICTEXT_0   0
#define Options_OBJ_STATICTEXT_1   1
#define Options_OBJ_STATICTEXT_2   2
#define Options_OBJ_STATICTEXT_3   3
#define Options_OBJ_BUTTON_0   4
#define Options_OBJ_BUTTON_1   5
#define Options_OBJ_BUTTON_2   6
#define Options_OBJ_BUTTON_3   7
#define Options_OBJ_BUTTON_4   8
#define Options_OBJ_BUTTON_5   9
#define Options_OBJ_BUTTON_6   10
#define Options_OBJ_BUTTON_7   11
#define Options_OBJ_BUTTON_8   12
#define Options_OBJ_BUTTON_9   13
#define Options_OBJ_BUTTON_10   14
#define Options_OBJ_BUTTON_11   15

#define Options_OBJ_BUTTON_12   16
#define Options_OBJ_BUTTON_13   17
#define Options_OBJ_BUTTON_14   18
#define Options_OBJ_BUTTON_15   19
#define Options_OBJ_BUTTON_16   20
#define Options_OBJ_BUTTON_17   21
#define Options_OBJ_BUTTON_18   22

#define Options_OBJ_PICTURE_0	23
#define Options_OBJ_PICTURE_1	24
#define Options_OBJ_PICTURE_2	25
#define Options_OBJ_PICTURE_3	26
#define Options_OBJ_PICTURE_4	27

void CreateOptions(void)
{
	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();
	xTimerStart( xTimers[ 1 ], 0 );
	
	if(page_create > 1)
	{
		if(pswrd != 12345)
			page_create = 4;	
	}
	   
	if(page_create == 0)
	{
		BtnCreate(Options_OBJ_BUTTON_12,18,139,60,181,10,BTN_DRAW,(void *)&Speaker0,NULL,defscheme);
		BtnCreate(Options_OBJ_BUTTON_13,89,139,131,181,10,BTN_DRAW,(void *)&Speaker1,NULL,defscheme);
		BtnCreate(Options_OBJ_BUTTON_14,160,139,202,181,10,BTN_DRAW,(void *)&Speaker2,NULL,defscheme);
	
		BtnCreate(Options_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,(void *)&Rarrow,/*(XCHAR*)Options_OBJ_BUTTON_9_text*/NULL,botbar);
		StCreate(Options_OBJ_STATICTEXT_1,0,0,239,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Options_OBJ_STATICTEXT_1_text,topbar);
	
	}
	else if(page_create == 1)
	{
		memcpy(basicscheme, defscheme, sizeof(GOL_SCHEME));
	
		basicscheme->Color1 = GRAY_RUN;
		basicscheme->Color0 = YELLOW_RUN;
		basicscheme->TextColor0 = BLACK;
		basicscheme->TextColorDisabled = YELLOW_RUN;
		basicscheme->pFont = (void*) &Arial_Narrow_Bold_18;
		basicscheme->EmbossDkColor = GRAY_RUN;
		basicscheme->EmbossLtColor = GRAY_RUN;
		basicscheme->CommonBkColor = GRAY_RUN;
		
		PictCreate(Options_OBJ_PICTURE_1,162,64,195,263,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&Pressbar_img,basicscheme);
	
		
//		40,46,200,270
		BtnCreate(Options_OBJ_BUTTON_15,50,60,100,95,5,BTN_DRAW,/*(void *)&Larrow*/NULL,(XCHAR*)Options_OBJ_BUTTON_15_text,basicscheme);
		BtnCreate(Options_OBJ_BUTTON_16,50,145,100,180,5,BTN_DRAW,/*(void *)&Larrow*/NULL,(XCHAR*)Options_OBJ_BUTTON_16_text,basicscheme);
		BtnCreate(Options_OBJ_BUTTON_17,50,230,100,265,5,BTN_DRAW,/*(void *)&Larrow*/NULL,(XCHAR*)Options_OBJ_BUTTON_17_text,basicscheme);
		
//		sprintf(run_str1,"%d",occlus_lmt[0]);
//		EbCreate(Run_OBJ_EDITBOX_0,42,96,135,122, EB_DRAW,(XCHAR*)run_str1, 50 ,runGrayScheme);
//		sprintf(run_str2,"%d",occlus_lmt[1]);
//		EbCreate(Run_OBJ_EDITBOX_1,42,240,135,266, EB_DRAW,(XCHAR*)run_str2, 50 ,runGrayScheme);
//		sprintf(run_str2,"%d",occlus_lmt[2]);
//		EbCreate(Run_OBJ_EDITBOX_1,42,240,135,266, EB_DRAW,(XCHAR*)run_str2, 50 ,runGrayScheme);
		

		PictCreate(Options_OBJ_PICTURE_2,148,100,160,112 ,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&Pointer_img,basicscheme);
		PictCreate(Options_OBJ_PICTURE_3,148,164,160,176 ,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&Pointer_img,basicscheme);
		PictCreate(Options_OBJ_PICTURE_4,148,228,160,240 ,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&Pointer_img,basicscheme);
		   
		BtnCreate(Options_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,(void *)&Larrow,/*(XCHAR*)Options_OBJ_BUTTON_8_text*/NULL,botbar);
		BtnCreate(Options_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,(void *)&Rarrow,/*(XCHAR*)Options_OBJ_BUTTON_9_text*/NULL,botbar);
		StCreate(Options_OBJ_STATICTEXT_2,0,0,239,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Options_OBJ_STATICTEXT_2_text,topbar);

	 
	}
	else if(page_create == 2)
	{
		
		BtnCreate(Options_OBJ_BUTTON_0,3,48,236,86,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_0_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_1,3,94,236,132,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_1_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_2,3,140,236,178,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_2_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_3,3,186,236,224,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_3_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_4,3,232,236,270,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_4_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,(void *)&Larrow,/*(XCHAR*)Options_OBJ_BUTTON_8_text*/NULL,botbar);
		BtnCreate(Options_OBJ_BUTTON_9,170,277,230,313,5,BTN_DRAW,(void *)&Rarrow,/*(XCHAR*)Options_OBJ_BUTTON_9_text*/NULL,botbar);
		StCreate(Options_OBJ_STATICTEXT_0,0,0,239,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Options_OBJ_STATICTEXT_0_text,topbar);
	
	}
	else if(page_create == 3)
	{
		BtnCreate(Options_OBJ_BUTTON_5,3,48,236,86,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_5_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_6,3,94,236,132,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_6_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_10,3,140,236,178,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_10_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_11,3,186,236,224,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_11_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_18,3,232,236,270,10,BTN_DRAW,NULL,(XCHAR*)Options_OBJ_BUTTON_18_text,defscheme);
		BtnCreate(Options_OBJ_BUTTON_8,92,277,152,313,5,BTN_DRAW,(void *)&Larrow,/*(XCHAR*)Options_OBJ_BUTTON_8_text*/NULL,botbar);
		StCreate(Options_OBJ_STATICTEXT_0,0,0,239,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Options_OBJ_STATICTEXT_0_text,topbar);
	}
    else
	{
		StCreate(Options_OBJ_STATICTEXT_0,0,0,239,30,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Options_OBJ_STATICTEXT_0_text,topbar);
		StCreate(Options_OBJ_STATICTEXT_3,10,60,228,160,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)Options_OBJ_STATICTEXT_3_text,defscheme);
	
	}

	BtnCreate(Options_OBJ_BUTTON_7,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);

	PictCreate(Options_OBJ_PICTURE_0, 209,0,239,30, PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&setting, topbar);

}
void CreatePrimitivesForOptions(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		SetColor(BLUE_DARK);
//		while(!Bar(0,279,239,319));
	if(page_create == 1)
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(40,46,200,270));
		
//		SetLineType(0);
//		SetLineThickness(0);
//		SetColor(GRAY_RUN);
//		while(!Bar(168,66,188,260));
		
		SetColor(YELLOW_RUN);
		while(!Bar(168, 260 - ((260-66)/6)*((vol_para.occlusion_lmt)*2+1),188,260));
	
	}
	else if(page_create == 0)
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(10,200,230,220));
		 
		SetColor(YELLOW_RUN);
		while(!Bar(10, 200, ((230-10)/6) *((2-bzz_volume)*2+1),220));
		
		
	}
}

void UpdateOptions(void)
{
	
	OBJ_HEADER* pObj;

#if 0
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
	 
	pObj = GOLFindObject(Run_OBJ_EDITBOX_4);
	if (pObj) {
		if(vol_para.infsd < 100.0)
	 		sprintf(run_str3,"INFUSED = %.1f ml",(double)vol_para.infsd);
	 	else
	 		sprintf(run_str3,"INFUSED = %.0f ml",(double)vol_para.infsd);
		EbSetText((EDITBOX*)pObj,run_str3); 
 		SetState((EDITBOX*) pObj, EB_DRAW);
	}
#endif

	if(page_display == 1)
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(168,66,188,260));
		
		SetColor(YELLOW_RUN);
		while(!Bar(168, 260 - ((260-66)/6)*((vol_para.occlusion_lmt)*2+1),188,260));
	}
#if 0	
	else if(page_display == 0)
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(10,200,230,220));
		 
		SetColor(YELLOW_RUN);
		while(!Bar(10, 200, ((230-10)/6) *((2-bzz_volume)*2+1),220));
	}
#endif	
	return 1;	

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

WORD msgOptions(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_TIMER1_ID:			
				//Timer expired
//				xTimerStart( xTimers[ 1 ], 0 );
				UpdateOptions();
				break;
			default:
				break;
		}
		
		return 1;	
	}
	
	switch (GetObjID(pObj)) {
		
		case Options_OBJ_BUTTON_11:                      //Rate calibration
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_RATECALIB,0,NULL);
			}	
#if 0
			if (objMsg == BTN_MSG_RELEASED) {
					 
				PMCON2bits.MSTSEL = 0;		// set CPU as Master
        // Call the external flash programming routine
        ProgramFlash();
#if defined (USE_COMM_PKT_MEDIA_USB)
        // check if USB has sent reply to host then do a detach
        while(!USBHandleBusy(USBGenericInHandle));
        USBDeviceDetach();
        // delay the reset to have time for the acknowledge data to be sent to the host side
        DelayMs(100);
#elif defined (USE_COMM_PKT_MEDIA_SERIAL_PORT)
        // check if UART is still busy sending replies to the host
        while(U2STAbits.TRMT);
        // delay the reset to have time for the acknowledge data to be sent to the host side
        DelayMs(10);
#endif
        // Force Reset to force the checking of the flash memory if programming was a success
        Reset();
			}	
#endif			
			return 1;
		case Options_OBJ_BUTTON_7:
			if (objMsg == BTN_MSG_RELEASED) {
				if(page_display == 4)
				{
					page_display = 1;
					GDDShiftScreen(page_display); //1st screen
				}
				else
				{
					GDDPrevScreen();
//					pswrd = 0;
				}

			}	
			return 1;
		case Options_OBJ_BUTTON_8:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, &Larrow_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap((BUTTON*)pObj, &Larrow);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
					if(page_display > 0)
						page_display--;
					GDDShiftScreen(page_display); //1st screen
			}	
			return 1;
			
		case Options_OBJ_BUTTON_9:
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
					if(page_display < 3)
						page_display++;
					if(page_display == 2 && pswrd != 12345)
					{
//						pswrd = 0;
//						GDDSetScreenwPswd(CREATE_SCREEN_OPTIONS,page_display,NULL);
						GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_PASSWORD,NULL); 
					}
					else
						GDDShiftScreen(page_display); //2nd screen
				}

			}	
			return 1;
		case Options_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_SETPROG,0,NULL);
			}	
			return 1;
		case Options_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_RELEASED) {
				memcpy((unsigned char*)&E2pImage_tmp,(unsigned char*)&E2pImage,sizeof(E2pImage_t));
//				GDDSetScreenwPswd(CREATE_SCREEN_SETMENU,0,NULL);
				GDDSetScreen(CREATE_SCREEN_SETMENU,0,NULL); //Set parameters

			}	
			return 1;
		case Options_OBJ_BUTTON_2:                        //Checkup
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_CHECKUP,0,NULL);
			}	
			return 1;
		case Options_OBJ_BUTTON_3:
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_DATE,NULL);  //data
				/*TODO update RTC*/
			}	
			return 1;
		case Options_OBJ_BUTTON_4:
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_TIME,NULL);  //Time
			}	
			return 1;
		case Options_OBJ_BUTTON_5:                   //Defaults
			if (objMsg == BTN_MSG_RELEASED) {
				vTaskSuspendAll();
				set_defaults();
				xTaskResumeAll();
				GDDShiftScreen(0); // Refresh screen
			}	
			return 1;
		case Options_OBJ_BUTTON_6:                  //Press calibration
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_CALIB,0,NULL);
			}	
			return 1;
		case Options_OBJ_BUTTON_10:		//Drugs Protocol
			return 1;
		
		case Options_OBJ_BUTTON_12:
			if (objMsg == BTN_MSG_RELEASED) {
				bzz_volume = 2;
				Beep(1000);
				/* put checksum to the last halfword */
  				((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
				vTaskSuspendAll();
				SST25SectorErase(PARAM_E2PIMG_BASE);
				if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)))
					/*CriticalError("eeprom err")*/;
				xTaskResumeAll();
//				GDDSetScreen(CREATE_SCREEN_CALIB,0,NULL);
			}	
			break;
		case Options_OBJ_BUTTON_13:
			if (objMsg == BTN_MSG_RELEASED) {
				bzz_volume = 1;
				Beep(1000);
				/* put checksum to the last halfword */
  				((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
				vTaskSuspendAll();
				SST25SectorErase(PARAM_E2PIMG_BASE);
				if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)))
					/*CriticalError("eeprom err")*/;
				xTaskResumeAll();

//				GDDSetScreen(CREATE_SCREEN_CALIB,0,NULL);
			}	
			break;
		case Options_OBJ_BUTTON_14:
			if (objMsg == BTN_MSG_RELEASED) {
				bzz_volume = 0;
				Beep(1000);
				/* put checksum to the last halfword */
  				((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
				vTaskSuspendAll();
				SST25SectorErase(PARAM_E2PIMG_BASE);
				if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)))
					/*CriticalError("eeprom err")*/;
				xTaskResumeAll();
//				GDDSetScreen(CREATE_SCREEN_CALIB,0,NULL);
			}	
			break;
		case Options_OBJ_BUTTON_15:
			if (objMsg == BTN_MSG_RELEASED) {
				vol_para.occlusion_lmt = 2;
				/* put checksum to the last halfword */
  				((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
				vTaskSuspendAll();
				SST25SectorErase(PARAM_E2PIMG_BASE);
				if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)))
					/*CriticalError("eeprom err")*/;
				xTaskResumeAll();
//				GDDSetScreen(CREATE_SCREEN_CALIB,0,NULL);
			}	
			break;
		case Options_OBJ_BUTTON_16:
			if (objMsg == BTN_MSG_RELEASED) {
				vol_para.occlusion_lmt = 1;
				/* put checksum to the last halfword */
  				((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
				vTaskSuspendAll();
				SST25SectorErase(PARAM_E2PIMG_BASE);
				if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)))
					/*CriticalError("eeprom err")*/;
				xTaskResumeAll();

//				GDDSetScreen(CREATE_SCREEN_CALIB,0,NULL);
			}	
			break;
		case Options_OBJ_BUTTON_17:
			if (objMsg == BTN_MSG_RELEASED) {
				vol_para.occlusion_lmt = 0;
				/* put checksum to the last halfword */
  				((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
				vTaskSuspendAll();
				SST25SectorErase(PARAM_E2PIMG_BASE);
				if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)))
					/*CriticalError("eeprom err")*/;
				xTaskResumeAll();
//				GDDSetScreen(CREATE_SCREEN_CALIB,0,NULL);
			}	
			break;
		case Options_OBJ_BUTTON_18:
			if (objMsg == BTN_MSG_RELEASED) {
				GDDSetScreen(CREATE_SCREEN_TEST,0,NULL);
			}	
			return 1;
		default:
			break;
	}	
	if(page_display == 1)
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(168,66,188,260));
		
		SetColor(YELLOW_RUN);
		while(!Bar(168, 260 - ((260-66)/6)*((vol_para.occlusion_lmt)*2+1),188,260));
	
	}
	else if(page_display == 0)
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(10,200,230,220));
		 
		SetColor(YELLOW_RUN);
		while(!Bar(10, 200, ((230-10)/6) *((2-bzz_volume)*2+1),220));
	}
	return 1;	
} 
