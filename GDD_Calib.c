/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_CALIB_PUB
#include "include.h"

// Strings
const __prog__ GFX_XCHAR __attribute__((space(prog))) Calib_OBJ_STATICTEXT_0_text[] = "CALIBRATION";

//const GFX_XCHAR Calib_OBJ_BUTTON_0_text[] = "EXIT";
const GFX_XCHAR Calib_OBJ_BUTTON_1_text[] = "CONTINUE";
//const GFX_XCHAR Calib_OBJ_BUTTON_2_text[] = "SAVE";

const __prog__ GFX_XCHAR __attribute__((space(prog))) Calib_msg_0[] = {
	"1.OPEN THE DOOR\r\n2.TAKE SET OUT\r\n3.PRESS CONTINUE",
};
const __prog__ GFX_XCHAR __attribute__((space(prog))) Calib_msg_1[] = {
	"4.INSERT \"CALLSET\"\r\n5. CLOSE THE DOOR\r\n6.APPLY ZERO PRESSURE\r\n7.PRESS CONTINUE",
};
const __prog__ GFX_XCHAR __attribute__((space(prog))) Calib_msg_2[] = {
	"8.APPLY 300mmHg\r\nTO \"CALSET\"\r\n9.PRESS CONTINUE",
};
const __prog__ GFX_XCHAR __attribute__((space(prog))) Calib_msg_3[] = {
	"END OF CALIBRATION.\r\nPRESS SAVE TO\r\nSTORE CALIBRATION\r\nRESULTS. THANKS",
};
const __prog__ GFX_XCHAR __attribute__((space(prog))) Calib_msg_4[] = {
	"ERROR CALIBRATION"
};
#define END_CLBR_PG				3
#define ERROR_CLBR_PG			4

#define PREPARE_ZERO_CLBR	0
#define PRESS1_ZERO_CLBR	1
#define PRESS2_ZERO_CLBR	2
#define END_ZERO_CLBR			3
#define SET_ZERO_CLBR			4
#define END_SETZERO_CLBR	5
#define SET_300_CLBR			6
#define END_CLBR					7

volatile unsigned char calib_status;
unsigned int scale_press1_tmp;
unsigned int scale_press2_tmp;
unsigned int set_press1_tmp;
unsigned int set_press2_tmp; 
unsigned int zero_press1_tmp;
unsigned int zero_press2_tmp; 
unsigned int calib_page;
static unsigned int calibr_val;
static unsigned int elapsedTime;
static GFX_XCHAR	calib_str[87];
static unsigned char time_halfsec;


#define Calib_OBJ_STATICTEXT_0		0
#define Calib_OBJ_BUTTON_0   			1
#define Calib_OBJ_BUTTON_1				2
#define Calib_OBJ_STATICTEXT_1		3
#define Calib_OBJ_STATICTEXT_2		4
#define Calib_OBJ_PICTURE_0			5
#define Calib_OBJ_PICTURE_1			6

void CreateCalib(void)
{
	_prog_addressT p;
	GFX_GOL_ObjectListFree();
	GFX_ColorSet(BLUE_LIGHT);
	GFX_ScreenClear();
	xTimerStart( xTimers[ 1 ], 0 );
	memcpy(basicscheme, defscheme, sizeof(GFX_GOL_OBJ_SCHEME));
	basicscheme->pFont = (void*)&Arial_Narrow_Bold_18;
	 
	calib_page = page_create;
	
	
	switch(calib_page)
	{
		case  0:
			_init_prog_address(p, Calib_msg_0);
			break;
		case  1:
			_init_prog_address(p, Calib_msg_1);
			break;
		case  2:
			_init_prog_address(p, Calib_msg_2);
			break;
		case  3:
			_init_prog_address(p, Calib_msg_3);
			break;
		case  4:
			_init_prog_address(p, Calib_msg_4);
			break;
	}
	_strncpy_p2d16(str_buf1,p,128);
	GFX_GOL_StaticTextCreate(Calib_OBJ_STATICTEXT_1,5,40,238,200,GFX_GOL_STATICTEXT_DRAW_STATE/*|ST_CENTER_ALIGN*/,str_buf1,GFX_ALIGN_LEFT,basicscheme);
//	GFX_GOL_StaticTextCreate(Calib_OBJ_STATICTEXT_1,5,40,238,200,GFX_GOL_STATICTEXT_DRAW_STATE|ST_CENTER_ALIGN,(GFX_XCHAR*)Calib_msg[calib_page],defscheme);
	if(calib_page == 0)
	{
		calibr_val = 0xfff;
		zero_press1_tmp = 0xFFF;
		zero_press2_tmp = 0xFFF;
		calib_status = PREPARE_ZERO_CLBR;  //Stop any calibration process
  }
	GFX_GOL_ButtonCreate(Calib_OBJ_BUTTON_0,5,277,66,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
	if (calib_page != ERROR_CLBR_PG)
	{
		if (calib_page == END_CLBR_PG)
			GFX_GOL_ButtonCreate(Calib_OBJ_BUTTON_1,132,277,232,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)SAVE_OBJ_BUTTON_text,botbar);
		else	 
			GFX_GOL_ButtonCreate(Calib_OBJ_BUTTON_1,132,277,232,313,5,BTN_DRAW,NULL,(GFX_XCHAR*)Calib_OBJ_BUTTON_1_text,botbar);
	}
	
	_init_prog_address(p, Calib_OBJ_STATICTEXT_0_text);
	_strncpy_p2d16(gStr1,p,128);
	GFX_GOL_StaticTextCreate(Calib_OBJ_STATICTEXT_0,1,0,238,30,GFX_GOL_STATICTEXT_DRAW_STATE,gStr1,GFX_ALIGN_CENTER,topbar);
//	GFX_GOL_StaticTextCreate(Calib_OBJ_STATICTEXT_0,1,0,238,30,GFX_GOL_STATICTEXT_DRAW_STATE|ST_CENTER_ALIGN,(GFX_XCHAR*)Calib_OBJ_STATICTEXT_0_text,topbar);
	GFX_GOL_PictureControlCreate(Calib_OBJ_PICTURE_1,202,64,235,263,GFX_GOL_PICTURECONTROL_DRAW_STATE, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)&Pressbar_img,basicscheme);
	

	GFX_GOL_PictureControlCreate(Calib_OBJ_PICTURE_0, 210,0,239,30, GFX_GOL_PICTURECONTROL_DRAW_STATE|PICT_HIDE , IMAGE_NORMAL, getWaitImg(), topbar);
	
	sprintf(calib_str,"Z1=%d   Z2=%d\r\nS1=%d   S1=%d\r\nC1=%d   C2=%d",zero_press1_tmp,zero_press2_tmp,set_press1_tmp,set_press2_tmp,scale_press1_tmp,scale_press2_tmp);
	GFX_GOL_StaticTextCreate(Calib_OBJ_STATICTEXT_2,5,174,170,268,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)calib_str,GFX_ALIGN_LEFT,blackScheme);


}
void CreatePrimitivesForCalib(void){
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

WORD msgCalib(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_TIMER1_ID:			
				//Timer expired
				xTimerStart( xTimers[ 1 ], 0 );
				UpdateCalib();
				break;
			default:
				break;
		}
		return 1;	
	}
	 
	switch (GFX_GOL_ObjectIDGet(pObj)) {
		
		case Calib_OBJ_BUTTON_0:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDPrevScreen();
			}	
			return 1;
		case Calib_OBJ_BUTTON_1:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				if(calib_status < END_CLBR)
				{
//					pObj = GOLFindObject(Calib_OBJ_BUTTON_1);
//					if (pObj) {
					SetState((BUTTON*) pObj, BTN_DRAW|BTN_DISABLED);
//					}
					
					calib_status++;
				
				}
				else
				{
					/*Save eeprom end back to prev screen*/
					zero_press1 = zero_press1_tmp;
					zero_press2 = zero_press2_tmp;
					set_press1 = set_press1_tmp;
					set_press2 = set_press2_tmp;
					scale_press1 = scale_press1_tmp;
					scale_press2 = scale_press2_tmp;
					calib_time = clock();
					vTaskSuspendAll();
					((unsigned int*)&Clbr_E2pImage)[sizeof(Clbr_E2pImage)/2 - 1] = crc16(&Clbr_E2pImage, sizeof(Clbr_E2pImage) - 2);
					SST25SectorErase(CLBR_E2PIMG_BASE);
					if(!SST25WriteArray(CLBR_E2PIMG_BASE, &Clbr_E2pImage, sizeof(Clbr_E2pImage)))
						/*CriticalError("eeprom err")*/;
					xTaskResumeAll();
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDPrevScreen();
				}
			}	
			return 1;
		default:
			break;
	}	

	return 1;	
} 

void UpdateCalib(void)
{
	GFX_GOL_OBJ_HEADER* pObj;
	static unsigned char i;
	static unsigned long lastClock;
//	unsignedsigned int elapsedTime;
	
	if(calib_status == PRESS1_ZERO_CLBR || calib_status == PRESS2_ZERO_CLBR || calib_status == SET_ZERO_CLBR || calib_status == SET_300_CLBR)
	{
			time_halfsec++;
			if(time_halfsec >= 5)
			{
				Beep(250);
				time_halfsec = 0;
			}
			
			pObj = GOLFindObject(Calib_OBJ_PICTURE_0);
			if (pObj) {
				PictSetBitmap(pObj, getWaitImg());
				ClrState(pObj, PICT_HIDE);
				SetState((PICTURE*) pObj, DRAW_UPDATE);
			}
//			pObj = GOLFindObject(Calib_OBJ_BUTTON_1);
//			if (pObj) {
//				SetState((BUTTON*) pObj, BTN_DRAW|BTN_DISABLED);
//			}
			
			elapsedTime += clock_ms() - lastClock;
	}
	else
	{
			pObj = GOLFindObject(Calib_OBJ_PICTURE_0);
			if (pObj) {
				SetState((PICTURE*) pObj, DRAW_UPDATE|PICT_HIDE);
			}
			pObj = GOLFindObject(Calib_OBJ_BUTTON_1);
			if (pObj) {
				ClrState(pObj, BTN_DISABLED);
				SetState((BUTTON*) pObj, BTN_DRAW);
			}
			elapsedTime = 0;
	}
	lastClock = clock_ms();
	
	
	switch(calib_status)
	{
		case PREPARE_ZERO_CLBR:
//			calibr_val = 0xfff;
//			zero_press1_tmp = 0xFFF;
//			zero_press2_tmp = 0xFFF;
			break;
		case PRESS1_ZERO_CLBR:
			vTaskSuspendAll();
			MCP4822Write(0, zero_press1_tmp , 0);
			vTaskDelay( 20 / portTICK_RATE_MS );   // Wait 500ms
			MCP4822Write(0, zero_press1_tmp , 0);
			xTaskResumeAll();
			
//			if(elapsedTime < 500)
//				break;
//			elapsedTime = 0;
			vTaskDelay( 500 / portTICK_RATE_MS );   // Wait 500ms
			
			calibr_val >>= 1;
			if(press1_raw > 5)
			{
				if(zero_press1_tmp > 0)
					zero_press1_tmp -= calibr_val; 
				else
				{
					calib_status = END_CLBR;
					GDDShiftScreen(ERROR_CLBR_PG); //Error calibration
				}
			}
			else
			{
				if((zero_press1_tmp + calibr_val) <= 0xfff)
					zero_press1_tmp += calibr_val; 
				else
				{
					calib_status = END_CLBR;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDShiftScreen(ERROR_CLBR_PG); //Error calibration
				}
			}
			if(calibr_val == 1)
			{
				calibr_val = 0xfff;
				calib_status++;
				elapsedTime = 0;
				lastClock = clock_ms();
			}
			break;
		case PRESS2_ZERO_CLBR:
			vTaskSuspendAll();
			MCP4822Write(1, zero_press2_tmp , 0);
			xTaskResumeAll();
//			if(elapsedTime < 500)
//				break;
//			elapsedTime = 0;
			vTaskDelay( 500 / portTICK_RATE_MS );   // Wait 500ms
			
			calibr_val >>= 1;
			if(press2_raw > 5)
			{
				if(zero_press2_tmp > 0)
					zero_press2_tmp -= calibr_val; 
				else
				{
					calib_status = END_CLBR;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDShiftScreen(ERROR_CLBR_PG); //Error calibration
				}
			}
			else
			{
				if((zero_press2_tmp + calibr_val) <= 0xfff)
					zero_press2_tmp += calibr_val; 
				else
				{
					calib_status = END_CLBR;
					if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
	   	     			xTimerStop( xTimers[ 1 ], 0 );
					GDDShiftScreen(ERROR_CLBR_PG); //Error calibration
				}
			}
			if(calibr_val == 1)
			{
				calib_page++;
				GDDShiftScreen(calib_page);
				calib_status++;
				vTaskSuspendAll();
				MCP4822Write(0, zero_press1_tmp , 0);
				MCP4822Write(1, zero_press2_tmp , 0);
				xTaskResumeAll();
			}
			break;
		case END_ZERO_CLBR:
			i = 0;
			set_press1_tmp = set_press2_tmp = 0;
			break;
		case SET_ZERO_CLBR:
//			if(elapsedTime < 1000)
//				break;
//			elapsedTime = 0;
			if ( i < 4)
			{
				vTaskDelay( 500 / portTICK_RATE_MS );   // Wait 500ms
				set_press1_tmp += press1_raw; 
				set_press2_tmp += press2_raw; 
				i++;
//			if( set_press1_tmp == 0 || set_press2_tmp == 0 || set_press1_tmp == 0xfff || set_press2_tmp == 0xfff )
//			{
//					calib_status = END_CLBR;
//					GDDShiftScreen(ERROR_CLBR_PG); //Error calibration
//			}
			}
			
			else
			{
				set_press1_tmp = set_press1_tmp>>2;
				set_press2_tmp = set_press2_tmp>>2;
				calib_page++;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(calib_page);
				calib_status++;
			}
			break;
		case END_SETZERO_CLBR:
			i = 0;
			scale_press1_tmp = scale_press2_tmp = 0;
			break;
		case SET_300_CLBR:
//			if(elapsedTime < 1000)
//				break;
//			elapsedTime = 0;
			
			if ( i < 4)
			{
				vTaskDelay( 500 / portTICK_RATE_MS );   // Wait 500ms
				scale_press1_tmp += press1_raw - set_press1_tmp;
				scale_press2_tmp += press2_raw - set_press2_tmp;
//				scale_press1_tmp = press1_raw; 
//				scale_press2_tmp = press2_raw; 
				i++;
//			if( scale_press1_tmp == 0 || scale_press2_tmp == 0 || scale_press1_tmp == 0xfff || scale_press2_tmp == 0xfff )
//			{
//					calib_status = END_CLBR;
//					GDDShiftScreen(ERROR_CLBR_PG); //Error calibration
//			}
			}
			else
			{
				scale_press1_tmp = scale_press1_tmp>>2;
				scale_press2_tmp = scale_press2_tmp>>2;
				calib_page++;
				if( xTimerIsTimerActive( xTimers[ 1 ] ) != pdFALSE ) 
   	     			xTimerStop( xTimers[ 1 ], 0 );
				GDDShiftScreen(calib_page);
				calib_status++;
			}
			break;

		case END_CLBR:
			break;

	}

}


