#ifndef pcf2123_h
#define pcf2123_h

#ifdef PCF2123_PUB
#define PCF2123PUB
#else
#define PCF2123PUB	extern
#endif

typedef struct
{
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char day;
	unsigned char wday;
	unsigned char month;
	unsigned int	year;
} TIME_t;

typedef struct
{
	unsigned char day;
	unsigned char month;
	unsigned int	year;
} DATE_t;


#ifdef PCF2123_PUB
const unsigned char RTC_days[] = { /* zero month is a stub */
  0,31,28,31,30,31,30,31,31,30,31,30,31
};
#else
extern const unsigned char RTC_days[];
#endif

//PCF2123PUB int rtc_write(unsigned int addr,	void *buf, unsigned int len);
PCF2123PUB unsigned char get_time_rtc(struct tm *time);
PCF2123PUB unsigned char set_time_rtc(struct tm *time);
PCF2123PUB unsigned char clear_os_rtc(void);
PCF2123PUB void reset_rtc(void);
PCF2123PUB void init_time_rtc(struct tm *time);


PCF2123PUB struct tm rtc_time;
#endif /*pcf2123_h*/

