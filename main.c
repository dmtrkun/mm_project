/*
 */
#define MAIN_PUB

/* Standard includes. */
#include "include.h"
#include <stdio.h>

/* Demo application includes. */
#include "partest.h"
#include "bsp/SST39LF400.h"

//#include "usb.h"
//#include "usb_function_generic.h"

_CONFIG1( WDTPS_PS32768 & FWPSA_PR128 & ALTVREF_ALTVREDIS & WINDIS_OFF & FWDTEN_OFF & ICS_PGx2 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
_CONFIG2( POSCMOD_HS & IOL1WAY_OFF & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
_CONFIG3( WPFP_WPFP255 & SOSCSEL_EC & WUTSEL_LEG & ALTPMP_ALTPMPEN & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
// ALTPMP_ALTPMPEN
//portCHAR pcTraceBuf__[1000] __attribute__((aligned(2)));
//portCHAR* pcTraceBuf = pcTraceBuf__;

//#define GRC_CRC32_EXTERNAL_MARKER 0xFCEECE8Bul
//#define GRC_CRC32_EXTERNAL_ADDR 0x00010B70ul
extern USB_HANDLE USBGenericInHandle;
// parallel flash
#define FLASHInit()             				
#define ChipErase()                     SST39LF400ChipErase();
#define WriteArray(address, pdata, len) SST39LF400WriteArray(address, pdata, len)
#define ReadArray(address, pdata, len)  SST39LF400ReadArray(address, pdata, len)

/*-----------------------------------------------------------*/
/*
 * Hardware Init
 */
static void prvSetupHardware( void );

//unsigned char tempor_byte1, tempor_byte2;
    DWORD   addr_test;

/////////////////////////////////////////////////////////////////////////////
// void CheckExternalFlashHex(void)
/////////////////////////////////////////////////////////////////////////////
void CheckExternalFlashHex()
{
    typedef struct 
    {
        UINT32 mchpSignature;
        UINT32 mchpCRCData;
    } CRC_CHECK; 

    CRC_CHECK externalCRC, expectedCRC;   
    WORD textHeight;
    void *pFont;
    GFX_XCHAR *pStr = NULL;
    BOOL  setProgram = FALSE;
	unsigned char IO_reg;

    GFX_XCHAR   msgStr1[] = "      Program External Data";
    GFX_XCHAR   msgStr2[] = "External data invalid.";
    GFX_XCHAR   msgStr3[] = "Please send data using";
    GFX_XCHAR   msgStr4[] = "\"External Memory Programmer\".";
    GFX_XCHAR   msgStr5[] = "Connect USB cabel and";
    GFX_XCHAR   msgStr6[] = "Press \"STOP\".";
    GFX_XCHAR   msgStr8[] = "Flash Err.";
	
//    GOLInit();


    DRV_GFX_Initialize();
    GFX_Initialize();


    pFont = (void*) &Gentium8;
    GFX_FontSet(pFont);
//    SetFont(pFont);
    textHeight = GFX_TextStringHeightGet(pFont);

	if(!DA210DEVBOARD_SST39LF400CheckID())
	{
            pStr = msgStr8 ;
            setProgram = TRUE;
        }
	else
            pStr = msgStr1;

//    while(!DA210DEVBOARD_SST39LF400CheckID());
	
	// check if the CRC matches the data stored in the external flash memory
    expectedCRC.mchpCRCData = GRC_CRC32_EXTERNAL_MARKER;
    expectedCRC.mchpSignature = 0x5048434D;                // this is "MCHP"

    if (setProgram == FALSE)
    {
        DA210DEVBOARD_SST39LF400ReadArray(GRC_CRC32_EXTERNAL_ADDR, (BYTE *)&externalCRC, 8);
    
        if  ((expectedCRC.mchpCRCData != externalCRC.mchpCRCData) || \
             (expectedCRC.mchpSignature != externalCRC.mchpSignature))
        {
            // expected and read CRC does not match, proceed to programming flash first
            // run the flash programming 
            pStr = msgStr2;
            setProgram = TRUE;
        }
    }
//     setProgram = TRUE;

    if (setProgram == TRUE)
    {

                Spi_init();
		MCP23S08Write(GPPU, 0x40 ); 
		_delay_spi(100);
		MCP23S08Write(GPIO, 0x08 ); //Set Back light ON, power ON(logic zero)
		_delay_spi(100);
		MCP23S08Write(IOCON, 0x04 ); //Set IRQ open Drain
		_delay_spi(100);
		MCP23S08Write(IODIR, 0xC7 ); // Directions !!!IN!!! In Out Out Out In In In  -  set WDI output HiImpedance Input mode

				 
		GFX_ColorSet(BLACK);
		GFX_ScreenClear();
		GFX_ColorSet(WHITE);
		GFX_TextStringDraw(10,10                 , pStr,strlen(pStr));
		GFX_TextStringDraw(10,10 + (textHeight*2), msgStr3,strlen(msgStr3));
		GFX_TextStringDraw(10,10 + (textHeight*3), msgStr4,strlen(msgStr4));
		GFX_TextStringDraw(10,10 + (textHeight*4), msgStr5,strlen(msgStr5));
		GFX_TextStringDraw(10,10 + (textHeight*5), msgStr6,strlen(msgStr6));
//        GFX_TextStringDraw(10,10 + (textHeight*6), msgStr7);
		GFX_TextStringDraw(10,10 + (textHeight*6), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*7), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*8), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*9), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*10), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*11), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*12), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*13), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*14), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*15), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*16), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*17), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*18), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*19), msgStr6,strlen(msgStr6));
		GFX_TextStringDraw(10,10 + (textHeight*20), "Test String Test String Test String Tesst String",48);
		GFX_TextStringDraw(10,10 + (textHeight*21), "Test String Test String Test String Tesst String",48);




		do
		{
			IO_reg = MCP23S08Read(GPIO ); //Read
		}
		while((IO_reg&0x01) == 1);				 
				
		PMCON2bits.MSTSEL = 0;		// set CPU as Master

//    WORD    pD;
//    WORD    wr_pD = 0x55aa;
//    DWORD   wr_addr = -1;
//    DWORD   wr_err_cntr = 0;
//    DWORD   rd_err_cntr = 0;
//
//
//            addr_test = 0x01ffff;
//
//
//        while(1)
//        {
////            addr = (0x40000>>1);
//            pD = lRead16(addr_test);
//            pD = lRead16(0x00000);
//        }




                // Call the external flash programming routine
//        ProgramFlash();
        SYSTEM_ProgramExternalMemory();
#if defined (USE_COMM_PKT_MEDIA_USB)

        // check if USB has sent reply to host then do a detach
        while(!USBHandleBusy(USBGenericInHandle));
        USBDeviceDetach();
        // delay the reset to have time for the acknowledge data to be sent to the host side
        DelayMs(100);

#elif defined (USE_COMM_PKT_MEDIA_SERIAL_PORT)

        // check if UART is still busy sending replies to the host
        while(U2STAbits.TRMT);
        // delay the reset to have time for the acknowledge data to be sent to the host side
        DelayMs(10);

#endif
        
		MCP23S08Write(IODIR, 0x47 ); // Directions Out In Out Out Out In In In  -  set WDI output
		while(1); //Wait to WDI reset
				 
		// Force Reset to force the checking of the flash memory if programming was a success
        Reset();
    }
    
}	


/*********************************************************************
* Function: WORD ExternalMemoryCallback(EXTDATA* memory, LONG offset, WORD nCount, void* buffer)
*
* PreCondition: none
*
* Input:  memory - pointer to the bitmap or font external memory structures
*                  (FONT_EXTERNAL or BITMAP_EXTERNAL)
*         offset - data offset
*         nCount - number of bytes to be transferred to the buffer
*         buffer - pointer to the buffer
*
* Output: number of bytes were transferred.
*
* Side Effects: none
*
* Overview: this function must be implemented in application. Graphics Library calls it
*           each time the data from external memory is required. The application must copy 
*           required data to the buffer provided.
*
* Note: none
*
********************************************************************/
// If there are several memories in the system they can be selected by IDs.
// In this demo ID for memory chip installed on Graphics PICTail board is assumed to be 0.
#if 0
#define SST39_MEMORY    0
/* */

WORD ExternalMemoryCallback(IMAGE_EXTERNAL *memory, LONG offset, WORD nCount, void *buffer)
{
    if(memory->ID == SST39_MEMORY)
    {

        // Read data requested into buffer provided
        SST25ReadArray(memory->address + offset, // address to read from
        (BYTE *)buffer, nCount);
    }

    return (nCount);
}
#endif

/*-----------------------------------------------------------*/

/*
 * Create the demo tasks then start the scheduler.
 */
int main( void )
{
/* for debugging purpose*/	
	vol_ptr = &VolPara;

//	INTCON1bits.NSTDIS = 1; //Disable nesting interrupst
	
	/* Configure any hardware required for this demo. */
	prvSetupHardware();
	
#ifndef SIM_DEBUG
/*TODO*/	
 	cdc_ena = 0;
	CheckExternalFlashHex();
 	cdc_ena = 1;
#endif	

#if 0	   
	/*RTOS tracing prepare*/
	LATGbits.LATG2 = 0; //Init pin to 0
	TRISGbits.TRISG2 = 0; //Set as output 
	LATGbits.LATG3 = 0; //Init pin to 0
	TRISGbits.TRISG3 = 0; //Set as output 
	
	TRISFbits.TRISF3 = 0; //Set as  
	TRISDbits.TRISD0 = 1; //Set as input
	__builtin_write_OSCCONL(OSCCON & 0xbf);
	RPINR18bits.U1RXR = 11; //RP11
	RPOR8bits.RP16R = 3;	//U1TX function
	__builtin_write_OSCCONL(OSCCON | 0x40);	
	U1MODEbits.UARTEN = 1; //Enable uart
	U1MODEbits.BRGH = 1; // High speed mode
	U1BRG =(GetPeripheralClock()/(4*115200)) -1;
#endif

//	vTaskStartTrace(pcTraceBuf, 1000);

	os_prepare();
		
	/* Finally start the scheduler. */
	vTaskStartScheduler();
	/* Will only reach here if there is insufficient heap available to start
	the scheduler. */
	return 0;
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
//	vParTestInitialise();
 	LATAbits.LATA5 = 1; //Set to 1  - disable motor
	TRISAbits.TRISA5 = 0; //Set as output	   
}

/*-----------------------------------------------------------*/

void PwrDownCmd( void )
{
	unsigned short reg;
//	vTaskSuspendAll();
	vTaskEndScheduler();	
	Beep(1000);
	stop_air_det();
	stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_STOP);
	reg = MCP23S08Read(GPIO ); //Read
	_delay_spi(50);
//	reg |= 0x08; //Set Back light OFF
	reg &= ~0x08; //Set Back light OFF
	while(Beep_wait()); //Wait for end of beep
	MCP23S08Write(GPIO, reg); 
	_delay_spi(50);
        ((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
	SST25SectorErase(PARAM_E2PIMG_BASE);
	if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)));
	reg |= 0x20; //Power off 
	MCP23S08Write(GPIO, reg );
	while(1); /*Wait for Power down*/
														 
}

volatile long mem_cntr;
void *my_malloc(size_t size)
{
	mem_cntr++; 
	return malloc(size); 
}
void my_free(void *ptr)
{
	mem_cntr--; 
	free(ptr);
}

void __attribute__((interrupt, no_auto_psv))_MathError(void) 
//void __attribute__((__interrupt__)) _MathError(void) 
{ 
Beep(10);
abort(); 
}
void __attribute__((interrupt, no_auto_psv))_StackError(void) 
//void __attribute__((__interrupt__)) _StackError(void) 
{ 
Beep(10);
abort(); 
}
void __attribute__((interrupt, no_auto_psv))_AddressError(void) 
//void __attribute__((__interrupt__)) _AddressError(void) 
{ 
Beep(10);
abort(); 
}

#if 0
#define traceQUEUE_SEND_FROM_ISR_FAILED(pxQueue) \
/* ���� ������ �� ������� � ������� hCONTROLQueue. */ \
if (pxQueue == hCONTROLQueue) { \
/* ������������� ����� ������ ���������� PG2. */ \
LATGbits.LATG2 ^= LATGbits.LATG2; \
}
#define traceQUEUE_SEND_FROM_ISR_FAILED(pxQueue) \
if (pxQueue == hADCSemaphore) { \
/* ������������� ����� ������ ���������� PG3. */ \
LATGbits.LATG3 ^= LATGbits.LATG3; \
}
#endif
void set_debug(unsigned char set)
{
//	LATGbits.LATG2 = set;
}

void trig_debug(xQueueHandle pxQueue)
{
//	if(pxQueue == hQVGAQueue)
//		LATGbits.LATG2 ^= LATGbits.LATG2;
}

#if 0
#define traceTASK_SWITCHED_OUT()\
if (pxCurrentTCB->pxTaskTag == 's') { \
set_debug(0); \
}
#define  traceTASK_SWITCHED_IN()\
if (pxCurrentTCB->pxTaskTag == 's') { \
set_debug(1); \
}
#endif
/*-----------------------------------------------------------*/

