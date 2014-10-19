/*****************************************************************************
 *****************************************************************************/
#define TASK_BCKGRND_PUB
#include "include.h"

//unsigned char tempor_byte1, tempor_byte2;

/*********************************************************************
 * Function:        void taskBackground(void* pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           void* pvParameter, any parameter from the creator
 *                  
 * Output:          Does not return
 *
 * Side Effects:    None
 *
 * Overview:        Background handling task
 *
 * Note:            
 ********************************************************************/

void taskBackground(void* pvParameter)
{
static unsigned int val1;
static unsigned int val2;
time_t time_sec;

//	vTaskSetApplicationTaskTag( NULL, ( void * ) 'b' );	
alarm_st = 0;
#ifndef SIM_DEBUG
//sysinit
	wdi_ena = 0;
	Spi_init();
	if(get_time_rtc(&rtc_time)== FALSE)
	{
//TBD		SetError(RTC_ERR, HARWARE_ALRM_SCR);
		reset_rtc();
		while(clear_os_rtc() == FALSE);
		init_time_rtc(&rtc_time);
		
//		rtc_time.tm_sec = 0;
 //		rtc_time.tm_min = 0;
// 		rtc_time.tm_hour = 0;
//		rtc_time.tm_mday = 1;
//		rtc_time.tm_wday = 0;
//		rtc_time.tm_mon = 0;
//		rtc_time.tm_year = 100;
//		rtc_time.tm_yday = 0;
//		rtc_time.tm_isdst = 0;
		set_time_rtc(&rtc_time)/*set_date()*/;
	}
	else if(mktime(&rtc_time)==-1)
	{
//		SetError(RTC_ERR, HARWARE_ALRM_SCR);
		init_time_rtc(&rtc_time);
		set_time_rtc(&rtc_time)/*set_date()*/;
	}
	
	time_sec  = mktime(&rtc_time); 
	set_clock(time_sec);

//	if(get_days(&calib_date) > 365)
//	if(time_sec - calib_time >= 31536000L /*365*24*60*60*/)
//	{
//			Beep(800);
//			lcd_clear();
//			beep(800,4);
//			RTclock.timer = 2000; //10sec timeout
//			draw_text( 15, LCD_TXTLINE1, (uchar*)"SEND THE PUMP", LCD_PIXEL_ON,0);
//			draw_text( 54, LCD_TXTLINE2, (uchar*)"TO", LCD_PIXEL_ON,0);
//			draw_text( 29, LCD_TXTLINE3, (uchar*)"CALIBRATE", LCD_PIXEL_ON,0);
//			while(RTclock.timer > 0);
//	}




	SST25ProtDisable();

	SST25ReadArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t));
	if(crc16((unsigned char*)&E2pImage, sizeof(E2pImage_t)) != 0)
	{
//TBD		SetError(EEPROM_ERR, HARWARE_ALRM_SCR);
		set_defaults();
	}
	SST25ReadArray(CLBR_E2PIMG_BASE, &Clbr_E2pImage, sizeof(Clbr_E2pImage_t));
	if(crc16((unsigned char*)&Clbr_E2pImage, sizeof(Clbr_E2pImage_t)) != 0)
	{
//TBD		SetError(EEPROM_ERR, HARWARE_ALRM_SCR);
		set_fact_defaults();
	}
        if(GetError() != 0)
	{
		err_code = GetError();
		ClearError();
                ((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
		SST25SectorErase(PARAM_E2PIMG_BASE);
		if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)))
			/*CriticalError("eeprom err")*/;
	}

	MCP23S08Init();
	MCP4822Write(0, zero_press1 , 0);
	MCP4822Write(1, zero_press2 , 0);

	init_motor();
	init_airdet();
#endif
	init_keypad();
	init_clock();
	CheckParams();

	/* drop task priority */	 
	vTaskPrioritySet( hBACKGRNDTask, tskIDLE_PRIORITY + 1 );	
	while (1) 
	{
            vTaskDelay( 50 / portTICK_RATE_MS );   // Wait 50ms
		 
            if(val1 > 0x0fff)
                val1 = 0;
            else
                val1++;
            if(val2 > 0x0fff)
                val1 = 0;
            else
                val2++;

            if(!wdi_ena)
                toggleExpGPO(WDI_EXTIOBIT);
//	ClrWdt();
//	WD_PIN^= 1; 			 /*toggle external watch dog */
	}	
}

void CheckParams(void)
{
	if(!(vol_para.rate <= max_rate && vol_para.rate > 0.1 ))
		vol_para.rate = 0.0;
	if(!(vol_para.vtbi > max_volume && vol_para.vtbi < 0.1 ))
		vol_para.vtbi = 0.0;
	if(!(vol_para.infsd > max_volume && vol_para.infsd < 0.1 ))
		vol_para.infsd = 0.0;
	vol_para.infusetime = 0;
//	vol_para.occlusion_lmt = 0;
	vol_para.occlusion_lmt = strtocclus_lmt;
	vol_para.drug_type = 0;
	vol_para.dose_vol = 0.0;
	vol_para.kvo_rate = 0.0;
	vol_para.dose_interval = 0;
	memset(vol_para.prog_steps,0,sizeof(STEP_t)*25);
	vol_para.prog_stepsnum = 1;
	vol_para.prog_step = 0;
}
void ClearParams(void)
{
	memset((unsigned char*)&vol_para,0,sizeof(vol_para));
	vol_para.prog_stepsnum = 1;
}



void set_defaults(void)
{
		/* write defaults */
//	zero_press1 = 1100;
//	zero_press2 = 1110;
//	set_press1 = 100;
//	set_press2 = 100;
//	scale_press1 = 100;
//	scale_press2 = 100;
	upocclus_lmt = 60;
	paraocclus_lmt = 60;	
	strtocclus_lmt = 1;
	occlus_lmt[0] = 230;
	occlus_lmt[1] = 460;
	occlus_lmt[2] = 725;
	bolus_init.rate = 500.0;
	bolus_init.volume = 5.0;
	bolus_init.maxrate = MAXRATE;
	bolus_init.maxvolume = 15.0;
	bolus_init.mode = 1;
	max_rate = MAXRATE;
	max_volume = 9999.0;
	memset(&drugs[0],0 ,sizeof(drugs));
	drugs[0].maxrate = MAXRATE;
	drugs[0].maxvolume = 9999.0;
	memset(&drug_list[0][0],0 ,sizeof(drug_list));
	strcpy(&drug_list[0][0],"CILAZAPRIL");
	memset(&depart_list[0][0],0 ,sizeof(depart_list));
//	strcpy(&depart_list[0][0],depname_msg);
	depart_name = 0;
	ail_limit = 100;
//	vol_calibr = 1;
	bzz_volume = 0;
	battype = BAT_6NIMH;
//	hwopt = 0x03;		/*0-1 BUZ volume, 2 - 4 BAT type*/
	prog_num = 0;
		/* put checksum to the last halfword */
  	((unsigned int*)&E2pImage)[sizeof(E2pImage_t)/2 - 1] = crc16(&E2pImage, sizeof(E2pImage_t) - 2);
		SST25SectorErase(PARAM_E2PIMG_BASE);
		if(!SST25WriteArray(PARAM_E2PIMG_BASE, &E2pImage, sizeof(E2pImage_t)))
			/*CriticalError("eeprom err")*/;

//		if(eeprom_write(0, &E2pImage, sizeof(E2pImage_t)) == 0)
//			critical_error((uchar*)eeprom_msg);

}

void set_fact_defaults(void)
{
		/* write defaults */
	memset((unsigned char*)&Clbr_E2pImage, 0 , sizeof(Clbr_E2pImage_t));
	zero_press1 = 1100;
	zero_press2 = 1110;
	set_press1 = 100;
	set_press2 = 100;
	scale_press1 = 100;
	scale_press2 = 100;
	vol_calibr = 1;
	calib_time = 0;
	/* put checksum to the last halfword */
  	((unsigned int*)&Clbr_E2pImage)[sizeof(Clbr_E2pImage)/2 - 1] = crc16(&Clbr_E2pImage, sizeof(Clbr_E2pImage) - 2);
		SST25SectorErase(CLBR_E2PIMG_BASE);
		if(!SST25WriteArray(CLBR_E2PIMG_BASE, &Clbr_E2pImage, sizeof(Clbr_E2pImage)))
			CriticalError("eeprom err");

//		if(eeprom_write(0, &E2pImage, sizeof(E2pImage_t)) == 0)
//			critical_error((uchar*)eeprom_msg);
}


