/*****************************************************************************
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_SCREENS_H_
#define	 _GDD_SCREENS_H_

#ifdef GDD_SCREENS_PUB
#define GDD_SCREENSPUB
#else
#define GDD_SCREENSPUB extern
#endif

//#include "include.h"

///////////////////////////////////////////////////////////////////
// display color schemes
GDD_SCREENSPUB	GOL_SCHEME* basicscheme;
GDD_SCREENSPUB	GOL_SCHEME* defscheme;
GDD_SCREENSPUB	GOL_SCHEME* topbar;
GDD_SCREENSPUB	GOL_SCHEME* botbar;
GDD_SCREENSPUB	GOL_SCHEME* basicbig;
GDD_SCREENSPUB	GOL_SCHEME* green_sch;
GDD_SCREENSPUB	GOL_SCHEME* btnSchemeSmall;		// black buttons, small font
GDD_SCREENSPUB	GOL_SCHEME* btnSchemeMedium;	// black buttons, medium font
GDD_SCREENSPUB	GOL_SCHEME* blueScheme;			// Blue title pane
GDD_SCREENSPUB	GOL_SCHEME* greenScheme;		// Green display button
GDD_SCREENSPUB	GOL_SCHEME* whiteScheme;		// standard white button scheme
GDD_SCREENSPUB	GOL_SCHEME* blackScheme;		// black scheme
GDD_SCREENSPUB	GOL_SCHEME* redScheme;			// Red display buttons
GDD_SCREENSPUB	XCHAR str_buf1[128];  
GDD_SCREENSPUB	XCHAR str_buf2[128];  
GDD_SCREENSPUB	XCHAR gStr1[30];  
GDD_SCREENSPUB	XCHAR gStr2[30];  
GDD_SCREENSPUB	XCHAR gStr3[30];  

void GDDDemoCreateFirstScreen(void);
void GDDCreateScreenCallback(unsigned char scr);
//void GDDDemoGOLMsgCallback(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
void GDDDemoGOLDrawCallback(void);
//void GDDDemoNextScreen(void);

GDD_SCREENSPUB	 void CreateSchemes(void);
GDD_SCREENSPUB	 void GDDShiftScreen(unsigned char param);
GDD_SCREENSPUB	 void GDDPrevScreen(void);
GDD_SCREENSPUB	 void GDDSetScreen(unsigned char new_scr,unsigned char param1,void * param2);
GDD_SCREENSPUB	 void GDDSetScreenwPswd(unsigned char new_scr,unsigned char param1,void * param2);

GDD_SCREENSPUB	 GFX_IMAGE_HEADER* getWaitImg(void);
GDD_SCREENSPUB	 GFX_IMAGE_HEADER* getBatImg(unsigned char batlevel);

extern const FONT_FLASH arial_narrow_0_0_0_14;
extern const FONT_FLASH arial_narrow_0_0_0_20;
extern const FONT_FLASH gentium_8_200_0_0_0_0;


#define	NUM_GDD_SCREENS	18
///////////////////////////////////////////////////////////////////
// Screens used in the demo
typedef enum {
	CREATE_SCREEN_INTRO = 0,
	DISPLAY_SCREEN_INTRO,
	CREATE_SCREEN_CLEAR,
	DISPLAY_SCREEN_CLEAR,
	CREATE_SCREEN_CONFIRM,
	DISPLAY_SCREEN_CONFIRM,
	CREATE_SCREEN_RUN,
	DISPLAY_SCREEN_RUN,
	CREATE_SCREEN_SETPROG,
	DISPLAY_SCREEN_SETPROG,
	CREATE_SCREEN_SETDRUG,
	DISPLAY_SCREEN_SETDRUG,
	CREATE_SCREEN_ADJUST,
	DISPLAY_SCREEN_ADJUST,
	CREATE_SCREEN_PRIME,
	DISPLAY_SCREEN_PRIME,
	CREATE_SCREEN_OPTIONS,
	DISPLAY_SCREEN_OPTIONS,
	CREATE_SCREEN_TEST,
	DISPLAY_SCREEN_TEST,
//	CREATE_SCREEN_ERROR,
//	DISPLAY_SCREEN_ERROR,
	CREATE_SCREEN_ALARM,
	DISPLAY_SCREEN_ALARM,
	CREATE_SCREEN_PWRDOWN,
	DISPLAY_SCREEN_PWRDOWN,
	CREATE_SCREEN_CALIB,
	DISPLAY_SCREEN_CALIB,
	CREATE_SCREEN_RATECALIB,
	DISPLAY_SCREEN_RATECALIB,
	CREATE_SCREEN_BOLUS,
	DISPLAY_SCREEN_BOLUS,
	CREATE_SCREEN_SETMENU,
	DISPLAY_SCREEN_SETMENU,
	CREATE_SCREEN_SETUP,
	DISPLAY_SCREEN_SETUP,
	CREATE_SCREEN_CHECKUP,
	DISPLAY_SCREEN_CHECKUP,
	CREATE_SCREEN_NEXT,
	DISPLAY_SCREEN_NEXT,
} SCREEN_STATES;

// current screen state
GDD_SCREENSPUB SCREEN_STATES screenState;

typedef struct{
	WORD	cmd;
//	union {
//		BYTE		bVal[8];
//		WORD		wVal[4];
//		DWORD		dVal[2];
//	} data;
} SCREEN_MSG;

// the queue used to send messages to the graphics task
GDD_SCREENSPUB xQueueHandle hSCREENQueue;

// number of entries in this queue
#define SCREEN_QUEUE_SIZE	5






typedef struct 
{
//void (*Create)(unsigned char);     //Create function 
void (*Create)(void);					     //Create function 
void (*CreatePrimitives)(void);    //Create primitives function
void (*Update)(void);              //Update function
unsigned char curr;                //Current TBD  
unsigned char prev;                //Prev create screen  state
unsigned char next;                //Next TBD
unsigned char opt;                 // screen option
//unsigned char *title;              //screen title
void 	*arg;                // input argument
}SCREEN_CONTROL_BLOCK;

#define OBJ_BUTTON_EXIT   	200
#define OBJ_BUTTON_LARROW   201
#define OBJ_BUTTON_RARROW   202

#ifdef GDD_SCREENS_PUB
const XCHAR EXIT_OBJ_BUTTON_text[] = "EXIT";
const XCHAR SAVE_OBJ_BUTTON_text[] = "SAVE";
const XCHAR* unit[] = {
	NULL,
	" ml/hr",
	" ml",
	" mmHg",
	" ul",
};


#else
extern const XCHAR EXIT_OBJ_BUTTON_text[];
extern const XCHAR SAVE_OBJ_BUTTON_text[];

extern SCREEN_CONTROL_BLOCK Screen_CB_array[];

#define NULL_UNIT	0
#define mlhr_UNIT	1
#define ml_UNIT		2
#define mmHg_UNIT	3
#define ul_UNIT		4
extern const XCHAR* unit[];
#endif

#define page_create (Screen_CB_array[(screenState+1)/2].opt) 
#define inp_param (Screen_CB_array[(screenState+1)/2].arg) 
#define page_display (Screen_CB_array[screenState/2].opt) 
#define page			 	 Screen_CB_array[screenState>>1].opt

#define set_page(x)  Screen_CB_array[screenState>>1].opt = x 
#define get_page() 	 Screen_CB_array[screenState>>1].opt


#ifdef	WHITE
#undef	WHITE 
#endif
#define WHITE				RGB565CONVERT(255,255,255)

#ifdef	BLACK
#undef	BLACK 
#endif
#define BLACK				RGB565CONVERT(0,0,0)

#define BLUE_LIGHT	RGB565CONVERT(190,229,249)
#define BLUE_DARK		RGB565CONVERT(30,140,200)

#ifdef	GREEN
#undef	GREEN 
#endif
#define GREEN				RGB565CONVERT(0,255,0)

#ifdef	RED
#undef	RED 
#endif
#define RED				RGB565CONVERT(200,10,10)
#define RED_DARK			RGB565CONVERT(24,255,24)

#define GRAY				RGB565CONVERT(128,128,128)
#define GRAY_LIGHT	RGB565CONVERT(138,138,138)

#define GRAY_RUN				RGB565CONVERT(60,60,60)
#define YELLOW_RUN				RGB565CONVERT(240,160,20)

#ifdef	YELLOW
#undef	YELLOW 
#endif
#define YELLOW				RGB565CONVERT(255,255,0)

#endif
