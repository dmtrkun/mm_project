 
#ifndef _MCP4822_H
#define _MCP4822_H


#ifdef MCP4822_PUB
#define MCP4822PUB
#else
#define MCP4822PUB extern
#endif


//#include "Compiler.h"
#include <xc.h>
#include <GenericTypeDefs.h>
#include "HardwareProfile.h"

MCP4822PUB void MCP4822Write(unsigned char dac, unsigned int val , unsigned char gain);

#endif //_MCP4822_H
