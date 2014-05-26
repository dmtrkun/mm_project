/*********************************************************************
 *                  LCC Graphics Driver (mchpGfxLCC)
 *********************************************************************
 * FileName:        mchpGfxLCC.h
 * Dependencies:    plib.h
 *
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32 v1 or higher
 *                  MPLAB IDE v8 or higher
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ********************************************************************/

#ifndef _mchpGfxLCC_H
    #define _mchpGfxLCC_H

    #if defined(__PIC32MX__)
        #include <plib.h>
        #define PMDIN1  PMDIN
    #endif
    
    #include "GraphicsConfig.h"
    #include "GenericTypeDefs.h"

    #ifdef USE_PALETTE
        #include "Graphics/Palette.h"
    #endif

    #ifndef DISP_HOR_RESOLUTION
        #error DISP_HOR_RESOLUTION must be defined in HardwareProfile.h
    #endif
    #ifndef DISP_VER_RESOLUTION
        #error DISP_VER_RESOLUTION must be defined in HardwareProfile.h
    #endif
    #ifndef COLOR_DEPTH
        #error COLOR_DEPTH must be defined in HardwareProfile.h
    #endif
    #ifndef DISP_ORIENTATION
        #error DISP_ORIENTATION must be defined in HardwareProfile.h
    #endif

/*********************************************************************
* Overview: Horizontal synchronization timing in pixels
*                  (from the glass datasheet).
*********************************************************************/

    #ifndef DISP_HOR_PULSE_WIDTH
        #error DISP_HOR_PULSE_WIDTH must be defined in HardwareProfile.h
    #endif
    #ifndef DISP_HOR_BACK_PORCH
        #error DISP_HOR_BACK_PORCH must be defined in HardwareProfile.h
    #endif
    #ifndef DISP_HOR_FRONT_PORCH
        #error DISP_HOR_FRONT_PORCH must be defined in HardwareProfile.h
    #endif

/*********************************************************************
* Overview: Vertical synchronization timing in lines
*                  (from the glass datasheet).
*********************************************************************/
    #ifndef DISP_VER_PULSE_WIDTH
        #error DISP_VER_PULSE_WIDTH must be defined in HardwareProfile.h
    #endif
    #ifndef DISP_VER_BACK_PORCH
        #error DISP_VER_BACK_PORCH must be defined in HardwareProfile.h
    #endif
    #ifndef DISP_VER_FRONT_PORCH
        #error DISP_VER_FRONT_PORCH must be defined in HardwareProfile.h
    #endif

/*********************************************************************
* PARAMETERS VALIDATION
*********************************************************************/
    #if (DISP_HOR_RESOLUTION % 8) != 0
        #error Horizontal resolution must be divisible by 8.
    #endif
    #if (DISP_ORIENTATION != 0) && (DISP_ORIENTATION != 180) && (DISP_ORIENTATION != 90) && (DISP_ORIENTATION != 270)
        #error The display orientation selected is not supported. It can be only 0,90,180 or 270.
    #endif


#endif // _mchpGfxLCC_H
