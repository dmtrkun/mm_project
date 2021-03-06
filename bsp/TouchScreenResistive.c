/*****************************************************************************
 *
 * Simple 4 wire resistive touch screen driver
 *
 *****************************************************************************
 * FileName:        TouchScreenResistive.c
 * Processor:       PIC24, PIC32, dsPIC, PIC24H
 * Compiler:       	MPLAB C30, MPLAB C32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright � 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 * Date        	Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 01/19/11		Ported from TouchScreen driver.
 * 05/06/11     Added IDLE state and set start up state to IDLE.
 *****************************************************************************/
#include "HardwareProfile.h"

#if defined (USE_TOUCHSCREEN_RESISTIVE)

#include "Graphics/Graphics.h"
#include "TimeDelay.h"
#include "TouchScreen.h"
#include "Compiler.h"

#define TOUCHCAL_CA 0x2A
#define TOUCHCAL_CB 0xE67E
#define TOUCHCAL_CC 0x31
#define TOUCHCAL_CD 0xE944

// Default Calibration Inset Value (percentage of vertical or horizontal resolution)
// Calibration Inset = ( CALIBRATIONINSET / 2 ) % , Range of 0�20% with 0.5% resolution
// Example with CALIBRATIONINSET == 20, the calibration points are measured
// 10% from the corners.
#define CALIBRATIONINSET   20       // range 0 <= CALIBRATIONINSET <= 40 

#define CAL_X_INSET    (((GetMaxX()+1)*(CALIBRATIONINSET>>1))/100)
#define CAL_Y_INSET    (((GetMaxY()+1)*(CALIBRATIONINSET>>1))/100)


//////////////////////// Resistive Touch Driver Version ////////////////////////////
// The first three digit is version number and 0xF is assigned to this
// 4-wire resistive driver.
const WORD mchpTouchScreenVersion = 0xF100;

//////////////////////// LOCAL PROTOTYPES ////////////////////////////
void    TouchGetCalPoints(void);
void 	TouchStoreCalibration(void);
void 	TouchCheckForCalibration(void);
void 	TouchLoadCalibration(void);

extern NVM_READ_FUNC           pCalDataRead;                // function pointer to data read
extern NVM_WRITE_FUNC          pCalDataWrite;               // function pointer to data write
extern NVM_SECTORERASE_FUNC    pCalDataSectorErase;         // function pointer to data sector erase


//////////////////////// GLOBAL VARIABLES ////////////////////////////
#ifndef TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD
    // you may define the threshold with a value, define the new value in the 
    // HardwareProfile.h
    #define TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD     256	// between 0-0x03ff the lesser this value 
											                // the lighter the screen must be pressed
#endif
#define CALIBRATION_DELAY   300				                // delay between calibration touch points

// Current ADC values for X and Y channels
//volatile SHORT      adcX = -1;
//volatile SHORT      adcY = -1;
//volatile SHORT      adcPot = 0;
extern volatile SHORT      adcX;
extern volatile SHORT      adcY;
extern volatile SHORT      adcPot;

volatile SHORT 		_trA = TOUCHCAL_CA;
volatile SHORT 		_trB = TOUCHCAL_CB;
volatile SHORT 		_trC = TOUCHCAL_CC;
volatile SHORT 		_trD = TOUCHCAL_CD;

// WARNING: Watch out when selecting the value of SCALE_FACTOR 
// since a big value will overflow the signed int type 
// and the multiplication will yield incorrect values.
#ifndef TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR
    // default scale factor is 128
    #define TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR 7
#endif

#define SCALE_FACTOR (1<<TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR)

// note the shift is dependent on the SCALE_FACTOR (shifting is faster than division)
#define  CalcTouchX(val) 	(((long)((long)_trC*val) + _trD)>>TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR)
#define  CalcTouchY(val) 	(((long)((long)_trA*val) + _trB)>>TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR)

typedef enum
{
	IDLE,
    SET_X,
    RUN_X,
    GET_X,
    RUN_CHECK_X,
    CHECK_X,
    SET_Y,
    RUN_Y,
    GET_Y,
    CHECK_Y,
    SET_VALUES,
    GET_POT,
    RUN_POT
} TOUCH_STATES;

volatile TOUCH_STATES state = IDLE;

/*********************************************************************
* Function: void TouchDetectPosition(void)
********************************************************************/
void TouchDetectPosition(void)
{
    static SHORT    tempX, tempY;
    SHORT           temp;

    switch(state)
    {
        case IDLE:
		    adcX = -1;
			adcY = -1;
            #ifdef ADC_POT
			    adcPot = 0;
			#endif
			break;
        case SET_VALUES:
            if(!TOUCH_ADC_DONE)
                break;

            if((WORD) TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD < (WORD) ADC1BUF0)
            {
                adcX = -1;
                adcY = -1;
            }
            else
            {
                adcX = tempX;
                adcY = tempY;
            }
        // If the hardware supports an analog pot, if not skip it
        #ifdef ADC_POT
            state = RUN_POT;

       case RUN_POT:
       		TOUCH_ADC_INPUT_SEL = ADC_POT;
            TOUCH_ADC_START = 1;   // run conversion
            state = GET_POT;
            break;

        case GET_POT:
            if(!AD1CON1bits.DONE)
                break;

            adcPot = ADC1BUF0;
        #endif
            state = SET_X;

        case SET_X:
       		TOUCH_ADC_INPUT_SEL = ADC_XPOS;

            TRIS_XPOS = 1;
            TRIS_YPOS = 1;
            TRIS_XNEG = 1;
            LAT_YNEG = 0;
            TRIS_YNEG = 0;

            TOUCH_ADC_START = 1;   // run conversion
            state = CHECK_X;
            break;

        case CHECK_X:
        case CHECK_Y:
            if(!TOUCH_ADC_DONE)
                break;

            if((WORD) TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD > (WORD) ADC1BUF0)
            {
	            if (state == CHECK_X)
	            {
                	LAT_YPOS = 1;
                	TRIS_YPOS = 0;
                	tempX = -1;
                	state = RUN_X;
                } 
                else 
                {
	                LAT_XPOS = 1;
    	            TRIS_XPOS = 0;
        	        tempY = -1;
            	    state = RUN_Y;    
	            }   	
            }
            else
            {
                adcX = -1;
                adcY = -1;
		        #ifdef ADC_POT
            	    state = RUN_POT;
            	#else
            		state = SET_X;	
            	#endif	    
                break;
            }

        case RUN_X:
        case RUN_Y:
            TOUCH_ADC_START = 1;
            state = (state == RUN_X) ? GET_X : GET_Y;
            // no break needed here since the next state is either GET_X or GET_Y
            
        case GET_X:
        case GET_Y:
            if(!TOUCH_ADC_DONE)
                break;

            temp = ADC1BUF0;
            if (state == GET_X)
	        {
	            if(temp != tempX)
	            {
	                tempX = temp;
	                state = RUN_X;
	                break;
	            }
	        }
	        else
	        {
	            if(temp != tempY)
	            {
	                tempY = temp;
	                state = RUN_Y;
	                break;
	            }		        
		    }     

            if (state == GET_X) 
            	TRIS_YPOS = 1;
            else	
	            TRIS_XPOS = 1;
            TOUCH_ADC_START = 1;
            state = (state == GET_X) ? SET_Y : SET_VALUES;
            break;

        case SET_Y:
            if(!TOUCH_ADC_DONE)
                break;

            if((WORD) TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD < (WORD) ADC1BUF0)
            {
                adcX = -1;
                adcY = -1;
		        #ifdef ADC_POT
            	    state = RUN_POT;
            	#else
                	state = SET_X;
                #endif	
                break;
            }
			
       		TOUCH_ADC_INPUT_SEL = ADC_YPOS;

            TRIS_XPOS = 1;
            TRIS_YPOS = 1;
            LAT_XNEG = 0;
            TRIS_XNEG = 0;
            TRIS_YNEG = 1;

            TOUCH_ADC_START = 1;   // run conversion
            state = CHECK_Y;
            break;

        default:
            state = SET_X;
    }

}

/*********************************************************************
* Function: void TouchHardwareInit(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Initializes the A/D channel used for the touch detection.
*
* Note: none
*
********************************************************************/
void TouchHardwareInit(void *initValues)
{
    // Initialize ADC
    AD1CON1 = 0x80E0;       // Turn on, auto-convert
    AD1CON2 = 0;            // AVdd, AVss, int every conversion, MUXA only
    AD1CON3 = 0x1FFF;       // 31 Tad auto-sample, Tad = 256*Tcy
    
    // set the used D/A port to be analog
	#ifdef ADPCFG_XPOS
    	ADPCFG_XPOS = 0;
	#endif
	#ifdef ADPCFG_YPOS
    	ADPCFG_YPOS = 0;
    #endif   
	#ifdef ADC_POT
    	ADC_POT_PCFG = 0;
    #endif	
    
    AD1CSSL = 0;            // No scanned inputs
	
	state = SET_X;          // set the state of the statemachine to start the sampling

}

/*********************************************************************
* Function: SHORT TouchGetX()
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
SHORT TouchGetX_(void)
{
    long    result;

    result = TouchGetRawX();

    if(result >= 0)
    {
		result = CalcTouchX(result);
		#ifdef TOUCHSCREEN_RESISTIVE_FLIP_X
			result = GetMaxX() - result;
		#endif	
	}
    return (result);
}
/*********************************************************************
* Function: SHORT TouchGetX()
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
SHORT TouchGetRawX(void)
{
    #ifdef TOUCHSCREEN_RESISTIVE_SWAP_XY
    return adcY;
    #else
    return adcX;
    #endif
}
/*********************************************************************
* Function: SHORT TouchGetY()
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
SHORT TouchGetY_(void)
{
    long    result;

    result = TouchGetRawY();
    
    if(result >= 0)
    {
		result = CalcTouchY(result);
		#ifdef TOUCHSCREEN_RESISTIVE_FLIP_Y
			result = GetMaxY() - result;
		#endif	
	}
    return (result);
}
/*********************************************************************
* Function: SHORT TouchGetRawY()
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
SHORT TouchGetRawY(void)
{
    #ifdef TOUCHSCREEN_RESISTIVE_SWAP_XY
    return adcX;
    #else
    return adcY;
    #endif
}

#if 0
/*********************************************************************
* Function: void TouchStoreCalibration(void)
*
* PreCondition: Non-volatile memory initialization function must be called before
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: stores calibration parameters into non-volatile memory
*
* Note: none
*
********************************************************************/
void TouchStoreCalibration(void)
{
 
 	if (pCalDataWrite != NULL)
	{
		// the coefficient A address is used since it is the first one
		// and this assumes that all stored values are located in one 
		// sector
		if (pCalDataSectorErase != NULL)
			pCalDataSectorErase(ADDRESS_RESISTIVE_TOUCH_COEFA);

    	pCalDataWrite(_trA, ADDRESS_RESISTIVE_TOUCH_COEFA);
    	pCalDataWrite(_trB, ADDRESS_RESISTIVE_TOUCH_COEFB);
    	pCalDataWrite(_trC, ADDRESS_RESISTIVE_TOUCH_COEFC);
    	pCalDataWrite(_trD, ADDRESS_RESISTIVE_TOUCH_COEFD);
    	pCalDataWrite(mchpTouchScreenVersion, ADDRESS_RESISTIVE_TOUCH_VERSION);
    	
 	}
 
}

/*********************************************************************
* Function: void TouchLoadCalibration(void)
*
* PreCondition: Non-volatile memory initialization function must be called before
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: loads calibration parameters from non-volatile memory
*
* Note: none
*
********************************************************************/
void TouchLoadCalibration(void)
{
	if (pCalDataRead != NULL)
	{
    	_trA = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_COEFA);
    	_trB = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_COEFB);
    	_trC = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_COEFC);
    	_trD = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_COEFD);
	}
}
#endif
/*********************************************************************
* Function: void TouchGetCalPoints(void)
*
* PreCondition: InitGraph() must be called before
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: gets values for 3 touches
*
* Note: none
*
********************************************************************/
void TouchCalculateCalPoints(WORD *xTouch, WORD *yTouch, WORD *xPoint, WORD *yPoint)
{

	long	trA, trB, trC, trD;						// variables for the coefficients 
	long    trAhold, trBhold, trChold, trDhold;
    long 	test1, test2; 							// temp variables (must be signed type)

	// calculate points transfer functiona
	// based on two simultaneous equations solve for the 
	// constants
	
	// use sample points 1 and 4
	// Dy1 = aTy1 + b; Dy4 = aTy4 + b 
	// Dx1 = cTx1 + d; Dy4 = aTy4 + b

	test1 = (long)yPoint[0] - (long)yPoint[3];
	test2 = (long)yTouch[0] - (long)yTouch[3];
	
	trA = ((long)(test1 * SCALE_FACTOR) / test2);
	trB = ((long)((long)yPoint[0] * SCALE_FACTOR) - (trA * (long)yTouch[0]));
	
	test1 = (long)xPoint[0] - (long)xPoint[2];
	test2 = (long)xTouch[0] - (long)xTouch[2];

	trC = ((long)(test1 * SCALE_FACTOR) / test2);
	trD = ((long)((long)xPoint[0] * SCALE_FACTOR) - (trC * (long)xTouch[0]));

	trAhold = trA; 
	trBhold = trB; 
	trChold = trC; 
	trDhold = trD; 

	// use sample points 2 and 3
	// Dy2 = aTy2 + b; Dy3 = aTy3 + b 
	// Dx2 = cTx2 + d; Dy3 = aTy3 + b

	test1 = (long)yPoint[1] - (long)yPoint[2];
	test2 = (long)yTouch[1] - (long)yTouch[2];

	trA = ((long)(test1 * SCALE_FACTOR) / test2);
	trB = ((long)((long)yPoint[1] * SCALE_FACTOR) - (trA * (long)yTouch[1]));

	test1 = (long)xPoint[1] - (long)xPoint[3];
	test2 = (long)xTouch[1] - (long)xTouch[3];

	trC = ((long)((long)test1 * SCALE_FACTOR) / test2);
	trD = ((long)((long)xPoint[1] * SCALE_FACTOR) - (trC * (long)xTouch[1]));


	// get the average and use the average
	trA = (trA + trAhold) >> 1;
	trB = (trB + trBhold) >> 1;
	trC = (trC + trChold) >> 1;
	trD = (trD + trDhold) >> 1;
	
    _trA = (SHORT)trA;
	_trB = (SHORT)trB;
	_trC = (SHORT)trC;
	_trD = (SHORT)trD;
	
}

/*********************************************************************
* Function: void TouchGetCalPoints(void)
*
* PreCondition: InitGraph() must be called before
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: gets values for 3 touches
*
* Note: none
*
********************************************************************/
void TouchCalHWGetPoints(void)
{
	#define TOUCH_DIAMETER	10
	#define SAMPLE_POINTS   4

    XCHAR   calStr1[] = {'o','n',' ','t','h','e',' ','f','i','l','l','e','d',0};
    XCHAR   calStr2[] = {'c','i','r','c','l','e',0};
    XCHAR  	calTouchPress[] = {'P','r','e','s','s',0};
    XCHAR   calTouchHold[] = {'H','o','l','d',0};
    XCHAR   calTouchRelease[] = {'R','e','l','e','a','s','e',0};
    SHORT   counter;

    WORD    tx[SAMPLE_POINTS], ty[SAMPLE_POINTS];
    WORD    dx[SAMPLE_POINTS], dy[SAMPLE_POINTS];
    WORD    textHeight, msgX, msgY;

	SetFont((void *) &FONTDEFAULT);
    SetColor(BRIGHTRED);

    textHeight = GetTextHeight((void *) &FONTDEFAULT);

    while
    (
        !OutTextXY
            (
                (GetMaxX() - GetTextWidth((XCHAR *)calStr1, (void *) &FONTDEFAULT)) >> 1,
                (GetMaxY() >> 1),
                (XCHAR *)calStr1
            )
    );

    while
    (
        !OutTextXY
            (
                (GetMaxX() - GetTextWidth((XCHAR *)calStr2, (void *) &FONTDEFAULT)) >> 1,
                ((GetMaxY() >> 1) + textHeight),
                (XCHAR *)calStr2
            )
    );



    // calculate center points (locate them at 15% away from the corners)
	// draw the four touch points

    dy[0] = dy[1] = CAL_Y_INSET; 
	dy[2] = dy[3] = (GetMaxY() - CAL_Y_INSET);
	dx[0] = dx[3] = CAL_X_INSET; 
	dx[1] = dx[2] = (GetMaxX() - CAL_X_INSET);


    msgY = ((GetMaxY() >> 1) - textHeight);
	
    for(counter = 0; counter < SAMPLE_POINTS; counter++)
    {
    
		// redraw the filled circle to unfilled (previous calibration point)
        if (counter > 0)
        {
        	SetColor(WHITE);
	    	while(!(FillCircle(dx[counter-1], dy[counter-1], TOUCH_DIAMETER-3)));
	    } 

		// draw the new filled circle (new calibration point)
        SetColor(BRIGHTRED);
	    while(!(Circle(dx[counter], dy[counter], TOUCH_DIAMETER)));
	    while(!(FillCircle(dx[counter], dy[counter], TOUCH_DIAMETER-3)));

		// show points left message
        msgX = (GetMaxX() - GetTextWidth((XCHAR *)calTouchPress, (void *) &FONTDEFAULT)) >> 1;
		TouchShowMessage(calTouchPress, BRIGHTRED, msgX, msgY);

        // Wait for press
        do {} 
    	    while((TouchGetRawX() == -1) && (TouchGetRawY() == -1));

		// erase points left message
		TouchShowMessage(calTouchPress, WHITE, msgX, msgY);
        
		// display HOLD message
	    msgX = (GetMaxX() - GetTextWidth((XCHAR *)calTouchHold, (void *) &FONTDEFAULT)) >> 1;
		TouchShowMessage(calTouchHold, BRIGHTRED, msgX, msgY);

       	// start the touch delay 
        DelayMs(CALIBRATION_DELAY<<1);

		#ifdef TOUCHSCREEN_RESISTIVE_FLIP_Y
        ty[3 - counter] = TouchGetRawY();
		#else
        ty[counter] = TouchGetRawY();
        #endif

        #ifdef TOUCHSCREEN_RESISTIVE_FLIP_X
        tx[3 - counter] = TouchGetRawX();
		#else
        tx[counter] = TouchGetRawX();
        #endif


		// erase HOLD message
		TouchShowMessage(calTouchHold, WHITE, msgX, msgY);

		// show RELEASE message
	    msgX = (GetMaxX() - GetTextWidth((XCHAR *)calTouchRelease, (void *) &FONTDEFAULT)) >> 1;
		TouchShowMessage(calTouchRelease, BRIGHTRED, msgX, msgY);

        // Wait for release
        do {} 
        	while((TouchGetRawX() != -1) && (TouchGetRawY() != -1));

        DelayMs(CALIBRATION_DELAY);
		// erase RELEASE message
		TouchShowMessage(calTouchRelease, WHITE, msgX, msgY);
       
    }

    // Wait for release
	do {} 
		while((TouchGetRawX() != -1) && (TouchGetRawY() != -1));

	
    TouchCalculateCalPoints(tx, ty, dx, dy);
    
    #ifdef ENABLE_DEBUG_TOUCHSCREEN
        TouchScreenResistiveTestXY();
    #endif
}


/*********************************************************************
* Function: void TouchScreenResistiveTestXY(void)
*
* PreCondition: TouchHardwareInit has been called
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: prints raw x,y calibrated x,y and calibration factors to screen
*
* Note: modify pre-processor macro to include/exclude this test code
*       a common place to call this from is at the end of TouchCalHWGetPoints()
*
********************************************************************/
#ifdef ENABLE_DEBUG_TOUCHSCREEN
#include <stdio.h>
void TouchScreenResistiveTestXY(void)
{
    #define BUFFCHARLEN 60
    char buffChar[BUFFCHARLEN];
    WORD buffCharW[BUFFCHARLEN];
    unsigned char i;
    SHORT tempXX, tempYY,tempXX2,tempYY2, calXX, calYY;
    tempXX = tempYY = tempXX2 = tempYY2 = -1;
    while(1)
    {
        do{tempXX = TouchGetRawX(); tempYY = TouchGetRawY();}
    	while((tempXX == -1) && (tempYY == -1));   
        
        // use this to always show the values even if not pressing the screen
        //tempXX = TouchGetRawX(); 
        //tempYY = TouchGetRawY();
        
        calXX = TouchGetX();
        calYY = TouchGetY();
        
        if((tempXX != tempXX2)||(tempYY != tempYY2))
        {
            SetColor(WHITE);
            ClearDevice();
            SetColor(BRIGHTRED);
            sprintf(buffChar,"raw_x=%d, raw_y=%d",(WORD)tempXX, (WORD)tempYY);
			
            #ifdef (USE_MULTIBYTECHAR)
              for(i = 0; i < BUFFCHARLEN;i++)
              {
                buffCharW[i] = buffChar[i];
              }
              while(!OutTextXY(0,0,(XCHAR*)buffCharW));
            #else
              while(!OutTextXY(0,0,(XCHAR*)buffChar));
            #endif
            
            sprintf(buffChar,"cal_x=%d, cal_y=%d",(WORD)calXX, (WORD)calYY);
            #ifdef (USE_MULTIBYTECHAR)
              for(i = 0; i < BUFFCHARLEN;i++)
              {
                buffCharW[i] = buffChar[i];
              }
              while(!OutTextXY(0,40,(XCHAR*)buffCharW));
            #else
              while(!OutTextXY(0,40,(XCHAR*)buffChar));
            #endif
            
            sprintf(buffChar,"_tr:A=%d,B=%d,C=%d,D=%d",(WORD)_trA,(WORD)_trB,(WORD)_trC,(WORD)_trD);
            #ifdef (USE_MULTIBYTECHAR)
              for(i = 0; i < BUFFCHARLEN;i++)
              {
                buffCharW[i] = buffChar[i];
              }
              while(!OutTextXY(0,80,(XCHAR*)buffCharW));
            #else
              while(!OutTextXY(0,80,(XCHAR*)buffChar));
            #endif

        }
        
        tempXX2=tempXX;
        tempYY2=tempYY;
    }
}
#endif //#ifdef ENABLE_DEBUG_TOUCHSCREEN


#endif // #if defined (USE_TOUCHSCREEN_RESISTIVE)

