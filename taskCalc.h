/*****************************************************************************
 *****************************************************************************/

#ifndef __TASK_CALC_H
#define __TASK_CALC_H

#ifdef TASK_CALC_PUB
#define TASK_CALCPUB
#else
#define TASK_CALCPUB extern
#endif


#define RUNNING 0
#define BACK_RUNNING 1

TASK_CALCPUB volatile unsigned char kvo_stat;
TASK_CALCPUB volatile unsigned long  hold_timer;
TASK_CALCPUB volatile unsigned char runhold_stat;
TASK_CALCPUB volatile unsigned int alarm_st;
TASK_CALCPUB volatile unsigned char air_alarm;
TASK_CALCPUB volatile unsigned char motor_alarm;
TASK_CALCPUB volatile unsigned char no_limit;
TASK_CALCPUB volatile unsigned long last_clock_end_alarm;



TASK_CALCPUB float bolus_rate;
TASK_CALCPUB float bolus_volume;
TASK_CALCPUB unsigned char occlusion_limit;
TASK_CALCPUB unsigned long estim_endtime;
TASK_CALCPUB unsigned long estim_infusetime;
TASK_CALCPUB unsigned long remain_infusetime;
TASK_CALCPUB int press1_mmHg;
TASK_CALCPUB int press2_mmHg;
TASK_CALCPUB unsigned int batt_mv;
TASK_CALCPUB volatile unsigned char batlevel;
TASK_CALCPUB volatile unsigned char test_mode;


// size of the stack for this task
#define STACK_SIZE_CALC		(configMINIMAL_STACK_SIZE * 2)
// handle for the task
TASK_CALCPUB xTaskHandle hCALCTask;

// the calc task
TASK_CALCPUB void taskCalc(void* pvParameter);
TASK_CALCPUB void infusedvol_1ms(void);
TASK_CALCPUB void calc_press(void);
TASK_CALCPUB unsigned char  check_press(void);
TASK_CALCPUB unsigned char  check_batt(void);
TASK_CALCPUB unsigned char  get_batt_level(void);
TASK_CALCPUB unsigned char check_hold_tmr(void);
TASK_CALCPUB void clear_hold_tmr(void);
TASK_CALCPUB void get_last_alarm_clock(void);
TASK_CALCPUB void run_prepare(void);
TASK_CALCPUB void	calc_rem_infusetime(void);


#endif // __TASK_CALC_H
