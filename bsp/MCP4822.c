#define MCP4822_PUB

#include "include.h"
#include <spi.h>
#include "MCP4822.h"


/*****************************************************************
     Function Name:    MCP4822Write                                
     Return Value:                                             
     Parameters:       register address, and data.               
     Description:      This routine performs a byte write.         
*******************************************************************/
void MCP4822Write(unsigned char dac, unsigned int val , unsigned char gain)
{
  unsigned char first_byte;
  unsigned char second_byte;
  
	first_byte = ((dac&0x01)<<7) | ((gain&0x01)<<6) | 0x10 | (unsigned char)((val & 0x0f00)>>8);
	second_byte = (unsigned char)(val & 0x00ff);

	CS_MUX(CS6_DAC,1);// Enable SPI Communication to  MCP4822
  while(SPI1STATbits.SPITBF);
  WriteSPI1(first_byte);
  while(!SPI1STATbits.SPIRBF);
  ReadSPI1();
  
  while(SPI1STATbits.SPITBF);
  WriteSPI1(second_byte);
  while(!SPI1STATbits.SPIRBF);
  ReadSPI1();
  
  CS_MUX(CS6_DAC,0);  // Disable SPI Communication to  MCP23S08
}

