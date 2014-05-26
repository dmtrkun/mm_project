/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_SETUP_H_
#define	 _GDD_SETUP_H_

#ifdef GDD_SETUP_PUB
#define GDD_SETUPPUB
#else
#define GDD_SETUPPUB extern
#endif

#include "clock.h"

#define SETUP_PASSWORD			0
#define SETUP_RATE_MAX			1
#define SETUP_VTBI_MAX			2
#define SETUP_BOLUS_MODE		3
#define SETUP_BOLUS_RATEMAX		4
#define SETUP_BOLUS_VTBIMAX		5
#define SETUP_BOLUS_RATEDEF		6
#define SETUP_BOLUS_VTBIDEF		7
#define SETUP_OCC_LIMIT			8
#define SETUP_OCC_HIGH			9
#define SETUP_OCC_MEDIUM		10
#define SETUP_OCC_LOW			11
#define SETUP_AIL_LIMITMAX		12
//#define SETUP_BUZZER_VOLUME		13
#define SETUP_UPPER_LIMIT		13
#define SETUP_PARA_LIMIT		14
#define SETUP_BATTERY_TYPE		15
#define SETUP_DATE				16
#define SETUP_TIME				17

GDD_SETUPPUB E2pImage_t E2pImage_tmp;

#define PARA_CHAR			0
#define PARA_WORD			1
#define PARA_DWORD		2
#define PARA_FLOAT		3
#define PARA_DOUBLE		4
#define PARA_OPTLIST	5
#define PARA_DATA			6

typedef struct 
{
	const XCHAR* title;
	void* pset_var;
	unsigned char type_var;
	unsigned char unit;
	const XCHAR** opt_list;
	unsigned char num_opt;
}SETUP_PARA_SPECS_t;


#ifdef GDD_SETUP_PUB

PARA_SPECS_t Setup_Para_Specs[] = 
{
	{"PASSWORD", 		(void*)&pswrd,						PARA_WORD, 		TYPE_PASSWORD,NULL,			0},
	{"RATE MAX",		&E2pImage_tmp._maxrate, 			PARA_FLOAT,		TYPE_RATE,NULL,			0},
	{"VTBI MAX",		&E2pImage_tmp._maxvolume, 			PARA_FLOAT,		TYPE_VOLUME,NULL,			0},
	{"BOLUS MODE",		&E2pImage_tmp._bolus_init.mode,		PARA_OPTLIST,	TYPE_GEN,BolusModelst,	2},
	{"BOLUS RATE MAX",	&E2pImage_tmp._bolus_init.maxrate, 	PARA_FLOAT,		TYPE_RATE,NULL,			0},
	{"BOLUS VTBI MAX", 	&E2pImage_tmp._bolus_init.maxvolume,PARA_FLOAT,		TYPE_VOLUME,NULL,			0},
	{"BOLUS RATE DEF.", &E2pImage_tmp._bolus_init.rate,		PARA_FLOAT,		TYPE_RATE,NULL,			0},
	{"BOLUS VTBI DEF.", &E2pImage_tmp._bolus_init.volume,	PARA_FLOAT,		TYPE_VOLUME,NULL,			0},
	{"OCC. LIMIT", 		&E2pImage_tmp._strtocclus_lmt, 		PARA_OPTLIST,	TYPE_GEN,HiMedlst,		3},
	{"OCC. HIGH", 		&E2pImage_tmp._occlus_lmts[2], 		PARA_WORD,		TYPE_PRESSURE,NULL,			0},
	{"OCC. MEDIUM", 	&E2pImage_tmp._occlus_lmts[1], 		PARA_WORD,		TYPE_PRESSURE,NULL,			0},
	{"OCC. LOW", 		&E2pImage_tmp._occlus_lmts[0], 		PARA_WORD,		TYPE_PRESSURE,NULL,			0},
	{"AIL LIMIT MAX", 	&E2pImage_tmp._ail_limit, 			PARA_WORD,		TYPE_AIL_LIMIT,NULL,			0},
	{"UPPER LIMIT", 	&E2pImage_tmp._upocclus_lmt, 		PARA_WORD,		TYPE_PRESSURE,NULL,		0},
	{"PARA LIMIT", 		&E2pImage_tmp._paraocclus_lmt, 		PARA_WORD,		TYPE_PRESSURE,NULL,			0},
	{"BATTERY TYPE", 	&E2pImage_tmp._battype, 			PARA_OPTLIST,	TYPE_GEN,BatTypelst,		4},
	{"DATE", 			&rtc_time, 					PARA_DATA,		TYPE_DATE,NULL,			0},
	{"TIME", 			&rtc_time, 					PARA_DATA,		TYPE_TIME,NULL,			0},
};                                                                          

#else
extern	 SETUP_PARA_SPECS_t Setup_Para_Specs[];
#endif

GDD_SETUPPUB void CreateSetup(void);
GDD_SETUPPUB void CreatePrimitivesForSetup(void);
GDD_SETUPPUB WORD msgSetup(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
GDD_SETUPPUB void GetValStr(unsigned char prmtr,unsigned int prmtr1, float prmtr2, char *val_str);


#endif
