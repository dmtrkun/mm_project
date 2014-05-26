/*****************************************************************************
 *****************************************************************************/

#ifndef __TASK_BCKGRND_H
#define __TASK_BCKGRND_H

#ifdef TASK_BCKGRND_PUB
#define TASK_BCKGRNDPUB
#else
#define TASK_BCKGRNDPUB extern
#endif

TASK_BCKGRNDPUB unsigned char wdi_ena;
TASK_BCKGRNDPUB void ClearParams(void);

// handle for the task
TASK_BCKGRNDPUB xTaskHandle hBACKGRNDTask;
// the Background task
TASK_BCKGRNDPUB void taskBackground(void* pvParameter);

// size of the stack for this task
#define STACK_SIZE_BACKGRND		(configMINIMAL_STACK_SIZE * 1)
#endif // __TASK_BCKGRND_H
