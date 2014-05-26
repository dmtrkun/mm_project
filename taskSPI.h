/*****************************************************************************
 *****************************************************************************/

#ifndef __TASKSPI_H
#define __TASKSPI_H

#ifdef TASKSPI_PUB
#define TASKSPIPUB
#else
#define TASKSPIPUB extern
#endif

#include "include.h"
#ifdef TASKSPI_PUB

#else

#endif

#define STOPKEY_EXTIOBIT		0
#define ONOFFKEY_EXTIOBIT		1
#define LCDPOWER_EXTIOBIT		3
#define DIRMOTOR_EXTIOBIT		4
#define POWERON_EXTIOBIT		5
#define DOOR_EXTIOBIT				6
#define WDI_EXTIOBIT				7



// size of the stack for this task
#define STACK_SIZE_SPI		(configMINIMAL_STACK_SIZE * 1)
// handle to the task
TASKSPIPUB xTaskHandle hSPITask;
TASKSPIPUB unsigned char ucExpGPIO;
TASKSPIPUB unsigned char ucExpGPO;
TASKSPIPUB xSemaphoreHandle hSPISemaphore;
TASKSPIPUB xSemaphoreHandle hIOSemaphore;
TASKSPIPUB void taskSPI(void* pvParameter);


#endif // __TASKSPI_H
