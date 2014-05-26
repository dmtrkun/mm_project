#ifndef stmotor_h
#define stmotor_h

#ifdef STMOTOR_PUB
#define STMOTORPUB
#else
#define STMOTORPUB extern
#endif


#define STMTR_STOP		0
#define STMTR_RUN		1
#define STMTR_RERUN		2
//#define STMTR_PAUSE		2
#define STMTR_DIR_LEFT		0
#define STMTR_DIR_RIGHT		1
#define STMTR_DIR_NOCHNG	3
//#define STMTR_POWER_OFF	0
//#define STMTR_POWER_ON	1


//#define TMR2_PERIOD 5000 // 0.125mS(8000Hz) for Fcy = 40MHz          40000000/8000
//#define TMR2_PERIOD 2000 // 0.125mS(8000Hz) for Fcy = 32MHz          16000000/8000


#define M_PULSEPERSTEP	  16.0
#define MOTOR_STEPPERTURN 200
#define MOTOR_DETECTERR 	15
//#define TENTHMLPERTURN		(0.336*vol_calibr) //0.2
//#define TENTHMLPERTURN		(0.13104*vol_calibr) //0.2
#define TENTHMLPERTURN		(0.167076*vol_calibr) 



#define FREQ							8000.0/M_PULSEPERSTEP
#define MAXRATE			    	(TENTHMLPERTURN*(FREQ/(float)MOTOR_STEPPERTURN)*3600.0)
#define MLPS			    		(TENTHMLPERTURN/(float)MOTOR_STEPPERTURN)
#define RATE_FACTOR_0			4
#define MAX_ST						(FREQ*RATE_FACTOR_0)    //((RATE_FACTOR_0*MAXRATE)/(3600*MLPS))
#define LINEAR_CORR  			70
#define WORKZONE	  			(MOTOR_STEPPERTURN -70)
#define TMR2_PERIOD 			(GetPeripheralClock()/8000) // 0.125mS(8000Hz)



#define STMOTOR_ENA_PIN		LATAbits.LATA5

STMOTORPUB void stmotor_step(unsigned char dir);
STMOTORPUB unsigned char stmotor_stat(void);
STMOTORPUB void stmotor_cmd(unsigned char dir,unsigned char cmd);
STMOTORPUB void stmotor_power(unsigned char cmd);
STMOTORPUB void init_motor(void);
STMOTORPUB void new_calc_rate(float rate);


/* globals */
STMOTORPUB unsigned int m_steps;
STMOTORPUB volatile unsigned long steps;
STMOTORPUB unsigned int st_rate;
STMOTORPUB unsigned int st_rate_cor;
STMOTORPUB unsigned int st_delay;
STMOTORPUB unsigned int st_delay_cor;
STMOTORPUB unsigned char st_div;
STMOTORPUB unsigned char st_div_cntr;
STMOTORPUB unsigned char st_state;
STMOTORPUB volatile unsigned char linear_cntr;
STMOTORPUB volatile unsigned char debounce_cntr;
STMOTORPUB volatile unsigned char rotate_det_cntr;
STMOTORPUB volatile unsigned char rotate_detector;
STMOTORPUB unsigned char steps_cntr;
STMOTORPUB volatile float g_f_rate;
STMOTORPUB volatile unsigned int g_m_rate;

STMOTORPUB unsigned char rotate_debug_max;
STMOTORPUB unsigned char rotate_debug_min;
STMOTORPUB unsigned char rotate_debug_last;


#endif /* stmotor_h */

