/*****************************************************************************
 *****************************************************************************
 * FileName:        taskTouchScreen.h
 *****************************************************************************/

#ifndef __TASKTOUCHSCREEN_H
#define __TASKTOUCHSCREEN_H

#ifdef TASKTOUCHSCREEN_PUB
#define TASKTOUCHSCREENPUB
#else
#define TASKTOUCHSCREENPUB extern
#endif

#include "include.h"
//#include "graphics.h"
// this sw is designed to run on the GRAPHICS_PICTAIL_VERSION 2
#define FLIP_Y


#ifdef TASKTOUCHSCREEN_PUB

// Default calibration values
#define YMINCAL         0x37d
#define YMAXCAL         0x096
#define XMINCAL         0x363
#define XMAXCAL         0x0C9

// Max/Min ADC values for each direction
volatile WORD _calXMin = XMINCAL;
volatile WORD _calXMax = XMAXCAL;
volatile WORD _calYMin = YMINCAL;
volatile WORD _calYMax = YMAXCAL;

#else

extern volatile WORD _calXMin;
extern volatile WORD _calXMax;
extern volatile WORD _calYMin;
extern volatile WORD _calYMax;

// Current ADC values for X and Y channels and potentiometer R6
extern volatile SHORT adcX;
extern volatile SHORT adcY;
extern volatile SHORT adcPot;
extern volatile SHORT adcTemp;

#endif

// Addresses for calibration and version values in FLASH
#define ADDRESS_VERSION  (unsigned long)0x00000000
#define ADDRESS_XMIN     (unsigned long)0x00000002
#define ADDRESS_XMAX     (unsigned long)0x00000004
#define ADDRESS_YMIN     (unsigned long)0x00000006
#define ADDRESS_YMAX     (unsigned long)0x00000008

// different touch screen scan rates
#define TOUCH_SLOW_SCAN		(100 / portTICK_RATE_MS)
#define TOUCH_FAST_SCAN		(10 / portTICK_RATE_MS)


// size of the stack for this task
#define STACK_SIZE_TOUCHSCREEN		(configMINIMAL_STACK_SIZE * 4)
// handle to the task
TASKTOUCHSCREENPUB xTaskHandle hTOUCHTask;
TASKTOUCHSCREENPUB xSemaphoreHandle hADCSemaphore;

/*********************************************************************
* Function: SHORT TouchGetX(void)
*
* PreCondition: none
*
* Input: none
*
* Output: x coordinate
*
* Side Effects: none
*
* Overview: returns x coordinate if touch screen is pressed
*           and -1 if not
*
* Note: none
*
********************************************************************/
SHORT TouchGetX(void);

/*********************************************************************
* Function: SHORT TouchGetY(void)
*
* PreCondition: none
*
* Input: none
*
* Output: y coordinate
*
* Side Effects: none
*
* Overview: returns y coordinate if touch screen is pressed
*           and -1 if not
*
* Note: none
*
********************************************************************/
SHORT TouchGetY(void);

/*********************************************************************
* Function: void TouchCalibration()
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Runs the calibration routine. 
*
* Note: none
*
********************************************************************/
void TouchCalibration();

/*********************************************************************
* Function: void TouchStoreCalibration(void)
*
* PreCondition: EEPROMInit() must be called before
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: stores calibration parameters into EEPROM
*
* Note: none
*
********************************************************************/
void TouchStoreCalibration(void);

/*********************************************************************
* Function: void TouchLoadCalibration(void)
*
* PreCondition: EEPROMInit() must be called before
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: loads calibration parameters from EEPROM
*
* Note: none
*
********************************************************************/
void TouchLoadCalibration(void);

/*********************************************************************
* Macros: ADCGetX()
*
* PreCondition: none
*
* Input: none
*
* Output: ADC result
*
* Side Effects: none
*
* Overview: returns ADC value for x direction if touch screen is pressed
*           and -1 if not
*
* Note: none
*
********************************************************************/
//#define ADCGetX() adcX
#define ADCGetX() (SHORT)xcor

/*********************************************************************
* Macros: ADCGetY()
*
* PreCondition: none
*
* Input: none
*
* Output: ADC result
*
* Side Effects: none
*
* Overview: returns ADC value for y direction if touch screen is pressed
*           and -1 if not
*
* Note: none
*
********************************************************************/
//#define ADCGetY() adcY
#define ADCGetY() (SHORT)ycor

/*********************************************************************
* Macros: ADCGetPot()
*
* PreCondition: none
*
* Input: none
*
* Output: ADC result
*
* Side Effects: none
*
* Overview: returns ADC value for potentiometer
*
* Note: none
*
********************************************************************/
#define ADCGetPot() adcPot

/*********************************************************************
 * Function:        void taskTouchScreen(void* pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *                  
 * Output:          Does not return
 *
 * Side Effects:    None
 *
 * Overview:        Touchscreen handling routine. Touchscreen events
 *					are detected and passed as messages to the graphics
 *					display task. This isolates the human interface
 *					events from the graphics drawing
 *
 * Note:            
 ********************************************************************/
void taskTouchScreen(void* pvParameter);

#endif // __TASKTOUCHSCREEN_H
