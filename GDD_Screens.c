/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_SCREENS_PUB
#include "include.h"

// Strings


SCREEN_CONTROL_BLOCK Screen_CB_array[NUM_GDD_SCREENS]= 
{
{&CreateIntro,	 &CreatePrimitivesForIntro,		NULL, 0,0,0,NULL,NULL},   
{&CreateClear,   &CreatePrimitivesForClear,		NULL, 0,0,0,NULL,NULL},
{&CreateConfirm, &CreatePrimitivesForConfirm,	NULL, 0,0,0,NULL,NULL},
{&CreateRun,	   &CreatePrimitivesForRun,			NULL, 0,0,0,NULL,NULL},
{&CreateSetprog, &CreatePrimitivesForSetprog,	NULL, 0,0,0,NULL,NULL},
{&CreateSetdrug, &CreatePrimitivesForSetdrug,	NULL, 0,0,0,NULL,NULL},
{&CreateAdjust,  &CreatePrimitivesForAdjust,	NULL, 0,0,0,NULL,NULL},
{&CreatePrime, 	 &CreatePrimitivesForPrime,		NULL, 0,0,0,NULL,NULL},
{&CreateOptions, &CreatePrimitivesForOptions,	NULL, 0,0,0,NULL,NULL},
{&CreateTest, 	 &CreatePrimitivesForTest, 		NULL, 0,0,0,NULL,NULL},
//{&CreateError, 	 &CreatePrimitivesForError, 	NULL, 0,0,0,NULL,NULL,0},
{&CreateAlarm, 	 &CreatePrimitivesForAlarm, 	NULL, 0,0,0,NULL,NULL},
{&CreatePwrdown, &CreatePrimitivesForPwrdown,	NULL, 0,0,0,NULL,NULL},
{&CreateCalib,	 &CreatePrimitivesForCalib,		NULL, 0,0,0,NULL,NULL},
{&CreateRCalib,	 &CreatePrimitivesForRCalib,	NULL, 0,0,0,NULL,NULL},
{&CreateBolus,	 &CreatePrimitivesForBolus,		NULL, 0,0,0,NULL,NULL},
{&CreateSetmenu, &CreatePrimitivesForSetmenu,	NULL, 0,0,0,NULL,NULL},
{&CreateSetup,	 &CreatePrimitivesForSetup,		NULL, 0,0,0,NULL,NULL},
{&CreateCheckup, &CreatePrimitivesForCheckup,	NULL, 0,0,0,NULL,NULL},
};

static unsigned char changescr_flg;

//  GOL Set screen
void GDDSetScreen(unsigned char new_scr,unsigned char param1,void *param2)
{
SCREEN_MSG scr_msg;	
	Screen_CB_array[(new_scr+1)/2].prev = screenState - 1;
	scr_msg.cmd = new_scr ;
	xQueueSend(hSCREENQueue, &scr_msg, 0);
//	screenState = new_scr;
	Screen_CB_array[(new_scr+1)/2].opt = param1;
	Screen_CB_array[(new_scr+1)/2].arg = param2;
}

//  GOL Set screen
void GDDShiftScreen(unsigned char param)
{
SCREEN_MSG scr_msg;	
	scr_msg.cmd = screenState - 1;
	xQueueSend(hSCREENQueue, &scr_msg, 0);
//	screenState -=1;
	Screen_CB_array[(screenState - 1)/2].opt = param;
}
void GDDPrevScreen(void)
{
SCREEN_MSG scr_msg;	
	scr_msg.cmd = Screen_CB_array[(screenState)/2].prev;
	xQueueSend(hSCREENQueue, &scr_msg, 0);
}
				
void GDDSetScreenwPswd(unsigned char new_scr,unsigned char param1,void * param2)
{
	GDDSetScreen(new_scr,param1,param2);
//	screenState++;
	GDDSetScreen(CREATE_SCREEN_SETUP,SETUP_PASSWORD,&pswrd); 
}


//  GOL Create screen
void GDDCreateScreenCallback(unsigned char scr)
{
//	if (xQueueReceive(hQVGAQueue, &msg, portMAX_DELAY) == pdTRUE);
	
	scr = scr/2;
	(*Screen_CB_array[scr].Create)();
	if(Screen_CB_array[scr].CreatePrimitives != NULL)
		(*Screen_CB_array[scr].CreatePrimitives)();
//	release

}

#if 0
//  GOL Message Callback
void GDDDemoGOLMsgCallback(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
	//Future event handling support by GDD
}
#endif

//void (*CreateFunctionArray[NUM_GDD_SCREENS])(void)=
//{
//&CreateIntro,&CreateClear,&CreateSetprog,&CreateAdjust,&CreatePrewSet,&CreateOptions
//};

//void (*CreatePrimitivesFunctionArray[NUM_GDD_SCREENS])(void)=
//{
//&CreatePrimitivesForIntro,&CreatePrimitivesForClear,&CreatePrimitivesForSetprog,&CreatePrimitivesForAdjust,&CreatePrimitivesForPrewSet,&CreatePrimitivesForOptions
//};

/*********************************************************************
 * Function:       void CreateSchemes(void) 
 *
 * PreCondition:    None
 *
 * Input:           None
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Create the styles used by the various screens
 *					Since the creation process involves calls
 *					to malloc/free vai the GOL we suspend all
 *					other tasks from executing because the standard
 *					malloc/free are not re-entrant
 *
 * Note:            
 ********************************************************************/
void CreateSchemes(void)
{
	vTaskSuspendAll();
	
	// Initialize the GOL
	GOLInit();
	ANSAbits.ANSA7 = 1;  //because GOLInit reinitialise PRESS2  analog input back to digital


	if(green_sch != NULL) free(green_sch);
	green_sch = GOLCreateScheme();
	green_sch->Color0 = GREEN;
	green_sch->Color1 = GREEN;
	green_sch->ColorDisabled = GREEN;
	green_sch->CommonBkColor = GREEN;
	green_sch->EmbossDkColor = GREEN;
	green_sch->EmbossLtColor = GREEN;
	green_sch->TextColor0 = BLACK;
	green_sch->TextColor1 = BLACK;
	green_sch->pFont = (void*)&arial_narrow_0_0_0_14;
	
	
	if(basicscheme != NULL) free(basicscheme);
	basicscheme = GOLCreateScheme();
	basicscheme->Color0 = 11542;
	basicscheme->Color1 = 64969;
	basicscheme->ColorDisabled = 55070;
	basicscheme->CommonBkColor = 59196;
	basicscheme->EmbossDkColor = 6172;
	basicscheme->EmbossLtColor = 44765;
	basicscheme->TextColor0 = 64520;
	basicscheme->TextColor1 = 31;
	basicscheme->pFont = (void*)&arial_narrow_0_0_0_14;

	if(topbar != NULL) free(topbar);
	topbar = GOLCreateScheme();
	topbar->Color0 = BLUE_DARK;
	topbar->Color1 = BLUE_DARK;
	topbar->ColorDisabled = GRAY;
	topbar->TextColorDisabled = GRAY_LIGHT;
	topbar->CommonBkColor = BLUE_DARK;
	topbar->EmbossDkColor = BLUE_DARK;
	topbar->EmbossLtColor = BLUE_DARK;
	topbar->TextColor0 = WHITE;
	topbar->TextColor1 = WHITE;
//	topbar->pFont = (void*)&arial_narrow_0_0_0_14;
	topbar->pFont = (void*)&Arial_Narrow_26;
	
	if(basicbig != NULL) free(basicbig);
	basicbig = GOLCreateScheme();
	basicbig->Color0 = 19583;
	basicbig->Color1 = 64969;
	basicbig->ColorDisabled = 55070;
	basicbig->CommonBkColor = 59196;
	basicbig->EmbossDkColor = 6172;
	basicbig->EmbossLtColor = 44765;
	basicbig->TextColor0 = 64520;
	basicbig->TextColor1 = 31;
	basicbig->pFont = (void*)&arial_narrow_0_0_0_20;
	
	if(defscheme != NULL) free(defscheme);
	defscheme = GOLCreateScheme();
	defscheme->Color0 = WHITE;
	defscheme->Color1 = GRAY_LIGHT;
	defscheme->ColorDisabled = 55070;
	defscheme->CommonBkColor = BLUE_LIGHT;
	defscheme->EmbossDkColor = BLUE_DARK;
	defscheme->EmbossLtColor = BLUE_DARK;
	defscheme->TextColor0 = BLACK;
	defscheme->TextColor1 = BLACK;//WHITE;
	defscheme->pFont = (void*)&Arial_Narrow_26;
	
	if(botbar != NULL) free(botbar);
	botbar = GOLCreateScheme();
	botbar->Color0 = BLUE_DARK;
	botbar->Color1 = BLUE_LIGHT;
	botbar->ColorDisabled = 55070;
	botbar->CommonBkColor = BLUE_LIGHT;
	botbar->EmbossDkColor = WHITE;
	botbar->EmbossLtColor = WHITE;
	botbar->TextColor0 = WHITE;
	botbar->TextColor1 = WHITE;
	botbar->pFont = (void*)&Arial_Narrow_Bold_18;
	
#if 0	
	// create the display schemes
	btnSchemeSmall = GOLCreateScheme();
	btnSchemeSmall->EmbossDkColor = RGB565CONVERT(0x1E, 0x00, 0xE5);
	btnSchemeSmall->EmbossLtColor = RGB565CONVERT(0xA9, 0xDB, 0xEF);
	btnSchemeSmall->TextColor0 = RGB565CONVERT(0x1E, 0x00, 0xE5);
	btnSchemeSmall->TextColor1 = RGB565CONVERT(0x1E, 0x00, 0xE5);
	btnSchemeSmall->TextColorDisabled = RGB565CONVERT(0xFF, 0xFF, 0xFF);
	btnSchemeSmall->Color0 = RGB565CONVERT(0x1E, 0x00, 0xE5);
	btnSchemeSmall->Color1 = RGB565CONVERT(0x1E, 0x00, 0xE5);
	btnSchemeSmall->ColorDisabled = RGB565CONVERT(0x1E, 0x00, 0xE5);
	btnSchemeSmall->CommonBkColor = RGB565CONVERT(0x1E, 0x00, 0xE5);
	btnSchemeSmall->pFont = (void*) &GOLSmallFont;
	
	btnSchemeMedium = GOLCreateScheme();
	memcpy(btnSchemeMedium, btnSchemeSmall, sizeof(GOL_SCHEME));
	btnSchemeMedium->pFont = (void*) &GOLMediumFont;
	
	blueScheme = GOLCreateScheme();
	blueScheme->TextColor0 = BLACK;
	blueScheme->TextColor1 = BLACK;
	blueScheme->TextColorDisabled = BLACK;
	
	greenScheme = GOLCreateScheme();
	greenScheme->Color0 = RGB565CONVERT(0x23, 0x9E, 0x0A);
	greenScheme->Color1 = BRIGHTGREEN;
	greenScheme->ColorDisabled = RGB565CONVERT(0x23, 0x9E, 0x0A);
	greenScheme->EmbossDkColor = DARKGREEN;
	greenScheme->EmbossLtColor = PALEGREEN;
	greenScheme->TextColor0 = RGB565CONVERT(0xFF, 0xFF, 0xFF);
	greenScheme->TextColor1 = BLACK;
	greenScheme->TextColorDisabled = RGB565CONVERT(0xDF, 0xAC, 0x83);

	redScheme = GOLCreateScheme();
	redScheme->Color0 = RGB565CONVERT(0xCC, 0x00, 0x00);
	redScheme->Color1 = BRIGHTRED;
	redScheme->EmbossDkColor = RED4;
	redScheme->EmbossLtColor = FIREBRICK1;
	redScheme->TextColor0 = RGB565CONVERT(0xC8, 0xD5, 0x85);
	redScheme->TextColor1 = BLACK;

	whiteScheme = GOLCreateScheme();
	whiteScheme->EmbossDkColor = RGB565CONVERT(0x40, 0x40, 0x40);
	whiteScheme->EmbossLtColor = RGB565CONVERT(0xE0, 0xE0, 0xE0);
	whiteScheme->TextColor0 = RGB565CONVERT(0x00, 0x00, 0x00);
	whiteScheme->TextColor1 = RGB565CONVERT(0x00, 0x00, 0x00);
	whiteScheme->TextColorDisabled = RGB565CONVERT(0x00, 0x00, 0x00);
	whiteScheme->Color0 = RGB565CONVERT(0xA0, 0xA0, 0xA0);
	whiteScheme->Color1 = RGB565CONVERT(0xA0, 0xA0, 0xA0);
	whiteScheme->ColorDisabled = RGB565CONVERT(0xFF, 0xFF, 0xFF);
	whiteScheme->CommonBkColor = RGB565CONVERT(0xFF, 0xFF, 0xFF);
	whiteScheme->pFont = (void*) &GOLFontDefault;
	   
#endif
	blackScheme = GOLCreateScheme();
	memcpy(blackScheme, botbar, sizeof(GOL_SCHEME));
	blackScheme->Color0 = BLACK;
	blackScheme->CommonBkColor = BLACK;
	blackScheme->TextColor0 = RGB565CONVERT(0xFF, 0xFF, 0xFF);
	blackScheme->TextColor1 = BLACK;
//	blackScheme->pFont = (void*) &GOLMediumFont;

	ConfirmShemes();
	AlarmShemes();
	BolusShemes();
	PrimeShemes();
	RunShemes();
	PwrdownShemes();
	
	xTaskResumeAll();
}

GFX_IMAGE_HEADER* getWaitImg(void)
{
	static unsigned char i;
	GFX_IMAGE_HEADER *pBtmap;
	if(i < 7)
		i++;
	else
		i=0;
	switch(i)
	{
		case 1:
			pBtmap = (GFX_IMAGE_HEADER *)&Wait2;
			break;
		case 2:
			pBtmap = (GFX_IMAGE_HEADER *)&Wait3;
			break;
		case 3:
			pBtmap = (GFX_IMAGE_HEADER *)&Wait4;
			break;
		case 4:
			pBtmap = (GFX_IMAGE_HEADER *)&Wait5;
			break;
		case 5:
			pBtmap = (GFX_IMAGE_HEADER *)&Wait6;
			break;
		case 6:
			pBtmap = (GFX_IMAGE_HEADER *)&Wait7;
			break;
		case 7:
			pBtmap = (GFX_IMAGE_HEADER *)&Wait8;
			break;
		case 0:
		default:
			pBtmap = (GFX_IMAGE_HEADER *)&Wait1;
			break;
	}
	return pBtmap;
}

GFX_IMAGE_HEADER* getBatImg(unsigned char batlevel)
{
	GFX_IMAGE_HEADER *pBtmap;
	if ( batt_raw > AC_MIN)
		return (GFX_IMAGE_HEADER *)&BatAC;
	
	switch(batlevel)
	{
		case 0:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat1;
			break;
		case 1:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat2;
			break;
		case 2:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat3;
			break;
		case 3:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat4;
			break;
		case 4:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat5;
			break;
		case 5:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat6;
			break;
		case 6:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat7;
			break;
		case 7:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat8;
			break;
		case 8:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat9;
			break;
		default:
		case 9:
			pBtmap = (GFX_IMAGE_HEADER *)&Bat10;
			break;
	}
	return pBtmap;
}



