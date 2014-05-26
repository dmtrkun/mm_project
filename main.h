#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef MAIN_PUB
#define MAINPUB
#else
#define MAINPUB extern
#endif
    
#include "include.h"
#include "PCF2123.h"

#define VERSION 180
#define VERSION_TXT "Ver 1.8"


#define LEFT_BAR		0			
#define RIGHT_BAR		127			
#define TOP_BAR3 		40			
#define DOWN_BAR3		55			
#define TOP_BAR4 		48			
#define DOWN_BAR4		63			

#define DEPART_NUM_MAX		5
#define DRUG_NUM_MAX		50

#define VOLUME_MAX	9999.0
//#define RATE_MAX   MAXRATE//		1800.0
#define RATE_MAX   	MAXRATE

#define KVO_STAT			1
#define DOSE_KVO_STAT	2

#define setBit(var, bitnum)   ((var)|=(1<<(bitnum)))
#define resBit(var, bitnum)   ((var)&=~(1<<(bitnum)))
#define clearBit(var, bitnum) ((var)&=~(1<<(bitnum)))
#define testBit(var, bitnum)  ((var)&(1<<(bitnum)))
#define toggleBit(var, bitnum)  ((var)^=(1<<(bitnum)))

typedef struct
{
	float rate;
	float vol;
}STEP_t;

typedef struct
{
	float rate;
	float vtbi;
	volatile float infsd;
	unsigned long infusetime;
	unsigned char occlusion_lmt;
	unsigned char drug_type;
	float bag_vol;
	float dose_vol;
	float dose_rate;
	unsigned long dose_interval;
	unsigned long dose_strt_interval;
	unsigned long dose_strt_time;
	unsigned long dose_time;
	float kvo_rate;
	STEP_t prog_steps[25];
	unsigned char prog_stepsnum;
	unsigned char prog_step;
	BOOL trig_flg;
} VOL_PARA_t;

#if 0
typedef struct
{
	unsigned int low;
	unsigned int med;
	unsigned int high;
} OCCLLIMIT_PARA_t;
#endif

typedef struct
{
	float rate;
	float volume;
	float maxrate;
	float maxvolume;
	unsigned char mode;
	unsigned char reserv;
} BOLUS_PARA_t;

typedef struct
{
	float maxrate;
	float maxvolume;
} DRUG_PARA_t;

typedef struct
{
	int min;
	int empty;
	int low;
	int full;
} BAT_TYPE_t;

typedef struct
{
	unsigned int _press1_zero;
	unsigned int _press2_zero;
	unsigned int _press1_set;
	unsigned int _press2_set;
	unsigned int _press1_scale;
	unsigned int _press2_scale;
	float _vol_calibr;
	time_t _calib_time;
	unsigned int reserved[2];
	unsigned int check;
}
Clbr_E2pImage_t;
typedef struct
{
        float _maxrate;  //save to pc
	float _maxvolume; //save to pc
//	OCCLLIMIT_PARA_t occlus_lmts;
	int _upocclus_lmt;//save to pc
	int _paraocclus_lmt; //save to pc
	int _occlus_lmts[3]; //save to pc
	unsigned char _strtocclus_lmt; //save to pc
	unsigned char	_prog_num;
	BOLUS_PARA_t	_bolus_init; //save to pc
	DRUG_PARA_t _drugs[DRUG_NUM_MAX];
	unsigned char _drug_list[DRUG_NUM_MAX][16];
	unsigned char _depart_list[DEPART_NUM_MAX][16];
	unsigned int	_ail_limit; //save to pc
	unsigned char	_depart_name; //save to pc
	unsigned char _bzz_volume; //save to pc
	unsigned char _battype; //save to pc
	unsigned char   _err_code;
	unsigned int _work_time;
	unsigned int reserved[2];
	unsigned int check;
}
E2pImage_t;

#define zero_press1			Clbr_E2pImage._press1_zero
#define zero_press2			Clbr_E2pImage._press2_zero
#define set_press1			Clbr_E2pImage._press1_set
#define set_press2			Clbr_E2pImage._press2_set
#define scale_press1                    Clbr_E2pImage._press1_scale
#define scale_press2                    Clbr_E2pImage._press2_scale
#define vol_calibr			Clbr_E2pImage._vol_calibr
#define calib_time			Clbr_E2pImage._calib_time

#define max_rate			E2pImage._maxrate
#define max_volume			E2pImage._maxvolume
#define upocclus_lmt    		E2pImage._upocclus_lmt
#define paraocclus_lmt          	E2pImage._paraocclus_lmt
#define occlus_lmt			E2pImage._occlus_lmts
#define strtocclus_lmt                  E2pImage._strtocclus_lmt
#define bolus_init			E2pImage._bolus_init
#define drugs				E2pImage._drugs		
#define drug_list			E2pImage._drug_list
#define depart_list			E2pImage._depart_list
#define ail_limit		 	E2pImage._ail_limit
#define depart_name			E2pImage._depart_name
#define bzz_volume			E2pImage._bzz_volume
#define battype		 		E2pImage._battype
#define work_time			E2pImage._work_time
#define prog_num			E2pImage._prog_num
#define err_code			E2pImage._err_code

#define BATTYPES		4

#define BAT_6NICAD		0				 /* 6 NiCad	*/
#define BAT_6NIMH			1					 /* 6 NiMh	*/
#define BAT_LIION			2					 /* LiIon		*/
#define BAT_LIPOLY		3				 /* LiPoly		*/
 
#ifdef MAIN_PUB
const BAT_TYPE_t bat_type[BATTYPES] = {
/*	min;	empty;	low;	full*/
	{	BAT_VOLT2RAW(6.0),	BAT_VOLT2RAW(6.2),		BAT_VOLT2RAW(6.7),	BAT_VOLT2RAW(9.0)},    /* 6 NiCad	*/
	{	BAT_VOLT2RAW(6.0),	BAT_VOLT2RAW(6.8),		BAT_VOLT2RAW(7.0),	BAT_VOLT2RAW(8.4)},    /* 6 NiMh	*/
	{	BAT_VOLT2RAW(6.0),	BAT_VOLT2RAW(6.1),		BAT_VOLT2RAW(6.3),	BAT_VOLT2RAW(8.4)},    /* LiIon		*/
	{	BAT_VOLT2RAW(6.0),	BAT_VOLT2RAW(6.1),		BAT_VOLT2RAW(6.3),	BAT_VOLT2RAW(8.4)},    /* LiPoly		*/
};
const unsigned char bat_disch_curv[] = {0,20,40,60,70,80,85,90,95,100};

#else
extern const BAT_TYPE_t bat_type[];
extern const unsigned char bat_disch_curv[];
#endif


#define BAT_MIN						 bat_type[battype].min
#define BAT_EMPTY					 bat_type[battype].empty
#define BAT_LOW						 bat_type[battype].low
#define BAT_FULL					 bat_type[battype].full

/* globals */
MAINPUB E2pImage_t E2pImage;
MAINPUB Clbr_E2pImage_t Clbr_E2pImage;
MAINPUB int E2pImage_ptr;
MAINPUB VOL_PARA_t VolPara;
MAINPUB VOL_PARA_t *vol_ptr;
#define vol_para VolPara
//MAINPUB VOL_PARA_t vol_para __attribute__ ((noload)) ;
MAINPUB unsigned char power_state;
MAINPUB unsigned char cdc_ena;
MAINPUB void critical_error(unsigned char *str);
MAINPUB void set_defaults(void);
MAINPUB void wait_off(void);
MAINPUB void PwrDownCmd( void );


#endif
