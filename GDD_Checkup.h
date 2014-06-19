/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_CHECKUP_H_
#define	 _GDD_CHECKUP_H_

#ifdef GDD_CHECKUP_PUB
#define GDD_CHECKUPPUB
#else
#define GDD_CHECKUPPUB extern
#endif

#include "clock.h"

#define CHECKUP_LASTCALIBR		0
#define CHECKUP_UPPRESS				1
#define CHECKUP_DOWNPRESS			2
#define CHECKUP_ACBATTERY			3
#define CHECKUP_SENSORS				4
#define CHECKUP_OUTPUTS				5
#define CHECKUP_CLEARERR			6
#define CHECKUP_WATCHDOG			7
//#define CHECKUP_BOLUS_VTBIDEF	7
//#define CHECKUP_OCC_LIMIT			8
//#define CHECKUP_OCC_HIGH			9
//#define CHECKUP_OCC_MEDIUM		10
//#define CHECKUP_OCC_LOW			11
//#define CHECKUP_AIL_LIMITMAX		12
//#define CHECKUP_BUZZER_VOLUME		13
//#define CHECKUP_PARA_LIMIT		14
//#define CHECKUP_BATTERY_TYPE		15
//#define CHECKUP_DATE				16

#if 0
const GFX_XCHAR* Checkup_OBJ_STATICTEXT_0_text[] = {
"PASSWORD",
"RATE MAX",
"VTBI MAX",
"BOLUS MODE",
"BOLUS RATE MAX",
"BOLUS VTBI MAX",
"BOLUS RATE DEF.",
"BOLUS VTBI DEF.",
"OCC. LIMIT",
"OCC. HIGH",
"OCC. MEDIUM",
"OCC. LOW",
"AIL LIMIT MAX",
"BUZZER VOLUME",
"PARA LIMIT",
"BATTERY TYPE",
"DATE"
};
#endif
//GDD_CHECKUPPUB E2pImage_t E2pImage_tmp;

#define PARA_CHAR			0
#define PARA_WORD			1
#define PARA_DWORD		2
#define PARA_FLOAT		3
#define PARA_DOUBLE		4
#define PARA_OPTLIST	5
#define PARA_DATA			6

typedef struct 
{
	const GFX_XCHAR* title;
	void* pset_var;
	unsigned char type_var;
	unsigned char unit;
	const GFX_XCHAR** opt_list;
	unsigned char num_opt;
}CHECKUP_PARA_SPECS_t;

#ifdef GDD_CHECKUP_PUB
CHECKUP_PARA_SPECS_t Checkup_Para_Specs[] = 
{
	{"LAST CALIBRATED",	(void*)&pswrd,						PARA_DATA, 		TYPE_DATE,		NULL,			0},
	{"UP PRESS",			&E2pImage_tmp._maxrate, 		PARA_FLOAT,		TYPE_PRESSURE,	NULL,			0},
	{"DOWN PRESS",		&E2pImage_tmp._maxvolume, 			PARA_FLOAT,		TYPE_PRESSURE,	NULL,			0},
	{"AC/BATTERY",		&E2pImage_tmp._bolus_init.mode,		PARA_OPTLIST,	TYPE_GEN,		BolusModelst,	2},
	{"AIR SENSOR", 	&E2pImage_tmp._bolus_init.maxrate, 	PARA_FLOAT,		TYPE_GEN,		NULL,			0},
	{"MOTOR/BUZZER", 	&E2pImage_tmp._bolus_init.maxvolume,PARA_FLOAT,		TYPE_GEN,		NULL,			0},
	{"CLEAR HWERROR",	&E2pImage_tmp._bolus_init.maxvolume,PARA_FLOAT,		TYPE_GEN,		NULL,			0},
	{"WATCHDOG",	&E2pImage_tmp._bolus_init.maxvolume,PARA_FLOAT,		TYPE_GEN,		NULL,			0},
};                                                                          

#else    
extern	 CHECKUP_PARA_SPECS_t Checkup_Para_Specs[];
#endif

GDD_CHECKUPPUB void CreateCheckup(void);
GDD_CHECKUPPUB void CreatePrimitivesForCheckup(void);
GDD_CHECKUPPUB WORD msgCheckup(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg);
#endif
