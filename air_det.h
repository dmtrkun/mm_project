#ifndef airdet_h
#define airdet_h

#ifdef AIRDET_PUB
#define AIRDETPUB
#else
#define AIRDETPUB extern
#endif

#define AIR_TRIG 			100 //140
#define AIR_NOISE 		40
#define AIR_VALID_AMP  100//160   /* ail_limit */

#define AIR_VOLUME ((float)ail_limit)/1000.0   //0.100		/*100uL*/
#define TMR3_PERIOD (GetPeripheralClock()/5000) // 200uS(5kHz) for Fcy = 32MHz


typedef	struct 
{
	int max_v;
	unsigned int start;
	unsigned int max;
	unsigned int end;
		   
}air_sec_struct;



/* globals */
AIRDETPUB void init_airdet(void);
AIRDETPUB void start_air_det(void);
AIRDETPUB void ramp_swing(void);
AIRDETPUB unsigned char get_air_det(void);

AIRDETPUB unsigned char airdet_enable;
AIRDETPUB unsigned char airdet_dir;
AIRDETPUB unsigned int airdet_ramp;
AIRDETPUB volatile unsigned int alarm_trig;
AIRDETPUB volatile unsigned int alarm_cntr;


#endif /* airdet_h */

