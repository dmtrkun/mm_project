/*****************************************************************************
 *****************************************************************************/

#ifndef __TASKUART_H
#define __TASKUART_H

#ifdef TASKUART_PUB
#define TASKUARTPUB
#else
#define TASKUARTPUB extern
#endif

#include "include.h"
#ifdef TASKUART_PUB

#else

#endif



typedef void * xComPortHandle;

typedef enum
{
	serCOM1,
	serCOM2,
	serCOM3,
	serCOM4,
	serCOM5,
	serCOM6,
	serCOM7,
	serCOM8
} eCOMPort;

typedef enum
{
	serNO_PARITY,
	serODD_PARITY,
	serEVEN_PARITY,
	serMARK_PARITY,
	serSPACE_PARITY
} eParity;

typedef enum
{
	serSTOP_1,
	serSTOP_2
} eStopBits;

typedef enum
{
	serBITS_5,
	serBITS_6,
	serBITS_7,
	serBITS_8
} eDataBits;

typedef enum
{
	ser50,
	ser75,
	ser110,
	ser134,
	ser150,
	ser200,
	ser300,
	ser600,
	ser1200,
	ser1800,
	ser2400,
	ser4800,
	ser9600,
	ser19200,
	ser38400,
	ser57600,
	ser115200
} eBaud;

// size of the stack for this task
#define STACK_SIZE_UART		(configMINIMAL_STACK_SIZE * 2)
// handle to the task
TASKUSBPUB xTaskHandle hUARTTask;
TASKUSBPUB void taskUART(void* pvParameter);


xComPortHandle xSerialPortInitMinimal( unsigned long ulWantedBaud, unsigned portBASE_TYPE uxQueueLength );
xComPortHandle xSerialPortInit( eCOMPort ePort, eBaud eWantedBaud, eParity eWantedParity, eDataBits eWantedDataBits, eStopBits eWantedStopBits, unsigned portBASE_TYPE uxBufferLength );
void vSerialPutString( xComPortHandle pxPort, const signed char * const pcString, unsigned short usStringLength );
signed portBASE_TYPE xSerialGetChar( xComPortHandle pxPort, signed char *pcRxedChar, portTickType xBlockTime );
signed portBASE_TYPE xSerialPutChar( xComPortHandle pxPort, signed char cOutChar, portTickType xBlockTime );
portBASE_TYPE xSerialWaitForSemaphore( xComPortHandle xPort );
void vSerialClose( xComPortHandle xPort );




#endif // __TASKUART_H
