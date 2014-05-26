/*PCF2123 SPI driver*/
#define PCF2123_PUB


#include	<spi.h>
#include 	"include.h"

/* instruction set */
#define RTCREAD		0x90	//Read data 
#define RTCWRITE	0x10	//Write data 

#define RtcCS(x)		{_delay_us(10); RTC_CS_PIN = 0x01&(x); _delay_us(10);}

static unsigned char iob[10]; /* command transfer buffer */
unsigned char MonDays(unsigned char mon, unsigned int year);


void RTC_Io(	unsigned char *out_buf /* source buffer */,
					unsigned char *in_buf /* destination buffer */,
					int len /* buffer size in bytes */)
{
unsigned char	data;

 	if(SPI1STATbits.SPIRBF)
		data = SPI1BUF & 0xff;
  	SPI1STATbits.SPIROV = 0;
	while(len--)
	{
//  		while(SPI1STATbits.SPITBF);
//  		WriteSPI1(gControlByte | WrtCmd | gAddrPins);
//  		while(!SPI1STATbits.SPIRBF);
//  		ReadSPI1();
		
		
		
		
		
		if(out_buf != 0)
			SPI1BUF = (*out_buf)&0xff;
		else
			SPI1BUF = 0x00;//			WriteSPI1(0xFF);
		out_buf++;
 		while(!SPI1STATbits.SPIRBF);
 		data = SPI1BUF & 0xff;
	  SPI1STATbits.SPIROV = 0;
		if(in_buf != 0)
		{
			*in_buf = data;
			in_buf ++;
		}
 	}
}

unsigned char get_time_rtc(struct tm *time)
{
	unsigned char stat = FALSE;
//	GLOB_CRITSECT_START;
//	RtcCS(1);
  CS_MUX(CS4_RTC,1);

	iob[0] = RTCREAD|0x02; /* read instruction  */
	RTC_Io( iob, 0, 1); /* write cmd */
	RTC_Io(0, iob, 7); /* read time */
//	RtcCS(0);
  CS_MUX(CS4_RTC,0);
	if((iob[0] & 0x80) == 0)  /*Test if oscillator has stopped or been interrupted */
		stat = TRUE;
#if 0	
	time->sec = ((iob[0]&0x70) >> 4)*10 + (iob[0]&0x0F);
	time->min = ((iob[1]&0x70) >> 4)*10 + (iob[1]&0x0F);
 	time->hour = ((iob[2]&0x30) >> 4)*10 + (iob[2]&0x0F);
	time->day = ((iob[3]&0x30) >> 4)*10 + (iob[3]&0x0F);
	time->wday = iob[4]&0x07;
	time->month = ((iob[5]&0x10) >> 4)*10 + (iob[5]&0x0F);
	time->year = ((iob[6]&0x10) >> 4)*10 + (iob[6]&0x0F) + 2000;
#else	
	time->tm_sec = ((iob[0]&0x70) >> 4)*10 + (iob[0]&0x0F);
	time->tm_min = ((iob[1]&0x70) >> 4)*10 + (iob[1]&0x0F);
 	time->tm_hour = ((iob[2]&0x30) >> 4)*10 + (iob[2]&0x0F);
	time->tm_mday = ((iob[3]&0x30) >> 4)*10 + (iob[3]&0x0F);
	time->tm_wday = iob[4]&0x07;
	time->tm_mon = ((iob[5]&0x10) >> 4)*10 + (iob[5]&0x0F) - 1;
	time->tm_year = ((iob[6]&0xF0) >> 4)*10 + (iob[6]&0x0F) + 100;
#endif	
	
	return stat;
//	GLOB_CRITSECT_STOP;
}


unsigned char set_time_rtc(struct tm *time)
{
	unsigned char stat = FALSE;
//	GLOB_CRITSECT_START;
	
	iob[0] = RTCWRITE|0x02; /* write instruction  */
#if 1	
	iob[1] = (0x7f&(time->tm_sec/10)<<4) | (time->tm_sec%10);
	iob[2] = (time->tm_min/10)<<4 | (time->tm_min%10);
	iob[3] = (time->tm_hour/10)<<4 | (time->tm_hour%10);
	iob[4] = (time->tm_mday/10)<<4 | (time->tm_mday%10);
	iob[5] = time->tm_wday;
	iob[6] = ((time->tm_mon+1)/10)<<4 | ((time->tm_mon+1)%10);
	iob[7] = ((time->tm_year - 100)/10)<<4 | ((time->tm_year - 100)%10);
#else
	iob[1] = (time->sec/10)<<4 | (time->sec%10);
	iob[2] = (time->min/10)<<4 | (time->min%10);
	iob[3] = (time->hour/10)<<4 | (time->hour%10);
	iob[4] = (time->day/10)<<4 | (time->day%10);
	iob[5] = time->wday;
	iob[6] = (time->month/10)<<4 | (time->month%10);
	iob[7] = ((time->year-2000)/10)<<4 | ((time->year-2000)%10);
#endif
  CS_MUX(CS4_RTC,1);
//	RtcCS(1);
	RTC_Io( iob, 0, 8); /* write cmd and data */
  CS_MUX(CS4_RTC,0);
//	RtcCS(0);
#if 0	
  CS_MUX(CS4_RTC,1);
//	RtcCS(1);
	iob[0] = RTCREAD|0x02; /* read instruction  */
	RTC_Io( iob, 0, 1); /* write cmd */
	RTC_Io(0, iob, 1); /* read osc status */
  CS_MUX(CS4_RTC,0);
//	RtcCS(0);
	
	if((iob[0] & 0x80) == 0)  /*Test if oscillator has stopped or been interrupted */
		stat = TRUE;
#endif	
	return stat;
//	GLOB_CRITSECT_STOP;
}
void init_time_rtc(struct tm *time)
{
	time->tm_sec = 0;
	time->tm_min = 0;
	time->tm_hour = 0;
	time->tm_mday = 1;
	time->tm_wday = 0;
	time->tm_mon = 0;
	time->tm_year = 100;
	time->tm_yday = 0;
	time->tm_isdst = 0;

}

void reset_rtc(void)
{
//	GLOB_CRITSECT_START;
	iob[0] = RTCWRITE|0x00; /* write instruction  */
	iob[1] = 0x58; /* Reset RTC*/ 
  CS_MUX(CS4_RTC,1);
	RTC_Io( iob, 0, 2); /* write cmd */
  CS_MUX(CS4_RTC,0);
//	GLOB_CRITSECT_STOP;
}

unsigned char clear_os_rtc(void)
{
//	GLOB_CRITSECT_START;
	iob[0] = RTCWRITE|0x02; /* write instruction  */
	iob[1] = 0; /* Clear OS flag*/ 
  CS_MUX(CS4_RTC,1);
//	RtcCS(1);
	RTC_Io( iob, 0, 2); /* write cmd */
  CS_MUX(CS4_RTC,0);
	_delay_spi(50);
	CS_MUX(CS4_RTC,1);
	iob[0] = RTCREAD|0x02; /* read instruction  */
	RTC_Io( iob, 0, 1); /* write cmd */
	RTC_Io(0, iob, 1); /* read osc status */
  CS_MUX(CS4_RTC,0);
	
	if((iob[0] & 0x80) == 0)  /*Test if oscillator has stopped or been interrupted */
		return TRUE;
	return FALSE;
//	GLOB_CRITSECT_STOP;
}

unsigned int get_days(DATE_t *para)
{
	unsigned int days = 0;
	DATE_t date;
	TIME_t time;

	date.day = para->day;
	date.month = para->month;
	date.year = para->year;
	get_time_rtc(&time);
	
	if(time.month == date.month && time.year == date.year)
	{
		days = time.day - date.day;
	}
	else
	{
		days = MonDays(date.month, date.year) - date.day; 
		date.month++;		
		while(date.year <= time.year)
		{
			for(/*date.month++*/ ;date.month <= 12;date.month++)
			{
					if(time.month == date.month && time.year == date.year)
					{
						days += time.day;
						return days;
					}
					days += MonDays(date.month, date.year);
			}
			date.year++;
			date.month = 1;
		}
	}
	return days;
}

/*
 * Returns the number of days in the month
 */
unsigned char MonDays(unsigned char mon, unsigned int year)
{
  if(mon == 2 && (year % 4) == 0)  /* leap year - up to 2099 */
    return 29;
  else
    return RTC_days[mon];
}
