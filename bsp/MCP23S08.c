#define MCP23S08_PUB

#include "include.h"
#include <spi.h>
#include "MCP23S08.h"


#if 0
void Get_Device_8bit(void);
void Write23X08_17(unsigned char reg, unsigned char data);
unsigned char Read23X08_17(unsigned char reg);
void SetSSP(unsigned char mode);
void SPIWriteByte(unsigned char reg, unsigned char data);
unsigned char SPIReadByte(unsigned char reg);
void Delay_ms(long num_ms);

unsigned char	gAddrPins;               



/*****************************************************************
     Function Name:    Get_Device_8bit                             
     Return Value:                                             
     Parameters:       
     Description:      This function returns the address for the 
                       appropriate 8 bit device to be written to 
                       or read from                   
*******************************************************************/
void Get_Device_8bit(void)
{
    gAddrPins = MCP23S08;
}
  

/******************************************************************
   Function Name:  Write23X08_17                                         
   Return Value:                                              
   Parameters:     Register address, Data                    
   Description:    Writes to a 23X08_17 register. I2C or SPI is in
                   global byte     
******************************************************************/
void Write23X08_17(unsigned char reg, unsigned char data)
{
	  SPIWriteByte(reg, data); 
}

/*****************************************************************
   Function Name:  Read23X08_17                                         
   Return Value:                                              
   Parameters:     Register address                    
   Description:    Reads a 23X08_17 register. I2C or SPI is in
                   global byte     
******************************************************************/
unsigned char Read23X08_17(unsigned char reg)
{
  unsigned char num;
	num = SPIReadByte(reg);
	return(num);
}

/*****************************************************************
	SetSSP(mode)
******************************************************************/
void SetSSP(void)
{  
	SSPCON1bits.SSPEN = 0;				      // disable other peripheral


  // Setup SPI
    // Sets up the indicator LED's and puts opposite devices in reset
  	PORTAbits.RA4 = 0;     // SPI LED's ON
	  PORTDbits.RD4 = 1;	   // I2C LED's OFF			
  	PORTDbits.RD5 = 0;     // Hold I2C devices in reset
  	PORTCbits.RC0 = 1;     // SPI devices active
  	
//    if(SPIClkMode == Mode11)        //Mode 11
//  		OpenSPI( SPI_FOSC_4, MODE_11, SMPMID);
//    else if (SPIClkMode == Mode00)  //Mode 00
  		OpenSPI( SPI_FOSC_4, MODE_00, SMPMID );

		TRISBbits.TRISB3 = 0;		// CS
		TRISCbits.TRISC7 = 0;		// SDO
		TRISBbits.TRISB0 = 1;		// SDI
		TRISBbits.TRISB1 = 0;		// SCK
	  CS_MUX(CS2_PORTEX,0);  // Disable SPI Communication to  MCP23S08
}

#endif

/*****************************************************************
     Function Name:    SPIWriteByte                                
     Return Value:                                             
     Parameters:       register address, and data.               
     Description:      This routine performs a byte write.         
*******************************************************************/
void MCP23S08Write(unsigned char reg, unsigned char data )
{
 
  CS_MUX(CS2_PORTEX,1);// Enable SPI Communication to  MCP23S08
  while(SPI1STATbits.SPITBF);
  WriteSPI1(gControlByte | WrtCmd | gAddrPins);
  while(!SPI1STATbits.SPIRBF);
  ReadSPI1();
  
  while(SPI1STATbits.SPITBF);
  WriteSPI1(reg);
  while(!SPI1STATbits.SPIRBF);
  ReadSPI1();
  
  while(SPI1STATbits.SPITBF);
  WriteSPI1(data);
  while(!SPI1STATbits.SPIRBF);
  ReadSPI1();
  
  CS_MUX(CS2_PORTEX,0);  // Disable SPI Communication to  MCP23S08
}

/*****************************************************************
     Function Name:    SPIReadByte                                
     Return Value:     Data at register                                        
     Parameters:       Register
     Description:      This routine performs a sequential write.         
*******************************************************************/
unsigned char MCP23S08Read(unsigned char reg)
{
  unsigned char n;
//  while(SPI1STATbits.SPIRBF)
//  	n = ReadSPI1();
  
  CS_MUX(CS2_PORTEX,1);// Enable SPI Communication to  MCP23S08
  while(SPI1STATbits.SPITBF);
  WriteSPI1(gControlByte | RdCmd | gAddrPins);
  while(!SPI1STATbits.SPIRBF);
  ReadSPI1();

  while(SPI1STATbits.SPITBF);
  WriteSPI1(reg);
  while(!SPI1STATbits.SPIRBF);
  ReadSPI1();

  while(SPI1STATbits.SPITBF);
  WriteSPI1(0);
  while(!SPI1STATbits.SPIRBF);
  n = ReadSPI1();
//  WriteSPI1(0);
//  while(SPI1STATbits.SPITBF);
//  WriteSPI1(0);
//  while(SPI1STATbits.SPITBF);
  CS_MUX(CS2_PORTEX,0);  // Disable SPI Communication to  MCP23S08
  
  return n;
}

#if 0
void E2P_Io(	uchar *out_buf /* source buffer */,
					uchar *in_buf /* destination buffer */,
					int len /* buffer size in bytes */)
{
uchar	data;

 	if(SSP1STATbits.BF)
		data = SSP1BUF & 0xff;
//?  	SSP1STATbits.SPIROV = 0;
	while(len--)
	{
		if(out_buf != 0)
			SSP1BUF = (*out_buf)&0xff;
		else
			SSP1BUF = 0x00;//			WriteSPI2(0xFF);
		out_buf++;
 		while(!SSP1STATbits.BF);
 		data = SSP1BUF & 0xff;
//?	  SPI2STATbits.SPIROV = 0;
		if(in_buf != 0)
		{
			*in_buf = data;
			in_buf ++;
		}
 	}
}
#endif


unsigned char reg1,reg2,reg3,reg4,reg5;	
void MCP23S08Init(void)
{
	MCP23S08Write(GPPU, 0x40 ); 
	_delay_spi(100);
	MCP23S08Write(GPIO, 0x08 ); //Set Back light ON, power ON(logic zero)
	_delay_spi(100);
	MCP23S08Write(IOCON, 0x04 ); //Set IRQ open Drain
	_delay_spi(100);
	MCP23S08Write(IODIR, 0x47 ); // Directions Out In Out Out Out In In In

}
/************************************************************************
*                                                                       
************************************************************************/
BYTE MCP23S08WriteWord(WORD data, DWORD address)
{

    return (0); // failed
}

/************************************************************************
*                                                                       
************************************************************************/
WORD MCP23S08ReadWord(DWORD address)
{
WORD temp= 0;

    return (temp);
}

/************************************************************************
*                                                                       
************************************************************************/
BYTE MCP23S08WriteArray(DWORD address, BYTE *pData, WORD nCount)
{
    return (1);
}

/************************************************************************
*                                                                       
************************************************************************/
void MCP23S08ReadArray(DWORD address, BYTE *pData, WORD nCount)
{

}

/************************************************************************
*                                                                       
************************************************************************/
void MCP23S08WaitProgram(void)
{
}

/************************************************************************
*
************************************************************************/
void MCP23S08ChipErase(void)
{
}

/************************************************************************
* Function: void MCP23S08SectorErase(DWORD address)                                 
*
* Overview: This function erases 2K Word section defined by address
*
* Input: address - The address location of the sector to be erased.
*				   The address is decided by Address[17:11] address lines.
*            
* Output: none
*
************************************************************************/
void MCP23S08SectorErase(DWORD address)
{
}

/************************************************************************
*
************************************************************************/
WORD MCP23S08CheckID()
{
		return 0;   		
}




