#define KEYPAD_PUB

#include "include.h"


static int keyUpdateTimer;

unsigned int key_timer;
//static unsigned int key_time;
static unsigned int keygap_time;
static int key_bounce_timer; /* de-bounce timer in clock ticks */
static unsigned char mkey, key_old, door; /* holds a keystroke */
static unsigned char key_latch; /* new keystroke */

#define KEYLTCH_TIME 40		//200mS

void init_keypad(void)
{
	keypad_stat = 0;
	power_state = 0;
	beep_state = BEEPSTATE_ON;
//	key_repeat_flg = REPEAT_ON;
	door_old = 0x40;   //Door closed
//	door_old = 0x00;   //Door closed
	key_latch = ONOFF_CMD|0x40;
	key_old = ONOFF_CMD; 
//	door_old = 0x40;   //Door closed
}


/*
 * Manages window/keypad events
 */
void event_man(void)
{
	static CONTROL_MSG cMsg;
	static GRAPHICS_MSG gMsg;
	portBASE_TYPE xTaskWoken;
	unsigned char	inp_evnt;
	unsigned char	inp_id;

	unsigned char update_trig = 0; 

  if(key_bounce_timer > 0)  /* A keystroke is still being checked */
    return;
	inp_evnt = INP_NOEVENT;
	cMsg.cmd = MSG_INPUT_EVENT;

#ifndef DOOR_DIS
	door = key_latch & DOOR_CMD;
	if(door_old != door )
	{
		cMsg.data.wVal[0] = INP_DOOR_ID;             //input event id  
		if(door == 0)
  	{
			cMsg.data.wVal[1] = INP_SET;     //input event status;
		}
		else
		{
			cMsg.data.wVal[1] = INP_RELEASE;     //input event status;
		}
		xQueueSendToBackFromISR(hCONTROLQueue, &cMsg, &xTaskWoken);
		door_old = door;
	}
#else
		door_old = door = 0x40;
#endif
	 
	mkey = key_latch & (STOP_CMD | ONOFF_CMD);  /* Hold old keystroke */
  key_time = key_timer; /* Keep time of key was pressed */
  key_bounce_timer = KEYLTCH_TIME; /* Ready for a new keystroke to be accepted */

  if(mkey == RELEASEKEY && key_old == RELEASEKEY)   /*No inputs*/
  {
  }
  else /* Check a new input */
	{
    if(mkey == RELEASEKEY) /* key released */
		{
      switch(key_old)
			{
				case ONOFF_CMD:
 					inp_evnt = INP_RELEASE;
 					inp_id = INP_ONOFF_ID;
					break;
				default:
					inp_evnt = INP_NOEVENT;
					break;
			}
		}
    else /* key pressed/holded */
		{
			if(key_old == RELEASEKEY) /*key pressed*/
			{
//				beep(15,1);
				keygap_time = key_timer; /* hold the gap time between two keystrokes */
				switch(mkey)
				{
     			case STOP_CMD:
						inp_evnt = INP_SET;
						inp_id = INP_STOP_ID;
						break;
     			case ONOFF_CMD:
						inp_evnt = INP_SET;
						inp_id = INP_ONOFF_ID;
						break;
					default:
						inp_evnt = INP_NOEVENT;
						break;
				}
		  }
			else if(key_old == mkey) /* key holded */
			{
#if 0	   			
    		if(key_time > 1000)  /*holded for more than 1sec*/
				{
					if(keyUpdateTimer > 0 || key_repeat_flg == REPEAT_OFF )
			 			return;  /* do not accept a key until interval expires */
					if(mkey == STEPPLUS_CMD || mkey == STEPMIN_CMD )
					{
//						beep(15,1);
						if(key_time > 8000)  /*10sec*/
							keyUpdateTimer = 50; /* run key update timer 100ms*/
						else if(key_time > 5400)  /*5sec*/
							keyUpdateTimer = 100; /* run key update timer 100ms*/
						else if(key_time > 3000)  /*3sec*/
							keyUpdateTimer = 300; /* run key update timer 300ms*/
						else //if(key_time > 1000)  /*1sec*/
							keyUpdateTimer = 500; /* run key update timer 0.5s*/
					}
					else
					{
						if(key_time > 1000)  /*1sec*/
							keyUpdateTimer = 1000; /* run key update timer 1000ms*/
			   	}
					switch(mkey)
			   	{
							case STEPPLUS_CMD:
          	 		if(update_trig)
									win_evnt = WE_UPHLD1;
								else	
									win_evnt = WE_UPHLD;
								break;
       				case STEPMIN_CMD:
          	 		if(update_trig)
	       					win_evnt = WE_DWNHLD1;
								else	
	       					win_evnt = WE_DWNHLD;
								break;
							case ONOFF_CMD:
     		  			win_evnt = WE_ONOFFHLD;
								break;
							default:
		       			win_evnt = WE_NOEVENT;
					}
				}
#endif					
			}
		}
    /* Accept a key */
    key_old = mkey;  /* Hold old keystroke */
		
 		cMsg.data.wVal[0] = inp_id;             //input event id  
 		cMsg.data.wVal[1] = inp_evnt;     //input event status
		
		if(inp_evnt != INP_NOEVENT)
		{
			if (power_state == 0)
			{
	 			xQueueSendToBackFromISR(hCONTROLQueue, &cMsg, &xTaskWoken);
			}
			else
			{
				if (inp_id == INP_ONOFF_ID)	
	 				xQueueSendToBackFromISR(hCONTROLQueue, &cMsg, &xTaskWoken);
			}
		}
	}
}

/*
 * Manages window/keypad events
 */
void new_event_man(void)
{
//	static CONTROL_MSG cMsg;
	static GRAPHICS_MSG gMsg;
	portBASE_TYPE xTaskWoken;
	unsigned char	inp_evnt;
	unsigned char	inp_id;

	unsigned char update_trig = 0; 

	if(key_bounce_timer > 0)  /* A keystroke is still being checked */
		return;
	inp_evnt = INP_NOEVENT;
	gMsg.cmd = MSG_INPUT_EVENT;

#ifndef DOOR_DIS
	door = key_latch & DOOR_CMD;
	if(door_old != door )
	{
		gMsg.data.golMsg.param1 = INP_DOOR_ID;             //input event id  
		if(door == 0)
		{
// 			stmotor_cmd(STMTR_NOCHNG,STMTR_STOP);
			gMsg.data.golMsg.param2 = INP_SET;     //input event status;
		}
		else
		{
			gMsg.data.golMsg.param2 = INP_RELEASE;     //input event status;
		}
 		xQueueSend(hQVGAQueue, &gMsg, 0);
		door_old = door;
	}
#else
		door_old = door = 0x40;
#endif	  
	mkey = key_latch & (STOP_CMD | ONOFF_CMD);  /* Hold old keystroke */
	key_time = key_timer; /* Keep time of key was pressed */
	key_bounce_timer = KEYLTCH_TIME; /* Ready for a new keystroke to be accepted */

	if(mkey == RELEASEKEY && key_old == RELEASEKEY)   /*No inputs*/
	{
	}
	else /* Check a new input */
	{
		if(mkey == RELEASEKEY) /* key released */
		{
			switch(key_old)
			{
				case ONOFF_CMD:
					inp_evnt = INP_RELEASE;
					inp_id = INP_ONOFF_ID;
					break;
				default:
					inp_evnt = INP_NOEVENT;
					break;
			}
		}
		else /* key pressed/holded */
		{
			if(key_old == RELEASEKEY) /*key pressed*/
			{
//				beep(15,1);
				keygap_time = key_timer; /* hold the gap time between two keystrokes */
				switch(mkey)
				{
					case STOP_CMD:
						inp_evnt = INP_SET;
						inp_id = INP_STOP_ID;
						break;
					case ONOFF_CMD:
						inp_evnt = INP_SET;
						inp_id = INP_ONOFF_ID;
						break;
					default:
						inp_evnt = INP_NOEVENT;
						break;
				}
			}
//			else if(key_old == mkey) /* key holded */
//			{
//			}
		}
		/* Accept a key */
		key_old = mkey;  /* Hold old keystroke */
		
		gMsg.data.golMsg.param1 = inp_id;             //input event id  
		gMsg.data.golMsg.param2 = inp_evnt;     //input event status
		
#if 1		
		if(inp_evnt != INP_NOEVENT)
		{
			if (power_state == 0)
			{
				xQueueSend(hQVGAQueue, &gMsg, 0);
			}
			else
			{
				if (inp_id == INP_ONOFF_ID)	
					xQueueSend(hQVGAQueue, &gMsg, 0);
			}
		}
#endif	
	}
}

#if 0
///////////////////////////////////////////////////////////////////////////
// Updates display timers
void UpdateDisTimers(void)
{
static unsigned long lastClock;
unsigned int elapsedTime;

	elapsedTime = clock_ms() - lastClock; /* time elapsed */
	lastClock = clock_ms();

  if(keyUpdateTimer > 0)  /* key update timer */
    keyUpdateTimer -= elapsedTime;
}
#endif

///////////////////////////////////////////////////////////////////////////
// Checks keypad status and counts a time while the key is pressed
unsigned char  ChkKeyPad(void)
{
static unsigned long lastClock;
unsigned int elapsedTime;
unsigned char key_new, exp_gpio;

	elapsedTime = clock_ms() - lastClock; /* Time elapsed */
	lastClock = clock_ms();
	key_timer += elapsedTime; /* Count time while a key is being pressed */
	exp_gpio = MCP23S08Read(GPIO);
	key_new = ((~exp_gpio)&(DOOR_CMD | STOP_CMD | ONOFF_CMD)); /* Read a keypad status */
	exp_gpio &= ~(DOOR_CMD | STOP_CMD | ONOFF_CMD);
//	exp_gpio |= key_new;
//	key_new = (~MCP23S08Read(GPIO )&(DOOR_CMD | STOP_CMD | ONOFF_CMD)); /* Read a keypad status */
	if(key_bounce_timer > 0) /* Test a key */
	{
    	if(key_latch != key_new)  /* Key was changed */
		{
      		key_latch = key_new; /* Keep new key */
      		key_bounce_timer = KEYLTCH_TIME; /* Run de-bounce timer for new keystroke */
      		if(key_latch != 0) /* Some key is pressed */
        		key_timer = 0; /* Restart key pressed timer */
		}
    	else
      		key_bounce_timer -= elapsedTime;
	}
	return exp_gpio;
}



