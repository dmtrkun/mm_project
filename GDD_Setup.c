/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_SETUP_PUB
#include "include.h"
#include <stdio.h>

//extern USB_HANDLE USBGenericInHandle;
// Strings
//typedef enum {
//RATE = 0,
//VTBI,
//INFUSED,
//BOLUS_RATE,
//BOLUS_VTBI,
//PRIME
//}ADJUST_STATES;

const GFX_XCHAR Setup_OBJ_BUTTON_0_text[] = "0";
const GFX_XCHAR Setup_OBJ_BUTTON_1_text[] = "1";
const GFX_XCHAR Setup_OBJ_BUTTON_2_text[] = "2";
const GFX_XCHAR Setup_OBJ_BUTTON_3_text[] = "3";
const GFX_XCHAR Setup_OBJ_BUTTON_4_text[] = "4";
const GFX_XCHAR Setup_OBJ_BUTTON_5_text[] = "5";
const GFX_XCHAR Setup_OBJ_BUTTON_6_text[] = "6";
const GFX_XCHAR Setup_OBJ_BUTTON_7_text[] = "7";
const GFX_XCHAR Setup_OBJ_BUTTON_8_text[] = "8";
const GFX_XCHAR Setup_OBJ_BUTTON_9_text[] = "9";
const GFX_XCHAR Setup_OBJ_BUTTON_10_text[] = ".";
const GFX_XCHAR Setup_OBJ_BUTTON_11_text[] = "NO LIMIT";
const GFX_XCHAR Setup_OBJ_BUTTON_MINUS_text[] = "-";

const GFX_XCHAR Setup_OBJ_BUTTON_12_text[] = "CLEAR";
//const GFX_XCHAR Setup_OBJ_BUTTON_13_text[] = "EXIT";
const GFX_XCHAR Setup_OBJ_BUTTON_14_text[] = "OK";

//const GFX_XCHAR Setup_OBJ_EDITBOX_0_text[] = "289.6";

#define Setup_OBJ_BUTTON_0   0
#define Setup_OBJ_BUTTON_1   1
#define Setup_OBJ_BUTTON_2   2
#define Setup_OBJ_BUTTON_3   3
#define Setup_OBJ_BUTTON_4   4
#define Setup_OBJ_BUTTON_5   5
#define Setup_OBJ_BUTTON_6   6
#define Setup_OBJ_BUTTON_7   7
#define Setup_OBJ_BUTTON_8   8
#define Setup_OBJ_BUTTON_9   9
#define Setup_OBJ_BUTTON_10   10
#define Setup_OBJ_BUTTON_11   11
#define Setup_OBJ_BUTTON_MINUS   12
#define Setup_OBJ_BUTTON_12   13
#define Setup_OBJ_BUTTON_13   14
#define Setup_OBJ_BUTTON_14   15
#define Setup_OBJ_EDITBOX_0   16
#define Setup_OBJ_STATICTEXT_0   17
#define Setup_OBJ_PICTURE_0		18

EDITBOX *pSetup_OBJ_EDITBOX_0;
static void *padj_val;
static float adj_val;
//static unsigned int adj_vali;
static unsigned long adj_vali;
static char dig_place;
static char state;
static char	adj_val_str[16];
WORD rb_stat[4];
static PARA_SPECS_t * pSpecs; 


#define Setup_OBJ_RADIOBUTTON_0   17
#define Setup_OBJ_RADIOBUTTON_1   18
#define Setup_OBJ_RADIOBUTTON_2   19
#define Setup_OBJ_RADIOBUTTON_3   20

//const GFX_XCHAR ItemList[] = "Line1n" "Line2n";
 

void CreateSetup(void)
{
	unsigned char i;
	state = 0;
	dig_place = 6;
	GFX_GOL_ObjectListFree();
	GFX_ColorSet(BLUE_LIGHT);
	GFX_ScreenClear();

	if(inp_param != NULL)
		pSpecs = (PARA_SPECS_t *)inp_param;
	else	 
		pSpecs = &Setup_Para_Specs[page_create];

	padj_val = (void*)(pSpecs->pset_var);	 
	if(pSpecs->type_var == PARA_FLOAT)
	{
//		padj_val = (void*)(pSpecs->pset_var);	 
		adj_val = *((float*)padj_val);
	}
	else if(pSpecs->type_var == PARA_WORD)
	{
//		padj_val = (void *)(pSpecs->pset_var);	 
		adj_vali = *((unsigned int *)padj_val);
	}
	else if(pSpecs->type_var == PARA_DATA)
	{
		adj_vali = clock();
		memcpy(&rtc_time,localtime(&adj_vali),sizeof(rtc_time));
//			time_sec  = mktime(&rtc_time); 
//		sprintf(test_str,"%s", ctime(&time_val));
	}
	else
	{
//		padj_val = (void *)pSpecs->pset_var;	 
		adj_vali = *((unsigned char *)padj_val);
	}
	
	switch(page_create)
	{
		case SETUP_OCC_LIMIT:
		case SETUP_BOLUS_MODE:
		case SETUP_BATTERY_TYPE:

		  for(i = 0; i < pSpecs->num_opt; i++)
			{
				rb_stat[i] = RB_DRAW;
				if(i == 0)
					rb_stat[i] |= RB_GROUP;
				if(adj_vali == i)
					rb_stat[i] |= RB_CHECKED;
				RbCreate(Setup_OBJ_RADIOBUTTON_0+i,15,40+i*45,160,70+i*45, rb_stat[i],pSpecs->opt_list[i],defscheme);
		  }
			break;
		
		case SETUP_UPPER_LIMIT:
		case SETUP_PARA_LIMIT:
			BtnCreate(Setup_OBJ_BUTTON_MINUS,164,229,227,266,5,BTN_DRAW,NULL,Setup_OBJ_BUTTON_MINUS_text,defscheme);
		case SETUP_TIME:
		case SETUP_DATE:
		case SETUP_PASSWORD:
		case SETUP_RATE_MAX:
		case SETUP_BOLUS_RATEMAX:
		case SETUP_BOLUS_RATEDEF:
		case SETUP_VTBI_MAX:
		case SETUP_BOLUS_VTBIMAX:
		case SETUP_BOLUS_VTBIDEF:
		case SETUP_OCC_HIGH:
		case SETUP_OCC_MEDIUM:
		case SETUP_OCC_LOW:
		case SETUP_AIL_LIMITMAX:
		default:
			BtnCreate(Setup_OBJ_BUTTON_1,13,92,75,129,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_1_text,defscheme);
			BtnCreate(Setup_OBJ_BUTTON_2,89,92,152,129,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_2_text,defscheme);
			BtnCreate(Setup_OBJ_BUTTON_3,164,92,227,129,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_3_text,defscheme);
	
			BtnCreate(Setup_OBJ_BUTTON_4,13,138,75,175,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_4_text,defscheme);
			BtnCreate(Setup_OBJ_BUTTON_5,89,138,152,175,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_5_text,defscheme);
			BtnCreate(Setup_OBJ_BUTTON_6,164,138,227,175,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_6_text,defscheme);
	
			BtnCreate(Setup_OBJ_BUTTON_7,13,184,75,221,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_7_text,defscheme);
			BtnCreate(Setup_OBJ_BUTTON_8,89,184,152,221,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_8_text,defscheme);
			BtnCreate(Setup_OBJ_BUTTON_9,164,184,227,221,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_9_text,defscheme);
	
			BtnCreate(Setup_OBJ_BUTTON_10,13,229,75,266,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_10_text,defscheme);
			BtnCreate(Setup_OBJ_BUTTON_0,89,229,152,266,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_0_text,defscheme);
			BtnCreate(Setup_OBJ_BUTTON_12,7,277,67,312,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_12_text,botbar);
			ValToStr(pSpecs->unit, adj_vali, adj_val, padj_val, adj_val_str);  
			pSetup_OBJ_EDITBOX_0 = EbCreate(Setup_OBJ_EDITBOX_0,55,45,185,84,EB_DRAW/*|EB_FOCUSED|EB_DRAW_CARET*/,adj_val_str/*8(GFX_XCHAR*)Setup_OBJ_EDITBOX_0_text*/,16,defscheme);
		break;
	}
	
	 
	BtnCreate(Setup_OBJ_BUTTON_13,90,277,150,312,5,BTN_DRAW,NULL,(GFX_XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
	BtnCreate(Setup_OBJ_BUTTON_14,172,277,232,312,5,BTN_DRAW,NULL,(GFX_XCHAR*)Setup_OBJ_BUTTON_14_text,botbar);

//	GFX_GOL_StaticTextCreate(Setup_OBJ_STATICTEXT_0,1,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)Setup_OBJ_STATICTEXT_0_text[page_create],topbar);
	GFX_GOL_StaticTextCreate(Setup_OBJ_STATICTEXT_0,1,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)pSpecs->title,GFX_ALIGN_LEFT,topbar);
	GFX_GOL_PictureControlCreate(Setup_OBJ_PICTURE_0, 209,0,239,30, PICT_DRAW, IMAGE_NORMAL, (GFX_RESOURCE_HDR *)&setting, topbar);
	

}
void CreatePrimitivesForSetup(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		GFX_ColorSet(11542);
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

WORD msgSetup(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
//	GFX_GOL_OBJ_HEADER* pSetPoint;
//	SHORT dialVal;
//	GFX_GOL_OBJ_HEADER* pOtherObj;
	float adj_val_tmp;
	unsigned int adj_vali_tmp;
	struct tm rtc_tmp;
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
		
		case Setup_OBJ_RADIOBUTTON_0:
		case Setup_OBJ_RADIOBUTTON_1:
		case Setup_OBJ_RADIOBUTTON_2:
		case Setup_OBJ_RADIOBUTTON_3:
			if (objMsg == RB_MSG_CHECKED) {
			   adj_vali_tmp	= GFX_GOL_ObjectIDGet(pObj);//RbGetCheck(pObj);                        
			   adj_vali = adj_vali_tmp - Setup_OBJ_RADIOBUTTON_0;
			}	  
			return 1;
		case Setup_OBJ_BUTTON_0:
		case Setup_OBJ_BUTTON_1:
		case Setup_OBJ_BUTTON_2:
		case Setup_OBJ_BUTTON_3:
		case Setup_OBJ_BUTTON_4:
		case Setup_OBJ_BUTTON_5:
		case Setup_OBJ_BUTTON_6:
		case Setup_OBJ_BUTTON_7:
		case Setup_OBJ_BUTTON_8:
		case Setup_OBJ_BUTTON_9:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
	  			if(page_display == SETUP_TIME)
					{
			  		if(dig_place == 0)
							return 1;
						if(dig_place > 5)
						{
							adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj)*10;
							if(adj_vali_tmp > 23)
								return 1;
							rtc_time.tm_hour = adj_vali_tmp;
						}
			  		else if(dig_place > 4)
						{
							adj_vali_tmp = rtc_time.tm_hour + GFX_GOL_ObjectIDGet(pObj);
							if(adj_vali_tmp > 23)
								return 1;
							rtc_time.tm_hour = adj_vali_tmp;
						}
						else if(dig_place > 3)
						{
							adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj)*10;
							if(adj_vali_tmp > 59)
								return 1;
							rtc_time.tm_min = adj_vali_tmp;
						}
						else if(dig_place > 2)
						{
							adj_vali_tmp = rtc_time.tm_min + GFX_GOL_ObjectIDGet(pObj);
							if(adj_vali_tmp > 59)
								return 1;
							rtc_time.tm_min = adj_vali_tmp;
						}
						else if(dig_place > 1)
						{
							adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj)*10;
							if(adj_vali_tmp > 59)
								return 1;
							rtc_time.tm_sec = adj_vali_tmp;
						}
						else
						{
							adj_vali_tmp = rtc_time.tm_sec + GFX_GOL_ObjectIDGet(pObj);
							if(adj_vali_tmp > 59)
								return 1;
							rtc_time.tm_sec = adj_vali_tmp;
						}
						adj_vali = mktime(&rtc_time);
						
						dig_place--;
						ValToStr(pSpecs->unit, adj_vali, adj_val, padj_val, adj_val_str);  
						if(pSetup_OBJ_EDITBOX_0 != NULL)
						{
							EbSetText(pSetup_OBJ_EDITBOX_0,adj_val_str);
							SetState(pSetup_OBJ_EDITBOX_0, EB_DRAW);
						}
						return 1;
					}
					
					if(page_display == SETUP_DATE)
			  	{
			  		if(dig_place == 0)
							return 1;
						if(dig_place > 5)
						{
							adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj);
							if(adj_vali_tmp == 0)
								adj_vali_tmp = 1;
							else
								adj_vali_tmp *= 10;
//							adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj)*10;
							if((adj_vali_tmp > 31)||(adj_vali_tmp < 1))
								return 1;
							rtc_time.tm_mday = adj_vali_tmp;
						}
			  		else if(dig_place > 4)
						{
							adj_vali_tmp = (rtc_time.tm_mday<10?0:rtc_time.tm_mday) + GFX_GOL_ObjectIDGet(pObj);
							if((adj_vali_tmp > 31)||(adj_vali_tmp < 1))
								return 1;
							rtc_time.tm_mday = adj_vali_tmp;
						}
						else if(dig_place > 3)
						{
							adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj);
							if(adj_vali_tmp == 0)
								adj_vali_tmp = 1;
							else
								adj_vali_tmp *= 10;
//							adj_vali_tmp = 1 + GFX_GOL_ObjectIDGet(pObj)*10;
							if(adj_vali_tmp > 12)
								return 1;
							rtc_time.tm_mon = adj_vali_tmp-1;
						}
						else if(dig_place > 2)
						{
							rtc_time.tm_mon++;
							if(rtc_time.tm_mon<10)
								rtc_time.tm_mon = 0;
							adj_vali_tmp = rtc_time.tm_mon + GFX_GOL_ObjectIDGet(pObj);
							if((adj_vali_tmp > 12)||(adj_vali_tmp < 1))
								return 1;
							rtc_time.tm_mon = adj_vali_tmp-1;
						}
						else if(dig_place > 1)
						{
							adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj)*10 +100;
							if(adj_vali_tmp > 199)
								return 1;
							rtc_time.tm_year = adj_vali_tmp;
						}
						else
						{
							adj_vali_tmp = rtc_time.tm_year + GFX_GOL_ObjectIDGet(pObj);
							if(adj_vali_tmp > 199)
								return 1;
							rtc_time.tm_year = adj_vali_tmp;
						}
						
						adj_vali = mktime(&rtc_time);
						dig_place--;
						ValToStr(pSpecs->unit,adj_vali, adj_val, padj_val, adj_val_str);
						if(pSetup_OBJ_EDITBOX_0 != NULL)
						{
							EbSetText(pSetup_OBJ_EDITBOX_0,adj_val_str);
							SetState(pSetup_OBJ_EDITBOX_0, EB_DRAW);
						}
			  		return 1;
					}
					
					if(state == 3)
			  		return 1;
			  	if(state == 2)
			  	{
			  		adj_val_tmp = adj_val + (float)GFX_GOL_ObjectIDGet(pObj)*0.1;
			  		state = 3;
			  	}
			  	else if(state == 1)
					{
			  		adj_val_tmp = adj_val*10.0 + (float)GFX_GOL_ObjectIDGet(pObj);
						adj_vali_tmp = adj_vali*10 + GFX_GOL_ObjectIDGet(pObj);
			  	}
					else
			  	{
			  		adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj);
						adj_val_tmp = (float)GFX_GOL_ObjectIDGet(pObj);
						state = 1;
			  	}
				
				switch(page_display)
				{
					case SETUP_RATE_MAX:
					case SETUP_BOLUS_RATEMAX:
					case SETUP_BOLUS_RATEDEF:
						if(adj_val_tmp > max_volume)
							return 1;
						break;
					case SETUP_VTBI_MAX:
					case SETUP_BOLUS_VTBIMAX:
					case SETUP_BOLUS_VTBIDEF:
						if(adj_val_tmp > max_volume)
							return 1;
						break;
					case SETUP_PASSWORD:
//						adj_vali = *((int*)padj_val);
//						sprintf(adj_val_str,"%d",(unsigned long)adj_vali);
					
					case SETUP_BOLUS_MODE:
					case SETUP_OCC_LIMIT:
					case SETUP_OCC_HIGH:
					case SETUP_OCC_MEDIUM:
					case SETUP_OCC_LOW:
					case SETUP_AIL_LIMITMAX:
//					case SETUP_BUZZER_VOLUME:
					case SETUP_UPPER_LIMIT:
					case SETUP_PARA_LIMIT:
					case SETUP_BATTERY_TYPE:
					case SETUP_DATE:
					case SETUP_TIME:
					default:
						break;
				}
				adj_val = adj_val_tmp;
				adj_vali = adj_vali_tmp;
				ValToStr(pSpecs->unit,adj_vali, adj_val, padj_val, adj_val_str);
				if(pSetup_OBJ_EDITBOX_0 != NULL)
				{
					EbSetText(pSetup_OBJ_EDITBOX_0,adj_val_str);
					SetState(pSetup_OBJ_EDITBOX_0, EB_DRAW);
				}
			}	
			return 1;
		case Setup_OBJ_BUTTON_10:          //Dot button
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {   //				EbAddChar(pSetup_OBJ_EDITBOX_0,'.');
				if(adj_val < 100.0)
				{
					state = 2;

//					sprintf(adj_val_str,"%.1f %s",(double)adj_val,unit[page_display]);
//					EbSetText(pSetup_OBJ_EDITBOX_0,adj_val_str);
//					SetState(pSetup_OBJ_EDITBOX_0, EB_DRAW);
				}

//				adj_val + (float)GFX_GOL_ObjectIDGet(pObj);
//				if(adj_val < 100.0)
//				{
//					SetState(pSetup_OBJ_EDITBOX_0, EB_DRAW);
//				}
			}	
			return 1;
		case Setup_OBJ_BUTTON_MINUS:          //Minus button
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {   
				adj_vali = adj_vali*(-1L);
				ValToStr(pSpecs->unit,adj_vali, adj_val, padj_val, adj_val_str);
				EbSetText(pSetup_OBJ_EDITBOX_0,adj_val_str);
				SetState((EDITBOX*)pSetup_OBJ_EDITBOX_0, EB_DRAW);
			}	
			return 1;
		case Setup_OBJ_BUTTON_11:      //No limit button
			if (objMsg == BTN_MSG_PRESSED) {
					BtnSetBitmap(pObj, (char*)&NoLimit_press);
					SetState((BUTTON*) pObj, BTN_DRAW);
			}
			else 
			{
				BtnSetBitmap(pObj, (char *)&NoLimit);
				SetState((BUTTON*) pObj, BTN_DRAW);
				if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
				{
	//				GDDSetScreen(CREATE_SCREEN_TEST,0,NULL);
				}
			}	
			return 1;
		case Setup_OBJ_BUTTON_12:      //CLEAR button
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
//				adj_val = 0.0;
//				sprintf(adj_val_str,"%.1f %s",(double)adj_val,unit[page_display]);
				state = 0;
				dig_place = 6;
				adj_val = 0.0;
				if(page_display != SETUP_DATE && page_display != SETUP_TIME)
					adj_vali = 0;
				ValToStr(pSpecs->unit,adj_vali, adj_val, padj_val, adj_val_str);
				EbSetText(pSetup_OBJ_EDITBOX_0,adj_val_str);
				SetState((EDITBOX*)pSetup_OBJ_EDITBOX_0, EB_DRAW);
			}	
			return 1;
		case Setup_OBJ_BUTTON_13:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
//				GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
				GDDPrevScreen();
			}	
			return 1;
		case Setup_OBJ_BUTTON_14:             //OK button
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				switch(page_display)
				{
					case SETUP_RATE_MAX:
					case SETUP_BOLUS_RATEMAX:
					case SETUP_BOLUS_RATEDEF:
					case SETUP_VTBI_MAX:
					case SETUP_BOLUS_VTBIMAX:
					case SETUP_BOLUS_VTBIDEF:
						*((float*)padj_val) = adj_val;
						break;			
					case SETUP_PARA_LIMIT:
					case SETUP_UPPER_LIMIT:
					case SETUP_AIL_LIMITMAX:
					case SETUP_OCC_HIGH:
					case SETUP_OCC_MEDIUM:
					case SETUP_OCC_LOW:
					case SETUP_PASSWORD:
						*((int*)padj_val) = adj_vali;
						break;			
					case SETUP_DATE:
					case SETUP_TIME:
						vTaskSuspendAll();
						set_clock(adj_vali);
						set_time_rtc(&rtc_time)/*set_date()*/;
						get_time_rtc(&rtc_tmp)/*set_date()*/;
						xTaskResumeAll();
						break;			 
//					case SETUP_BUZZER_VOLUME:
					case SETUP_OCC_LIMIT:
					case SETUP_BOLUS_MODE:
					case SETUP_BATTERY_TYPE:
					default:
						*((unsigned char*)padj_val) = adj_vali;
						break;
				}
				
				GDDPrevScreen();
			}	  
			return 1;
		default:
			break;
	}	

	return 1;	
} 
void UpdateSetup(void)
{
//	GFX_GOL_OBJ_HEADER* pObj;
	 
}


