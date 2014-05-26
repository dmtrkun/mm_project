/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#define VAL_CONV_PUB
#include "include.h"
#include <stdio.h>


void ValToStr(unsigned char type,unsigned long prmtr1, float prmtr2, void* ptr, char *val_str)
{
//int i;
	switch(type)
	{
		case TYPE_GEN:
			sprintf(val_str,"%d",(unsigned int)prmtr1);
			break;
		case TYPE_PASSWORD:
			if(prmtr1 > 0)
			{
				sprintf(val_str,"%d",(unsigned int)prmtr1);
//				for(i = strlen(val_str)-1;i >=0;i--)
//					val_str[i] = '*';
			}
			else
				*val_str = 0x00;
			break;
		case TYPE_RATE:
			if(prmtr2 < 100.0)
				sprintf(val_str,"%.1f%s",(double)prmtr2,unit[mlhr_UNIT]);
			else
				sprintf(val_str,"%.0f%s",(double)prmtr2,unit[mlhr_UNIT]);
			break;
		case TYPE_VOLUME:
			if(prmtr2 < 100.0)
				sprintf(val_str,"%.1f%s",(double)prmtr2,unit[ml_UNIT]);
			else
				sprintf(val_str,"%.0f%s",(double)prmtr2,unit[ml_UNIT]);
			break;
		case TYPE_PRESSURE:
				sprintf(val_str,"%d%s",(int)prmtr1,unit[mmHg_UNIT]);
			break;
		case TYPE_AIL_LIMIT:
				sprintf(val_str,"%d%s",(unsigned int)prmtr1,unit[ul_UNIT]);
			break;
		case TYPE_DATE:
//			strftime(val_str, 100, "%d.%m.%y", &rtc_time);
			strftime(val_str, 100, "%d.%m.%y", localtime((time_t*)&prmtr1));
			break;
		case TYPE_TIME:
 //			strftime(val_str, 100, "%H:%M:%S", &rtc_time);
			strftime(val_str, 100, "%H:%M:%S", localtime((time_t*)&prmtr1));
			break;
		case TYPE_TIMEINTERVAL:
 //			strftime(val_str, 100, "%H:%M:%S", &rtc_time);
			strftime(val_str, 100, "%H:%M", localtime((time_t*)&prmtr1));
			break;
		default:
			sprintf(val_str, "-");
			break;
	}
}


