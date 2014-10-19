/*****************************************************************************
 *****************************************************************************
 * FileName:        taskTouchScreen.c
 *
 *****************************************************************************/
#define TASKTOUCHSCREEN_PUB

#include "include.h"
#include <GenericTypeDefs.h>
#include "HardwareProfile.h"
#include "framework/gfx/gfx.h"
#include "taskGraphics.h"
#include "taskTouchScreen.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"


// sampling interval for the Timer routine
//#define PRESS_THRESHOLD 256		// pressure threshold for the touchscreen
#define PRESS_THRESHOLD 500		// pressure threshold for the touchscreen

///////////////////////////////////////////////////////////////////
// Local Variables and prototypes
void TouchGetCalPoints(WORD* ax, WORD* ay, WORD radius);

// Max/Min Values
//volatile WORD _calXMin = XMINCAL;
//volatile WORD _calXMax = XMAXCAL;
//volatile WORD _calYMin = YMINCAL;
//volatile WORD _calYMax = YMAXCAL;

// current ADC values for X and Y channels and pot
// adcPot and adcTemp can only be accessed via atomic actions
// however adcX and adcY are updated as a pair so tasks accessing
// their values must be written accordingly
volatile SHORT adcX		= -1;	// current X or -1 for not pressed
volatile SHORT adcY		= -1;	// same for Y
volatile SHORT adcPot	= 0;	// Potentiometer reading
volatile SHORT adcTemp	= 0;	// Temperature reading
volatile SHORT prevX = -1;
volatile SHORT prevY = -1;
volatile SHORT x, y;
extern volatile long xcor, ycor;


// semaphore to regulate access to the FLASH to read calibration
// constants and one for accessing the QVGA display
extern xSemaphoreHandle FLASHSemaphore;
//extern xSemaphoreHandle QVGAMutSemaphore;

//extern const FONT_FLASH GOLFontDefault;
//extern const FONT_FLASH GOLMediumFont;
//extern const FONT_FLASH GOLSmallFont;


// handle to the task
//xTaskHandle hTOUCHTask;

// this semaphore is used to indicate when there is new data to be 
// processed by the touch screen task

void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)
{
	portBASE_TYPE taskWoken = pdFALSE;
//	// clear the interrupt flag
//		IFS1bits.INT1IF = 0;

#if 0	
	TouchDetectPosition();
	// convert the reading and signal the semaphore if an action detected
	x = TouchGetX(); y = TouchGetY();
	if ((x == -1) || (y == -1)) {
		x = -1; y = -1;
	}
	
	if ((x != prevX) && (y != prevY)) {
		///////////////////////////////////////////////////////////
		// change since last cycle so send wake-up to touchscreen task
		// we use the hADCSemaphore to signal the touchscreen task
		// that it needs to do some processing
		xSemaphoreGiveFromISR(hADCSemaphore, &taskWoken);	
	}
#endif	
	xSemaphoreGiveFromISR(hADCSemaphore, &taskWoken);	
	// this macro will allow a higher priority task than the one originally
	// interrupted to be woken after servicing the interrupt
//	// clear the interrupt flag
	IFS1bits.INT1IF = 0;
	portEND_SWITCHING_ISR(taskWoken);		

}


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
#if 1
void TouchLoadCalibration(void)
{
#if (GRAPHICS_PICTAIL_VERSION == 3)
    _calXMin = SST25ReadWord(ADDRESS_XMIN);
    _calXMax = SST25ReadWord(ADDRESS_XMAX);
    _calYMin = SST25ReadWord(ADDRESS_YMIN);
    _calYMax = SST25ReadWord(ADDRESS_YMAX);
#else
//	SST39PMPInit();

		_calXMin = DA210DEVBOARD_SST39LF400ReadWord(ADDRESS_XMIN);
    _calXMax = DA210DEVBOARD_SST39LF400ReadWord(ADDRESS_XMAX);
    _calYMin = DA210DEVBOARD_SST39LF400ReadWord(ADDRESS_YMIN);
    _calYMax = DA210DEVBOARD_SST39LF400ReadWord(ADDRESS_YMAX);

///    LCDPMPInit();
#endif
}
#endif
/*********************************************************************
* Function: void TouchStoreCalibration(void)
*
* PreCondition: EEPROMInit() must be called before, the EEPROM
*				semaphore must be held
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
#if 1
void TouchStoreCalibration(void)
{
#if (GRAPHICS_PICTAIL_VERSION == 3)
    SST25SectorErase(ADDRESS_VERSION); // erase 4K sector
    SST25WriteWord(ADDRESS_XMIN, _calXMin);
    SST25WriteWord(ADDRESS_XMAX, _calXMax);
    SST25WriteWord(ADDRESS_YMIN, _calYMin);
    SST25WriteWord(ADDRESS_YMAX, _calYMax);
    SST25WriteWord(ADDRESS_VERSION, GRAPHICS_LIBRARY_VERSION);
#else
//	SST39PMPInit();
    DA210DEVBOARD_SST39LF400SectorErase(ADDRESS_VERSION); // erase 4K sector
    DA210DEVBOARD_SST39LF400WriteWord(_calXMin, ADDRESS_XMIN);
    DA210DEVBOARD_SST39LF400WriteWord(_calXMax, ADDRESS_XMAX);
    DA210DEVBOARD_SST39LF400WriteWord(_calYMin, ADDRESS_YMIN);
    DA210DEVBOARD_SST39LF400WriteWord(_calYMax, ADDRESS_YMAX);
    DA210DEVBOARD_SST39LF400WriteWord(GRAPHICS_LIBRARY_VERSION, ADDRESS_VERSION);
//	LCDPMPInit();
#endif
}
#endif
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
void TouchCalibration(void)
{
#if 0
    static const GFX_XCHAR scr1StrLn1[] = {'I','M','P','O','R','T','A','N','T','.',0};
	static const GFX_XCHAR scr1StrLn2[] = {"Now calibration"};
	static const GFX_XCHAR scr1StrLn3[] = {"will be performed. Touch"};
	static const GFX_XCHAR scr1StrLn4[] = {"EXACTLY at the positions"};
	static const GFX_XCHAR scr1StrLn5[] = {"shown by arrows."};
	static const GFX_XCHAR scr1StrLn6[] = {"Touch screen to continue"};
	
	static const GFX_XCHAR scr2StrLn1[] = {'H','o','l','d',' ','S','3',' ','b','u','t','t','o','n',' ','a','n','d',0};
	static const GFX_XCHAR scr2StrLn2[] = {'p','r','e','s','s',' ','M','C','L','R',' ','r','e','s','e','t','(','S','1',')',0};
	static const GFX_XCHAR scr2StrLn3[] = {'t','o',' ','R','E','P','E','A','T',' ','t','h','e',' ','c','a','l','i','b','r','a','t','i','o','n',0};
	static const GFX_XCHAR scr2StrLn4[] = {'p','r','o','c','e','d','u','r','e','.',0};
	
	SHORT counter;
	SHORT x, y;
	WORD ax[3], ay[3];
	SHORT textHeight;
	GFX_XCHAR str[30];

	     
	// Initialize display
    InitGraph();
	SetFont((void*) &GOLFontDefault);
	textHeight = GetTextHeight((void*) &GOLFontDefault);
//	SetFont((void *) &FONTDEFAULT);
//	textHeight = GetTextHeight((void *) &FONTDEFAULT);

	SetColor(WHITE);
	ClearDevice();
	
	SetFont((void *) &FONTDEFAULT);
	textHeight = GetTextHeight((void *) &FONTDEFAULT);
	
    SetColor(BRIGHTRED);
    OutTextXY(0,0*textHeight, (GFX_XCHAR*)scr1StrLn1);
    SetColor(BLACK);
    OutTextXY(0,1*textHeight, (GFX_XCHAR*)scr1StrLn2);
    OutTextXY(0,2*textHeight, (GFX_XCHAR*)scr1StrLn3);
    OutTextXY(0,3*textHeight, (GFX_XCHAR*)scr1StrLn4);
    OutTextXY(0,4*textHeight, (GFX_XCHAR*)scr1StrLn5);
    SetColor(BRIGHTRED);
    OutTextXY(0,6*textHeight, (GFX_XCHAR*)scr1StrLn6);
	
	// wait for touch
	do {
		vTaskDelay(20 / portTICK_RATE_MS);
		x = ADCGetX(); y = ADCGetY();
	} while ((y == -1) || (x == -1));
	
	vTaskDelay(500 / portTICK_RATE_MS);
	
	SetColor(WHITE);
	ClearDevice();
	SetColor(BRIGHTRED);
	
    Line(5,5,5,15);
    Line(4,5,4,15);
    Line(6,5,6,15);

    Line(5,5,15,5);
    Line(5,4,15,4);
    Line(5,6,15,6);

    Line(5,6,15,16);
    Line(5,4,15,14);
    Line(5,5,15,15);

	TouchGetCalPoints(ax, ay, 10);
#if 0    
	// Get min X and min Y
    _calYMin = 0xFFFF;
    _calXMin = 0xFFFF;
    for(counter=0; counter<3; counter++){
        if(_calYMin > ay[counter])
            _calYMin = ay[counter];

        if(_calXMin > ax[counter])
            _calXMin = ax[counter];
    }
#else	
	
	// Get min X and max Y
    _calYMax = 0;
    _calXMin = 0xFFFF;
    for(counter=0; counter<3; counter++){
        if(_calYMax < ay[counter])
            _calYMax = ay[counter];

        if(_calXMin > ax[counter])
            _calXMin = ax[counter];
    }
#endif	
    
	SetColor(WHITE);
    ClearDevice();
	SetColor(BRIGHTRED);
    
    Line(5,GetMaxY()-5,5,GetMaxY()-15);
    Line(4,GetMaxY()-5,4,GetMaxY()-15);
    Line(6,GetMaxY()-5,6,GetMaxY()-15);

    Line(5,GetMaxY()-5,15,GetMaxY()-5);
    Line(5,GetMaxY()-4,15,GetMaxY()-4);
    Line(5,GetMaxY()-6,15,GetMaxY()-6);

    Line(5,GetMaxY()-6,15,GetMaxY()-16);
    Line(5,GetMaxY()-4,15,GetMaxY()-14);
    Line(5,GetMaxY()-5,15,GetMaxY()-15);
	
    TouchGetCalPoints(ax, ay,10);
	
#if 0    
	// Get max Y
    _calYMax = 0;
    for(counter=0; counter<3; counter++){
        if(_calYMax < ay[counter])
            _calYMax = ay[counter];
    }
#else
	// Get min Y
    _calYMin = 0xffff;
    for(counter=0; counter<3; counter++){
        if(_calYMin > ay[counter])
            _calYMin = ay[counter];
    }
#endif
    SetColor(WHITE);
    ClearDevice();
    SetColor(BRIGHTRED);    

    Line(GetMaxX()-5,GetMaxY()/2-5,GetMaxX()-5,GetMaxY()/2-15);
    Line(GetMaxX()-4,GetMaxY()/2-5,GetMaxX()-4,GetMaxY()/2-15);
    Line(GetMaxX()-6,GetMaxY()/2-5,GetMaxX()-6,GetMaxY()/2-15);

    Line(GetMaxX()-5,GetMaxY()/2-5,GetMaxX()-15,GetMaxY()/2-5);
    Line(GetMaxX()-5,GetMaxY()/2-4,GetMaxX()-15,GetMaxY()/2-4);
    Line(GetMaxX()-5,GetMaxY()/2-6,GetMaxX()-15,GetMaxY()/2-6);

    Line(GetMaxX()-5,GetMaxY()/2-6,GetMaxX()-15,GetMaxY()/2-16);
    Line(GetMaxX()-5,GetMaxY()/2-4,GetMaxX()-15,GetMaxY()/2-14);
    Line(GetMaxX()-5,GetMaxY()/2-5,GetMaxX()-15,GetMaxY()/2-15);

    TouchGetCalPoints(ax, ay,10);

    // Get max X
    _calXMax = 0;
    for(counter=0; counter<3; counter++){
        if(_calXMax < ax[counter])
            _calXMax = ax[counter];
    }

    SetColor(WHITE);
    ClearDevice();
    SetColor(BLACK);
    
    OutTextXY(10,1*textHeight,(GFX_XCHAR*)scr2StrLn1);
    OutTextXY(10,2*textHeight,(GFX_XCHAR*)scr2StrLn2);
    OutTextXY(10,3*textHeight,(GFX_XCHAR*)scr2StrLn3);
    OutTextXY(10,4*textHeight,(GFX_XCHAR*)scr2StrLn4);
	
	SetFont((void*) &GOLMediumFont);
	textHeight = GetTextHeight((void*) &GOLMediumFont);
	SetColor(BRIGHTRED);
    OutTextXY(10,6*textHeight,(GFX_XCHAR*)scr1StrLn6);
	sprintf(str,"xMax = %04d; xMin = %04d",_calXMax,_calXMin);
	OutTextXY(10,7*textHeight,str);
	sprintf(str,"yMax = %04d;  yMin = %04d",_calYMax,_calYMin);
	OutTextXY(10,8*textHeight,str);

    // Wait for touch
    do{
        x=ADCGetX(); y=ADCGetY();
    } while ((y == -1) || (x == -1));

    vTaskDelay(500 / portTICK_RATE_MS);

    SetColor(BLACK);
    ClearDevice();
#endif
}

#if 0
/*********************************************************************
* Function: void TouchGetCalPoints(WORD* ax, WORD* ay)
*
* PreCondition: InitGraph() must be called before
*
* Input: ax - pointer to array receiving 3 X touch positions
*        ay - pointer to array receiving 3 Y touch positions
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
void TouchGetCalPoints(WORD* ax, WORD* ay)
{
	static const GFX_XCHAR calStr[] = {'C','A','L','I','B','R','A','T','I','O','N',0};
	GFX_XCHAR calTouchLeft[] = {'3',' ','t','o','u','c','h','e','s',' ','l','e','f','t',0};
	SHORT counter;
	SHORT x,y;

    SetFont((void*)&GOLFontDefault);
    SetColor(BRIGHTRED);
    OutTextXY((GetMaxX() - GetTextWidth((GFX_XCHAR*) calStr,(void*) &GOLFontDefault)) >> 1,
              (GetMaxY() - GetTextHeight((void*) &GOLFontDefault)) >> 1,
              (GFX_XCHAR*) calStr);

    for(counter = 0; counter < 3; counter++) {
        SetColor(BRIGHTRED);
        calTouchLeft[0] = '3' - counter;

        OutTextXY((GetMaxX() - GetTextWidth(calTouchLeft, (void*)&GOLFontDefault)) >> 1,
                  (GetMaxY() + GetTextHeight((void*) &GOLFontDefault)) >> 1,
                   calTouchLeft);

        // Wait for press
        do{
            x = ADCGetX(); y = ADCGetY();
        }while((y == -1) || (x == -1));

         *(ax + counter) = x; *(ay + counter) = y;
     
        // Wait for release
        do{
            x = ADCGetX(); y = ADCGetY();
        } while ((y != -1) && (x != -1));

        SetColor(WHITE);
        OutTextXY((GetMaxX() - GetTextWidth(calTouchLeft, (void*) &GOLFontDefault)) >> 1,
                  (GetMaxY() + GetTextHeight((void*) &GOLFontDefault)) >> 1,
                   calTouchLeft);

        vTaskDelay(500 / portTICK_RATE_MS);
    }
}
#endif
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
#if 0
SHORT TouchGetX(void)
{
	long result;

    result = ADCGetX();

	if (result >= 0) {
    	result -= _calXMin;
    	result *= GetMaxX();
    	result = result / ((long) _calXMax - (long) _calXMin);
 
#ifdef FLIP_X
        result = GetMaxX()- result;
#endif
    }
    
    return result;
}
#endif
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
#if 0
SHORT TouchGetY(void)
{
	long result;

    result = ADCGetY();

    if (result >= 0) {
        result -= _calYMin;
        result *= GetMaxY();
        result = result / ((long) _calYMax - (long) _calYMin);

#ifdef FLIP_Y
        result = GetMaxY()- result;
#endif
    }
    
    return result;
}
#endif

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
 *					events from the graphics drawing improving
 *					overall responsiveness
 *
 * Note:            
 ********************************************************************/
void taskTouchScreen(void* pvParameter)
{
	WORD version;
	static GRAPHICS_MSG msg;
	// notify task started
//	UARTprintf("TOUCH: Task Started.\r\n");

//	vTaskSetApplicationTaskTag( NULL, ( void * ) 't' );	


	// create the semaphore used to signal touch activity from the ADC ISR
	vSemaphoreCreateBinary(hADCSemaphore);
	xSemaphoreTake(hADCSemaphore, portMAX_DELAY);

	// we may need to access the QVGA display to perform calibration
	// To prevent the Graphics task running we immediately take
	// the QVGA semaphore and only return it when startup is complete
	xSemaphoreTake(QVGAMutSemaphore, portMAX_DELAY);
	

	// read the configuration information from the FLASH 
//	if (xSemaphoreTake(FLASHSemaphore, 0) != pdTRUE) {
//		UARTprintf("TOUCH: Unable to access FLASH\r\n");
//		vTaskSuspend(NULL);
//	}
	
	#if (GRAPHICS_PICTAIL_VERSION == 3)
		version = SST25ReadWord(ADDRESS_VERSION);
	#else
//		SST39PMPInit();
		version = DA210DEVBOARD_SST39LF400ReadWord(ADDRESS_VERSION);
//		version = SST39ReadWord(ADDRESS_VERSION);
//		version = GRAPHICS_LIBRARY_VERSION;
//		LCDPMPInit();
	#endif

#if 1	
	TouchHardwareInit(0);
	
	ANSC &= ~0x0010;   //RC4
	__builtin_write_OSCCONL(OSCCON & 0xbf);
	RPINR0bits.INT1R = 41;
 //	RPOR13bits.RP26R = 18; //OC1
	__builtin_write_OSCCONL(OSCCON | 0x40);	
	INTCON2bits.INT1EP = 0; //Polarity - interrupt on pozitive edge	
	IFS1bits.INT1IF = 0;
	IEC1bits.INT1IE = 1;
	IPC5bits.INT1IP = 4;
	
	
	
	
	// check the version, if it is not correct then we take control
	// of the QVGA display and perform touchscreen calibration
//	if ((version != GRAPHICS_LIBRARY_VERSION)/* || (BUTTON3_IO == 0)*/) {
//		UARTprintf("TOUCH: Performing calibration\r\n");
		
		// call the calibration routine
//		TouchCalibration();
//		TouchStoreCalibration();
//	}
	
//	TouchLoadCalibration();	
	
	// we are done with the FLASH now so release the semaphore
//	xSemaphoreGive(FLASHSemaphore);
#endif	
	
	// release control of the QVGA display
	xSemaphoreGive(QVGAMutSemaphore);
	// any messages that we send will always be of this type
	msg.cmd = MSG_TOUCH_EVENT;
	msg.data.golMsg.type = TYPE_TOUCHSCREEN;
	
	// read the touchscreen. If the screen has been
	// touched then send a message to the graphics display
	// task. 
	while (1) {
//		vTaskDelay(10);
//		taskYIELD();
		///////////////////////////////////////////////////////////
		// use a semaphore to wait for updates from the ISR
		// block forever waiting for hADCSemaphore to arrive
		xSemaphoreTake(hADCSemaphore, portMAX_DELAY);

#if 1	
	TouchDetectPosition();
	// convert the reading and signal the semaphore if an action detected
	x = TouchGetX(); y = TouchGetY();
	if ((x == -1) || (y == -1)) {
		x = -1; y = -1;
	}
	
//	if ((x != prevX) && (y != prevY)) {
		///////////////////////////////////////////////////////////
		// change since last cycle so send wake-up to touchscreen task
		// we use the hADCSemaphore to signal the touchscreen task
		// that it needs to do some processing
//		xSemaphoreGiveFromISR(hADCSemaphore, &taskWoken);	
//	}
#endif	
		
		   
		// analyze the current screen state and send an update to the
		// graphics task
		// something has changed (press, release or move)
		if ((prevX == -1) && (prevY == -1)) {
			// screen pressed
			msg.data.golMsg.uiEvent = EVENT_PRESS;
			msg.data.golMsg.param1 = x;
			msg.data.golMsg.param2 = y;
		} else if ((x == -1) && (y== -1)) {
			// screen released
			msg.data.golMsg.uiEvent = EVENT_RELEASE;
			msg.data.golMsg.param1 = prevX;
			msg.data.golMsg.param2 = prevY;
		} else {
			// screen moved
			msg.data.golMsg.uiEvent = EVENT_MOVE;
			msg.data.golMsg.param1 = x;
			msg.data.golMsg.param2 = y;				
		}
		
		// send a message to update the graphics task
		xQueueSend(hQVGAQueue, &msg, portMAX_DELAY);
		prevX = x; prevY = y;		
	}	
}

