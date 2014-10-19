/*****************************************************************************
 *****************************************************************************/
#define TASK_CALC_PUB

#include "include.h"





/*********************************************************************
 * Function:        void taskCalc(void* pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           void* pvParameter, any parameter from the creator
 *                  
 * Output:          Does not return
 *
 * Side Effects:    None
 *
 * Overview:        Calc handling task
 *
 * Note:            
 ********************************************************************/
void taskCalc(void* pvParameter)
{
	static CONTROL_MSG msg;
	static GRAPHICS_MSG gMsg;
	gMsg.cmd = MSG_INPUT_EVENT;
	unsigned char rslt,hipriority_rslt;
	static unsigned long last_clock;
//	static unsigned long last_clock_end_alarm;
//	vTaskDelay( 500 / portTICK_RATE_MS );   // Wait 50ms
        test_mode = 0;
	while (1) {
		
		vTaskDelay( 50 / portTICK_RATE_MS );   // Wait 50ms
		hipriority_rslt = get_batt_level();
		if(hipriority_rslt > 0)
		{
			gMsg.data.golMsg.param1 = hipriority_rslt;
			gMsg.data.golMsg.param2 = INP_SET;     //input event status;
 			xQueueSend(hQVGAQueue, &gMsg, 0);
			continue;
//			break;
		}
		
		hipriority_rslt = check_hold_tmr();
		calc_press();
//		if(!testBit( runhold_stat, RUNNING))
		if(stmotor_stat()== STMTR_STOP || test_mode == 1)
		{
#if 1
//TBD			if((alarm_st&RED_ALARM_MASK) == 0 && motor_alarm == TRUE)
//			{
//				if(hipriority_rslt < INP_MOTOR_ID)
//				{
//					hipriority_rslt = INP_MOTOR_ID;
//					setBit( alarm_st, MOTOR_ALRM);
//				}
//			}
#endif
			
			if(hipriority_rslt > 0)
			{	
				gMsg.data.golMsg.param1 = hipriority_rslt;
				gMsg.data.golMsg.param2 = INP_SET;     //input event status;
 				xQueueSend(hQVGAQueue, &gMsg, 0);
			}
			continue;
		}		
		get_last_alarm_clock();
		clear_hold_tmr();
		rslt = check_batt();
		if((rslt > 0)&&(hipriority_rslt < rslt))
		{
			hipriority_rslt = rslt;
		}	
		rslt = check_press();
		if((rslt > 0)&&(hipriority_rslt < rslt))
		{
			hipriority_rslt = rslt;
		}	
//TBD		if((alarm_st&RED_ALARM_MASK) == 0 && air_alarm == TRUE)
//		{
//			if(hipriority_rslt < INP_AIR_ID)
//			{
//				hipriority_rslt = INP_AIR_ID;
//				setBit( alarm_st, AIR_ALRM);
//			}
//		}
#if 0		
		if((alarm_st&RED_ALARM_MASK) == 0 && motor_alarm == TRUE)
//		if(!testBit( alarm_st, MOTOR_ALRM) && motor_alarm == TRUE)
		{
			if(hipriority_rslt < INP_MOTOR_ID)
			{
				hipriority_rslt = INP_MOTOR_ID;
				setBit( alarm_st, MOTOR_ALRM);
			}
		}
#endif
		infusedvol_1ms();
		calc_rem_infusetime();
		if(((no_limit == 0) ||(vol_para.vtbi > 0.0001))&&(vol_para.infsd > vol_para.vtbi))
	 	{
			if((prog_num == 4) && ((vol_para.prog_step + 1) < vol_para.prog_stepsnum))     /*Program - STEPS*/
			{
				vol_para.prog_step++;
				vol_para.rate = vol_para.prog_steps[vol_para.prog_step].rate;
				vol_para.vtbi += vol_para.prog_steps[vol_para.prog_step].vol;
				new_calc_rate(vol_para.rate);
                                stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_RERUN);
			}
			else if(((prog_num == 2)||(prog_num == 3))&&(vol_para.infsd < vol_para.bag_vol)&&( vol_para.trig_flg == FALSE)
																								&&((clock() - vol_para.dose_strt_interval) > vol_para.dose_interval))
			{
//				if((clock() - vol_para.dose_strt_interval) > vol_para.dose_interval)
				vol_para.trig_flg = TRUE;
				clearBit(kvo_stat, KVO_STAT);
				vol_para.rate = vol_para.dose_rate;
 				if(vol_para.bag_vol > (vol_para.infsd + vol_para.dose_vol))
 					vol_para.vtbi = vol_para.infsd + vol_para.dose_vol;
 				else
 					vol_para.vtbi = vol_para.bag_vol; 
//					vol_para.dose_interval_cntr = 0;
//				vol_para.dose_strt_time = clock();		 
 				new_calc_rate(vol_para.rate);
                                stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_RERUN);
			}
			else
			{
				/*reduce rate*/
				switch(prog_num)
				{
					case 2:				
					case 3:				
//				if((clock() - vol_para.dose_strt_time) > vol_para.dose_interval)
						if(vol_para.trig_flg == TRUE)
						{
							vol_para.dose_strt_interval = clock();
							vol_para.trig_flg = FALSE;
						}	 
						break;				 
					default:
						vol_para.kvo_rate = 5.0;
//						new_calc_rate(5.0);
						break;				
				}
				if(testBit( kvo_stat, KVO_STAT) == 0 && vol_para.rate > vol_para.kvo_rate)
				{
					vol_para.rate = vol_para.kvo_rate;
					new_calc_rate(vol_para.kvo_rate);
                                        stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_RERUN);
				}
				setBit(kvo_stat, KVO_STAT);
				
				if((clock_ms() - last_clock) > 7L*1000L) /* 7 sec*/
				{
					if((alarm_st/*&YELLOW_ALARM_MASK*/ == 0))
					{
						if((hipriority_rslt < INP_KVO_ID) &&((clock_ms() - last_clock_end_alarm)> 2*1000))
						{
							hipriority_rslt = INP_KVO_ID;
//TBD							setBit( alarm_st, KVO_ALRM);
							last_clock = clock_ms();
						}				
					}
					else
						last_clock_end_alarm = clock_ms();
				}
//TBD				if(testBit( alarm_st, KVO_ALRM))
//					last_clock = clock_ms();
			}
		
		}



		if(hipriority_rslt > 0)
		{
			gMsg.data.golMsg.param1 = hipriority_rslt;             //input event id  
			gMsg.data.golMsg.param2 = INP_SET;     //input event status;
			xQueueSend(hQVGAQueue, &gMsg, 0);
		}
	}	  
}


void	calc_rem_infusetime(void)
{
		if(estim_endtime < clock())
			remain_infusetime = 0;
		else
			remain_infusetime = estim_endtime - clock();
}

void infusedvol_1ms(void)
{             
#if 1	
	vol_para.infsd = ((float)steps*MLPS/**(2.0 - vol_calibr)*/);  // 200 motor steps per turn, 1 turn - 0.2ml (100 steps - 0.1ml
#else
	if(vol_para.rate >= 700.0)
		vol_para.infsd = ((float)steps*MLPS);
	else
	{
		vol_para.infsd = ((float)steps*(TENTHMLPERTURN/(float)130))*0.5;
	}
#endif
}

void calc_press(void)
{
float tmp;	 
	if(scale_press2>0)
	{
		tmp = (float)press2_raw - (float)set_press2;
		press2_mmHg = (int)((tmp /(float)scale_press2)*300.0);
	}
	else
		press2_mmHg	= 0;
	 
	if(scale_press1>0)
	{
		tmp = (float)press1_raw - (float)set_press1;
		press1_mmHg = (int)((tmp/(float)scale_press1)*300.0);
	}
	else
		press1_mmHg	= 0;
}

unsigned char check_press(void)
{
unsigned char alrm_type = 0;

	if((press1_mmHg < -300)&&(press1_mmHg < -300))
 	{
#ifndef NOSET_DIS		 
			stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_STOP);
//TBD			if((alarm_st&RED_ALARM_MASK) == 0)
//			{
//				setBit( alarm_st, NOSET_ALRM);
//				alrm_type = INP_NOSET_ID; //
//			}
			return alrm_type;
#endif /*NOSET_DIS*/	
	}

//	if(press2_mmHg >= occlus_lmt[vol_para.occlusion_lmt])
	if(press2_mmHg >= occlus_lmt[occlusion_limit])
	{
#ifndef DOWNOCCL_DIS		 
//			if((alarm_st&RED_ALARM_MASK) == 0)
//			{
//				stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_STOP);
//				setBit( alarm_st, DOWNOCC_ALRM);
//				alrm_type = INP_DOWNOCC_ID; // WE_DOWNOCC
//				if(!testBit( runhold_stat, BACK_RUNNING))
//				{
//					setBit( runhold_stat, BACK_RUNNING);
//					new_calc_rate(600.0);
//					steps_cntr = 60;
//					stmotor_cmd(STMTR_DIR_RIGHT,STMTR_RUN);
//				}
//			}
			return alrm_type;
#endif /*DOWNOCCL_DIS*/	
	}	
	else //if(runhold_stat == TRUE)
	{
//			clearBit( runhold_stat, RUNNING);
//			runhold_stat = 0;
//			steps_cntr = 0;
	}
	if(press1_mmHg < upocclus_lmt)
 	{
#ifndef UPOCCL_DIS		 
			stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_STOP);
//TBD			if((alarm_st&RED_ALARM_MASK) == 0)
//			{
//				setBit( alarm_st, UPOCC_ALRM);
//				alrm_type = INP_UPOCC_ID; // WE_UPOCC
//			}
			return alrm_type;
#endif /*UPOCCL_DIS*/	
	}	
	if(press2_mmHg < paraocclus_lmt)
	{
#ifndef PARAOCCL_DIS		 
	 		stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_STOP);
//TBD			if((alarm_st&RED_ALARM_MASK) == 0)
//			{
//				setBit( alarm_st, PARAOCC_ALRM);
//				alrm_type = INP_PARAOCC_ID; // WE_PARAOCC
//			}
			return alrm_type;
#endif /*PARAOCCL_DIS*/	
	}	
	
	return alrm_type;
}

unsigned char get_batt_level(void)
{
	
	if ( batt_raw > BAT_FULL)
		batlevel = 10;
	else
		batlevel =(batt_raw - BAT_MIN)/((BAT_FULL - BAT_MIN)/10.0);

//	if ( batt_raw > AC_MIN)
//		return 0;

	if (batt_raw< BAT_MIN) /*Power off*/
			return INP_NOBAT_ID;
	return 0;

}

unsigned char check_batt(void)
{
	static unsigned long lastClock;
//	static unsigned long last_clock_end_alarm;
	unsigned char alrm_type = 0;


	if ( batt_raw > AC_MIN)
		return alrm_type;

	if (batt_raw< BAT_MIN) /*Power off*/
	{
			alrm_type = INP_NOBAT_ID;
	}
	else if (batt_raw< BAT_EMPTY) /*empty battery*/
	{
//		if((alarm_st&RED_ALARM_MASK) == 0)
//		{
//	 		stmotor_cmd(STMTR_DIR_NOCHNG,STMTR_STOP);
//TBD			setBit( alarm_st, BATEMPTY_ALRM);
//			alrm_type = INP_BATEMPTY_ID;
//		}
	}
	else if(batt_raw< BAT_LOW) /*Low battery*/
	{

		if(clock_ms() - lastClock > 5*1000) /* 5 sec*/
		{
			if(alarm_st/*&YELLOW_ALARM_MASK*/ == 0)
			{
				if((clock_ms() - last_clock_end_alarm)> 2*1000)
				{
//TBD					setBit( alarm_st, BATLOW_ALRM);
					alrm_type = INP_BATLOW_ID;
				}
			}
			else
				last_clock_end_alarm = clock_ms();
		}
//TBD 		if(testBit( alarm_st, BATLOW_ALRM))
// 		{
//			lastClock = clock_ms();
//		}
	}
	else  /*No AC*/
	{
		if(clock_ms() - lastClock > 5*1000) /* 5 sec*/
		{
			if(alarm_st/*&YELLOW_ALARM_MASK*/ == 0)
			{
				if((clock_ms() - last_clock_end_alarm)> 2*1000)
				{
//TBD					setBit( alarm_st, NOAC_ALRM);
					alrm_type = INP_NOAC_ID;
				}
			}
			else
				last_clock_end_alarm = clock_ms();
		}
//TBD 		if(testBit( alarm_st, NOAC_ALRM))
// 		{
//			lastClock = clock_ms();
//		}
	}

	return alrm_type;
}

unsigned char check_hold_tmr(void)
{
	unsigned char alrm_type = 0;
		
		if((clock_ms() - hold_timer) > 120L*1000L) /* 120 sec*/
		{
//			if(!testBit( alarm_st, HOLD_ALRM))
			if(alarm_st == 0)
			{
//TBD				setBit( alarm_st, HOLD_ALRM);
				alrm_type = INP_ONHOLD_ID;
			}
			else 
				hold_timer = clock_ms();
		}
		return alrm_type;

}
void clear_hold_tmr(void)
{
	hold_timer = clock_ms();
}

void get_last_alarm_clock(void)
{
	if(alarm_st/*&YELLOW_ALARM_MASK*/ != 0)
		last_clock_end_alarm = clock_ms();
}

void run_prepare()
{
int i;
float infused_part;
	 
	runhold_stat = 0;
        test_mode = 0;
	vol_para.trig_flg = TRUE;
	switch(prog_num)
	{
		default:
		case 0:
			if (vol_para.vtbi >= vol_para.infsd)
				estim_infusetime = (unsigned long)(((vol_para.vtbi-vol_para.infsd)/vol_para.rate)*3600.0);
			else
				estim_infusetime = 0;
			break;
		case 1:
			if (estim_infusetime > 0 && (vol_para.vtbi >= vol_para.infsd))
//				estim_infusetime = (unsigned long)(((vol_para.vtbi-vol_para.infsd)/vol_para.rate)*3600.0);
			 	vol_para.rate	= (vol_para.vtbi - vol_para.infsd)/((float)estim_infusetime/3600.0);
			else
				vol_para.rate = 5.0;
			break;
		case 2:
			vol_para.vtbi = vol_para.dose_vol;
			vol_para.rate = vol_para.dose_rate;
			vol_para.dose_strt_time = clock();
			if (vol_para.vtbi >= vol_para.infsd)
				estim_infusetime = (unsigned long)(((vol_para.vtbi-vol_para.infsd)/vol_para.rate)*3600.0);
			else
				estim_infusetime = 0;
			break;
//				vol_para.bag_vol = 0.0;
//				vol_para.dose_vol = 0.0;
//				vol_para.dose_rate = 0.0;
//				vol_para.dose_interval = 0;
//				vol_para.kvo_rate = 0.0;
//				vol_para.infsd = 0.0;
		
		case 3:
			vol_para.vtbi = vol_para.dose_vol;
			vol_para.dose_rate = (vol_para.vtbi - vol_para.infsd)/((float)vol_para.dose_time/3600.0);
			vol_para.rate = vol_para.dose_rate;
			vol_para.dose_strt_time = clock();		 
			if (vol_para.vtbi >= vol_para.infsd)
				estim_infusetime = (unsigned long)(((vol_para.vtbi-vol_para.infsd)/vol_para.rate)*3600.0);
			else
				estim_infusetime = 0;
			break;
		
		case 4:
			infused_part =	vol_para.infsd; 
			for(i = 0, vol_para.prog_step = 0; i < vol_para.prog_stepsnum; i++)
			{
				if(vol_para.prog_steps[i].vol <= infused_part	)
				{
					vol_para.prog_step++;
					infused_part -= vol_para.prog_steps[i].vol;
					estim_infusetime = 0;
					continue;
				}
				estim_infusetime += ((vol_para.prog_steps[i].vol-infused_part)/vol_para.prog_steps[i].rate)*3600.0;
				infused_part = 0.0;
			}						
			vol_para.vtbi = vol_para.prog_steps[vol_para.prog_step].vol;
			vol_para.rate = vol_para.prog_steps[vol_para.prog_step].rate;
			
			break;
		case 5:
			break;
			
	}
	estim_endtime = estim_infusetime + clock();
}


