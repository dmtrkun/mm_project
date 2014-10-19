 
#ifndef _BOARD_H
#define _BOARD_H

#ifdef BOARD_PUB
#define BOARDPUB
#else
#define BOARDPUB extern
#endif



//#include "Compiler.h"
#include <xc.h>
#include <GenericTypeDefs.h>
#include "HardwareProfile.h"

/**************************************************************/
#define CS_MUX(num,set)		cs_mux(num, set)

#define  	CS2_PORTEX    4		 
#define  	CS3_TSC		    2		 
#define  	CS4_RTC		    6		 
#define  	CS5_EEPROM    1		 
#define  	CS6_DAC		    5		 
//#define CS_MUX(num,set)		(PORTA = (PORTA & 0xF8)|(set == 0 ? 0:(num & 0x07)))		
//#define CS_MUX(num,set)		_delay_spi(2);PORTA &=0xF8; PORTA |= (set == 0 ? 0:(num & 0x07));_delay_spi(2);
//#define CS_MUX(num,set)		cs_mux(num, set)

void cs_mux(unsigned char num, unsigned char set);
BOARDPUB void Spi_init(void);
BOARDPUB void _delay_spi(unsigned char time);


#endif //_BOARD_H
