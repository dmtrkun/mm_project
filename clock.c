/*
** Real Time Clock
**
**  Uses Timer1
**  and interrupt on period match
*/
#define CLOCK_PUB

#include "include.h"

/* Timer1 period for 1 ms */
#define TMR1_PERIOD (GetPeripheralClock()/1000) 

unsigned long clock_ms(void)
{

	return RTclock.ticks;
}
clock_t clock(void)
{
	return RTclock.seconds;
}

void set_clock(unsigned long sec)
{
	RTclock.seconds = sec;
}

void init_clock(void)
 {
   RTclock.timer = 0;      /* clear software registers  */
   RTclock.ticks = 0;
//   RTclock.seconds = 0;
   
	 beep_cb.beeptmr = 0;
	 beep_cb.beepcnt = 0;

   TMR1 = 0;               /* clear timer1 register     */
   PR1 = TMR1_PERIOD;      /* set period1 register      */
   T1CONbits.TCS = 0;      /* set internal clock source */
   T1CONbits.TCKPS = 0;   /* set prescaler 1:1					*/
   IPC0bits.T1IP = 4;      /* set priority level        */
   IFS0bits.T1IF = 0;      /* clear interrupt flag      */
   IEC0bits.T1IE = 1;      /* enable interrupts         */
//   SRbits.IPL = 3;         /* enable CPU priority levels 4-7*/
   T1CONbits.TON = 1;      /* start the timer*/
 }


void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
	static int sticks=0;

	beep_hndl();

	RTclock.ticks++;         /* increment ticks counter     */
  if (sticks++ > 1000)
  {                           /* if time to rollover         */
	  sticks = 0;              /*  clear seconds ticks     */
  	RTclock.seconds++;       /*  and increment seconds   */
#if 0		
		sec++;
		if ( sec>59)
		{
			sec = 0;
			min++;
			if ( min>59)
			{
				min = 0;
				hour++;
				if ( hour > 23)
					hour = 0;
			}
		}
#endif	
	}
	
	IFS0bits.T1IF = 0;       /* clear interrupt flag     */
	return;
}

/********************************************************
 * 
 * 
 * RTC driver
 * 
 * 
 ********************************************************/


