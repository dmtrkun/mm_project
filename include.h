/*
*/

#ifndef INCLUDE_H
#define INCLUDE_H

#include <time.h>
#include <stdio.h>
#include <xc.h>
#include <libpic30.h>
#include <spi.h>

#include "board.h"
#include "framework\gfx\gfx.h"
//#include "Graphics\Graphics.h"

#include <GenericTypeDefs.h>
#include "HardwareProfile.h"


// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "croutine.h"
//#include "graphics.h"
#include "val_conv.h"

#include "osapi.h"
#include "main.h"
#include "GDD_Intro.h"
//#include "GDD_Alarm.h"
//#include "GDD_Pwrdown.h"
#include "GDD_Screens.h"
//#include "GDD_Options.h"
//#include "GDD_Calib.h"
//#include "GDD_RateCalib.h"
//#include "GDD_Adjust.h"
#include "GDD_Clear.h"
//#include "GDD_Run.h"
//#include "GDD_Confirm.h"
#include "GDD_SetProg.h"
#include "GDD_SetDrug.h"
//#include "GDD_Test.h"
//#include "GDD_Prime.h"
//#include "GDD_Bolus.h"
//#include "GDD_Setmenu.h"
//#include "GDD_Setup.h"
//#include "GDD_Checkup.h"
#include "crc16.h"



#include "taskGraphics.h"
#include "taskTouchScreen.h"
#include "taskCalc.h"
#include "taskControl.h"
#include "taskBackground.h"
#include "taskSPI.h"
#include "taskUSB.h"
#include "taskUART.h"
#include "beep.h"
#include "keypad.h"
#include "clock.h"
#include "com.h"
#include "stmotor.h"
#include "air_det.h"
#include "board.h"
#include "SST25VF016.h"
#include "MCP23S08.h"
#include "PCF2123.h"
#include "Graphics Resources\new.h"

#include "framework/usb/usb.h"
#include "framework/usb/usb_device_generic.h"


			 
#endif /* INCLUDE_H */


