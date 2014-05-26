/*****************************************************************************
 *****************************************************************************/

#ifndef _OSAPI_H
#define _OSAPI_H

#ifdef OSAPI_PUB
#define OSAPIPUB
#else
#define OSAPIPUB extern
#endif

#define NUM_TIMERS 3
 /* An array to hold handles to the created timers. */
OSAPIPUB	xTimerHandle xTimers[ NUM_TIMERS ];

OSAPIPUB	xSemaphoreHandle QVGAMutSemaphore;

OSAPIPUB	void BeepInit(void);
OSAPIPUB	 void os_prepare( void );
OSAPIPUB	 void EnterCriticalSPI( void );
OSAPIPUB	 void ExitCriticalSPI( void );

#endif // _OSAPI_H
