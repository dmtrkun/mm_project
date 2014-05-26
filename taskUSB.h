/*****************************************************************************
 *****************************************************************************/

#ifndef __TASKUSB_H
#define __TASKUSB_H

#ifdef TASKUSB_PUB
#define TASKUSBPUB
#else
#define TASKUSBPUB extern
#endif

#include "include.h"
#ifdef TASKUSB_PUB

#else

#endif

// size of the stack for this task
#define STACK_SIZE_USB		(configMINIMAL_STACK_SIZE * 2)
// handle to the task
TASKUSBPUB xTaskHandle hUSBTask;
TASKUSBPUB void taskUSB(void* pvParameter);


#endif // __TASKUSB_H
