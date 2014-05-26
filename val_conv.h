/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_VAL_CONV_H_
#define	 _VAL_CONV_H_

#ifdef VAL_CONV_PUB
#define VAL_CONVPUB
#else
#define VAL_CONVPUB extern
#endif

#include "clock.h"

#define TYPE_GEN			0
#define TYPE_PASSWORD		1
#define TYPE_RATE	 		2
#define TYPE_VOLUME	 		3
#define TYPE_PRESSURE		4
#define TYPE_AIL_LIMIT		5
#define TYPE_DATE	 		6
#define TYPE_TIME	 		7
#define TYPE_TIMEINTERVAL	8

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
}PARA_SPECS_t;


#ifdef VAL_CONV_PUB
const XCHAR* BolusModelst[] = {
"OFF",
"ON"
};
const XCHAR* HiMedlst[] = {
"High",
"Medium",
"Low",
};
const XCHAR* BatTypelst[] = {
"6NiCd",
"6NiMH",
"LiIon",
"LiPo",
};


#else
extern	const XCHAR* BatTypelst[];
extern	const XCHAR* HiMedlst[];
extern	 const XCHAR* BolusModelst[];
#endif

VAL_CONVPUB void ValToStr(unsigned char type,unsigned long prmtr1, float prmtr2, void* ptr, char *val_str);

#endif
