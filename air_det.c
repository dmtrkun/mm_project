#define AIRDET_PUB

#include	<adc.h>
#include	"include.h"

volatile char dbg_cntr;
volatile unsigned char air_state = 0;
volatile unsigned int air_cnt;
volatile air_sec_struct air_seq[50];
volatile int air_min1, air_max, air_min2;
volatile unsigned int air_max_old_idx, air_max_idx, air_strt_idx, air_end_idx;
unsigned char tmp_cntr;

volatile unsigned int accum_air_vol[15];
volatile unsigned char accum_air_vol_idx;
volatile unsigned long accum_air_vol_sum;
volatile unsigned long accum_air_vol_1Msum;
volatile unsigned int accum_air_cntr;
#define ACCUM_PERIOD		4000		/*15ms intervals for 1min*/


void init_airdet(void)
{
    
	/*RC13 for RAMP output*/	
#if 0	   
	ANSCbits.ANSC13 = 0; //Set as digital
	LATCbits.LATC13 = 0; //Init pin to 0
	TRISCbits.TRISC13 = 0; //Set as output 
#endif
	
	/*RB5 for RAMP output*/	   
#if 1	   
	ANSBbits.ANSB5 = 0; //Set as digital
	LATBbits.LATB5 = 0; //Init pin to 0
	TRISBbits.TRISB5 = 0; //Set as output 
	__builtin_write_OSCCONL(OSCCON & 0xbf);
	RPOR9bits.RP18R = 22;	//OC5 function
	__builtin_write_OSCCONL(OSCCON | 0x40);	


#endif
			 
		//For Timer 3
		/*ramp*/
	OC5CON1bits.OCM = 0b000; // Disable Output Compare Module
	OC5R = 100; // Write the duty cycle for the first PWM pulse
	OC5RS = 200; // Write the duty cycle for the second PWM pulse
	OC5CON1bits.OCTSEL = 1; // Select Timer 3 as output compare time base
	OC5R = 100; // Load the Compare Register Value
//	OC5CON1bits.OCM = 0b111; // Select the Output Compare mode
	OC5CON1bits.OCM = 0b110; // Select the Output Compare mode
	OC5CON2bits.OCTRIS = 0; //Connect output
	OC5CON2bits.SYNCSEL = 0b01101; 
//	IPC10bits.OC5IP = 6;
//	IFS2bits.OC5IF = 0; // Clear OC5 interrupt flag
//	IEC2bits.OC5IE = 1; // Enable OC5 interrupt

	// Initialize and enable Timer3
	T3CONbits.TON = 0; // Disable Timer
	T3CONbits.TCS = 0; // Select internal instruction cycle clock
	T3CONbits.TGATE = 0; // Disable Gated Timer mode
//    T3CONbits.TCKPS = 0b001; // Select 1:8 Prescaler
	T3CONbits.TCKPS = 0b000; // Select 1:1 Prescaler
	TMR3 = 0x00; // Clear timer register
	PR3 = TMR3_PERIOD; // Load the period value
	IPC2bits.T3IP = 6; // Set Timer 3 Interrupt Priority Level
	IFS0bits.T3IF = 0; // Clear Timer 3 Interrupt Flag
	IEC0bits.T3IE = 1; // Enable Timer 3 interrupt
	T3CONbits.TON = 1; // Start Timer
	
	
	airdet_enable = FALSE;
	airdet_dir = 0;
	airdet_ramp = 400;
}

void start_air_det(void)
{
	air_min1 = air_max = air_raw;
	air_state = 0;
	air_cnt = 0;
	alarm_cntr = 0;
	airdet_enable = TRUE;
	airdet_dir = 0;
	airdet_ramp = 400;

}
void stop_air_det(void)
{
	airdet_enable = FALSE;
}
unsigned char get_air_det(void)
{
	if(dbg_cntr > 0)
		return 1;
	else	
		return 0;
}

void air_detector(unsigned char trig)
{
	int air_val;

#if 0	/*Accumulated air*/
	accum_air_cntr++;
	if(accum_air_cntr >= ACCUM_PERIOD)
	{
		accum_air_cntr = 0;
		accum_air_vol_sum -= accum_air_vol[accum_air_vol_idx];
		accum_air_vol[accum_air_vol_idx] = accum_air_vol_1Msum;
		accum_air_vol_sum += accum_air_vol_1Msum;
		accum_air_vol_idx++;
		if(accum_air_vol_idx >= 15)
			accum_air_vol_idx = 0;
		accum_air_vol_1Msum = 0;
#ifndef	AIRDET_DIS
		if(accum_air_vol_sum > (alarm_trig*10))/*1mL = alarm_trig*10  ---- for alarm_trig 0.1mL */
		{
			if(stmotor_stat()== STMTR_RUN)
			{
				if(air_alarm == FALSE)
					air_alarm = TRUE; 
			}
		}
#endif			   
	}
#endif

	air_val = air_raw;
	if(air_state == 0)  /*before pulse start */
	{
		if(air_val > AIR_TRIG)
		{
			air_state = 1;
			air_strt_idx = airdet_ramp;
			if(air_val > air_max)
			{
				air_max = air_val;
				air_max_idx = airdet_ramp;
			}
		}
	}
	else if(air_state == 1)
	{
		if(air_val > air_max)
		{
			air_max = air_val;
			air_max_idx = airdet_ramp;
		}
		else if(air_val < AIR_TRIG)
		{
			air_state = 2;
			air_end_idx = airdet_ramp;
		}
	}
	if (trig)
	{
		tmp_cntr++;
		if(tmp_cntr >= 50)
			tmp_cntr = 0;
		air_seq[tmp_cntr].max_v = air_max;
		air_seq[tmp_cntr].start = air_strt_idx;
		air_seq[tmp_cntr].max = air_max_idx;
		air_seq[tmp_cntr].end = air_end_idx;
		/* find max/min */
		if((air_max > AIR_VALID_AMP)&& air_state == 2/* && abs(air_max_old_idx - air_max_idx) < 40 */&& abs(air_end_idx - air_strt_idx) < 420 )
		{
			alarm_cntr = 0;
			dbg_cntr = 0;

		}
		else
		{
#if 0
			accum_air_vol_1Msum++;
#endif			
			if(alarm_cntr < alarm_trig/*20*/)
				alarm_cntr++;
			else
			{
				
				dbg_cntr++;

#ifndef	AIRDET_DIS
//				if(stmotor_stat()== STMTR_RUN)
//				{
					if(air_alarm == FALSE)
						air_alarm = TRUE; 
//				}
#endif			   
			}
		}
		air_min1 = air_max = air_raw;
		air_max_old_idx = air_max_idx;
		air_strt_idx = air_end_idx = air_max_idx = 0;
		air_state = 0;
	}
}


void ramp_swing(void)
{
	if(airdet_enable)
	{
		if ( airdet_dir == 0 )
		{
			if(airdet_ramp < 1600)
			{
				air_detector(0);
				airdet_ramp+=5;           //increment 85  -> 80 steps - 
			}
			else 
			{
				air_detector(1);
				airdet_dir = 1;
			}
		}
		else
		{
			if(airdet_ramp > 400)
			{
				air_detector(0);
				airdet_ramp-=5;
			}
			else 
			{
				air_detector(1);
				airdet_dir = 0;
			}
		}
	 OC5R = airdet_ramp; 
	}
}
/* Timer 3 ISR*/
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)
{
	ramp_swing();
	IFS0bits.T3IF = 0; // Clear Timer 3 interrupt flag
}




