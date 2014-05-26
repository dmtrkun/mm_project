#ifndef clock_h
#define clock_h

#ifdef CLOCK_PUB
#define CLOCKPUB
#else
#define CLOCKPUB extern
#endif



typedef struct
{
   unsigned long ticks;     /* absolute time, milliseconds   */
   unsigned long seconds;   /* absolute time, seconds        */
   unsigned int timer;     /* countdown timer, milliseconds */
   unsigned int timer2;     /* countdown timer, milliseconds rxuart*/
}clockType;
   

CLOCKPUB volatile clockType RTclock;
//CLOCKPUB unsigned char hour;
//CLOCKPUB unsigned char min;
//CLOCKPUB unsigned char sec;
CLOCKPUB void init_clock(void);
CLOCKPUB clock_t clock(void);
CLOCKPUB unsigned long clock_ms(void);
#endif /* clock_h */
