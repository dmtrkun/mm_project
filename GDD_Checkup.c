/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_CHECKUP_PUB
#include "include.h"
#include <stdio.h>

//const XCHAR Checkup_OBJ_STATICTEXT_1_text[] = "Working Time:";
//const XCHAR Checkup_OBJ_STATICTEXT_2_text[] = "Press \"Clear\" \r\nand wait for RESET";
const __prog__ XCHAR __attribute__((space(prog))) Checkup_OBJ_STATICTEXT_1_text[] = "Working Time:";
const __prog__ XCHAR __attribute__((space(prog))) Checkup_OBJ_STATICTEXT_2_text[] = "Press \"Clear\" \r\nand wait for RESET";
const __prog__ XCHAR __attribute__((space(prog))) Checkup_OBJ_STATICTEXT_3_text[] = "AIR\r\nIN SYSTEM";
const __prog__ XCHAR __attribute__((space(prog))) Checkup_OBJ_STATICTEXT_4_text[] = "NO\r\nAIR";
//const __prog__ XCHAR __attribute__((space(prog))) Checkup_OBJ_STATICTEXT_5_text[] = "LINEAR";


const XCHAR Checkup_OBJ_BUTTON_0_text[] = "RUN";
const XCHAR Checkup_OBJ_BUTTON_1_text[] = "STOP";
const XCHAR Checkup_OBJ_BUTTON_2_text[] = "BEEP";
const XCHAR Checkup_OBJ_BUTTON_3_text[] = "CLEAR";
//const XCHAR Checkup_OBJ_BUTTON_4_text[] = "DOOR";
//const XCHAR Checkup_OBJ_BUTTON_5_text[] = "AIR";
//const XCHAR Checkup_OBJ_BUTTON_6_text[] = "LINEAR";



//const XCHAR Checkup_OBJ_BUTTON_7_text[] = "7";
//const XCHAR Checkup_OBJ_BUTTON_8_text[] = "8";
//const XCHAR Checkup_OBJ_BUTTON_9_text[] = "9";
//const XCHAR Checkup_OBJ_BUTTON_10_text[] = ".";
//const XCHAR Checkup_OBJ_BUTTON_11_text[] = "NO LIMIT";

//const XCHAR Checkup_OBJ_BUTTON_12_text[] = "CLEAR";
//const XCHAR Checkup_OBJ_BUTTON_13_text[] = "EXIT";
//const XCHAR Checkup_OBJ_BUTTON_14_text[] = "OK";

//const XCHAR Checkup_OBJ_EDITBOX_0_text[] = "289.6";

#define Checkup_OBJ_BUTTON_0   0
#define Checkup_OBJ_BUTTON_1   1
#define Checkup_OBJ_BUTTON_2   2
#define Checkup_OBJ_BUTTON_3   3
#define Checkup_OBJ_BUTTON_4   4
#define Checkup_OBJ_BUTTON_5   5
#define Checkup_OBJ_BUTTON_6   6
#define Checkup_OBJ_BUTTON_13   7
#define Checkup_OBJ_BUTTON_14   8
#define Checkup_OBJ_EDITBOX_0   9
#define Checkup_OBJ_EDITBOX_1   10
#define Checkup_OBJ_STATICTEXT_0   11
#define Checkup_OBJ_STATICTEXT_1   12
#define Checkup_OBJ_PICTURE_0		13
#define Checkup_OBJ_PICTURE_1		14
#define Checkup_OBJ_RADIOBUTTON_0   15
#define Checkup_OBJ_RADIOBUTTON_1   16
#define Checkup_OBJ_RADIOBUTTON_2   17
#define Checkup_OBJ_RADIOBUTTON_3   18
#define Checkup_OBJ_PROGRESSBAR_0		19

EDITBOX *pCheckup_OBJ_EDITBOX_0;
static CONTROL_MSG cMsg;
static void *padj_val;
static float adj_val;
static unsigned int adj_vali;
static unsigned long adj_vall;
static char state;
static char batlvl;
static char	val_str1[16];
static char	val_str2[16];
static beep_test_flg;
//static WORD rb_stat[4];

void CreateCheckup(void)
{
	_prog_addressT p;
	unsigned char i;
	state = 0;
	GOLFree();
	SetColor(BLUE_LIGHT);
	ClearDevice();
        beep_test_flg = 0;

	memcpy(basicscheme, defscheme, sizeof(GOL_SCHEME));
	basicscheme->Color1 = GRAY_RUN;
	basicscheme->Color0 = YELLOW_RUN;
	basicscheme->TextColor0 = BLACK;
	basicscheme->TextColorDisabled = YELLOW_RUN;
	basicscheme->pFont = (void*) &Arial_Narrow_Bold_18;
	basicscheme->EmbossDkColor = GRAY_RUN;
	basicscheme->EmbossLtColor = GRAY_RUN;
	basicscheme->CommonBkColor = GRAY_RUN;

	if(Checkup_Para_Specs[page_create].type_var == PARA_FLOAT)
	{
		padj_val = (void*)(Checkup_Para_Specs[page_create].pset_var);	 
		adj_val = *((float*)padj_val);
	}
	else if(Checkup_Para_Specs[page_create].type_var == PARA_WORD)
	{
		padj_val = (void *)(Checkup_Para_Specs[page_create].pset_var);	 
		adj_vali = *((unsigned int *)padj_val);
	}
	else if(Checkup_Para_Specs[page_create].type_var == PARA_DATA)
	{
		padj_val = (void *)(Checkup_Para_Specs[page_create].pset_var);	 
		adj_vall = *((unsigned long *)padj_val);
	}
	else
	{
		padj_val = (void *)Checkup_Para_Specs[page_create].pset_var;	 
		adj_vali = *((unsigned char *)padj_val);
	}
	
	switch(page_create)
	{
//#define CHECKUP_LASTCALIBR			0
//#define CHECKUP_UPPRESS			1
//#define CHECKUP_DOWNPRESS			2
//#define CHECKUP_ACBATTERY		3
//#define CHECKUP_SENSORS		4
//#define CHECKUP_OUTPUTS		5
		
		case CHECKUP_LASTCALIBR:
			memcpy(&rtc_time,localtime(&calib_time),sizeof(rtc_time));
			strftime(val_str1, 100, "%d.%m.%y", &rtc_time);
			EbCreate(Checkup_OBJ_EDITBOX_0,55,45,185,84,EB_DRAW/*|EB_FOCUSED|EB_DRAW_CARET*/,val_str1/*8(XCHAR*)Checkup_OBJ_EDITBOX_0_text*/,16,defscheme);
			_init_prog_address(p, Checkup_OBJ_STATICTEXT_1_text);
			_strncpy_p2d16(str_buf1,p,128);
			StCreate(Checkup_OBJ_STATICTEXT_1,50,120,190,150,ST_DRAW,(XCHAR*)str_buf1,defscheme);
			sprintf(val_str2,"%d hours",work_time/60);
			EbCreate(Checkup_OBJ_EDITBOX_1,55,160,185,200,EB_DRAW/*|EB_FOCUSED|EB_DRAW_CARET*/,val_str2/*8(XCHAR*)Checkup_OBJ_EDITBOX_0_text*/,16,defscheme);
			break;
		case CHECKUP_UPPRESS:
			xTimerStart( xTimers[ 1 ], 0 );
			sprintf(val_str1,"%d mmHg",press1_mmHg);
			EbCreate(Checkup_OBJ_EDITBOX_0,42,54,135,80, EB_DRAW,(XCHAR*)val_str1, 50 ,basicscheme);
			PictCreate(Checkup_OBJ_PICTURE_1,162,64,195,263,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&Pressbar_img,basicscheme);
			break;
		case CHECKUP_DOWNPRESS:
			xTimerStart( xTimers[ 1 ], 0 );
			sprintf(val_str2,"%d mmHg",press2_mmHg);
			EbCreate(Checkup_OBJ_EDITBOX_1,42,240,135,266, EB_DRAW,(XCHAR*)val_str2, 50 ,basicscheme);
			PictCreate(Checkup_OBJ_PICTURE_1,162,64,195,263,PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&Pressbar_img,basicscheme);
			break;
			
		case CHECKUP_ACBATTERY:
			xTimerStart( xTimers[ 1 ], 0 );

//			batlevel =(batt_raw - BAT_MIN)/((BAT_FULL - BAT_MIN)/10.0);
			if ( batt_raw > AC_MIN)
			{
				sprintf(val_str1,"AC ON - Charging");
			}
			else
			{
				sprintf(val_str1,"Bat %.1fV",BAT_RAW2VOLT(batt_raw));
			}
			
			if(batt_raw >= BAT_FULL )
				batlvl = 100;
			else
				batlvl =(batt_raw - BAT_MIN)/((BAT_FULL - BAT_MIN)/100.0);			 
			PbCreate(Checkup_OBJ_PROGRESSBAR_0, 10, 186, 229, 224, PB_DRAW, batlvl,100,NULL,defscheme);
			EbCreate(Checkup_OBJ_EDITBOX_0,35,65,205,104,EB_DRAW/*|EB_FOCUSED|EB_DRAW_CARET*/,val_str1/*8(XCHAR*)Checkup_OBJ_EDITBOX_0_text*/,16,defscheme);
			break;
		case CHECKUP_SENSORS:
			xTimerStart( xTimers[ 1 ], 0 );
			start_air_det();
#if 0
			_init_prog_address(p, Checkup_OBJ_STATICTEXT_3_text);
			_strncpy_p2d16(gStr1,p,128);
			if(GetDoorState())
                            strcat(gStr2," OPENED");
                        else
                            strcat(gStr2," CLOSED");


			_init_prog_address(p, Checkup_OBJ_STATICTEXT_5_text);
			_strncpy_p2d16(gStr3,p,128);
			if(GetDoorState())
                            strcat(gStr2," ON");
                        else
                            strcat(gStr2," OFF");
			StCreate(Checkup_OBJ_STATICTEXT_1,80,80,165,120,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)gStr1,defscheme);
			StCreate(Checkup_OBJ_STATICTEXT_1,80,180,165,220,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)gStr3,defscheme);
#endif
                	basicscheme->Color1 = GRAY_LIGHT;
                	basicscheme->TextColor0 = BLACK;
                	basicscheme->pFont = (void*) &Arial_Narrow_26;

                        if(get_air_det())
                        {
                                _init_prog_address(p, Checkup_OBJ_STATICTEXT_3_text);
                                basicscheme->CommonBkColor = RED;
                                _strncpy_p2d16(gStr1,p,128);
                        	StCreate(Checkup_OBJ_STATICTEXT_1,60,120,185,180,ST_DRAW|ST_CENTER_ALIGN|ST_FRAME,(XCHAR*)gStr1,basicscheme);
                        }
                        else{
                                _init_prog_address(p, Checkup_OBJ_STATICTEXT_4_text);
                                basicscheme->CommonBkColor = GREEN;
                                _strncpy_p2d16(gStr1,p,128);
        			StCreate(Checkup_OBJ_STATICTEXT_1,60,120,185,180,ST_DRAW|ST_CENTER_ALIGN|ST_FRAME,(XCHAR*)gStr1,basicscheme);
                        }

//                            strcat(gStr1,"\r\nIN SYSTEM");
//                        else
//                            strcat(gStr1,"\r\nFREE");
                        
			break;
		case CHECKUP_OUTPUTS:			 
                        test_mode = 1;
                        BtnCreate(Checkup_OBJ_BUTTON_0,80,80,160,120,5,BTN_DRAW,NULL,(XCHAR*)Checkup_OBJ_BUTTON_0_text,defscheme);
			BtnCreate(Checkup_OBJ_BUTTON_1,80,130,160,170,5,BTN_DRAW,NULL,(XCHAR*)Checkup_OBJ_BUTTON_1_text,defscheme);
			BtnCreate(Checkup_OBJ_BUTTON_2,80,180,160,220,5,BTN_DRAW|BTN_TOGGLE,NULL,(XCHAR*)Checkup_OBJ_BUTTON_2_text,defscheme);
			break;
		case CHECKUP_CLEARERR:			 
			BtnCreate(Checkup_OBJ_BUTTON_3,80,130,160,170,5,BTN_DRAW,NULL,(XCHAR*)Checkup_OBJ_BUTTON_3_text,defscheme);
			break;
			
		case CHECKUP_WATCHDOG:			 
			_init_prog_address(p, Checkup_OBJ_STATICTEXT_2_text);
			_strncpy_p2d16(str_buf1,p,128);
			StCreate(Checkup_OBJ_STATICTEXT_1,20,90,220,150,ST_DRAW|ST_CENTER_ALIGN,(XCHAR*)str_buf1,defscheme);
			BtnCreate(Checkup_OBJ_BUTTON_3,80,170,160,210,5,BTN_DRAW,NULL,(XCHAR*)Checkup_OBJ_BUTTON_3_text,defscheme);
			break;
			

#if 0			
		case CHECKUP_BATTERY_TYPE:

		  for(i = 0; i < Checkup_Para_Specs[page_create].num_opt; i++)
			{
				rb_stat[i] = RB_DRAW;
				if(i == 0)
					rb_stat[i] |= RB_GROUP;
				if(adj_vali == i)
					rb_stat[i] |= RB_CHECKED;
				RbCreate(Checkup_OBJ_RADIOBUTTON_0+i,15,40+i*45,160,70+i*45, rb_stat[i],Checkup_Para_Specs[page_create].opt_list[i],defscheme);
		  }
			break;
		
//		case CHECKUP_BOLUS_RATEDEF:
//		case CHECKUP_BOLUS_VTBIDEF:
//		case CHECKUP_OCC_HIGH:
//		case CHECKUP_OCC_MEDIUM:
//		case CHECKUP_OCC_LOW:
//		case CHECKUP_PARA_LIMIT:
		case CHECKUP_AIL_LIMITMAX:
#endif		
		default:
	
			ValToStr(Checkup_Para_Specs[page_display].unit, adj_vali, adj_val, padj_val, val_str1);
			pCheckup_OBJ_EDITBOX_0 = EbCreate(Checkup_OBJ_EDITBOX_0,55,45,185,84,EB_DRAW/*|EB_FOCUSED|EB_DRAW_CARET*/,val_str1/*8(XCHAR*)Checkup_OBJ_EDITBOX_0_text*/,16,defscheme);
		break;
	}
	
						
	BtnCreate(OBJ_BUTTON_EXIT,5,277,66,313,5,BTN_DRAW,NULL,(XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
	BtnCreate(OBJ_BUTTON_LARROW,92,277,152,313,5,BTN_DRAW,(void *)&Larrow,/*(XCHAR*)Options_OBJ_BUTTON_8_text*/NULL,botbar);
	BtnCreate(OBJ_BUTTON_RARROW,170,277,230,313,5,BTN_DRAW,(void *)&Rarrow,/*(XCHAR*)Options_OBJ_BUTTON_9_text*/NULL,botbar);

//	StCreate(Checkup_OBJ_STATICTEXT_0,1,0,239,30,ST_DRAW,(XCHAR*)Checkup_OBJ_STATICTEXT_0_text[page_create],topbar);
	StCreate(Checkup_OBJ_STATICTEXT_0,1,0,239,30,ST_DRAW,(XCHAR*)Checkup_Para_Specs[page_create].title,topbar);
	PictCreate(Checkup_OBJ_PICTURE_0, 209,0,239,30, PICT_DRAW, IMAGE_NORMAL, (GFX_IMAGE_HEADER *)&setting, topbar);

}
void CreatePrimitivesForCheckup(void){
	if((page_create > 0)&& (page_create < 3))
	{
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(40,46,200,270));
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

WORD msgCheckup(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
{
//	OBJ_HEADER* pSetPoint;
//	SHORT dialVal;
//	OBJ_HEADER* pOtherObj;
//	float adj_val_tmp;
	unsigned int adj_vali_tmp;
	if(pObj == NULL)
	{
		switch(pMsg->param1)
		{
			case INP_TIMER1_ID:			
				//Timer expired
				xTimerStart( xTimers[ 1 ], 0 );
				if(beep_test_flg)
                                    Beep(200);
                                UpdateCheckup();
				break;
			default:
				break;
		}
		
		return 1;	
	}

#if 0	
	switch(page_create)
	{

	
	case CHECKUP_LASTCALIBR:
	case CHECKUP_UPPRESS:
	case CHECKUP_DOWNPRESS:
	case CHECKUP_ACBATTERY:
	case CHECKUP_SENSORS:
	case CHECKUP_OUTPUTS:
	
	}	
#endif	
	
	switch (GetObjID(pObj)) {
		
		case Checkup_OBJ_RADIOBUTTON_0:
		case Checkup_OBJ_RADIOBUTTON_1:
		case Checkup_OBJ_RADIOBUTTON_2:
		case Checkup_OBJ_RADIOBUTTON_3:
			if (objMsg == RB_MSG_CHECKED) {
			   adj_vali_tmp	= GetObjID(pObj);//RbGetCheck(pObj);                        
			   adj_vali = adj_vali_tmp - Checkup_OBJ_RADIOBUTTON_0;
			}	  
			return 1;
		case Checkup_OBJ_BUTTON_0:
			if (objMsg == BTN_MSG_RELEASED) {
                            steps = 0;
                            if(stmotor_stat()== STMTR_STOP)
                            {
                                vol_para.rate = 1000;
                                vol_para.vtbi = 9999;
                                cMsg.cmd = MSG_CONTROL_START_INFUS;
                                xQueueSend(hCONTROLQueue, &cMsg, 0);
                            }
                        }
			return 1;

        	case Checkup_OBJ_BUTTON_1:
			if (objMsg == BTN_MSG_RELEASED) {
        			//Stop infusion
				cMsg.cmd = MSG_CONTROL_STOP_INFUS;
				xQueueSend(hCONTROLQueue, &cMsg, 0);
                        }
			return 1;
        	case Checkup_OBJ_BUTTON_2:
			if (objMsg == BTN_MSG_PRESSED)
                                beep_test_flg = 1;
                        else if(objMsg == BTN_MSG_RELEASED)
                                beep_test_flg = 0;
			return 1;
#if 0
                case Checkup_OBJ_BUTTON_2:
		case Checkup_OBJ_BUTTON_3:
		case Checkup_OBJ_BUTTON_4:
		case Checkup_OBJ_BUTTON_5:
		case Checkup_OBJ_BUTTON_6:
		case Checkup_OBJ_BUTTON_7:
		case Checkup_OBJ_BUTTON_8:
		case Checkup_OBJ_BUTTON_9:
			if (objMsg == BTN_MSG_RELEASED) {
			  	if(state == 3)
			  		return 1;
			  	if(state == 2)
			  	{
			  		adj_val_tmp = adj_val + (float)GetObjID(pObj)*0.1;
			  		state = 3;
			  	}
			  	else if(state == 1)
				{
			  		adj_val_tmp = adj_val*10.0 + (float)GetObjID(pObj);
					adj_vali_tmp = adj_vali*10 + GetObjID(pObj);
			  	}
				else
			  	{
			  		adj_vali_tmp = GetObjID(pObj);
					adj_val_tmp = (float)GetObjID(pObj);
					state = 1;
			  	}
				
				switch(page_display)
				{
					case CHECKUP_RATE_MAX:
					case CHECKUP_BOLUS_RATEMAX:
					case CHECKUP_BOLUS_RATEDEF:
						if(adj_val_tmp > max_rate)
							return 1;
						break;
					case CHECKUP_VTBI_MAX:
					case CHECKUP_BOLUS_VTBIMAX:
					case CHECKUP_BOLUS_VTBIDEF:
						if(adj_val_tmp > max_volume)
							return 1;
						break;
					case CHECKUP_LASTCALIBR:
//						adj_vali = *((int*)padj_val);
//						sprintf(adj_val_str,"%d",(unsigned long)adj_vali);
					
					case CHECKUP_BOLUS_MODE:
					case CHECKUP_OCC_LIMIT:
					case CHECKUP_OCC_HIGH:
					case CHECKUP_OCC_MEDIUM:
					case CHECKUP_OCC_LOW:
					case CHECKUP_AIL_LIMITMAX:
					case CHECKUP_BUZZER_VOLUME:
					case CHECKUP_PARA_LIMIT:
					case CHECKUP_BATTERY_TYPE:
					case CHECKUP_DATE:
					default:
						break;
				}
				adj_val = adj_val_tmp;
				adj_vali = adj_vali_tmp;
				ValToStr(Checkup_Para_Specs[page_display].unit, adj_vali, adj_val, padj_val, val_str1);
				if(pCheckup_OBJ_EDITBOX_0 != NULL)
				{
					EbSetText(pCheckup_OBJ_EDITBOX_0,val_str1);
					SetState(pCheckup_OBJ_EDITBOX_0, EB_DRAW);
				}
			}	
			return 1;
		case Checkup_OBJ_BUTTON_10:
			if (objMsg == BTN_MSG_RELEASED) {   //				EbAddChar(pCheckup_OBJ_EDITBOX_0,'.');
				if(adj_val < 100.0)
				{
					state = 2;

//					sprintf(adj_val_str,"%.1f %s",(double)adj_val,unit[page_display]);
//					EbSetText(pCheckup_OBJ_EDITBOX_0,adj_val_str);
//					SetState(pCheckup_OBJ_EDITBOX_0, EB_DRAW);
				}

//				adj_val + (float)GetObjID(pObj);
//				if(adj_val < 100.0)
//				{
//					SetState(pCheckup_OBJ_EDITBOX_0, EB_DRAW);
//				}
			}	
			return 1;
		case Checkup_OBJ_BUTTON_11:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap(pObj, (char*)&NoLimit_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap(pObj, (char *)&NoLimit);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED)
				{
	//				GDDSetScreen(CREATE_SCREEN_TEST,0,NULL);
				}
			}	
			return 1;
#endif		
		case Checkup_OBJ_BUTTON_3:
			if (objMsg == BTN_MSG_RELEASED) {
				if(page_display == CHECKUP_WATCHDOG)
				{
					wdi_ena = 1;
				}
				else
				{
					err_code = 0;
					vTaskSuspendAll();
	  			((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
					SST25SectorErase(PARAM_E2PIMG_BASE);
					if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)))
					/*CriticalError("eeprom err")*/;
					xTaskResumeAll();
				}
			}	
			return 1;
		
		case Checkup_OBJ_BUTTON_5:
			if (objMsg == BTN_MSG_RELEASED) {
//				adj_val = 0.0;
//				sprintf(adj_val_str,"%.1f %s",(double)adj_val,unit[page_display]);
				adj_val = 0.0;
				adj_vali = 0;
				ValToStr(Checkup_Para_Specs[page_display].unit, adj_vali, adj_val, padj_val, val_str1);
				EbSetText(pCheckup_OBJ_EDITBOX_0,val_str1);
				SetState((EDITBOX*)pCheckup_OBJ_EDITBOX_0, EB_DRAW);
			}	
			return 1;
		case OBJ_BUTTON_LARROW:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, &Larrow_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
    			{
                                if(stmotor_stat()== STMTR_RUN)
                                {
        				cMsg.cmd = MSG_CONTROL_STOP_INFUS;
                			xQueueSend(hCONTROLQueue, &cMsg, 0);
                                }

                                test_mode = 0;
                                BtnSetBitmap((BUTTON*)pObj, &Larrow);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					if(page_display > 0)
						page_display--;
					GDDShiftScreen(page_display); //
				}
			}	
			return 1;
		case OBJ_BUTTON_RARROW:
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap((BUTTON*)pObj, &Rarrow_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
                                if(stmotor_stat()== STMTR_RUN)
                                {
        				cMsg.cmd = MSG_CONTROL_STOP_INFUS;
                			xQueueSend(hCONTROLQueue, &cMsg, 0);
                                }
                                test_mode = 0;
				BtnSetBitmap((BUTTON*)pObj, &Rarrow);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == BTN_MSG_RELEASED) 
				{
					if(page_display < 7)
						page_display++;
					if (page_display == CHECKUP_SENSORS)
		 				stop_air_det();
					GDDShiftScreen(page_display); //2nd screen
				}
			}	
			return 1;
		case OBJ_BUTTON_EXIT:
			if (objMsg == BTN_MSG_RELEASED) {
                                test_mode = 0;
                                if(stmotor_stat()== STMTR_RUN)
                                {
        				cMsg.cmd = MSG_CONTROL_STOP_INFUS;
                			xQueueSend(hCONTROLQueue, &cMsg, 0);
                                }
//				GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
				GDDPrevScreen();
			}	
			return 1;
		case Checkup_OBJ_BUTTON_14:
			if (objMsg == BTN_MSG_RELEASED) {
#if 0				
				switch(page_display)
				{
					
					case CHECKUP_BOLUS_RATEDEF:
					case CHECKUP_BOLUS_VTBIDEF:
						*((float*)padj_val) = adj_val;
						break;			
					case CHECKUP_AIL_LIMITMAX:
					case CHECKUP_OCC_HIGH:
					case CHECKUP_OCC_MEDIUM:
					case CHECKUP_OCC_LOW:
					case CHECKUP_LASTCALIBR:
						*((int*)padj_val) = adj_vali;
						break;			
//					case CHECKUP_BOLUS_MODE:
					case CHECKUP_OCC_LIMIT:
					case CHECKUP_BUZZER_VOLUME:
					case CHECKUP_PARA_LIMIT:
					case CHECKUP_BATTERY_TYPE:
					case CHECKUP_DATE:
					default:
						*((unsigned char*)padj_val) = adj_vali;
						break;
				}
#endif				
				GDDPrevScreen();
			}	  
			return 1;
		default:
			break;
	}	

	return 1;	
} 
void UpdateCheckup(void)
{
	OBJ_HEADER* pObj;
       	_prog_addressT p;

//	time_t time_val;

	if(page_display == CHECKUP_UPPRESS)
	{
		pObj = GOLFindObject(Checkup_OBJ_EDITBOX_0);
		if (pObj) {
			sprintf(val_str1,"%d mmHg", press1_mmHg);
			EbSetText((EDITBOX*)pObj,val_str1);   
 			SetState((EDITBOX*) pObj, EB_DRAW);
		}
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(168,66,188,260));
		
		SetColor(YELLOW_RUN);
		while(!Bar(168, ((260 - press2hight(press1_mmHg)) < 66 ? 66 : (260 - press2hight(press1_mmHg))),188,260));
	}
	else if(page_display == CHECKUP_DOWNPRESS)
	{
		pObj = GOLFindObject(Checkup_OBJ_EDITBOX_1);
		if (pObj) {
	 		sprintf(val_str2,"%d mmHg", press2_mmHg);
			EbSetText((EDITBOX*)pObj,val_str2);   
 			SetState((EDITBOX*) pObj, EB_DRAW);
		}
		SetLineType(0);
		SetLineThickness(0);
		SetColor(GRAY_RUN);
		while(!Bar(168,66,188,260));
		
		SetColor(YELLOW_RUN);
		while(!Bar(168, ((260 - press2hight(press2_mmHg)) < 66 ? 66 : (260 - press2hight(press2_mmHg))),188,260));
	}
	else if(page_display == CHECKUP_ACBATTERY)
	{
		if ( batt_raw > AC_MIN)
		{
			sprintf(val_str1,"AC ON - Charging");
		}
		else
		{
			sprintf(val_str1,"Bat %.1fV",BAT_RAW2VOLT(batt_raw));
		}
		if(batt_raw >= BAT_FULL )
			batlvl = 100;
		else
			batlvl =(batt_raw - BAT_MIN)/((BAT_FULL - BAT_MIN)/100.0);			 
		pObj = GOLFindObject(Checkup_OBJ_PROGRESSBAR_0);
		if (pObj) 
		{
			PbSetPos((PROGRESSBAR*) pObj, (WORD)batlvl);
			SetState((PROGRESSBAR*) pObj, DRAW_UPDATE);
		}
//			PbCreate(Checkup_OBJ_PROGRESSBAR_0, 10, 206, 229, 244, PB_DRAW, 0,batlvl,basicscheme);
		pObj = GOLFindObject(Checkup_OBJ_EDITBOX_0);
		if (pObj) {
			EbSetText((EDITBOX*)pObj,val_str1);   
			SetState((EDITBOX*) pObj, EB_DRAW);
		}
//		EbCreate(Checkup_OBJ_EDITBOX_0,35,45,205,84,EB_DRAW/*|EB_FOCUSED|EB_DRAW_CARET*/,val_str1/*8(XCHAR*)Checkup_OBJ_EDITBOX_0_text*/,16,defscheme);
	}
	else if(page_display == CHECKUP_SENSORS)
	{
		pObj = GOLFindObject(Checkup_OBJ_STATICTEXT_1);
                if (pObj)
		{
                        if(get_air_det())
                        {
                                _init_prog_address(p, Checkup_OBJ_STATICTEXT_3_text);
                                basicscheme->CommonBkColor = RED;
                                _strncpy_p2d16(gStr1,p,128);
//                        	StCreate(Checkup_OBJ_STATICTEXT_1,60,120,185,180,ST_DRAW|ST_CENTER_ALIGN|ST_FRAME,(XCHAR*)gStr1,basicscheme);
                        }
                        else{
                                _init_prog_address(p, Checkup_OBJ_STATICTEXT_4_text);
                                basicscheme->CommonBkColor = GREEN;
                                _strncpy_p2d16(gStr1,p,128);
//        			StCreate(Checkup_OBJ_STATICTEXT_1,60,120,185,180,ST_DRAW|ST_CENTER_ALIGN|ST_FRAME,(XCHAR*)gStr1,basicscheme);
                        }

			StSetText((STATICTEXT*) pObj, gStr1);
			SetState((STATICTEXT*) pObj, DRAW_UPDATE);
		}
//			PbCreate(Checkup_OBJ_PROGRESSBAR_0, 10, 206, 229, 244, PB_DRAW, 0,batlvl,basicscheme);
		pObj = GOLFindObject(Checkup_OBJ_EDITBOX_0);
		if (pObj) {
			EbSetText((EDITBOX*)pObj,val_str1);
			SetState((EDITBOX*) pObj, EB_DRAW);
		}
//		EbCreate(Checkup_OBJ_EDITBOX_0,35,45,205,84,EB_DRAW/*|EB_FOCUSED|EB_DRAW_CARET*/,val_str1/*8(XCHAR*)Checkup_OBJ_EDITBOX_0_text*/,16,defscheme);
	}




#if 0	
	 
	pObj = GOLFindObject(Test_OBJ_EDITBOX_4);
	if (pObj) {
//			sprintf(str," = %.2fV", BAT_RAW2VOLT(batt_raw));
		sprintf(bat_str,"Bat %.1fV",BAT_RAW2VOLT(batt_raw));
		EbSetText((EDITBOX*)pObj,bat_str);        //
		SetState((EDITBOX*) pObj, EB_DRAW);
	}
//	pObj = GOLFindObject(Test_OBJ_DIGITALMETER_1);
//	if (pObj) {
//		DmSetValue((DIGITALMETER*)pObj,air_raw);
//		SetState((DIGITALMETER*) pObj, DRAW_UPDATE);
//	}
	pObj = GOLFindObject(Test_OBJ_EDITBOX_2);
	if (pObj) {
		sprintf(press1_str,"P1 %d mmHg\r\n(%d)",press1_mmHg,press1_raw);
		EbSetText((EDITBOX*)pObj,press1_str);   
		SetState((EDITBOX*) pObj, EB_DRAW);
	}
	pObj = GOLFindObject(Test_OBJ_EDITBOX_3);
	if (pObj) {
		sprintf(press2_str,"P2 %d mmHg\r\n(%d)", press2_mmHg,press2_raw);
		EbSetText((EDITBOX*)pObj,press2_str);   
 		SetState((EDITBOX*) pObj, EB_DRAW);
	}
	pObj = GOLFindObject(Test_OBJ_EDITBOX_1);
	if (pObj) {
		time_val = clock();
//		sprintf(test_str,"%s", ctime(&time_val));
		strftime(test_str, 100, "%H:%M:%S %d.%m.%Y", localtime(&time_val));

//		sprintf(test_str,"Time %02d:%02d:%02d \r\n Infused %d ml", hour, min, sec, (unsigned int)vol_para.infsd);
		EbSetText((EDITBOX*)pObj,test_str); 
 		SetState((EDITBOX*) pObj, EB_DRAW);
//		StSetText(pObj,test_str); 
// 		SetState((STATICTEXT*) pObj, ST_DRAW);
// 		SetState((STATICTEXT*) pObj, ST_UPDATE);
	
	}
#endif
}

