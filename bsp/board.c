#define BOARD_PUB

#include <spi.h>
#include "include.h"
void SelectSPIdevice(unsigned char num);


/* */
void _delay_spi(unsigned char time)
{
    unsigned short  delay;
    while(time--)
        for(delay = 0; delay < 5; delay++);
}
void cs_mux(unsigned char num, unsigned char set)
{
	 if(set == 1)	//set chipselect
	 {
		 SelectSPIdevice(num);
		 EnterCriticalSPI();
		 LATA &=0xF8; 
		 LATA |= (num & 0x07);
	 	 _delay_spi(2);
	 
	 }
	 else
	 {
	 	 _delay_spi(2);
		 LATA &=0xF8; 
	 	 ExitCriticalSPI();
	 }
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






/*
config1 - This contains the parameters to be configured in the SPIxCON1 register as defined below:
SCK Pin Control bit  -   DISABLE_SCK_PIN,   ENABLE_SCK_PIN

SDO Pin Control bit -    DISABLE_SDO_PIN,   ENABLE_SDO_PIN

Word/Byte Communication mode -    SPI_MODE16_ON,   SPI_MODE16_OFF

SPI Data Input Sample phase -    SPI_SMP_ON,   SPI_SMP_OFF

SPI Clock Edge Select -    SPI_CKE_ON,   SPI_CKE_OFF

SPI slave select enable -    SLAVE_SELECT_ENABLE_ON,   SLAVE_SELECT_ENABLE_OFF

SPI Clock polarity select -    CLK_POL_ACTIVE_LOW,   CLK_POL_ACTIVE_HIGH

SPI Mode Select bit -    MASTER_ENABLE_ON,   MASTER_ENABLE_OFF

Secondary Prescale select
   SEC_PRESCAL_1_1
   SEC_PRESCAL_2_1
   SEC_PRESCAL_3_1
   SEC_PRESCAL_4_1
   SEC_PRESCAL_5_1
   SEC_PRESCAL_6_1
   SEC_PRESCAL_7_1
   SEC_PRESCAL_8_1

Primary Prescale select
   PRI_PRESCAL_1_1
   PRI_PRESCAL_4_1
   PRI_PRESCAL_16_1
   PRI_PRESCAL_64_1

config2 - This contains the parameters to be configured in the
SPIxCON2 register as defined below:
Framed SPI support Enable/Disable -     FRAME_ENABLE_ON,    FRAME_ENABLE_OFF

Frame Sync Pulse direction control -     FRAME_SYNC_INPUT,    FRAME_SYNC_OUTPUT

Frame Sync Pulse Polarity control -     FRAME_SYNC_ACTIVE_HIGH,    FRAME_SYNC_ACTIVE_LOW

Frame Sync Pulse Edge select -     SPI_FRM_PULSE_FIRST_CLK,    SPI_FRM_PULSE_PREV_CLK

Enhanced Buffer Mode Bit -     SPI_ENH_BUFF_ENABLE,    SPI_ENH_BUFF_DISABLE

Config3 - This contains the parameters to be configured in the SPIxSTAT register as defined below:
SPI Enable/Disable -    SPI_ENABLE,   SPI_DISABLE

SPI Idle mode operation -    SPI_IDLE_CON,   SPI_IDLE_STOP

Clear Receive Overflow Flag bit -    SPI_RX_OVFLOW_CLR
*/






/************************************************************************
************************************************************************/
void Spi_init(void)
{
  unsigned int SPICON1Value;
  unsigned int SPICON2Value;
  unsigned int SPISTATValue;
	
/* Turn off SPI module */
	CloseSPI1();

	__builtin_write_OSCCONL(OSCCON & 0xbf);
	RPINR20bits.SDI1R = 0; //RP0
	RPOR0bits.RP1R = 7; //RP1    SDO1
	RPOR1bits.RP2R = 8; //RP2    SCK1OUT
	__builtin_write_OSCCONL(OSCCON | 0x40);	
	
	TRISA &= 0xFFF8; //Set as output
//	PORTA &= 0xFFF8; //Set to 0
	LATA &= 0xFFF8; //Set to 0
	ANSB &= 0xFFFC;
//	TRISD &=0xFEFF;	
//	TRISB &=0xFFFD;	
//	TRISB |= 0x0001;

//	CNPU1bits.CN3PUE = 1;	



#if 0
/* Configure SPI1 interrupt */
   ConfigIntSPI1(SPI_INT_EN | SPI_INT_PRI_6);
#endif	
/* Configure SPI1 module to 8 bit master mode */
   SPICON1Value = ENABLE_SCK_PIN & ENABLE_SDO_PIN & SPI_MODE16_OFF &
   SPI_SMP_ON & SPI_CKE_OFF &
   SLAVE_ENABLE_OFF &
   CLK_POL_ACTIVE_HIGH &
   MASTER_ENABLE_ON &
   SEC_PRESCAL_7_1 &
   PRI_PRESCAL_64_1;

   SPICON1Value = ENABLE_SCK_PIN & ENABLE_SDO_PIN & SPI_MODE16_OFF &
//   SPI_SMP_ON & 
   SPI_SMP_OFF & 
   SPI_CKE_ON & CLK_POL_ACTIVE_HIGH &  /*Mode 1.1*/
   SLAVE_ENABLE_OFF &
   MASTER_ENABLE_ON &
   SEC_PRESCAL_2_1 &
   PRI_PRESCAL_1_1;


#if 0  //touch screen init
   SPICON1Value = ENABLE_SCK_PIN & ENABLE_SDO_PIN & SPI_MODE16_OFF &
   SPI_SMP_OFF & 
   SPI_CKE_OFF & CLK_POL_ACTIVE_HIGH &  /*Mode 1.1*/
   SLAVE_ENABLE_OFF &
   MASTER_ENABLE_ON &
   SEC_PRESCAL_2_1 &
   PRI_PRESCAL_4_1;
#endif






//   SPICON2Value = FRAME_ENABLE_OFF;
   SPICON2Value = 0x0000;

   SPISTATValue = SPI_ENABLE & SPI_IDLE_CON &
   SPI_RX_OVFLOW_CLR;

   OpenSPI1(SPICON1Value,SPICON2Value,SPISTATValue );

//	CS_MUX(CS2_PORTEX,1);
//	CS_MUX(CS2_PORTEX,0);

}
void SelectSPIdevice(unsigned char num)
{
unsigned int SPICON1Value;
unsigned int SPICON2Value;
unsigned int SPISTATValue;
	
	CloseSPI1();
	if ( num == CS4_RTC)
	{
		//  maximum clock 900 Khz
	   	SPICON1Value = ENABLE_SCK_PIN & ENABLE_SDO_PIN & SPI_MODE16_OFF &
   		SPI_SMP_OFF & 
   		SPI_CKE_OFF & CLK_POL_ACTIVE_HIGH &  /*Mode 1.0*/
   		SLAVE_ENABLE_OFF &
   		MASTER_ENABLE_ON &
   		SEC_PRESCAL_2_1 &
   		PRI_PRESCAL_1_1;
	}	 
	else if ( num == CS3_TSC)
	{
		//  maximum clock 900 Khz
	   	SPICON1Value = ENABLE_SCK_PIN & ENABLE_SDO_PIN & SPI_MODE16_OFF &
   		SPI_SMP_OFF & 
   		SPI_CKE_OFF & CLK_POL_ACTIVE_HIGH &  /*Mode 1.0*/
   		SLAVE_ENABLE_OFF &
   		MASTER_ENABLE_ON &
   		SEC_PRESCAL_2_1 &
   		PRI_PRESCAL_4_1;
	}	 
	else
	{
	   	//  clock 8Mhz
		SPICON1Value = ENABLE_SCK_PIN & ENABLE_SDO_PIN & SPI_MODE16_OFF &
   		SPI_SMP_OFF & 
   		SPI_CKE_ON & CLK_POL_ACTIVE_HIGH &  /*Mode 1.1*/
   		SLAVE_ENABLE_OFF &
   		MASTER_ENABLE_ON &
   		SEC_PRESCAL_2_1 &
   		PRI_PRESCAL_1_1;
	}
//	ifRTC
//  maximum clock 6Mhz

   SPICON2Value = 0x0000;

   SPISTATValue = SPI_ENABLE & SPI_IDLE_CON &
   SPI_RX_OVFLOW_CLR;

   OpenSPI1(SPICON1Value,SPICON2Value,SPISTATValue );
	   
}


