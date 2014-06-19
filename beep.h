/*****************************************************************************
 *****************************************************************************/

#ifndef _BEEP_H
#define _BEEP_H

#ifdef BEEP_PUB
#define BEEPPUB
#else
#define BEEPPUB extern
#endif

//#include "graphics.h"



#define BEEP_ON		{(OC1CON2bits.OCTRIS = 0);} // Start the Output Compare mode       
#define BEEP_OFF	{(OC1CON2bits.OCTRIS = 1);} // Stop the Output Compare mode        

#define BEEPSTATE_ON	1 
#define BEEPSTATE_OFF	2
#define REPEAT_OFF		0
#define REPEAT_ON			1

typedef struct
{
	 unsigned char beepcnt;             /* number of beeps, times */
	 unsigned int beepdrn;     /* beep duration, milliseconds */
	 unsigned int beeptmr;     /* countdown timer, milliseconds */
}beepType;
BEEPPUB volatile beepType beep_cb;



BEEPPUB unsigned char beep_state;

BEEPPUB	void BeepInit(void);
BEEPPUB void beep_(unsigned int time, unsigned char cnt);
BEEPPUB	void Beep(unsigned int);
BEEPPUB	unsigned int Beep_wait(void);
BEEPPUB void beepTimerCallback( xTimerHandle pxTimer );
BEEPPUB void beep_hndl(void);
#endif // _BEEP_H
