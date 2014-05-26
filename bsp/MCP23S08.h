 
#ifndef _MCP23S08_H
#define _MCP23S08_H


#ifdef MCP23S08_PUB
#define MCP23S08PUB
#else
#define MCP23S08PUB extern
#endif



#include "Compiler.h"
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"

/**************************************************************/
#define IODIR   	0x00
#define IPOL   	  0x01
#define GPINTEN   0x02
#define DEFVAL    0x03
#define INTCON 		0x04
#define IOCON		  0x05
#define GPPU  		0x06
#define INTF 		  0x07
#define INTCAP 		0x08
#define GPIO  		0x09
#define OLAT   		0x0A

#define gControlByte 0x40
#define gAddrPins 0x00
#define WrtCmd  0
#define RdCmd   1








MCP23S08PUB void MCP23S08Init();
MCP23S08PUB unsigned char MCP23S08Read(unsigned char reg);
MCP23S08PUB void MCP23S08Write(unsigned char reg, unsigned char data );

MCP23S08PUB BYTE MCP23S08WriteWord(WORD data, DWORD address);
MCP23S08PUB WORD MCP23S08ReadWord(DWORD address);
MCP23S08PUB BYTE MCP23S08WriteArray(DWORD address, BYTE *pData, WORD nCount);
MCP23S08PUB void MCP23S08ReadArray(DWORD address, BYTE *pData, WORD nCount);
MCP23S08PUB void MCP23S08WaitProgram(void);
MCP23S08PUB void MCP23S08ChipErase(void);
MCP23S08PUB void MCP23S08SectorErase(DWORD address);
MCP23S08PUB WORD MCP23S08CheckID();

#endif //_MCP23S08_H
