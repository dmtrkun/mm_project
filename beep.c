/*****************************************************************************
 *****************************************************************************/
#define BEEP_PUB
#include "include.h"
xTimerHandle beepTimer;
unsigned long duration;
unsigned char wave_idx;
#define MS_1	16000L
#define US_1	1000
//const unsigned int wave[16] = {750,249,2000,249,750,2000,249,750};
//const unsigned int wave[16] ={500,500,850,149,995,5,850,149,500,500,149,850,5,995,149,850,500};
const unsigned int wave[3][16] = {
{500,500,853,146,1853,146,500,500,146,1853,146,853,  0,  0,  0,  0},
{500,500,782,217,900, 100,782,217,500,500, 217,782,100,900,217,782},
{500,500,676,323,750, 250,676,323,500,500, 323,676,250,750,323,676},
};


//const unsigned int wave1[16] ={500,500,853,146,1853,146,500,500,146,1853,146,853,  0,  0,  0,  0};
//const unsigned int wave2[16] ={500,500,782,217,900, 100,782,217,500,500, 217,782,100,900,217,782};
//const unsigned int wave3[16] ={500,500,782,217,900, 100,782,217,500,500, 217,782,100,900,217,782};

/*********************************************************************
 * Function:        oUTPUT cOMPARE 1 ISR
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        Beep ISR. 
 * Note:            
 ********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _OC1Interrupt(void)
{
unsigned char vol = bzz_volume;
#if 1		   
		if (duration > 0)
		{
			if(duration >= wave[vol][wave_idx])
				duration -= wave[vol][wave_idx];
			else
				duration = 0;
		}
 	 	else 
			OC1CON2bits.OCTRIS = 1;// disable output

		if(vol == 0)
			wave_idx = (wave_idx+1)%12;
		else
			wave_idx = (wave_idx+1)%16;
		OC1R = OC1TMR + wave[vol][wave_idx]; 
#else
		if(OC1CON2bits.OCTRIS = 1)// disable output
	 		OC1R = OC1TMR + 1000;	
		else
		{
			wave_idx = (wave_idx+1)%12;
			OC1R = OC1TMR + wave1[wave_idx]; 
		}
#endif	
	// clear the interrupt flag
		IFS0bits.OC1IF = 0;
}


void beep_hndl(void)
{
#if 0	
	if(beep_cb.beeptmr > 0)   /* if countdown timer is active */
      beep_cb.beeptmr -= 1;  /*  decrement it               */
	else
	{
		if(beep_cb.beepcnt > 0)
		{
			if(beep_cb.beepcnt & 0x01)
			{
				beep_cb.beeptmr = beep_cb.beepdrn;
				BEEP_ON;
			}
			else	 
			{
				beep_cb.beeptmr = beep_cb.beepdrn/10;
				BEEP_OFF;
			}
			beep_cb.beepcnt--;
		}
		else
			BEEP_OFF;
	}
#endif
}

void beep_(unsigned int time, unsigned char cnt)
{
#ifdef BEEP_DISABLE	
	return;
#endif
	if (beep_state == BEEPSTATE_OFF)
		return;
	BEEP_OFF;
	beep_cb.beepcnt = beep_cb.beeptmr = 0;
	beep_cb.beepcnt = (cnt-1)<<1;
	beep_cb.beepdrn = beep_cb.beeptmr = time;

//	beep_cb.beeptmr += time;
	BEEP_ON;
}


/*********************************************************************
 * Function:        void BeepInit(void)
 * PreCondition:    None
 * Input:           None
 * Output:          Does not return
 * Side Effects:    None
 * Overview:        Beep handling routine. 
 * Note:            
 ********************************************************************/
void BeepInit(void)
{
	ANSG &= ~0x0080;
	__builtin_write_OSCCONL(OSCCON & 0xbf);
	RPOR13bits.RP26R = 18; //OC1
	__builtin_write_OSCCONL(OSCCON | 0x40);	
	OC1CON1 = 0x1c0b;// 01110000001011  500b      32Mhz/2 Clock
	OC1CON2 = 0x0020;// disable output
	OC1R = MS_1;  
	OC1RS = 0x000e;  
	wave_idx = 0;
	IFS0bits.OC1IF = 0;
	IEC0bits.OC1IE = 1;
	IPC0bits.OC1IP = 7;

#if 0
	beepTimer = xTimerCreate(  (GFX_XCHAR*)"BeepTmr",        /* Just a text name, not used by the kernel. */
                                       ( 1 ),    /* The timer period in ticks. */
                                       pdTRUE,         /* The timers will auto-reload themselves when they expire. */
                                       ( void * ) 1,   /* Assign each timer a unique id equal to its array index. */
                                       beepTimerCallback  /* Each timer calls the same callback when it expires. */);
#endif
}	

unsigned int Beep_wait(void)
{
	return duration;
}
void Beep(unsigned int durat)
{
	
	duration = (unsigned long)durat * MS_1;
//	xTimerStart( beepTimer, 0 );
#ifndef BEEP_DISABLE	
	OC1CON2bits.OCTRIS = 0;// enable output
#endif
}
 
#if 0 
 void beepTimerCallback( xTimerHandle pxTimer )
 {
     /* Optionally do something if the pxTimer parameter is NULL. */
     configASSERT( pxTimer );
 	 OC1CON2bits.OCTRIS = 1;// disable output
     xTimerStop( pxTimer, 0 );
 
 }
#endif
