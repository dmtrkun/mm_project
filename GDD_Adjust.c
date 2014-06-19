/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define GDD_ADJUST_PUB
#include "include.h"
#include <stdio.h>

const GFX_XCHAR Adjust_OBJ_BUTTON_0_text[] = "0";
const GFX_XCHAR Adjust_OBJ_BUTTON_1_text[] = "1";
const GFX_XCHAR Adjust_OBJ_BUTTON_2_text[] = "2";
const GFX_XCHAR Adjust_OBJ_BUTTON_3_text[] = "3";
const GFX_XCHAR Adjust_OBJ_BUTTON_4_text[] = "4";
const GFX_XCHAR Adjust_OBJ_BUTTON_5_text[] = "5";
const GFX_XCHAR Adjust_OBJ_BUTTON_6_text[] = "6";
const GFX_XCHAR Adjust_OBJ_BUTTON_7_text[] = "7";
const GFX_XCHAR Adjust_OBJ_BUTTON_8_text[] = "8";
const GFX_XCHAR Adjust_OBJ_BUTTON_9_text[] = "9";
const GFX_XCHAR Adjust_OBJ_BUTTON_10_text[] = ".";
const GFX_XCHAR Adjust_OBJ_BUTTON_11_text[] = "NO LIMIT";

const GFX_XCHAR Adjust_OBJ_BUTTON_12_text[] = "CLEAR";
//const GFX_XCHAR Adjust_OBJ_BUTTON_13_text[] = "EXIT";
const GFX_XCHAR Adjust_OBJ_BUTTON_14_text[] = "OK";

//const GFX_XCHAR Adjust_OBJ_EDITBOX_0_text[] = "289.6";

#define Adjust_OBJ_BUTTON_0   0
#define Adjust_OBJ_BUTTON_1   1
#define Adjust_OBJ_BUTTON_2   2
#define Adjust_OBJ_BUTTON_3   3
#define Adjust_OBJ_BUTTON_4   4
#define Adjust_OBJ_BUTTON_5   5
#define Adjust_OBJ_BUTTON_6   6
#define Adjust_OBJ_BUTTON_7   7
#define Adjust_OBJ_BUTTON_8   8
#define Adjust_OBJ_BUTTON_9   9
#define Adjust_OBJ_BUTTON_10   10
#define Adjust_OBJ_BUTTON_11   11
#define Adjust_OBJ_BUTTON_12   12
#define Adjust_OBJ_BUTTON_13   13
#define Adjust_OBJ_BUTTON_14   14
#define Adjust_OBJ_EDITBOX_0   15
#define Adjust_OBJ_STATICTEXT_0   16

EDITBOX *pAdjust_OBJ_EDITBOX_0;
static void *padj_val;
static float adj_val;
static void *padj_vali;
static unsigned long adj_vali;
static unsigned long adj_vali_tmp;
struct tm adj_time;

static char state;
static char	adj_val_str[16];
static char dig_place;
static PARA_SPECS_t *pSpecs;
void cmdAdjust_clear(void); 

void CreateAdjust(void)
{
	state = 0;
	dig_place = 4;
	GFX_GOL_ObjectListFree();
	GFX_ColorSet(BLUE_LIGHT);
	GFX_ScreenClear();

	BtnCreate(Adjust_OBJ_BUTTON_1,13,92,75,129,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_1_text,defscheme);
	BtnCreate(Adjust_OBJ_BUTTON_2,89,92,152,129,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_2_text,defscheme);
	BtnCreate(Adjust_OBJ_BUTTON_3,164,92,227,129,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_3_text,defscheme);
	
	BtnCreate(Adjust_OBJ_BUTTON_4,13,138,75,175,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_4_text,defscheme);
	BtnCreate(Adjust_OBJ_BUTTON_5,89,138,152,175,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_5_text,defscheme);
	BtnCreate(Adjust_OBJ_BUTTON_6,164,138,227,175,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_6_text,defscheme);
	
	BtnCreate(Adjust_OBJ_BUTTON_7,13,184,75,221,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_7_text,defscheme);
	BtnCreate(Adjust_OBJ_BUTTON_8,89,184,152,221,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_8_text,defscheme);
	BtnCreate(Adjust_OBJ_BUTTON_9,164,184,227,221,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_9_text,defscheme);
	
	BtnCreate(Adjust_OBJ_BUTTON_10,13,229,75,266,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_10_text,defscheme);
	BtnCreate(Adjust_OBJ_BUTTON_0,89,229,152,266,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_0_text,defscheme);
	if(page_create == 1)
		BtnCreate(Adjust_OBJ_BUTTON_11,164,229,227,266,5,BTN_DRAW,(void *)&NoLimit,NULL,defscheme);
	 

	BtnCreate(Adjust_OBJ_BUTTON_12,7,277,67,312,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_12_text,botbar);
	BtnCreate(Adjust_OBJ_BUTTON_13,90,277,150,312,5,BTN_DRAW,NULL,(GFX_XCHAR*)EXIT_OBJ_BUTTON_text,botbar);
	BtnCreate(Adjust_OBJ_BUTTON_14,172,277,232,312,5,BTN_DRAW,NULL,(GFX_XCHAR*)Adjust_OBJ_BUTTON_14_text,botbar);

	if(inp_param != NULL)
		pSpecs = (PARA_SPECS_t *)inp_param;
	else	 
		pSpecs = &Adjust_Para_Specs[page_create];
	
	if(pSpecs->pset_var == NULL)
		padj_val = adjust_val_ptr;
	else
 		padj_val = (pSpecs->pset_var);	 
	
	
	if(pSpecs->type_var == PARA_FLOAT)
		adj_val = *((float*)padj_val);
	else if(pSpecs->type_var == PARA_CHAR)
		adj_vali = *((unsigned char*)padj_val);
	else if(pSpecs->type_var == PARA_DATA)
		adj_vali = *((unsigned long*)padj_val);
	else
		adj_vali = *((unsigned int*)padj_val);
	
	
	if(no_limit && page_create == ADJUST_VTBI)
		sprintf(adj_val_str,"NO LIMIT");
	else
		ValToStr(pSpecs->unit, adj_vali, adj_val, padj_val, adj_val_str);
	
	if(pSpecs->unit == TYPE_TIMEINTERVAL)
//	if(page_create == ADJUST_INFTIME)
	{

//	adj_vali = mktime(&adj_time);
		memcpy(&adj_time,localtime((time_t*)&adj_vali),sizeof(adj_time));
	}
	
	
	pAdjust_OBJ_EDITBOX_0 = EbCreate(Adjust_OBJ_EDITBOX_0,55,45,185,84,EB_DRAW/*EB_CARET|EB_FOCUSED|EB_DRAW_CARET*/,adj_val_str/*8(GFX_XCHAR*)Adjust_OBJ_EDITBOX_0_text*/,16,defscheme);

	GFX_GOL_StaticTextCreate(Adjust_OBJ_STATICTEXT_0,1,0,239,30,GFX_GOL_STATICTEXT_DRAW_STATE,(GFX_XCHAR*)pSpecs->title,GFX_ALIGN_LEFT,topbar);
	

}
void CreatePrimitivesForAdjust(void){
//		SetLineType(0);
//		SetLineThickness(0);
//		SetColor(11542);
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

WORD msgAdjust(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
{
//	GFX_GOL_OBJ_HEADER* pSetPoint;
//	SHORT dialVal;
//	GFX_GOL_OBJ_HEADER* pOtherObj;
	float adj_val_tmp;
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
		
		case Adjust_OBJ_BUTTON_0:
		case Adjust_OBJ_BUTTON_1:
		case Adjust_OBJ_BUTTON_2:
		case Adjust_OBJ_BUTTON_3:
		case Adjust_OBJ_BUTTON_4:
		case Adjust_OBJ_BUTTON_5:
		case Adjust_OBJ_BUTTON_6:
		case Adjust_OBJ_BUTTON_7:
		case Adjust_OBJ_BUTTON_8:
		case Adjust_OBJ_BUTTON_9:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) 
			{
				if(pSpecs->unit == TYPE_TIMEINTERVAL)
				{
					if(dig_place == 0)
						return 1;

					if(dig_place > 3)
					{
						adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj)*10;
						if(adj_vali_tmp > 24)
							cmdAdjust_clear();
						else 
						{
							adj_time.tm_hour = adj_vali_tmp;
							dig_place--;
						}
					}
			  		else if(dig_place > 2)
					{
						adj_vali_tmp = adj_time.tm_hour + GFX_GOL_ObjectIDGet(pObj);
						if(adj_vali_tmp > 24)
						{
							cmdAdjust_clear();
//							return 1;
//							break;
						}
						else
						{
							adj_time.tm_hour = adj_vali_tmp;
							dig_place--;
						}
					}
					else if(dig_place > 1)
					{
						adj_vali_tmp = GFX_GOL_ObjectIDGet(pObj)*10;
						if(adj_vali_tmp > 59)
						{
							cmdAdjust_clear();
//							return 1;
//							break;
						}
						else
						{
							adj_time.tm_min = adj_vali_tmp;
							dig_place--;
						}
					}
					else
					{
						adj_vali_tmp = adj_time.tm_min + GFX_GOL_ObjectIDGet(pObj);
						if(adj_vali_tmp > 59)
						{
							cmdAdjust_clear();
//							return 1;
//							break;
						}
						else
						{
							adj_time.tm_min = adj_vali_tmp;
							dig_place--;
						}
					}
					adj_vali = mktime(&adj_time);
						
					ValToStr(pSpecs->unit, adj_vali, adj_val, padj_val, adj_val_str);
					if(pAdjust_OBJ_EDITBOX_0 != NULL)
					{
						EbSetText(pAdjust_OBJ_EDITBOX_0,adj_val_str);
						SetState(pAdjust_OBJ_EDITBOX_0, EB_DRAW);
					}
					return 1;
//					break;
				}
	  			if(page_display == ADJUST_INT)
				{
					if(state == 0)
					{
						adj_vali = (int)GFX_GOL_ObjectIDGet(pObj);
						state = 1;
					}
					else
						adj_vali = adj_vali*10 + (int)GFX_GOL_ObjectIDGet(pObj);
						
					ValToStr(pSpecs->unit, adj_vali, adj_val, padj_val, adj_val_str);
					if(pAdjust_OBJ_EDITBOX_0 != NULL)
					{
						EbSetText(pAdjust_OBJ_EDITBOX_0,adj_val_str);
						SetState(pAdjust_OBJ_EDITBOX_0, EB_DRAW);
					}
					return 1;
//					break;
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
					if(pSpecs->unit == TYPE_TIMEINTERVAL)
//					if(page_display == ADJUST_INFTIME)
				  	;
					else
						adj_val_tmp = adj_val*10.0 + (float)GFX_GOL_ObjectIDGet(pObj);
				}
				else
			  	{
			  		adj_val_tmp = (float)GFX_GOL_ObjectIDGet(pObj);
					state = 1;
			  	}

				
				switch(page_display)
				{
					case ADJUST_BOLUS_RATE:
						if(adj_val_tmp + vol_para.rate > max_rate)
						{
							cmdAdjust_clear();
//							return 1;
//							break;
						}
						else
							adj_val = adj_val_tmp;
						break;
					case ADJUST_KVORATE:
					case ADJUST_DOSERATE:
					case ADJUST_RATE:
						if(adj_val_tmp > max_rate)
						{
							cmdAdjust_clear();
//							return 1;
//							break;
						}
						else
							adj_val = adj_val_tmp;
						break;
					case ADJUST_BAGVOL:
					case ADJUST_DOSEVOL:
					case ADJUST_VTBI:
					case ADJUST_INFUSED:
					case ADJUST_BOLUS_VTBI:
					case ADJUST_PRIME:
						if(adj_val_tmp > max_volume)
						{
							cmdAdjust_clear();
							//return 1;
//							break;
						}
						else
							adj_val = adj_val_tmp;
						break;
					default:
						adj_val = adj_val_tmp;
						break;
				}
				
				
//				adj_val = adj_val_tmp;
				if(no_limit && page_display == ADJUST_VTBI)
					sprintf(adj_val_str,"NO LIMIT");
				else
				{
					ValToStr(pSpecs->unit,adj_vali, adj_val, padj_val, adj_val_str);
				}
				EbSetText(pAdjust_OBJ_EDITBOX_0,adj_val_str);
				SetState(pAdjust_OBJ_EDITBOX_0, EB_DRAW);
			}	
			return 1;
		case Adjust_OBJ_BUTTON_10:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {   //				EbAddChar(pAdjust_OBJ_EDITBOX_0,'.');
				
				if(no_limit && page_display == ADJUST_VTBI)
						sprintf(adj_val_str,"NO LIMIT");
				else // if(adj_val < 100.0)
				{
			  	if(state != 3)
						state = 2;
					ValToStr(pSpecs->unit,adj_vali, adj_val, padj_val, adj_val_str);
					EbSetText(pAdjust_OBJ_EDITBOX_0,adj_val_str);
					SetState(pAdjust_OBJ_EDITBOX_0, EB_DRAW);
				}

//				adj_val + (float)GFX_GOL_ObjectIDGet(pObj);
//				if(adj_val < 100.0)
//				{
//					SetState(pAdjust_OBJ_EDITBOX_0, EB_DRAW);
//				}
			}	
			return 1;
		case Adjust_OBJ_BUTTON_11:
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
			  		if(state != 3)
					{
						no_limit = 1;
						adj_val = 0.0;
						adj_vali = 0;
						sprintf(adj_val_str,"NO LIMIT");
						EbSetText(pAdjust_OBJ_EDITBOX_0,adj_val_str);
						SetState((EDITBOX*)pAdjust_OBJ_EDITBOX_0, EB_DRAW);
					}
	//				GDDSetScreen(CREATE_SCREEN_TEST,0,NULL);
				}
			}	
			return 1;
		case Adjust_OBJ_BUTTON_12:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				state = 0;
				no_limit = 0;
				adj_val = 0.0;
				adj_vali = 0;
				dig_place = 4;
				if(pSpecs->unit == TYPE_TIMEINTERVAL)
				{
					memcpy(&adj_time,localtime(&adj_vali),sizeof(adj_time));
				}
				ValToStr(pSpecs->unit,adj_vali, adj_val, padj_val, adj_val_str);
				EbSetText(pAdjust_OBJ_EDITBOX_0,adj_val_str);
				SetState((EDITBOX*)pAdjust_OBJ_EDITBOX_0, EB_DRAW);
			}	
			return 1;
		case Adjust_OBJ_BUTTON_13:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
//				GDDSetScreen(CREATE_SCREEN_CLEAR,0,NULL);
				GDDPrevScreen();
			}	
			return 1;
		case Adjust_OBJ_BUTTON_14:
			if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) {
				if(pSpecs->type_var == PARA_FLOAT)
					*((float*)padj_val) = adj_val;
				else if(pSpecs->type_var == PARA_DATA)
					*((unsigned long*)padj_val) = adj_vali;
				else if(pSpecs->type_var == PARA_CHAR)
					*((unsigned char*)padj_val) = adj_vali;
				else
					*((unsigned int*)padj_val) = adj_vali;
				   

				if(page_display == ADJUST_INFUSED)
					steps = (unsigned long)(vol_para.infsd/(MLPS/**vol_calibr*/));
				GDDPrevScreen();
			}	  
			return 1;
		default:
			break;
	}	

	return 1;	
} 
void cmdAdjust_clear(void)
{
	state = 0;
	no_limit = 0;
	adj_val = 0.0;
	adj_vali = 0;
	dig_place = 4;
	if(pSpecs->unit == TYPE_TIMEINTERVAL)
	{
		memcpy(&adj_time,localtime(&adj_vali),sizeof(adj_time));
	}
	Beep(1000);
}


void UpdateAdjust(void)
{
//	GFX_GOL_OBJ_HEADER* pObj;
	 
}

