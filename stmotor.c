#define STMOTOR_PUB

#include	"include.h"


void init_stmotor(void)
{

	__builtin_write_OSCCONL(OSCCON & 0xbf);
	RPINR1bits.INT2R = 37; //RPI37 Linear interrupt
	RPOR10bits.RP21R = 19; //RP21    OC2
	__builtin_write_OSCCONL(OSCCON | 0x40);	
	
	/*Enable motor pin*/
	TRISAbits.TRISA5 = 0; //Set as output	   
	LATAbits.LATA5 = 1; //Set to 1 -disable  motor
	
	/*Step motor pin*/
	TRISGbits.TRISG6 = 0; //Set as output	   
	LATGbits.LATG6 = 0; //Set to 0
	ANSGbits.ANSG6 = 0; //Set as digital
	
	/*Linear interrupt pin*/
	TRISCbits.TRISC14 = 1; //Set as input	   
	ANSCbits.ANSC14 = 0; //Set as digital
	
	    
		// Initialize Output Compare Module
    //For Timer 2
	/*motor*/
	OC2CON1bits.OCM = 0b000; // Disable Output Compare Module
	OC2R = 100; // Write the duty cycle for the first PWM pulse
//    OC2RS = 2100; // Write the duty cycle for the second PWM pulse
    OC2RS = 2000; // Write the duty cycle for the second PWM pulse


//	OC2RS = 3100; // Write the duty cycle for the second PWM pulse
	OC2CON1bits.OCTSEL = 0; // Select Timer 2 as output compare time base
//    OC2CONbits.OCM = 0b000; // Select the Output Compare mode
//    OC2CONbits.OCM = 0b101; // Select the Output Compare mode

    /*Interrupt for Motor*/
	IPC1bits.OC2IP = 5;
	IFS0bits.OC2IF = 0;
	IEC0bits.OC2IE = 1;
		
		// Initialize and enable Timer2
	T2CONbits.TON = 0; // Disable Timer
	T2CONbits.TCS = 0; // Select internal instruction cycle clock
	T2CONbits.TGATE = 0; // Disable Gated Timer mode
	T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
	TMR2 = 0x00; // Clear timer register
	PR2 = TMR2_PERIOD; // Load the period value 2kHz and step motor
//	PR2 = 40000; // Load the period value 1kHz for buzzer and step motor
 	IPC1bits.T2IP = 6; // Set Timer2 Interrupt Priority Level
 	IFS0bits.T2IF = 0; // Clear Timer2 Interrupt Flag
// 	IEC0bits.T2IE = 1; // Enable Timer2 interrupt
//	IPC1bits.OC2IP = 0x01;
//	IFS0bits.OC2IF = 0;
//	IEC0bits.OC2IE = 1;
	T2CONbits.TON = 1; // Start Timer
}

unsigned int cntrRT[40];
unsigned int st_delay_cor_max = 0;
unsigned int st_rate_cor_max = 0;

volatile float f_rate;
volatile unsigned int m_rate;

void new_calc_rate(float rate)
{
	unsigned int m_delay, div;

	if(rate>max_rate)
		rate = max_rate;
	
	/*init vars*/
	st_rate = st_rate_cor = st_delay = st_delay_cor = 0;
	st_div = st_div_cntr = 0;

//	rate = rate*(1.0+(float)LINEAR_CORR/(float)MOTOR_STEPPERTURN);
	if ((unsigned int)rate > MAXRATE)
		rate = MAXRATE;
#if 0	
	if((m_rate == 0)||(m_delay == 0))
	{
		st_rate = m_rate;
		st_delay = m_delay;
		return;
	}


	for (div = 40; div > 0; div--)
	{
		if((m_rate/div > 0)&&(m_delay/div > 0))
		{
			if((m_rate%div == 0)&&(m_delay%div == 0))
	   		{
	   			st_rate = m_rate/div;
	   			st_delay = m_delay/div;
	   			break;
	   		}
	   		if(m_rate%div == 0)
	   		{
	   				st_rate = m_rate/div;
	   				st_delay = m_delay/div;
	   				st_delay_cor = m_delay%div;
	   				break;
	   		}
	   		if(m_delay%div == 0)
	   		{
 	   				st_rate = m_rate/div;
 	   				st_delay = m_delay/div;
 	   				st_rate_cor = m_rate%div;
	   				break;
	   		}
			st_rate = m_rate/div;
			st_delay = m_delay/div;
			st_delay_cor = m_delay%div;
 			st_rate_cor = m_rate%div;
			break;
		}

	}
	st_div = div;
	cntrRT[div-1]++;

	if(st_delay_cor_max < st_delay_cor)
		st_delay_cor_max = st_delay_cor;
	if(st_rate_cor_max < st_rate_cor)
		st_rate_cor_max = st_rate_cor;
#else
//	m_rate = (unsigned int)(rate);
	div = 1;
	for(m_rate = 0; m_rate < 4; m_rate++ )
	{
//		f_rate = ((GetPeripheralClock()/((float)MOTOR_STEPPERTURN*M_PULSEPERSTEP))*(3600.0*TENTHMLPERTURN))/((float)div*rate);
#if 0			
		if(vol_para.rate >= 700.0)
			f_rate = (GetPeripheralClock()*3600.0*TENTHMLPERTURN)/((float)MOTOR_STEPPERTURN*M_PULSEPERSTEP*(float)div*rate);
		else
		{
			f_rate = (GetPeripheralClock()*3600.0*TENTHMLPERTURN)/((float)130*M_PULSEPERSTEP*(float)div*rate);
			f_rate *= 0.5;
		}
#else			 
		if(vol_para.rate >= 700.0)
			f_rate = ((float)GetPeripheralClock()*3600.0*TENTHMLPERTURN)/((float)MOTOR_STEPPERTURN*M_PULSEPERSTEP*(float)div*rate);
		else
			f_rate = ((float)GetPeripheralClock()*3600.0*TENTHMLPERTURN*(700.0*(float)MOTOR_STEPPERTURN - (float)LINEAR_CORR*rate))/\
													((float)MOTOR_STEPPERTURN*M_PULSEPERSTEP*(float)div*rate*700.0*(float)WORKZONE);
//			(GetPeripheralClock()*3600.0*TENTHMLPERTURN)/(M_PULSEPERSTEP*(float)div*rate*WORKZONE) - 
//				(GetPeripheralClock()*3600.0*TENTHMLPERTURN*(float)LINEAR_CORR)/((float)MOTOR_STEPPERTURN*M_PULSEPERSTEP*(float)div*700.0*WORKZONE);
#endif
		if(f_rate < 65535)
			break;
		div = div*8;
	}
	if(m_rate == 4)
	{
		m_rate = 3;
//		PR2 = (unsigned int)65535;
		g_f_rate = 65535.0; 
	}
	else
//		PR2 =(unsigned int)f_rate;
		g_f_rate = f_rate;
	
//	T2CONbits.TCKPS = m_rate;
	g_m_rate = m_rate;

//	alarm_trig = (unsigned int)((3600.0 * AIR_VOLUME)/(0.015 * rate));
	alarm_trig = (unsigned int)((3600.0 * AIR_VOLUME)/(0.048 * rate));

#endif

}
void stmotor_setdir(unsigned char dir)
{
	setExpGPO(dir, DIRMOTOR_EXTIOBIT);
}

void stmotor_cmd(unsigned char dir,unsigned char cmd)
{
	static unsigned long run_time;
	if(dir != STMTR_DIR_NOCHNG)
		stmotor_setdir((~dir)&0x01);
#if 0	
        switch(cmd)
        {
            case STMTR_STOP:
		if(st_state != cmd)
		{
        		st_state = cmd;
                        work_time += (clock() - run_time)/60;
//       		IEC0bits.T2IE = 0; // Disable Timer2 interrupt
			STMOTOR_ENA_PIN =1;
//      		OC2CONbits.OCM = 0b0; // stop  motor
                }
                break;
            case STMTR_RUN:
 		if(st_state != cmd)
		{
        		st_state = cmd;
                        run_time = clock();
			/*config	interrupt 2 for Linear*/
			INTCON2bits.INT2EP = 1; //Interrupt on Negative edge
			IPC7bits.INT2IP = 6; // Set INT2 Interrupt Priority Level to unmaskable
 			IFS1bits.INT2IF = 0; // Clear INT2 Interrupt Flag
 			IEC1bits.INT2IE = 1; // Enable INT2 interrupt

// 			m_steps = MAX_ST*4;
 			m_steps = 0;
			PR2 =(unsigned int)g_f_rate;
			T2CONbits.TCKPS = g_m_rate;
			
			rotate_detector = 0;
	 		rotate_det_cntr = MOTOR_STEPPERTURN + MOTOR_DETECTERR;
			rotate_debug_max = 0;
			rotate_debug_min = rotate_debug_last = 255;
			
			IFS0bits.T2IF = 0; // Clear Timer2 Interrupt Flag
 			IEC0bits.T2IE = 1; // Enable Timer2 interrupt
			
			STMOTOR_ENA_PIN = 0; //Enable motor
			OC2CON1bits.OCM = 0b101; // run  motor
		
			setBit(runhold_stat, RUNNING);
		}
                break;
            case STMTR_RERUN:
                if(st_state == STMTR_RUN)
                {
                    PR2 =(unsigned int)g_f_rate;
                    T2CONbits.TCKPS = g_m_rate;
                }
                
                break;
            default:
                break;
        }
        
#else        
        
        
        
        
        
        
        
        if(st_state == STMTR_RUN && cmd == STMTR_RERUN)
        {
        	PR2 =(unsigned int)g_f_rate;
		T2CONbits.TCKPS = g_m_rate;
                return;
                
        }
        if(st_state != cmd)
	{
		st_state = cmd;
		if(cmd == STMTR_RUN)
		{
			run_time = clock();
			/*config	interrupt 2 for Linear*/
			INTCON2bits.INT2EP = 1; //Interrupt on Negative edge
			IPC7bits.INT2IP = 6; // Set INT2 Interrupt Priority Level to unmaskable
 			IFS1bits.INT2IF = 0; // Clear INT2 Interrupt Flag
 			IEC1bits.INT2IE = 1; // Enable INT2 interrupt

// 			m_steps = MAX_ST*4;
 			m_steps = 0;
			PR2 =(unsigned int)g_f_rate;
			T2CONbits.TCKPS = g_m_rate;
			
			rotate_detector = 0;
	 		rotate_det_cntr = MOTOR_STEPPERTURN + MOTOR_DETECTERR;
			rotate_debug_max = 0;
			rotate_debug_min = rotate_debug_last = 255;
			
			IFS0bits.T2IF = 0; // Clear Timer2 Interrupt Flag
 			IEC0bits.T2IE = 1; // Enable Timer2 interrupt
			
			STMOTOR_ENA_PIN = 0; //Enable motor
			OC2CON1bits.OCM = 0b101; // run  motor
		
			setBit(runhold_stat, RUNNING);
		}
		else
		{
		  work_time += (clock() - run_time)/60;

//       		IEC0bits.T2IE = 0; // Disable Timer2 interrupt
			STMOTOR_ENA_PIN =1;
//      		OC2CONbits.OCM = 0b0; // stop  motor
		}
	}
#endif

}
//void stmotor_power(unsigned char cmd)
//{
//	_RG1 = cmd&0x01 ; //Motor Voltage select
//}

void stmotor_step(unsigned char dir)
{
int i;
//	STMOTOR_ENA_PIN = 0; //Enable
//	_RF2 = dir&0x01;
	_RD1 = 1;	//Step
	for(i = 0; i<2000;i++);
	_RD1 = 0;
//	STMOTOR_ENA_PIN = 1; //Disable

}

unsigned char stmotor_stat(void)
{
	return st_state;
}


void init_motor(void)
{
	init_stmotor();
//	stmotor_power(STMTR_POWER_ON);
	stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_STOP);
}


/* OC2 ISR Step motor interrupt procedure*/
void __attribute__((interrupt, no_auto_psv)) _OC2Interrupt(void)
{
	IFS0bits.OC2IF = 0; // Clear Timer 2 interrupt flag
}


#define DIS_DELAY		20 //20*0.5ms - 10 ms
/*****************************************************
 * Timer 2 ISR
 * 
 * Calls every micrpostep and check motor health
 * When in linear region - run with maximum rate
 * 
 */
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
//unsigned int n_rate, n_delay;
//static unsigned int n_rate_cor, n_delay_cor;
static unsigned int step;
//static unsigned short disable_tmr;

	if ((m_steps&0x0f) == 0x0f) /*every 16 step*/
	{
		if((rotate_det_cntr > 0)&&(rotate_detector == 0))
		{
//			motor_alarm = FALSE;
			rotate_det_cntr--;
		}
		else
		{
#ifndef MOTORCHK_DIS				 
			if(rotate_detector == 0 && test_mode == 0)
			{
				STMOTOR_ENA_PIN = 1; //Disable motor
				st_state = STMTR_STOP;
				IEC0bits.T2IE = 0; // Disable Timer2 interrupt
				OC2CON1bits.OCM = 0b0; // stop  motor
 				IEC1bits.INT2IE = 0; // Disable Linear INT0 interrupt
				m_steps = 0;
//				put_evnt_queue(WE_MOTORFAULT);
				if(motor_alarm == FALSE)
					motor_alarm = TRUE;
				IFS0bits.T2IF = 0; // Clear Timer 2 Interrupt Flag
				return;
			}
#endif				
			if(debounce_cntr > 0)
			{
				debounce_cntr--;
				rotate_det_cntr--;
			}
			else
			{
				rotate_detector = 0;
				if(LATCbits.LATC14 == 0)
				{
	 				rotate_det_cntr = MOTOR_STEPPERTURN + MOTOR_DETECTERR;
				}
			}
		}
		if(steps_cntr > 0)
		{
//			step++;
//			if(step > steps_cntr)
			steps_cntr--;
			if(steps_cntr == 0)
			{
				STMOTOR_ENA_PIN =1;
//				step = 0;
				st_state = STMTR_STOP;
				IEC0bits.T2IE = 0; // Disable Timer2 interrupt
				OC2CON1bits.OCM = 0b0; // stop  motor
 				IEC1bits.INT2IE = 0; // Disable Linear INT2 interrupt
				m_steps = 0;
				IFS0bits.T2IF = 0; // Clear Timer 2 Interrupt Flag
				return;
			}
		}
		if(linear_cntr > 0) //if still in linear region - decrement cntr
		{
				linear_cntr--;
				if(linear_cntr == 0) //end of linear region - stop count linear and run in programmed rate
				{
					PR2	= (unsigned int)f_rate;
					T2CONbits.TCKPS = m_rate;
				}
//				if(m_steps > (int)M_PULSEPERSTEP)
//					m_steps -= (int)M_PULSEPERSTEP;

//				m_steps++;
//				IFS0bits.T2IF = 0; // Clear Timer 2 interrupt flag
//				return;
		}
		if(st_state == STMTR_STOP)
		{
			STMOTOR_ENA_PIN =1;
			IEC0bits.T2IE = 0; // Disable Timer2 interrupt
			OC2CON1bits.OCM = 0b0; // stop  motor
 			IEC1bits.INT2IE = 0; // Disable Linear INT2 interrupt
			m_steps = 0;
			IFS0bits.T2IF = 0; // Clear Timer 2 Interrupt Flag
			return;
		}
		steps++;
	}
	m_steps++;
	IFS0bits.T2IF = 0; // Clear Timer 2 Interrupt Flag
}

void __attribute__ ((interrupt, no_auto_psv)) _INT2Interrupt(void)
{
static unsigned char odd_even;
	

	if(linear_cntr == 0)
	{
		rotate_detector = 1;
		debounce_cntr = 5;
		if(rotate_debug_max < rotate_det_cntr)
			rotate_debug_max = rotate_det_cntr;
		if(rotate_debug_min > rotate_det_cntr)
			rotate_debug_min = rotate_det_cntr;
		rotate_debug_last = rotate_det_cntr;
	}
//	if(odd_even)
	{
		odd_even = 0;
		if(linear_cntr != 0 || vol_para.rate > 700.0)
		{
			IFS1bits.INT2IF = 0; // Clear INT2 interrupt
			return;
		}
	
		
		linear_cntr = LINEAR_CORR;
// 		if(T2CONbits.TCKPS != 0)
		T2CONbits.TCKPS = 0;
// 		if ( PR2 > (unsigned int)(((GetPeripheralClock()/((float)MOTOR_STEPPERTURN*M_PULSEPERSTEP))*(3600.0*TENTHMLPERTURN))/700.0))
		PR2	= (unsigned int)(((GetPeripheralClock()/((float)MOTOR_STEPPERTURN*M_PULSEPERSTEP))*(3600.0*TENTHMLPERTURN))/700.0);
	}
//	else
//		odd_even = 1;
	IFS1bits.INT2IF = 0; // Clear INT2 interrupt
}


