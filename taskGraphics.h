/*****************************************************************************
 *****************************************************************************
 * FileName:        taskGraphics.h
 *****************************************************************************/

#ifndef __TASK_GRAPHICS_H
#define __TASK_GRAPHICS_H

#ifdef TASK_GRAPHICS_PUB
#define TASK_GRAPHICSPUB
#else
#define TASK_GRAPHICSPUB extern
#endif

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"
#include "graphics.h"

///////////////////////////////////////////////////////////////////
// objects to be passed to the graphics display routines are
// encapsulated in this data type. All incoming messages are
// expressed using this structure and then passed onto the
// incoming queue
typedef struct{
	WORD	cmd;
	union {
		BYTE		bVal[8];
		WORD		wVal[4];
		DWORD		dVal[2];
		GOL_MSG 	golMsg;
	} data;
} GRAPHICS_MSG;

// the queue used to send messages to the graphics task
TASK_GRAPHICSPUB xQueueHandle hQVGAQueue;

// number of entries in this queue
#define QVGA_QUEUE_SIZE	10


///////////////////////////////////////////////////////////////////
// Defines for the possible messages to be sent
#define MSG_DEFAULT					0	// do nothing
#define MSG_TIMER_EXPIRED			1	// timer expired
#define MSG_UPDATE_DISPLAY		2	// redraw the display
#define MSG_UPDATE_CURSOR			3		//fast cursor update
#define MSG_UPDATE_OFF				4		// keypad activity
#define MSG_UPDATE_STOP				5		// keypad activity
#define MSG_TOUCH_EVENT				6	// touchscreen activity
#define MSG_INPUT_EVENT				7	// input activity
#define MSG_ERROR						8 // error event


// these defined is used to scale the task usage bar graph display
#if defined(__PIC24F__)
//#define MAX_BAR_LENGTH	12
#define MAX_BAR_LENGTH	24
#else
//#define MAX_BAR_LENGTH 	30
#define MAX_BAR_LENGTH 	60
#endif

// Graphics task itself
TASK_GRAPHICSPUB void taskGraphics(void* pvParameter);

// size of the stack for this task
#define STACK_SIZE_GRAPHICS		(configMINIMAL_STACK_SIZE * 12)
// handle to the task
TASK_GRAPHICSPUB xTaskHandle hGRAPHICSTask;

#endif // __TASK_GRAPHICS_H

