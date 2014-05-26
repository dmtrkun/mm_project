/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_ADJUST_H_
#define	 _GDD_ADJUST_H_

#include "include.h"
#include "taskCalc.h"
//#include "val_conv.h"

#ifdef GDD_ADJUST_PUB
#define GDD_ADJUSTPUB
#else
#define GDD_ADJUSTPUB extern
#endif

#define ADJUST_RATE			0
#define ADJUST_VTBI			1
#define ADJUST_INFUSED		2
#define ADJUST_BOLUS_RATE	3
#define ADJUST_BOLUS_VTBI	4
#define ADJUST_PRIME		5
#define ADJUST_INFUSED_CLBR		6
#define ADJUST_INFTIME			7
#define ADJUST_INT			8
#define ADJUST_BAGVOL			9
#define ADJUST_DOSEVOL			10
#define ADJUST_DOSERATE			11
#define ADJUST_DOSETIME			12
#define ADJUST_INTERVALTIME			13
#define ADJUST_KVORATE			14

GDD_ADJUSTPUB void CreateAdjust(void);
GDD_ADJUSTPUB void CreatePrimitivesForAdjust(void);
GDD_ADJUSTPUB WORD msgAdjust(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
GDD_ADJUSTPUB float* adjust_val_ptr;

#if 0
typedef struct 
{
	const XCHAR* title;
	void* pset_var;
	unsigned char type_var;
	unsigned char unit;
	const XCHAR** opt_list;
	unsigned char num_opt;
}ADJUST_PARA_SPECS_t;
#endif

#ifdef GDD_ADJUST_PUB

PARA_SPECS_t Adjust_Para_Specs[] = 
{
	{"RATE", 	   (void*)&vol_para.rate,	PARA_FLOAT,TYPE_RATE,		NULL,			0},
	{"VTBI",	   (void*)&vol_para.vtbi, 	PARA_FLOAT,TYPE_VOLUME,		NULL,			0},
	{"INFUSED",	   (void*)&vol_para.infsd, 	PARA_FLOAT,TYPE_VOLUME,		NULL,			0},
	{"BOLUS RATE", (void*)&bolus_rate,		PARA_FLOAT,TYPE_RATE,		NULL,			0},
	{"BOLUS VTBI", (void*)&bolus_volume, 	PARA_FLOAT,TYPE_VOLUME,		NULL,			0},
	{"PRIME", 	   (void*)&vol_para.vtbi,  	PARA_FLOAT,TYPE_VOLUME,		NULL,			0},
	{"INFUSED",	   NULL,					PARA_FLOAT, TYPE_VOLUME,		NULL,			0},
	{"TIME",	   (void*)&estim_infusetime,PARA_DATA, TYPE_TIMEINTERVAL,		NULL,			0},
	{" ",	   	   NULL,					PARA_WORD, TYPE_GEN,		NULL,			0},
	{"BAG VOL",	   (void*)&vol_para.bag_vol,		PARA_FLOAT,	TYPE_VOLUME,	NULL,			0},
	{"DOSE VOL",   (void*)&vol_para.dose_vol,		PARA_FLOAT,	TYPE_VOLUME,	NULL,			0},
	{"DOSE RATE",  (void*)&vol_para.dose_rate,		PARA_FLOAT,	TYPE_RATE,		NULL,			0},
	{"DOSE TIME",  (void*)&vol_para.dose_time,		PARA_DATA,	TYPE_TIMEINTERVAL,	NULL,			0},
	{"INTERVAL TIME",	(void*)&vol_para.dose_interval,	PARA_DATA,	TYPE_TIMEINTERVAL,	NULL,			0},
	{"KVO RATE",   (void*)&vol_para.kvo_rate,		PARA_FLOAT,	TYPE_RATE,					NULL,			0},
};                                                                          

#else
extern PARA_SPECS_t Adjust_Para_Specs[];
#endif

#endif
