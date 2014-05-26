/*
*/
#include "include.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Demo includes. */
#include "lcd.h"
//#include "main.h"
#include "Configs/HWP_DA210_BRD_16PMP_PFLASH_QVGAv1.h"

/*
 * The LCD is written to by more than one task so is controlled by this
 * 'gatekeeper' task.  This is the only task that is actually permitted to
 * access the LCD directly.  Other tasks wanting to display a message send
 * the message to the gatekeeper.
 */
//static void vLCDTask( void *pvParameters );

/*-----------------------------------------------------------*/

/* Brief delay to permit the LCD to catch up with commands. */
#define lcdSHORT_DELAY		3

/* SFR that seems to be missing from the standard header files. */
#define PMAEN				*( ( unsigned short * ) 0x60c )

/* The length of the queue used to send messages to the LCD gatekeeper task. */
#define lcdQUEUE_SIZE		3
/*-----------------------------------------------------------*/
int main_graph(void);
void TickInit(void);
void DA210DEVBOARD_SST39LF400SectorErase(DWORD address);
void DA210DEVBOARD_SST39LF400WriteWord(WORD data, DWORD address);
WORD DA210DEVBOARD_SST39LF400ReadWord(DWORD address);


/************************************************************************************
* Function: DA210DEVBOARD_SST39LF400SectorErase(DWORD address)
*
* Notes: Erase the sector specified by the address in the parallel flash.
*        The graphics module is locked out during this function but
*        since this function occurs fast enough and only called when 
*        calibrating the touch screen, it will not be noticeable.
*
*************************************************************************************/
void DA210DEVBOARD_SST39LF400SectorErase(DWORD address)
{
    // this function locks out the graphics module from accessing
    // external memory until the MSTSEL is reset back to Graphics

    // to minimize effects on the screen refresh 
    // wait until the VSYNC starts
    while(!_VMRGN); 

  	PMCON2bits.MSTSEL = 0;		// set CPU as Master
    SST39LF400SectorErase(address);
  	PMCON2bits.MSTSEL = 3;		// set Graphics as Master

}    

/************************************************************************************
* Function: DA210DEVBOARD_SST39LF400WriteWord(WORD data, DWORD address)
*
* Notes: Write a word to parallel flash with the given address.
*        The graphics module is locked out during this function but
*        since this function occurs fast enough and only called when 
*        calibrating the touch screen, it will not be noticeable.
*
*************************************************************************************/
void DA210DEVBOARD_SST39LF400WriteWord(WORD data, DWORD address)
{
    // this function locks out the graphics module from accessing
    // external memory until the MSTSEL is reset back to Graphics

    // to minimize effects on the screen refresh 
    // wait until the VSYNC starts
    while(!_VMRGN); 

  	PMCON2bits.MSTSEL = 0;		// set CPU as Master
    SST39LF400WriteWord(data, address);
  	PMCON2bits.MSTSEL = 3;		// set Graphics as Master
    
}
 
/************************************************************************************
* Function: WORD DA210DEVBOARD_SST39LF400ReadWord(DWORD address)
*
* Notes: Reads the data from the parallel flash located in the given address.  
*        The graphics module is locked out during this function but
*        since this function occurs fast enough and only called when 
*        calibrating the touch screen, it will not be noticeable.
*
*************************************************************************************/
WORD DA210DEVBOARD_SST39LF400ReadWord(DWORD address)
{
    // this function locks out the graphics module from accessing
    // external memory until the MSTSEL is reset back to Graphics

    WORD readWord;

    // to minimize effects on the screen refresh 
    // wait until the VSYNC starts
    while(!_VMRGN); 

  	PMCON2bits.MSTSEL = 0;		// set CPU as Master
    readWord = SST39LF400ReadWord(address);
  	PMCON2bits.MSTSEL = 3;		// set Graphics as Master
    
    return readWord;

}    


// dummy function
WORD ExternalMemoryCallback(GFX_EXTDATA *memory, LONG offset, WORD nCount, void *buffer)
{
	// dummy function
    return (1);
}





