/*****************************************************************************
 *  Module for Microchip Graphics Library
 *  Epson S1D13522 EPD controller driver
 *****************************************************************************
 * FileName:        S1D13522.c
 * Compiler:       	MPLAB C30, C32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright (C) 2012 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *****************************************************************************/
#include "HardwareProfile.h"

#ifdef GFX_USE_DISPLAY_CONTROLLER_S1D13522

#include "Compiler.h"
#include "TimeDelay.h"
#include "Graphics/gfxcolors.h"
#include "Graphics/DisplayDriver.h"
#include "Graphics/S1D13522.h"
#include "Graphics/gfxtcon.h"
#include "Graphics/Primitive.h"


#if defined (USE_GFX_PMP)
    #include "Graphics/gfxpmp.h"
#elif defined (USE_GFX_EPMP)
    #include "Graphics/gfxepmp.h"
#endif  

#if defined ( USE_SPI_CHANNEL )
	#include "drv_spi.h"
#endif

// Pip/Main/Cursor
static SHORT g_HostMemAccessCfg;
static GFX_LAYER g_ActiveLayer = GFX_MAIN_LAYER;
static WORD g_PipLayerWidth;
static WORD g_PipLayerHeight;
static WORD g_PipConfig;
static WORD g_CursorLayerWidth;
static WORD g_CursorLayerHeight;
static WORD g_CursorConfig;


WORD DefAutoUpd;

// Color
GFX_COLOR    _color;

// Clipping region control
SHORT       _clipRgn;

// Clipping region borders
SHORT       _clipLeft;
SHORT       _clipTop;
SHORT       _clipRight;
SHORT       _clipBottom;

void        PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE *bitmap, BYTE stretch);
void        PutImage2BPP(SHORT left, SHORT top, FLASH_BYTE *bitmap, BYTE stretch);
void        PutImage4BPP(SHORT left, SHORT top, FLASH_BYTE *bitmap, BYTE stretch);
void        PutImage8BPP(SHORT left, SHORT top, FLASH_BYTE *bitmap, BYTE stretch);

void        PutImage1BPPExt(SHORT left, SHORT top, void *bitmap, BYTE stretch);
void        PutImage2BPPExt(SHORT left, SHORT top, void *bitmap, BYTE stretch);
void        PutImage4BPPExt(SHORT left, SHORT top, void *bitmap, BYTE stretch);
void        PutImage8BPPExt(SHORT left, SHORT top, void *bitmap, BYTE stretch);

//=============================================================================
//	STATIC (PRIVATE) FUNCTIONS
//=============================================================================
// ----------------------------------------------------------------------------------
// seDeviceWrite()
// 
// ----------------------------------------------------------------------------------
static inline void seDeviceWrite(WORD data) 
{
#if defined ( USE_SPI_CHANNEL )
	
// See definitions are in HWP_S1D13522_EPD.h file

//***********************************************
// SPI Setup 
//***********************************************										 
	// When SPI settings are being changed, even if the settings are the same as before,
	// for some reasons, the SCK output from the MCU will not be driven for a period of time.
	// The change of this signal from driven low to tri-state may be treated by S1D13522 as 1
	// extra serial host input clock if at that moment the HCS_L is low. Because of this extra
	// clock, the subsequent data read will all be shifted. To avoid this, make sure HCS_L is
	// high when writing to MCU's SPI configurations.										 
	DisplayDisable();				// Set HCS_L high before writing to SPI configurations	
        EPD_SPI_STAT(USE_SPI_CHANNEL)           = 0;
       
        EPD_SPI_CONbits(USE_SPI_CHANNEL).MSTEN  = SPI_MSTEN;
        EPD_SPI_CONbits(USE_SPI_CHANNEL).MODE16 = SPI_MODE;
        EPD_SPI_CONbits(USE_SPI_CHANNEL).CKP    = SPI_CKP;
        EPD_SPI_CONbits(USE_SPI_CHANNEL).CKE    = SPI_CKE;
        EPD_SPI_CONbits(USE_SPI_CHANNEL).SMP    = SPI_SMP;       
    #ifdef __PIC32MX
        EPD_SPI_CONbits(USE_SPI_CHANNEL).MODE32 = 0;
        EPD_SPI_BRG(USE_SPI_CHANNEL) 			= SPI_BAUDRATE;							
        EPD_SPI_CONbits(USE_SPI_CHANNEL).ON 	= SPI_MODULE_ENABLE;
    #else
        EPD_SPI_CON2(USE_SPI_CHANNEL) 			= 0;
        EPD_SPI_CONbits(USE_SPI_CHANNEL).PPRE   = SPI_PPRE; 
        EPD_SPI_CONbits(USE_SPI_CHANNEL).SPRE   = SPI_SPRE; 
        EPD_SPI_STATbits(USE_SPI_CHANNEL).SPIEN = SPI_MODULE_ENABLE;
    #endif 
	DisplayEnable();				// Set HCS_L low after writing to SPI configurations
    
//***********************************************
// SPI	Write
//***********************************************
    #if defined(__PIC32MX__)
		SpiChnPutC(USE_SPI_CHANNEL, data);
        WORD value = (WORD)SpiChnGetC(USE_SPI_CHANNEL);
    #else
		#if (USE_SPI_CHANNEL == 1)
			IFS0bits.EPD_SPI_IF(USE_SPI_CHANNEL) = 0;
			// remove from the buffer if any
			WORD value = EPD_SPI_BUF(USE_SPI_CHANNEL);
			// write
	   	   	EPD_SPI_BUF(USE_SPI_CHANNEL) = data;
	   	   	while( IFS0bits.EPD_SPI_IF(USE_SPI_CHANNEL) == 0 );
		#else		// assumed to be 2
			IFS2bits.EPD_SPI_IF(USE_SPI_CHANNEL) = 0;
			// remove from the buffer if any
			WORD value = EPD_SPI_BUF(USE_SPI_CHANNEL);
			// write
	   	   	EPD_SPI_BUF(USE_SPI_CHANNEL) = data;
	   	   	while( IFS2bits.EPD_SPI_IF(USE_SPI_CHANNEL) == 0 );
		#endif
	#endif

#elif defined ( USE_16BIT_PMP )
	
	DeviceWrite( data );
		
#else

	DeviceWrite( (BYTE)(data>>0) );
	DeviceWrite( (BYTE)(data>>8) );       
       
#endif

}

// ----------------------------------------------------------------------------------
// seDeviceRead()
// 
// ----------------------------------------------------------------------------------
static inline WORD seDeviceRead()
{	
#if defined ( USE_SPI_CHANNEL )
	WORD value;
	
    #if defined(__PIC32MX__)
        // remove from the buffer if any
        value = (WORD)getcSPI1();
        
        // dummy read
        putcSPI1(0x00);
        value = (WORD)getcSPI1();
        
		// dummy read	
        putcSPI1(0x00);
        value = (WORD)getcSPI1();
    #else	
		// remove from the buffer if any
		value = EPD_SPI_BUF(USE_SPI_CHANNEL);
		
		// dummy read
		IFS0bits.EPD_SPI_IF(USE_SPI_CHANNEL) = 0;
		EPD_SPI_BUF(USE_SPI_CHANNEL) = 0;
	   	while(IFS0bits.EPD_SPI_IF(USE_SPI_CHANNEL) == 0){};
		value = EPD_SPI_BUF(USE_SPI_CHANNEL);
		
		// read
		IFS0bits.EPD_SPI_IF(USE_SPI_CHANNEL) = 0;
		EPD_SPI_BUF(USE_SPI_CHANNEL) = 0;
		while(IFS0bits.EPD_SPI_IF(USE_SPI_CHANNEL) == 0){};
		value = EPD_SPI_BUF(USE_SPI_CHANNEL);
	#endif
	
	return value;

#elif defined ( USE_16BIT_PMP )
	
	WORD value = DeviceRead();

	return value;
	
#else

	WORD value;
	
	value  = (WORD)DeviceRead() << 0;
	value |= (WORD)DeviceRead() << 8;

	return value;	
	
#endif

}

// ----------------------------------------------------------------------------------
// seWAIT_HRDY()
// 
// ----------------------------------------------------------------------------------
static inline void __attribute__ ((always_inline)) seWAIT_HRDY( void )
{
#if defined (EPD_BUSY_LINE)	
	
	while ( EPD_BUSY_LINE );
	
#else

	DisplaySetCommand();					// set RS line to low for command
	seDeviceWrite(RD_REG);					// write command
	DisplaySetData();						// set RS line to high for data		
	seDeviceWrite( REG000A_SYSTEM_STATUS );	// write data	
	while ( seDeviceRead() & 0x20 );		// read data	
	
#endif
}

//=============================================================================
//	GFX FUNCTIONS
//=============================================================================

/*********************************************************************
* Function:  void ResetDevice()
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: resets LCD, initializes PMP
*
* Note: none
*
********************************************************************/
void ResetDevice(void)
{
	//DWORD i, Count = ( (DWORD)DISP_VER_RESOLUTION / 16 ) * DISP_HOR_RESOLUTION;

    /////////////////////////////////////////////////////////////////////
    // Initialize the device
    /////////////////////////////////////////////////////////////////////
    
#if defined( USE_SPI_CHANNEL )  

	BusyLineConfig();
	DisplayResetEnable();               // hold in reset by default
    DisplayResetConfig();               // enable RESET line
    DisplayCmdDataConfig();             // enable RS line
    DisplayDisable();                   // not selected by default
    DisplayConfig();                    // enable chip select line
	Delay10us(20);  

    DisplayResetDisable();              // release from reset

    Delay10us(20);  
	
#else
	
  #if defined (USE_GFX_EPMP)
    #if defined (EPMPCS1_ADDRESS_LINE_COUNT) || defined (EPMPCS2_ADDRESS_LINE_COUNT)
      WORD i, addrEnable, addrCount;
    #endif
  #endif
 
    // variable for PMP timing calculation
	// GetPeripheralClock() is in Mhz. pClockPeriod will be in nanoseconds.
    DWORD pClockPeriod = (1000000000ul) / GetPeripheralClock();

	DisplayResetEnable();               // hold in reset by default
    DisplayResetConfig();               // enable RESET line
    DisplayCmdDataConfig();             // enable RS line
    DisplayDisable();                   // not selected by default
    DisplayConfig();                    // enable chip select line
    DisplayBacklightOff();              // initially set the backlight to off
    DisplayBacklightConfig();           // set the backlight control pin

    #if defined (USE_GFX_EPMP)
      // EPMP setup
      PMCON1bits.ADRMUX = 0;	  // address is not multiplexed
      PMCON1bits.MODE = 3;        // master mode
      PMCON1bits.CSF = 0;         // PMCS1 pin used for chip select 1, PMCS2 pin used for chip select 2
      PMCON1bits.ALP = 0;         // set address latch strobes to high active level 
      PMCON1bits.ALMODE = 0;      // "smart" address strobes are not used
      PMCON1bits.BUSKEEP = 0;     // bus keeper is not used
	
      PMCON2bits.RADDR = 0xff;	  // set CS2 end address
		
      #if defined (__PIC24FJ256DA210__)	
		    PMCON2bits.MSTSEL = 0;		// set CPU as Master
      #endif
      
      //enable the address lines if required
      #if defined (EPMPCS1_ADDRESS_LINE_COUNT) || defined (EPMPCS2_ADDRESS_LINE_COUNT)
          // decide how many address lines to use
          #if (EPMPCS1_ADDRESS_LINE_COUNT > EPMPCS2_ADDRESS_LINE_COUNT)
              addrCount = EPMPCS1_ADDRESS_LINE_COUNT;
          #else     
              addrCount = EPMPCS2_ADDRESS_LINE_COUNT;
          #endif
              
          for(addrEnable = 1, i = 0; i < addrCount; i++)
          {
              if (i <= 15)
                  PMCON4 |= addrEnable;
              else
                  PMCON3 |= addrEnable;
              
              // change the addrEnable back to 1 when it reaches 16 count
              if (addrEnable == 0x8000)
                  addrEnable = 0x0001;
              else
                  addrEnable = addrEnable << 1;    
          }    
      #else    
      
          PMCON4 = 0;                 // PMA0 - PMA15 address lines are disabled
          PMCON3 |= 0;                // PMA16 - PMA17 address line is disabled
          
      #endif    

      #if defined (EPMPCS1_DATA_SETUP_TIME)

       #if defined (__PIC24FJ256DA210__)	
        PMCS1BS = (GFX_EPMP_CS1_BASE_ADDRESS >> 8);
       #else	  
        PMCS1BS = 0x0200; 	        // CS1 start address
        PMCS2BS = 0xff00;			// set CS1 end address and CS2 start address  
       #endif	    

      	PMCS1CFbits.CSDIS = 0;      // enable CS
      	PMCS1CFbits.CSP = 0;        // CS active low
      	PMCS1CFbits.CSPTEN = 1;     // enable CS port
      	PMCS1CFbits.BEP = 0;        // byte enable active low
      	PMCS1CFbits.WRSP = 0;       // write strobe active low
      	PMCS1CFbits.RDSP = 0;       // read strobe active low
      	PMCS1CFbits.SM = 0;         // read and write strobes on separate lines 
      
       #ifdef USE_16BIT_PMP
       	PMCS1CFbits.PTSZ = 2;       // data bus width is 16-bit 
       #else
       	PMCS1CFbits.PTSZ = 0;       // data bus width is 8-bit 
       #endif
      
      	PMCS1MDbits.ACKM = 0;        // PMACK is not used

      
        if (EPMPCS1_DATA_SETUP_TIME < (pClockPeriod/4))
            PMCS1MDbits.DWAITB = 0;
        else if (EPMPCS1_DATA_SETUP_TIME >= (pClockPeriod/4))
        {
            PMCS1MDbits.DWAITB = (EPMPCS1_DATA_SETUP_TIME / pClockPeriod);
            if ((EPMPCS1_DATA_SETUP_TIME % pClockPeriod) > 0)
                PMCS1MDbits.DWAITB += 1;
        }        
                
        if (EPMPCS1_DATA_WAIT_TIME < ((pClockPeriod*3)/4))
            PMCS1MDbits.DWAITM = 0;
        else if (EPMPCS1_DATA_WAIT_TIME >= ((pClockPeriod*3)/4))
        {
            PMCS1MDbits.DWAITM = (EPMPCS1_DATA_WAIT_TIME / pClockPeriod);
            if ((EPMPCS1_DATA_WAIT_TIME % pClockPeriod) > 0)
                PMCS1MDbits.DWAITM += 1;
        }        

        if (EPMPCS1_DATA_HOLD_TIME <= (pClockPeriod/4))
            PMCS1MDbits.DWAITE = 0;
        else if (EPMPCS1_DATA_HOLD_TIME >= (pClockPeriod/4))
        {
            PMCS1MDbits.DWAITE = (EPMPCS1_DATA_HOLD_TIME / pClockPeriod);
            if ((EPMPCS1_DATA_HOLD_TIME % pClockPeriod) > 0)
                PMCS1MDbits.DWAITE += 1;
        }       
      #endif // #if defined (EPMPCS1_DATA_SETUP_TIME)
      
      #if defined (EPMPCS2_DATA_SETUP_TIME)

       #if defined (__PIC24FJ256DA210__)	
   	    PMCS2BS = (GFX_EPMP_CS2_BASE_ADDRESS >> 8);
       #endif    	

      	PMCS2CFbits.CSDIS = 0;      // enable CS
      	PMCS2CFbits.CSP = 0;        // CS active low
      	PMCS2CFbits.CSPTEN = 1;     // enable CS port
      	PMCS2CFbits.BEP = 0;        // byte enable active low
      	PMCS2CFbits.WRSP = 0;       // write strobe active low
      	PMCS2CFbits.RDSP = 0;       // read strobe active low
      	PMCS2CFbits.SM = 0;         // read and write strobes on separate lines 
      
       #ifdef USE_16BIT_PMP
       	PMCS2CFbits.PTSZ = 2;       // data bus width is 16-bit 
       #else
       	PMCS2CFbits.PTSZ = 0;       // data bus width is 8-bit 
       #endif
      
      	PMCS2MDbits.ACKM = 0;        // PMACK is not used

        if (EPMPCS2_DATA_SETUP_TIME < (pClockPeriod/4))
            PMCS2MDbits.DWAITB = 0;
        else if (EPMPCS2_DATA_SETUP_TIME >= (pClockPeriod/4))
        {
            PMCS2MDbits.DWAITB = (EPMPCS2_DATA_SETUP_TIME / pClockPeriod);
            if ((EPMPCS2_DATA_SETUP_TIME % pClockPeriod) > 0)
                PMCS2MDbits.DWAITB += 1;
        }        
                
        if (EPMPCS2_DATA_WAIT_TIME < ((pClockPeriod*3)/4))
            PMCS2MDbits.DWAITM = 0;
        else if (EPMPCS2_DATA_WAIT_TIME >= ((pClockPeriod*3)/4))
        {
            PMCS2MDbits.DWAITM = (EPMPCS2_DATA_WAIT_TIME / pClockPeriod);
            if ((EPMPCS2_DATA_WAIT_TIME % pClockPeriod) > 0)
                PMCS2MDbits.DWAITM += 1;
        }        

        if (EPMPCS2_DATA_HOLD_TIME <= (pClockPeriod/4))
            PMCS2MDbits.DWAITE = 0;
        else if (EPMPCS2_DATA_HOLD_TIME >= (pClockPeriod/4))
        {
            PMCS2MDbits.DWAITE = (EPMPCS2_DATA_HOLD_TIME / pClockPeriod);
            if ((EPMPCS2_DATA_HOLD_TIME % pClockPeriod) > 0)
                PMCS2MDbits.DWAITE += 1;
        }    
      #endif // #if defined (EPMPCS2_DATA_SETUP_TIME)

	  PMCON3bits.PTWREN = 1;      // enable write strobe port
	  PMCON3bits.PTRDEN = 1;      // enable read strobe port
	  PMCON3bits.PTBE0EN = 0;     // disable byte enable port
	  PMCON3bits.PTBE1EN = 0;     // disable byte enable port
	  PMCON3bits.AWAITM = 0;      // don't care
	  PMCON3bits.AWAITE = 0;      // don't care
		
	  PMCON1bits.PMPEN = 1;
    #else
      // PMP setup
      PMMODE = 0;
      PMAEN = 0;
      PMCON = 0;
      PMMODEbits.MODE = 2;                // Intel 80 master interface

      #if (PMP_DATA_SETUP_TIME == 0)
          PMMODEbits.WAITB = 0;
      #else    
          if (PMP_DATA_SETUP_TIME <= pClockPeriod)
              PMMODEbits.WAITB = 0;
          else if (PMP_DATA_SETUP_TIME > pClockPeriod)
              PMMODEbits.WAITB = (PMP_DATA_SETUP_TIME / pClockPeriod) + 1;
      #endif
      
      #if (PMP_DATA_WAIT_TIME == 0)
          PMMODEbits.WAITM = 0;
      #else    
          if (PMP_DATA_WAIT_TIME <= pClockPeriod)
              PMMODEbits.WAITM = 1;
          else if (PMP_DATA_WAIT_TIME > pClockPeriod)
              PMMODEbits.WAITM = (PMP_DATA_WAIT_TIME / pClockPeriod) + 1;
      #endif
      
      #if (PMP_DATA_HOLD_TIME == 0)
          PMMODEbits.WAITE = 0;
      #else
          if (PMP_DATA_HOLD_TIME <= pClockPeriod)
              PMMODEbits.WAITE = 0;
          else if (PMP_DATA_HOLD_TIME > pClockPeriod)
              PMMODEbits.WAITE = (PMP_DATA_HOLD_TIME / pClockPeriod) + 1;
      #endif

      #ifdef USE_16BIT_PMP
       PMMODEbits.MODE16 = 1;              // 16 bit mode
      #else
       PMMODEbits.MODE16 = 0;              // 8 bit mode
      #endif
      
      PMCONbits.PTRDEN = 1;               // enable RD line
      PMCONbits.PTWREN = 1;               // enable WR line
      PMCONbits.PMPEN = 1;                // enable PMP
    #endif

    DisplayResetDisable();              // release from reset
	
	// hard delay inserted here for devices that needs delays after reset.
	// Value will vary from device to device, please refer to the specific 
	// device data sheet for details.
    Delay10us(20);
	
#endif

	DisplayEnable();					// enable S1D13522

	// INIT_SYS_RUN
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( INIT_SYS_RUN );	// write command
	
	// RD_WFM_INFO	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( RD_WFM_INFO );		// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( (WORD)((DWORD)WFM_ST_ADR >>  0) );
	seDeviceWrite( (WORD)((DWORD)WFM_ST_ADR >> 16) );
		
	// UPD_GDRV_CLR	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( UPD_GDRV_CLR );	// write command
	
	// WAIT_DSPE_TRG		
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( WAIT_DSPE_TRG );	// write command

	// LD_IMG
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG );		// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( SRC_1BIT );


	seWAIT_HRDY();	
	DisplaySetCommand();					// set RS line to low for command
	seDeviceWrite( WR_REG );				// write command
	DisplaySetData();						// set RS line to high for data	
	seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );
	
	DWORD i, Count = ( (DWORD)DISP_VER_RESOLUTION / 16 ) * DISP_HOR_RESOLUTION;
	for ( i = 0; i < Count; i++ )
	{
		seDeviceWrite( 0xffff );
	}

	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_END );	// write command

	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( UPD_FULL );		// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( WFM_INIT );
	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( WAIT_DSPE_TRG );	// write command	
	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( WAIT_DSPE_FREND );	// write command
				
				
	// AutoWaveform enable			
    DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite(RD_REG);
	DisplaySetData();				// set RS line to high for data
	seDeviceWrite(REG0330_UPDATE_BUFFER_CONFIG);	
	DWORD value = seDeviceRead();
	value |= (1<<6);
	value &= 0x7FFF;
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite(WR_REG);
	DisplaySetData();				// set RS line to high for data
	seDeviceWrite(REG0330_UPDATE_BUFFER_CONFIG);
	seDeviceWrite(value);	
					
	DisplayDisable();				// disable S1D13522	

}


/*********************************************************************
* Function: void PutPixel(SHORT x, SHORT y)
*
* PreCondition: none
*
* Input: x,y - pixel coordinates
*
* Output: none
*
* Side Effects: none
*
* Overview: puts pixel
*
* Note: none
*
********************************************************************/
void PutPixel(SHORT x, SHORT y)
{
	if ( g_ActiveLayer == GFX_CURSOR_LAYER )
	{
		// not available for cursor layer
		return;	
	}
	else
	{	
		WORD pxl = _color;
	
		DisplayEnable();				// enable S1D13522	
			
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_AREA );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( SRC_COLOR | g_HostMemAccessCfg );
		seDeviceWrite( x );
		seDeviceWrite( y );
		seDeviceWrite( 1 );
		seDeviceWrite( 1 );
	
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( WR_REG );		// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );
		seDeviceWrite( pxl );

		seWAIT_HRDY();	
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_END );	// write command

		DisplayDisable();				// disable S1D13522	
	}

      
}

/*********************************************************************
* Function: WORD GetPixel(SHORT x, SHORT y)
*
* PreCondition: none
*
* Input: x,y - pixel coordinates 
*
* Output: pixel color
*
* Side Effects: none
*
* Overview: returns pixel color at x,y position
*
* Note: none
*
********************************************************************/
GFX_COLOR GetPixel(SHORT x, SHORT y)
{
#if (COLOR_DEPTH == 1)
    return (1);
#elif (COLOR_DEPTH == 4)
    return (0x0F);
#else
    return (0xFF);
#endif
}

/*********************************************************************
* Function: WORD Bar(SHORT left, SHORT top, SHORT right, SHORT bottom)
*
* PreCondition: none
*
* Input: left,top - top left corner coordinates,
*        right,bottom - bottom right corner coordinates
*
* Output: For NON-Blocking configuration:
*         - Returns 0 when device is busy and the shape is not yet completely drawn.
*         - Returns 1 when the shape is completely drawn.
*         For Blocking configuration:
*         - Always return 1.
*
* Side Effects: none
*
* Overview: draws rectangle filled with current color
*
* Note: none
*
********************************************************************/
WORD Bar(SHORT left, SHORT top, SHORT right, SHORT bottom)
{
	if ( g_ActiveLayer == GFX_CURSOR_LAYER )
	{
		// not available for cursor layer
		return 1;	
	}
	else
	{	
		WORD pxl    = _color;
		WORD Width  = right - left + 1;
		WORD Height = bottom - top + 1;
		DWORD Count = Width * Height;
	
	    if(left > right) 
	        return(1);        //Added to make sure function call is accurate
	    
	    if(bottom < top) 
	        return(1);        //Added to make sure function call is accurate
	        
		if ( _color == WHITE || _color == BLACK )
		{
			pxl = _color == WHITE ? 0xFFFF : 0;
			Count = Count%16 ? 1+Count/16 : Count/16;
		}
		else
		{	
		#if ( SRC_COLOR == SRC_8BIT )				//input packed pixel = 1 byte-per-pixel (8 bpp)
			Count = Count%2 ? 1+Count/2 : Count/2;						
			pxl   = (pxl<<8) | (pxl<<0);
		#elif ( SRC_COLOR == SRC_4BIT )				//packed pixel = 4 bpp
			Count = Count%4 ? 1+Count/4 : Count/4;		
			pxl   = (pxl<<12) | (pxl<<8) | (pxl<<4) | (pxl<<0);
		#elif ( SRC_COLOR == SRC_2BIT )				//packed pixel = 2 bpp
			Count = Count%8 ? 1+Count/8 : Count/8;		
			pxl   = (pxl<<14) | (pxl<<12) | (pxl<<10) | (pxl<<8) | (pxl<<6) | (pxl<<4) | (pxl<<2) | (pxl<<0);
		#elif ( SRC_COLOR == SRC_1BIT )				//packed pixel = 1 bpp
			Count = Count%16 ? 1+Count/16 : Count/16;		
			pxl   = (pxl<<15) | (pxl<<14) | (pxl<<13) | (pxl<<12) | (pxl<<11) | (pxl<<10) | (pxl<<9) | (pxl<<8) |
					(pxl<< 7) | (pxl<< 6) | (pxl<< 5) | (pxl<< 4) | (pxl<< 3) | (pxl<< 2) | (pxl<<1) | (pxl<<0);
		#endif
		}
	
		DisplayEnable();				// enable S1D13522	
			
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_AREA );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( ((_color == WHITE || _color == BLACK) ?  SRC_1BIT : SRC_COLOR ) | g_HostMemAccessCfg );
		seDeviceWrite( left );
		seDeviceWrite( top );
		seDeviceWrite( Width );
		seDeviceWrite( Height );
	
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( WR_REG );		// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );
	
		while ( Count-- )
		{
			seDeviceWrite( pxl );
		}
	
		seWAIT_HRDY();	
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_END );	// write command
	
		DisplayDisable();				// disable S1D13522	
	
	    return 1;	
	}   	
}

/*********************************************************************
* Function: IsDeviceBusy()
*
* Overview: Returns non-zero if LCD controller is busy 
*           (previous drawing operation is not completed).
*
* PreCondition: none
*
* Input: none
*
* Output: Busy status.
*
* Side Effects: none
*
********************************************************************/
WORD IsDeviceBusy(void)
{  
/*
#if defined (EPD_BUSY_LINE)	
	
	while(  EPD_BUSY_LINE  );
	
	return 0;
	
#else

	return ( (GFX_DRIVER_RdReg(REG000A_SYSTEM_STATUS) & 0x20)>>5 );
	
#endif    
*/


#if defined (EPD_BUSY_LINE)	
	seWAIT_HRDY();
#else
	DisplayEnable();
	seWAIT_HRDY();
	DisplayDisable();
#endif	

	return 0;
	
}

/*********************************************************************
* Function: SetClipRgn(left, top, right, bottom)
*
* Overview: Sets clipping region.
*
* PreCondition: none
*
* Input: left - Defines the left clipping region border.
*		 top - Defines the top clipping region border.
*		 right - Defines the right clipping region border.
*	     bottom - Defines the bottom clipping region border.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void SetClipRgn(SHORT left, SHORT top, SHORT right, SHORT bottom)
{
    _clipLeft=left;
    _clipTop=top;
    _clipRight=right;
    _clipBottom=bottom;

}

/*********************************************************************
* Function: SetClip(control)
*
* Overview: Enables/disables clipping.
*
* PreCondition: none
*
* Input: control - Enables or disables the clipping.
*			- 0: Disable clipping
*			- 1: Enable clipping
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void SetClip(BYTE control)
{
    _clipRgn=control;
}

/*********************************************************************
* Function: void ClearDevice(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: clears screen with current color 
*
* Note: none
*
********************************************************************/
void ClearDevice(void)
{
	if ( g_ActiveLayer == GFX_CURSOR_LAYER )
	{
		// not available for cursor layer
		return;	
	}
	else 
	{	
		WORD pxl  = _color;
		DWORD i, Count = (DWORD)DISP_VER_RESOLUTION * (DWORD)DISP_HOR_RESOLUTION; // if layer is main
		
		if ( g_ActiveLayer == GFX_PIP_LAYER )
			Count = (DWORD)DISP_VER_RESOLUTION * (DWORD)DISP_HOR_RESOLUTION;
		
		if ( pxl == WHITE || pxl == BLACK )	
		{
			pxl = _color == WHITE ? 0xffff : 0;
			Count /= 16;
			//UpdateMode = WFM_DU;
		}
		else
		{			
		#if ( SRC_COLOR == SRC_8BIT )				
			Count /= 2;								// packed pixel = 8 bpp 
			pxl   = (pxl<<8) | (pxl<<0);
		#elif ( SRC_COLOR == SRC_4BIT )				//packed pixel = 4 bpp
			Count /= 4;
			pxl   = (pxl<<12) | (pxl<<8) | (pxl<<4) | (pxl<<0);
		#elif ( SRC_COLOR == SRC_2BIT )				//packed pixel = 2 bpp
			Count /= 8;
			pxl   = (pxl<<14) | (pxl<<12) | (pxl<<10) | (pxl<<8) | (pxl<<6) | (pxl<<4) | (pxl<<2) | (pxl<<0);
		#elif ( SRC_COLOR == SRC_1BIT )				//packed pixel = 1 bpp
			Count /= 16;
			pxl   = (pxl<<15) | (pxl<<14) | (pxl<<13) | (pxl<<12) | (pxl<<11) | (pxl<<10) | (pxl<<9) | (pxl<<8) |
					(pxl<< 7) | (pxl<< 6) | (pxl<< 5) | (pxl<< 4) | (pxl<< 3) | (pxl<< 2) | (pxl<<1) | (pxl<<0);
		#endif
		}
	
		
		DisplayEnable();
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG );		// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( ( _color == WHITE || _color == BLACK ) ? SRC_1BIT : SRC_COLOR );

		seWAIT_HRDY();	
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( WR_REG );		// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );
		
		for ( i = 0; i < Count; i++ )
		{
			seDeviceWrite( pxl );
		}
	
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_END );	// write command
			
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( UPD_FULL );		// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( WFM_GC8 );
			
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( WAIT_DSPE_TRG );	// write command
	
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( WAIT_DSPE_FREND );	// write command

		DisplayDisable();				// disable S1D13522	
	}	
}

/*********************************************************************
* void SwapBitsInByte(BYTE *buffer, WORD size)
* Use to swap the bits for the 1BPP pictures
********************************************************************/
void SwapBitsInByte(BYTE *buffer, WORD size)
{
    int k;
    BYTE mask;
    BYTE bit;

    for(k = 0; k < size; k++)
    {
        BYTE data;

        data = buffer[k];
        buffer[k] = 0;

        mask = 0x80;
        bit = 1;

        while(mask)
        {
            if(mask & data)
                buffer[k] |= bit;

            mask >>= 1;
            bit <<= 1;
        }

    }
}
#ifdef USE_BITMAP_FLASH
/*********************************************************************
* Function: void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner,
*        bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE *bitmap, BYTE stretch)
{
    if ( g_ActiveLayer == GFX_CURSOR_LAYER )
   		return;
    
    FLASH_BYTE          *flashAddress;
    FLASH_WORD          *imageAddress;
    WORD                sizeX, sizeY;
	
    // Move pointer to size information
    flashAddress = bitmap + 2;

    // Read image size
    sizeY = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
	
    // skip palette
    flashAddress += 4;              // 2 entries at 16bpp
    
	DisplayEnable();				// enable S1D13522		
	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_AREA );	// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( SRC_1BIT | g_HostMemAccessCfg );
	seDeviceWrite( left );
	seDeviceWrite( top );
	seDeviceWrite( sizeX );
	seDeviceWrite( sizeY );

	//setup Count using specified area size
	DWORD Count = (DWORD)sizeY * (DWORD)sizeX;
	Count += 15;
    Count /= 16;
	
	seWAIT_HRDY();
	DisplaySetCommand();		// set RS line to low for command
	seDeviceWrite( WR_REG );	// write command
	DisplaySetData();			// set RS line to high for data	
	seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );

    imageAddress = (FLASH_WORD *)flashAddress;
    
	while( Count-- )
	{
		SwapBitsInByte((BYTE *)&imageAddress, 2);
        seDeviceWrite( *imageAddress++ );
	}	

	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_END );	// write command
	
	DisplayDisable();				// disable S1D13522	
}

/*********************************************************************
* Function: void PutImage2BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage2BPP(SHORT left, SHORT top, FLASH_BYTE *bitmap, BYTE stretch)
{
    if ( g_ActiveLayer == GFX_CURSOR_LAYER )
    	return;

    FLASH_BYTE          *flashAddress;
    FLASH_WORD          *imageAddress;
    WORD                sizeX, sizeY;
	
    // Move pointer to size information
    flashAddress = bitmap + 2;

    // Read image size
    sizeY = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
	
    // skip palette
    flashAddress += 8;              // 4 entries at 16bpp

	DisplayEnable();				// enable S1D13522		
	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_AREA );		// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( SRC_2BIT | g_HostMemAccessCfg );
	seDeviceWrite( left );
	seDeviceWrite( top );
	seDeviceWrite( sizeX );
	seDeviceWrite( sizeY );

	//setup Count using specified area size
	DWORD Count = (DWORD)sizeY * (DWORD)sizeX;
	Count /= 8;
	
	seWAIT_HRDY();
	DisplaySetCommand();		// set RS line to low for command
	seDeviceWrite( WR_REG );	// write command
	DisplaySetData();			// set RS line to high for data	
	seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );

    imageAddress = (FLASH_WORD *)flashAddress;

	while( Count-- )
	{
		seDeviceWrite( *imageAddress++ );
	}	
	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_END );	// write command

	DisplayDisable();				// disable S1D13522	

}


/*********************************************************************
* Function: void PutImage4BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage4BPP(SHORT left, SHORT top, FLASH_BYTE *bitmap, BYTE stretch)
{
    FLASH_BYTE          *flashAddress;
    FLASH_WORD          *imageAddress;
    WORD                sizeX, sizeY;
	
    // Move pointer to size information
    flashAddress = bitmap + 2;

    // Read image size
    sizeY = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
	
	
    // skip palette
    flashAddress += 32;              // 16 entries at 16bpp

    if ( g_ActiveLayer == GFX_CURSOR_LAYER )
    {	    
	   	WORD x, y;
	   	WORD stride16 = (4*sizeX)%16 ? (4*sizeX)/16 + 1 : (4*sizeX)/16;
	   	DisplayEnable();				// enable S1D13522

		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_ADRCFG );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( 0 );		   	
	   			
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( WR_REG );		// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( REG03DE_CRS_MEM_LOAD );
		
		imageAddress = (FLASH_WORD *)flashAddress;
	
	    for(y = 0; y < sizeY; y++)
	    {
	        for(x = 0; x < stride16; x++)
	        {
	        	seDeviceWrite( *imageAddress++ );
	        }        
	    }
	    
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_ADRCFG );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( 0 );		   	
		    
		DisplayDisable();				// disable S1D13522	 
	} 
	else
	{
		DisplayEnable();				// enable S1D13522	
			
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_AREA );		// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( SRC_4BIT | g_HostMemAccessCfg );
		seDeviceWrite( left );
		seDeviceWrite( top );
		seDeviceWrite( sizeX );
		seDeviceWrite( sizeY );
	
		//setup Count using specified area size
		DWORD Count = (DWORD)sizeY * (DWORD)sizeX;
		Count /= 4;
		
		seWAIT_HRDY();
		DisplaySetCommand();		// set RS line to low for command
		seDeviceWrite( WR_REG );	// write command
		DisplaySetData();			// set RS line to high for data	
		seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );
	
	    imageAddress = (FLASH_WORD *)flashAddress;
	
		while( Count-- )
		{
			seDeviceWrite( *imageAddress++ );
		}	
	
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_END );	// write command
		
		DisplayDisable();				// disable S1D13522	
	}
}

/*********************************************************************
* Function: void PutImage8BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage8BPP(SHORT left, SHORT top, FLASH_BYTE *bitmap, BYTE stretch)
{
    if ( g_ActiveLayer == GFX_CURSOR_LAYER )
    	return;
    		
    FLASH_BYTE          *flashAddress;
    FLASH_WORD          *imageAddress;
    WORD                sizeX, sizeY;
	
    // Move pointer to size information
    flashAddress = bitmap + 2;

    // Read image size
    sizeY = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
	
    // skip palette
    flashAddress += 512;              // 256 entries at 16bpp

	DisplayEnable();				// enable S1D13522
			
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_AREA );		// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( SRC_8BIT | g_HostMemAccessCfg );
	seDeviceWrite( left );
	seDeviceWrite( top );
	seDeviceWrite( sizeX );
	seDeviceWrite( sizeY );

	//setup Count using specified area size
	DWORD Count = (DWORD)sizeY * (DWORD)sizeX;
	Count /= 2;
	
	seWAIT_HRDY();
	DisplaySetCommand();		// set RS line to low for command
	seDeviceWrite( WR_REG );	// write command
	DisplaySetData();			// set RS line to high for data	
	seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );

    imageAddress = (FLASH_WORD *)flashAddress;

	while( Count-- )
	{
		seDeviceWrite( *imageAddress++ );
	}	
	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_END );	// write command

	DisplayDisable();				// disable S1D13522	

}
#endif

#ifdef USE_BITMAP_EXTERNAL
/*********************************************************************
* Function: void PutImage1BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage1BPPExt(SHORT left, SHORT top, void *bitmap, BYTE stretch)
{
    if ( g_ActiveLayer == GFX_CURSOR_LAYER )
    	return;
    		
    register DWORD  memOffset;
    BITMAP_HEADER   bmp;

    BYTE            lineBuffer[((GetMaxX() + 7) / 8)];
    WORD            *pData16;
    SHORT           byteWidth;

    WORD            sizeX, sizeY;
    WORD            x, y;

    // Get bitmap header
    ExternalMemoryCallback(bitmap, 0, sizeof(BITMAP_HEADER), &bmp);
    // Set offset to the image data
	memOffset = sizeof(BITMAP_HEADER) + 4;
    // Line width in bytes
    byteWidth = (bmp.width + 7)/8;    
    // Get size
    //****sizeX = (bmp.width + 1) & 0xFFFE;
    sizeX = ((byteWidth + 1) & 0xFFFE) << 3;//****
    sizeY = bmp.height;
    
   	DisplayEnable();				// enable S1D13522	
   		
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_AREA );		// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( SRC_1BIT | g_HostMemAccessCfg );
	seDeviceWrite( left );
	seDeviceWrite( top );
	seDeviceWrite( sizeX );
	seDeviceWrite( sizeY );
	
	seWAIT_HRDY();
	DisplaySetCommand();		// set RS line to low for command
	seDeviceWrite( WR_REG );	// write command
	DisplaySetData();			// set RS line to high for data	
	seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );

    for(y = 0; y < sizeY; y++)
    {
        // Get line
        ExternalMemoryCallback(bitmap, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;
        SwapBitsInByte(lineBuffer, byteWidth); 
        pData16 = (WORD*)lineBuffer;
        
        for(x = 0; x < (byteWidth + 1)/2; x++)
        {
        	seDeviceWrite( *pData16++ );
        }
    }	

	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_END );		// write command

	DisplayDisable();				// disable S1D13522	

}



/*********************************************************************
* Function: void PutImage2BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage2BPPExt(SHORT left, SHORT top, void *bitmap, BYTE stretch)
{
    if ( g_ActiveLayer == GFX_CURSOR_LAYER )
    	return;
    		
    register DWORD  memOffset;
    BITMAP_HEADER   bmp;

    BYTE            lineBuffer[((GetMaxX() + 3) / 4)];
    WORD            *pData16;
    SHORT           byteWidth;

    WORD            sizeX, sizeY;
    WORD            x, y;

    // Get bitmap header
    ExternalMemoryCallback(bitmap, 0, sizeof(BITMAP_HEADER), &bmp);
    // Set offset to the image data
	memOffset = sizeof(BITMAP_HEADER) + 8;
    // Line width in bytes
    byteWidth = (bmp.width + 3)/4;    
    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;
    
   	DisplayEnable();				// enable S1D13522		
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_AREA );		// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( SRC_2BIT | g_HostMemAccessCfg );
	seDeviceWrite( left );
	seDeviceWrite( top );
	seDeviceWrite( sizeX );
	seDeviceWrite( sizeY );
	
	seWAIT_HRDY();
	DisplaySetCommand();		// set RS line to low for command
	seDeviceWrite( WR_REG );	// write command
	DisplaySetData();			// set RS line to high for data	
	seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );

    for(y = 0; y < sizeY; y++)
    {
        // Get line
        ExternalMemoryCallback(bitmap, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;
        pData16 = (WORD*)lineBuffer;
        
        for(x = 0; x < byteWidth/2; x++)
        {
        	seDeviceWrite( *pData16++ );
        }	        
    }	
	
	seWAIT_HRDY();	
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_END );	// write command

	DisplayDisable();				// disable S1D13522	

}

/*********************************************************************
* Function: void PutImage4BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage4BPPExt(SHORT left, SHORT top, void *bitmap, BYTE stretch)
{
    register DWORD  memOffset;
    BITMAP_HEADER   bmp;

    BYTE            lineBuffer[((GetMaxX() + 1) / 2)];
    WORD            *pData16;
    SHORT           byteWidth;

    WORD            sizeX, sizeY;
    WORD            x, y;

    // Get bitmap header
    ExternalMemoryCallback(bitmap, 0, sizeof(BITMAP_HEADER), &bmp);
    // Set offset to the image data
	memOffset = sizeof(BITMAP_HEADER) + 32;
    // Line width in bytes
    byteWidth = (bmp.width + 1)/2;    
    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;
    
    if ( g_ActiveLayer == GFX_CURSOR_LAYER )
    {	    
	   	DisplayEnable();				// enable S1D13522

		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_ADRCFG );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( 0 );		   	
	   			
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( WR_REG );		// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( REG03DE_CRS_MEM_LOAD );
	
	    for(y = 0; y < sizeY; y++)
	    {
	        // Get line
	        ExternalMemoryCallback(bitmap, memOffset, byteWidth, lineBuffer);
	        memOffset += byteWidth;
	        pData16 = (WORD*)lineBuffer;
	        
	        for(x = 0; x < byteWidth/2; x++)
	        {
	        	seDeviceWrite( *pData16++ );
	        }        
	    }
	    
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_ADRCFG );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( 0 );		   	
		    
		DisplayDisable();				// disable S1D13522	 
	} 
	else
	{
	   	DisplayEnable();				// enable S1D13522		
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_AREA );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( SRC_4BIT | g_HostMemAccessCfg );
		seDeviceWrite( left );
		seDeviceWrite( top );
		seDeviceWrite( sizeX );
		seDeviceWrite( sizeY );
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( WR_REG );		// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );
	
	    for(y = 0; y < sizeY; y++)
	    {
	        // Get line
	        ExternalMemoryCallback(bitmap, memOffset, byteWidth, lineBuffer);
	        memOffset += byteWidth;
	        pData16 = (WORD*)lineBuffer;
	        
	        for(x = 0; x < byteWidth/2; x++)
	        {
	        	seDeviceWrite( *pData16++ );
	        }	        
	    }	
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_END );	// write command
	
		DisplayDisable();				// disable S1D13522	
	}
}

/*********************************************************************
* Function: void PutImage8BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage8BPPExt(SHORT left, SHORT top, void *bitmap, BYTE stretch)
{
    if ( g_ActiveLayer == GFX_CURSOR_LAYER )
    	return;
    		
    register DWORD  memOffset;
    BITMAP_HEADER   bmp;

    BYTE            lineBuffer[GetMaxX()];
    WORD            *pData16;
    SHORT           byteWidth;

    WORD            sizeX, sizeY;
    WORD            x, y;

    // Get bitmap header
    ExternalMemoryCallback(bitmap, 0, sizeof(BITMAP_HEADER), &bmp);

    // Set offset to the image data
	memOffset = sizeof(BITMAP_HEADER) + 512;
    // Line width in bytes
    byteWidth = bmp.width;    

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;
    
   	DisplayEnable();				// enable S1D13522
   			
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_AREA );	// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( SRC_8BIT | g_HostMemAccessCfg );
	seDeviceWrite( left );
	seDeviceWrite( top );
	seDeviceWrite( sizeX );
	seDeviceWrite( sizeY );
	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( WR_REG );		// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );

    for(y = 0; y < sizeY; y++)
    {
        // Get line
        ExternalMemoryCallback(bitmap, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;
        pData16 = (WORD*)lineBuffer;
        
        for(x = 0; x < byteWidth / 2; x++)
        {
        	seDeviceWrite( *pData16++ );
        }	        
    }	
	
	seWAIT_HRDY();	
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( LD_IMG_END );		// write command
	
	DisplayDisable();				// disable S1D13522	
}
#endif

//---------------------------------------------------------------------------
//	GFX_DRIVER_CreateLayer()
//---------------------------------------------------------------------------
void GFX_DRIVER_CreateLayer( GFX_LAYER Layer, WORD Config, WORD XStart, WORD YStart, WORD Width, WORD Height )
{
	if ( Layer == GFX_PIP_LAYER )
	{
		g_PipLayerWidth  = Width;
		g_PipLayerHeight = Height;
		g_PipConfig      = 0x01C0&Config;
		g_PipConfig     |= (0x000F&Config)<<12;	
		g_PipConfig     |= 0x0020;
		
		DisplayEnable();				// enable S1D13522	
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( PIP_ENABLE );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( g_PipConfig );
		seDeviceWrite( Width );
		seDeviceWrite( Height );
		seDeviceWrite( 0 );
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( PIP_XYSETUP );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( XStart );
		seDeviceWrite( YStart );
	
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( PIP_DISABLE );	// write command
		
		DisplayDisable();				// disable S1D13522			
	}
	else if ( Layer == GFX_CURSOR_LAYER )		 
	{
		g_CursorLayerWidth  = Width;
		g_CursorLayerHeight = Height;
		g_CursorConfig      = 0x01C0&Config;		// Transparency enable, Cursor Pixel Output Value control
		g_CursorConfig     |= (0x000F&Config)<<12;	// Transparency value		
		g_CursorConfig     |= 0x0020;
		
		DisplayEnable();				// enable S1D13522
				
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_MAINCFG );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( g_CursorConfig );
		seDeviceWrite( Width );
		seDeviceWrite( Height );
		seDeviceWrite( 0 ); 			
		
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_XYSETUP );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( XStart );
		seDeviceWrite( XStart );		
	
		DisplayDisable();				// disable S1D13522			
	}	
	
}
	
//---------------------------------------------------------------------------
//	GFX_DRIVER_MoveLayer()
//---------------------------------------------------------------------------	
void GFX_DRIVER_MoveLayer( GFX_LAYER Layer, WORD X, WORD Y )
{
	if ( Layer == GFX_PIP_LAYER )
	{
		DisplayEnable();				// enable S1D13522		
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( PIP_XYSETUP );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( X );
		seDeviceWrite( Y );
	
		DisplayDisable();				// disable S1D13522	
	}
	else if ( Layer == GFX_CURSOR_LAYER )		 
	{
		DisplayEnable();				// enable S1D13522	
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_XYSETUP );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( X );
		seDeviceWrite( Y );
		
		DisplayDisable();				// disable S1D13522	
	}	
}
	
//---------------------------------------------------------------------------
//	GFX_DRIVER_ShowLayer()
//---------------------------------------------------------------------------	
void GFX_DRIVER_ShowLayer( GFX_LAYER Layer )
{
	if ( Layer == GFX_PIP_LAYER )
	{
		DisplayEnable();				// enable S1D13522	
			
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( PIP_ENABLE );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( g_PipConfig );
		seDeviceWrite( g_PipLayerWidth );
		seDeviceWrite( g_PipLayerHeight );
		seDeviceWrite( 0 );
	
		DisplayDisable();				// disable S1D13522	
	}
	else if ( Layer == GFX_CURSOR_LAYER )		 
	{
		DisplayEnable();				// enable S1D13522	
			
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_MAINCFG );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( g_CursorConfig | 1 );
		seDeviceWrite( g_CursorLayerWidth );
		seDeviceWrite( g_CursorLayerHeight );
		seDeviceWrite( 0 ); 
		
		DisplayDisable();				// disable S1D13522	
	}	
}
	
//---------------------------------------------------------------------------
//	GFX_DRIVER_HideLayer()
//---------------------------------------------------------------------------	
void GFX_DRIVER_HideLayer( GFX_LAYER Layer )
{
	if ( Layer == GFX_PIP_LAYER )
	{
		DisplayEnable();				// enable S1D13522		
		
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( PIP_DISABLE );	// write command
	
		DisplayDisable();				// disable S1D13522	
	}
	else if ( Layer == GFX_CURSOR_LAYER )		 
	{
		DisplayEnable();				// enable S1D13522
				
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_MAINCFG );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( g_CursorConfig ); 
		seDeviceWrite( g_CursorLayerWidth );
		seDeviceWrite( g_CursorLayerHeight );
		seDeviceWrite( 0 ); 
		
		DisplayDisable();				// disable S1D13522	
	}	
}
	
//---------------------------------------------------------------------------
//	GFX_DRIVER_ActivateLayer()
//---------------------------------------------------------------------------	
void GFX_DRIVER_ActivateLayer( GFX_LAYER Layer )
{
	if ( Layer == GFX_MAIN_LAYER )
	{
		g_ActiveLayer = GFX_MAIN_LAYER;
		g_HostMemAccessCfg &= ~WRITE_TO_PIP;
	}
	else if ( Layer == GFX_PIP_LAYER )
	{
		g_ActiveLayer = GFX_PIP_LAYER;
		g_HostMemAccessCfg |=  WRITE_TO_PIP;
	}
	else if ( Layer == GFX_CURSOR_LAYER )		 
	{
		g_ActiveLayer = GFX_CURSOR_LAYER;
	}	
}	

//---------------------------------------------------------------------------
//	GFX_DRIVER_RunSystem()
//---------------------------------------------------------------------------
void GFX_DRIVER_RunSystem( void )
{
	DisplayEnable();				// enable S1D13522		
	
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( RUN_SYS );		// write command

	DisplayDisable();				// disable S1D13522	
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_Standby()
//---------------------------------------------------------------------------
void GFX_DRIVER_Standby( void )
{
	DisplayEnable();				// enable S1D13522		
	seWAIT_HRDY();
	
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( STBY );			// write command

	DisplayDisable();				// disable S1D13522	
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_Sleep()
//---------------------------------------------------------------------------
void GFX_DRIVER_Sleep( void )
{
	DisplayEnable();				// enable S1D13522		
	seWAIT_HRDY();
	
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( SLP );				// write command

	DisplayDisable();				// disable S1D13522	
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_InitRotmode()
//---------------------------------------------------------------------------
void GFX_DRIVER_InitRotmode( WORD RotMode )
{
	DisplayEnable();				// enable S1D13522
			
	seWAIT_HRDY();
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( INIT_ROTMODE );	// write command
	DisplaySetData();				// set RS line to high for data	
	seDeviceWrite( RotMode );

	DisplayDisable();				// disable S1D13522	
}



//---------------------------------------------------------------------------
// GFX_DRIVER_LoadImage()
// If specified, image data is sent in pData (otherwise pData=NULL).
//---------------------------------------------------------------------------
void GFX_DRIVER_LoadImage( WORD HostOptions, WORD XStart, WORD YStart, WORD Width, WORD Height, const WORD* pData )
{
	if ( g_ActiveLayer == GFX_CURSOR_LAYER )
	{
		// not available for cursor layer
		//return;	
		
	    WORD sizeX, sizeY, StrideSize16;
	    WORD x, y;
    
	    // Get curent width and height size
	#if ( DISP_ORIENTATION == 0 || DISP_ORIENTATION == 180 )
	    sizeX = g_CursorLayerWidth;
	    sizeY = g_CursorLayerHeight;
	#else 
	    sizeY = g_CursorLayerWidth;
	    sizeX = g_CursorLayerHeight;	
	#endif
	
		if ((HostOptions & 0x0030) == 0x0030)		//input packed pixel = 1 byte-per-pixel (8 bpp)
			return; // no 8 bpp support for GFX_CURSOR_LAYER
		else if ((HostOptions & 0x0030) == 0x0020)	//packed pixel = 4 bpp
			StrideSize16 = sizeX%4 ? sizeX/4 + 1 : sizeX/4; 
		else if ((HostOptions & 0x0030) == 0x0010)	//packed pixel = 2 bpp
			StrideSize16 = sizeX%8 ? sizeX/8 + 1 : sizeX/8; 
		else if ((HostOptions & 0x0030) == 0x0000)	//packed pixel = 1 bpp
			StrideSize16 = sizeX%16 ? sizeX/16 + 1 : sizeX/16; 		
	    
	   	DisplayEnable();				// enable S1D13522
	   	
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_ADRCFG );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( 0 );	
			   		
		seWAIT_HRDY();
	
		DisplaySetCommand();		// set RS line to low for command
		seDeviceWrite( WR_REG );	// write command
	
		DisplaySetData();			// set RS line to high for data	
		seDeviceWrite( REG03DE_CRS_MEM_LOAD );
		
	    for(y = 0; y < sizeY; y++)
	    {
	        for(x = 0; x < StrideSize16; x++)
	        {
	        	seDeviceWrite( *pData++ );
	        }        
	    }						
	    
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( CSR_ADRCFG );	// write command
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( 0 );	
			    
		DisplayDisable();				// disable S1D13522		
	}
	else
	{
		DisplayEnable();				// enable S1D13522		
		seWAIT_HRDY();
		
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_AREA );	// write command
	
		DisplaySetData();				// set RS line to high for data	
		seDeviceWrite( HostOptions | g_HostMemAccessCfg );
		seDeviceWrite( XStart );
		seDeviceWrite( YStart );
		seDeviceWrite( Width );
		seDeviceWrite( Height );
	
		if ( pData )					//if no data specified, skip image load (data write)
		{
			//setup Count using specified area size
			DWORD Count = (DWORD)Width * (DWORD)Height;
	
			if ((HostOptions & 0x0030) == 0x0030)		//input packed pixel = 1 byte-per-pixel (8 bpp)
				Count = Count%2 ? 1+Count/2 : Count/2;	
			else if ((HostOptions & 0x0030) == 0x0020)	//packed pixel = 4 bpp
				Count = Count%4 ? 1+Count/4 : Count/4;
			else if ((HostOptions & 0x0030) == 0x0010)	//packed pixel = 2 bpp
				Count = Count%8 ? 1+Count/8 : Count/8;
			else if ((HostOptions & 0x0030) == 0x0000)	//packed pixel = 1 bpp
				Count = Count%16 ? 1+Count/16 : Count/16;
	
			seWAIT_HRDY();
			DisplaySetCommand();		// set RS line to low for command
			seDeviceWrite( WR_REG );	// write command
	
			DisplaySetData();			// set RS line to high for data	
			seDeviceWrite( REG0154_HOST_MEMORY_ACCESS_PORT );
	
			while( Count-- )
			{
				seDeviceWrite( *pData++ );
			}	
		}
	
		seWAIT_HRDY();
		DisplaySetCommand();			// set RS line to low for command
		seDeviceWrite( LD_IMG_END );	// write command
	
		DisplayDisable();				// disable S1D13522	
	}
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_UpdateEpd()
//---------------------------------------------------------------------------
void GFX_DRIVER_UpdateEpd( WORD UpdateOptions, WORD XStart, WORD YStart, WORD Width, WORD Height )
{
    WORD value;

    DisplayEnable();							// enable S1D13522
    DisplaySetCommand();						// set RS line to low for command
	seDeviceWrite(RD_REG);
	DisplaySetData();							// set RS line to high for data
	seDeviceWrite(REG0338_DISPLAY_BUSY_STATUS);	
	value = seDeviceRead();
	DisplayDisable();							// disable S1D13522	
	
	value &= 0x21;
	
	if ( UpdateOptions & GFX_UPDATE_AS_IT_DRAWS )
	{	
		if ( value != 0x20 )
			return;
			
		UpdateOptions |= GFX_UPDATE_NO_FLASH;
	}
	else
	{
		if ( value != 0x20 )
		{
			DisplayEnable();					// enable S1D13522
					
			seWAIT_HRDY();
			DisplaySetCommand();				// set RS line to low for command
			seDeviceWrite( WAIT_DSPE_LUTFREE );	// write command
			
			DisplayDisable();					// disable S1D13522				
		}		
	}			
	
	if ( UpdateOptions & GFX_UPDATE_NO_FLASH )
	{	
		DisplayEnable();						// enable S1D13522	
		
		seWAIT_HRDY();
		DisplaySetCommand();					// set RS line to low for command
		seDeviceWrite( UPD_PART_AREA );			// write command
		DisplaySetData();						// set RS line to high for data	
		seDeviceWrite( 0 );
		seDeviceWrite( XStart );
		seDeviceWrite( YStart );
		seDeviceWrite( Width );
		seDeviceWrite( Height );
		
		DisplayDisable();						// disable S1D13522			
	}	
	else if ( UpdateOptions & GFX_UPDATE_HIGH_QUALITY )
	{
		DisplayEnable();						// enable S1D13522		
		
		seWAIT_HRDY();
		DisplaySetCommand();					// set RS line to low for command
		seDeviceWrite( UPD_FULL_AREA );			// write command
		DisplaySetData();						// set RS line to high for data	
		seDeviceWrite( 0 );
		seDeviceWrite( XStart );
		seDeviceWrite( YStart );
		seDeviceWrite( Width );
		seDeviceWrite( Height );
	
		DisplayDisable();						// disable S1D13522			
	}
	
	if ( UpdateOptions & (GFX_WAIT_IMAGE_UPDATED | GFX_WAIT_IMAGE_DISPLAYED)  )
	{
		DisplayEnable();						// enable S1D13522		
		
		seWAIT_HRDY();	
		DisplaySetCommand();					// set RS line to low for command
		seDeviceWrite( WAIT_DSPE_TRG );			// write command
		
		DisplayDisable();
	}
	
	if ( UpdateOptions & GFX_WAIT_IMAGE_DISPLAYED )
	{	
		DisplayEnable();						// enable S1D13522	
		
		seWAIT_HRDY();
		DisplaySetCommand();					// set RS line to low for command
		seDeviceWrite( WAIT_DSPE_FREND );		// write command
		
		DisplayDisable();						// disable S1D13522		
	}
	
}	




//---------------------------------------------------------------------------
//** Update Related Functions for GOL Autoupdate enabled and special cases **
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Definitions and local functions
//---------------------------------------------------------------------------
#define DISPLAY_STATUS_TIRGGER_BUSY 	(1<< 0)
#define LUT_CONFLICT_DETECT				(1<< 7)
#define UPDATE_RECT_MODE_MASK			(3<<12)
enum { UPDATE_RECT_MODE_FULL, UPDATE_RECT_MODE_HOST, UPDATE_RECT_MODE_SPEC };

//---------------------------------------------------------------------------
// GFX_DRIVER_RdReg()
// Returns the register value.
//---------------------------------------------------------------------------
static WORD GFX_DRIVER_ReadRegister( WORD index ) 
{

    WORD value;
 
	index &= ~1;			// index must be 2 bytes aligned

    DisplayEnable();		// enable S1D13522

    DisplaySetCommand();	// set RS line to low for command
	seDeviceWrite(RD_REG);
	DisplaySetData();		// set RS line to high for data
	seDeviceWrite(index);	
	value = seDeviceRead();

	DisplayDisable();		// disable S1D13522

	return value;
}


//---------------------------------------------------------------------------
//	GFX_DRIVER_WrReg()
//---------------------------------------------------------------------------
static void GFX_DRIVER_WriteRegister(WORD index, WORD value)
{	
	if ( (index&1) == 0 )		// index must be 2 bytes aligned
	{	
		DisplayEnable();		// enable S1D13522
		
		seWAIT_HRDY();
		DisplaySetCommand();	// set RS line to low for command
		seDeviceWrite(WR_REG);
		DisplaySetData();		// set RS line to high for data
		seDeviceWrite(index);
		seDeviceWrite(value);

		DisplayDisable();		// disable S1D13522
	}
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_WaitDisplayEngineOperationComplete()
//---------------------------------------------------------------------------
static void GFX_DRIVER_WaitDisplayEngineOperationComplete( void )
{
	DisplayEnable();				// enable S1D13522		
	seWAIT_HRDY();
	
	DisplaySetCommand();			// set RS line to low for command
	seDeviceWrite( WAIT_DSPE_TRG );	// write command

	DisplayDisable();				// disable S1D13522	
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_WaitDisplayEngineMaskedLUTFree()
//---------------------------------------------------------------------------
static void GFX_DRIVER_WaitDisplayEngineMaskedLUTFree( WORD LutMask )
{
	DisplayEnable();					// enable S1D13522		
	seWAIT_HRDY();
	
	DisplaySetCommand();				// set RS line to low for command
	seDeviceWrite( WAIT_DSPE_MLUTFREE );	// write command

	DisplaySetData();					// set RS line to high for data	
	seDeviceWrite( LutMask );

	DisplayDisable();					// disable S1D13522	
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_IsDisplayEngineTriggerBusy()
//---------------------------------------------------------------------------
static WORD GFX_DRIVER_IsDisplayEngineTriggerBusy(void)
{
	DisplayEnable();				// enable S1D13522		
    seWAIT_HRDY();
    return GFX_DRIVER_ReadRegister(REG0338_DISPLAY_BUSY_STATUS) & DISPLAY_STATUS_TIRGGER_BUSY; 
}
//---------------------------------------------------------------------------
//	GFX_DRIVER_CollisionOccurred()
//---------------------------------------------------------------------------
static WORD GFX_DRIVER_CollisionOccurred(void)
{
	DisplayEnable();				// enable S1D13522		
    seWAIT_HRDY();
    return GFX_DRIVER_ReadRegister(REG033A_DISPLAY_INTERRUPT_RAW_STATUS) & LUT_CONFLICT_DETECT; 
}
//---------------------------------------------------------------------------
//	GFX_DRIVER_DisplayEngineGetAreaUpdate(startx, starty, endx, endy)
//---------------------------------------------------------------------------
static void GFX_DRIVER_DisplayEngineGetAreaUpdate(WORD *startx, WORD *starty, WORD *endx, WORD *endy)
{
    WORD updateMode;

	DisplayEnable();				// enable S1D13522		
    seWAIT_HRDY();
    updateMode = GFX_DRIVER_ReadRegister(REG0334_DISPLAY_CONTROL_TRIGGER) & UPDATE_RECT_MODE_MASK;

    switch(updateMode)
    {
    case UPDATE_RECT_MODE_FULL:
        *startx = 0;
        *starty = 0;
        *endx = GetMaxX();
        *endy = GetMaxY();
        break;

    case UPDATE_RECT_MODE_HOST:
        *startx = GFX_DRIVER_ReadRegister(REG0388_HOST_PXL_RECT_XSTART);
        *starty = GFX_DRIVER_ReadRegister(REG038A_HOST_PXL_RECT_YSTART);
        *endx = GFX_DRIVER_ReadRegister(REG038C_HOST_PXL_RECT_XEND);
        *endy = GFX_DRIVER_ReadRegister(REG038E_HOST_PXL_RECT_YEND);
        break;

    case UPDATE_RECT_MODE_SPEC:
        *startx = GFX_DRIVER_ReadRegister(REG0380_AREA_UPD_PXL_RECT_XSTART);
        *starty = GFX_DRIVER_ReadRegister(REG0382_AREA_UPD_PXL_RECT_YSTART);
        *endx = *startx + GFX_DRIVER_ReadRegister(REG0384_AREA_UPD_PXL_RECT_XEND);
        *endy = *starty + GFX_DRIVER_ReadRegister(REG0386_AREA_UPD_PXL_RECT_YEND);
        break;

    default:
        *startx = 0;
        *starty = 0;
        *endx = 0;
        *endy = 0;
        break;
    }
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_CheckXOverlap(startx, endx, startOverlapX, endOverlapX)
//---------------------------------------------------------------------------
static WORD GFX_DRIVER_CheckXOverlap(WORD startx, WORD endx, WORD startOverlapX, WORD endOverlapX)
{
    if((startx < startOverlapX) &&  (endx > startOverlapX))
        return 1;

    if((startx < endOverlapX) &&  (endx > endOverlapX))
        return 1;

    if((startx > startOverlapX) &&  (endx < endOverlapX))
        return 1;

    return 0;
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_CheckYOverlap(starty, endy, startOverlapY, endOverlapY)
//---------------------------------------------------------------------------
static WORD GFX_DRIVER_CheckYOverlap(WORD starty, WORD endy, WORD startOverlapY, WORD endOverlapY)
{
    if((starty < startOverlapY) &&  (endy > startOverlapY))
        return 1;

    if((starty < endOverlapY) &&  (endy > endOverlapY))
        return 1;

    if((starty > startOverlapY) &&  (endy < endOverlapY))
        return 1;

    return 0;
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_OverlapUpdateArea(startx, starty, endx, endy)
//---------------------------------------------------------------------------
static WORD GFX_DRIVER_OverlapUpdateArea(WORD startx, WORD starty, WORD endx, WORD endy)
{
    WORD updateAreaStartX;
    WORD updateAreaStartY;
    WORD updateAreaEndX;
    WORD updateAreaEndY;
    WORD overlap;

    if(GFX_DRIVER_IsDisplayEngineTriggerBusy() == 0)
        return 0;

    GFX_DRIVER_DisplayEngineGetAreaUpdate(  &updateAreaStartX,
                                            &updateAreaStartY,
                                            &updateAreaEndX,
                                            &updateAreaEndY);

    overlap = GFX_DRIVER_CheckXOverlap(startx, endx, updateAreaStartX, updateAreaEndX);
    overlap &= GFX_DRIVER_CheckXOverlap(starty, endy, updateAreaStartY, updateAreaEndY);

    return overlap;
}


//---------------------------------------------------------------------------
// **                            Public functions                          **
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	GFX_DRIVER_AutoDisable(void)
//---------------------------------------------------------------------------
void GFX_DRIVER_AutoUpdDisable(void)
{
	DefAutoUpd = 0;
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_AutoFull(void)
//---------------------------------------------------------------------------
void GFX_DRIVER_AutoUpdFull(void)
{
	DefAutoUpd = 1;
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_AutoPart(void)
//---------------------------------------------------------------------------
void GFX_DRIVER_AutoUpdPart(void)
{
	DefAutoUpd = 2;
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_CollisionCheckAndRepair(void)
//---------------------------------------------------------------------------
void GFX_DRIVER_CollisionCheckAndRepair(void)
{
    WORD updateAreaStartX;
    WORD updateAreaStartY;
    WORD updateAreaEndX;
    WORD updateAreaEndY;
    WORD lutStatus;


    if(GFX_DRIVER_IsDisplayEngineTriggerBusy())
        GFX_DRIVER_WaitDisplayEngineOperationComplete();


    while(GFX_DRIVER_CollisionOccurred())
    {
        GFX_DRIVER_WriteRegister(REG033C_DISPLAY_INTERRUPT_STATUS, LUT_CONFLICT_DETECT);

        lutStatus = GFX_DRIVER_ReadRegister(REG0336_LOOKUP_TABLE_STATUS);

        GFX_DRIVER_WaitDisplayEngineMaskedLUTFree(lutStatus);


        GFX_DRIVER_DisplayEngineGetAreaUpdate(  &updateAreaStartX,
                                                &updateAreaStartY,
                                                &updateAreaEndX,
                                                &updateAreaEndY);

		GFX_DRIVER_UpdateEpd(	GFX_UPDATE_NO_FLASH|GFX_WAIT_IMAGE_UPDATED,
                                updateAreaStartX,
                                updateAreaStartY,
                                updateAreaEndX - updateAreaStartX,
                                updateAreaEndY - updateAreaStartY);

		GFX_DRIVER_WaitDisplayEngineOperationComplete();
    }
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_SetupDrawUpdate(WORD startx, WORD starty, WORD endx, WORD endy)
//---------------------------------------------------------------------------
void GFX_DRIVER_SetupDrawUpdate(WORD startx, WORD starty, WORD endx, WORD endy)
{
    if(GFX_DRIVER_OverlapUpdateArea(startx, starty, endx, endy) == 0)
        return;

    GFX_DRIVER_WaitDisplayEngineOperationComplete();
}

//---------------------------------------------------------------------------
//	GFX_DRIVER_CompleteDrawUpdate(WORD startx, WORD starty, WORD endx, WORD endy)
//---------------------------------------------------------------------------
void GFX_DRIVER_CompleteDrawUpdate(WORD startx, WORD starty, WORD endx, WORD endy)
{
	GFX_DRIVER_CollisionCheckAndRepair();
	
	DisplayEnable();					// enable S1D13522
	seWAIT_HRDY();
	DisplaySetCommand();				// set RS line to low for command
	seDeviceWrite( WAIT_DSPE_LUTFREE );	// write command
	DisplayDisable();					// disable S1D13522	
			
	if (DefAutoUpd==1)		// Full Update
	{
		GFX_DRIVER_UpdateEpd(	GFX_UPDATE_HIGH_QUALITY,
                                startx,
                                starty,
                                endx - startx,
                                endy - starty);
	}
	else if (DefAutoUpd==2)	// Partial Update
	{
		GFX_DRIVER_UpdateEpd(	GFX_UPDATE_NO_FLASH,
                                startx,
                                starty,
                                endx - startx,
                                endy - starty);
	}
}
	
#endif //GFX_USE_DISPLAY_CONTROLLER_S1D13522
