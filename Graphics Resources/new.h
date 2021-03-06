/*****************************************************************************
 * FileName:        new.h
 * Processor:       PIC24F, PIC24H, dsPIC
 * Compiler:        MPLAB C30 (see release notes for tested revision)
 * Linker:          MPLAB LINK30
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright(c) 2012 Microchip Technology Inc.  All rights reserved.
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
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * AUTO-GENERATED CODE:  Graphics Resource Converter version: 3.17.47
 *****************************************************************************/

#ifndef NEW_H_FILE
#define NEW_H_FILE
/*****************************************************************************
 * SECTION:  Includes
 *****************************************************************************/
#include <Graphics/Graphics.h>
#include "HardwareProfile.h"

/*****************************************************************************
 * SECTION:  Graphics Library Firmware Check
 *****************************************************************************/
#if(GRAPHICS_LIBRARY_VERSION != 0x0304)
#warning "It is suggested to use Graphics Library verson 3.04 with this version of GRC."
#endif

/*****************************************************************************
 * SECTION: Hardware Profile
 * Place these byte count defines in the application level hardware profile header file
 *
 * #define GFX_DECOMPRESSED_BUFFER_SIZE     (38034)
 *****************************************************************************/

/*****************************************************************************
 * This is an error check for the color depth
 *****************************************************************************/
#if (COLOR_DEPTH > 16)
#error "Color Depth needs to be 16 to correctly use these resources"
#endif


/*****************************************************************************
 * This is a unique marker to verify the external memory data
 * The marker is a total of 8 bytes in length starting at the location GRC_CRC32_EXTERNAL_ADDR.
 * The first four bytes, starting at GRC_CRC32_EXTERNAL_ADDR, will always equal 'M', 'C', 'H', 'P'.
 * The next four byte is the generated 32-bit CRC.  The application can compare the value read from the
 * external memory to the value of GRC_CRC32_EXTERNAL_MARKER to verify that the data is valid.
 *****************************************************************************/
#define GRC_CRC32_EXTERNAL_MARKER 0x8CBE44A5ul
#define GRC_CRC32_EXTERNAL_ADDR 0x00013780ul

/*****************************************************************************
 * SECTION:  BITMAPS
 *****************************************************************************/

/*********************************
 * Bitmap Structure
 * Label: Intro
 * Description:  226x166 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Intro;
#define Intro_WIDTH     (226)
#define Intro_HEIGHT    (166)
#define Intro_SIZE      (38034)
/*********************************
 * Bitmap Structure
 * Label: Param_btn
 * Description:  224x26 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Param_btn;
#define Param_btn_WIDTH     (224)
#define Param_btn_HEIGHT    (26)
#define Param_btn_SIZE      (6342)
/*********************************
 * Bitmap Structure
 * Label: Wait1
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Wait1;
#define Wait1_WIDTH     (28)
#define Wait1_HEIGHT    (28)
#define Wait1_SIZE      (1302)
/*********************************
 * Bitmap Structure
 * Label: Wait2
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Wait2;
#define Wait2_WIDTH     (28)
#define Wait2_HEIGHT    (28)
#define Wait2_SIZE      (1302)
/*********************************
 * Bitmap Structure
 * Label: Wait3
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Wait3;
#define Wait3_WIDTH     (28)
#define Wait3_HEIGHT    (28)
#define Wait3_SIZE      (1302)
/*********************************
 * Bitmap Structure
 * Label: Wait4
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Wait4;
#define Wait4_WIDTH     (28)
#define Wait4_HEIGHT    (28)
#define Wait4_SIZE      (1302)
/*********************************
 * Bitmap Structure
 * Label: Param_btn_press
 * Description:  224x26 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Param_btn_press;
#define Param_btn_press_WIDTH     (224)
#define Param_btn_press_HEIGHT    (26)
#define Param_btn_press_SIZE      (6342)
/*********************************
 * Bitmap Structure
 * Label: Larrow_press
 * Description:  55x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Larrow_press;
#define Larrow_press_WIDTH     (55)
#define Larrow_press_HEIGHT    (30)
#define Larrow_press_SIZE      (2168)
/*********************************
 * Bitmap Structure
 * Label: Rarrow_press
 * Description:  55x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Rarrow_press;
#define Rarrow_press_WIDTH     (55)
#define Rarrow_press_HEIGHT    (30)
#define Rarrow_press_SIZE      (2168)
/*********************************
 * Bitmap Structure
 * Label: Larrow
 * Description:  55x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Larrow;
#define Larrow_WIDTH     (55)
#define Larrow_HEIGHT    (30)
#define Larrow_SIZE      (2168)
/*********************************
 * Bitmap Structure
 * Label: Rarrow
 * Description:  55x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Rarrow;
#define Rarrow_WIDTH     (55)
#define Rarrow_HEIGHT    (30)
#define Rarrow_SIZE      (2168)
/*********************************
 * Bitmap Structure
 * Label: drug_Adrenaline
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER drug_Adrenaline;
#define drug_Adrenaline_WIDTH     (102)
#define drug_Adrenaline_HEIGHT    (54)
#define drug_Adrenaline_SIZE      (6026)
/*********************************
 * Bitmap Structure
 * Label: drug_Midazolam
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER drug_Midazolam;
#define drug_Midazolam_WIDTH     (102)
#define drug_Midazolam_HEIGHT    (54)
#define drug_Midazolam_SIZE      (6026)
/*********************************
 * Bitmap Structure
 * Label: drug_Morph_Midaz
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER drug_Morph_Midaz;
#define drug_Morph_Midaz_WIDTH     (102)
#define drug_Morph_Midaz_HEIGHT    (54)
#define drug_Morph_Midaz_SIZE      (6026)
/*********************************
 * Bitmap Structure
 * Label: drug_NoName
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER drug_NoName;
#define drug_NoName_WIDTH     (102)
#define drug_NoName_HEIGHT    (54)
#define drug_NoName_SIZE      (6026)
/*********************************
 * Bitmap Structure
 * Label: drug_Noradrenaline
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER drug_Noradrenaline;
#define drug_Noradrenaline_WIDTH     (102)
#define drug_Noradrenaline_HEIGHT    (54)
#define drug_Noradrenaline_SIZE      (6026)
/*********************************
 * Bitmap Structure
 * Label: drug_Remitentanil
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER drug_Remitentanil;
#define drug_Remitentanil_WIDTH     (102)
#define drug_Remitentanil_HEIGHT    (54)
#define drug_Remitentanil_SIZE      (6026)
/*********************************
 * Bitmap Structure
 * Label: Wait5
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Wait5;
#define Wait5_WIDTH     (28)
#define Wait5_HEIGHT    (28)
#define Wait5_SIZE      (1302)
/*********************************
 * Bitmap Structure
 * Label: Wait6
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Wait6;
#define Wait6_WIDTH     (28)
#define Wait6_HEIGHT    (28)
#define Wait6_SIZE      (1302)
/*********************************
 * Bitmap Structure
 * Label: Wait7
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Wait7;
#define Wait7_WIDTH     (28)
#define Wait7_HEIGHT    (28)
#define Wait7_SIZE      (1302)
/*********************************
 * Bitmap Structure
 * Label: Wait8
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Wait8;
#define Wait8_WIDTH     (28)
#define Wait8_HEIGHT    (28)
#define Wait8_SIZE      (1302)
/*********************************
 * Bitmap Structure
 * Label: prog_ContROV
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER prog_ContROV;
#define prog_ContROV_WIDTH     (110)
#define prog_ContROV_HEIGHT    (72)
#define prog_ContROV_SIZE      (8438)
/*********************************
 * Bitmap Structure
 * Label: prog_ContVOT
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER prog_ContVOT;
#define prog_ContVOT_WIDTH     (110)
#define prog_ContVOT_HEIGHT    (72)
#define prog_ContVOT_SIZE      (8438)
/*********************************
 * Bitmap Structure
 * Label: prog_IntROV
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER prog_IntROV;
#define prog_IntROV_WIDTH     (110)
#define prog_IntROV_HEIGHT    (72)
#define prog_IntROV_SIZE      (8438)
/*********************************
 * Bitmap Structure
 * Label: prog_IntVOT
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER prog_IntVOT;
#define prog_IntVOT_WIDTH     (110)
#define prog_IntVOT_HEIGHT    (72)
#define prog_IntVOT_SIZE      (8438)
/*********************************
 * Bitmap Structure
 * Label: prog_PCA
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER prog_PCA;
#define prog_PCA_WIDTH     (110)
#define prog_PCA_HEIGHT    (72)
#define prog_PCA_SIZE      (8438)
/*********************************
 * Bitmap Structure
 * Label: prog_Step
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER prog_Step;
#define prog_Step_WIDTH     (110)
#define prog_Step_HEIGHT    (72)
#define prog_Step_SIZE      (8438)
/*********************************
 * Bitmap Structure
 * Label: clock_img
 * Description:  128x128 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER clock_img;
#define clock_img_WIDTH     (128)
#define clock_img_HEIGHT    (128)
#define clock_img_SIZE      (16902)
/*********************************
 * Bitmap Structure
 * Label: Pointer_img
 * Description:  12x12 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Pointer_img;
#define Pointer_img_WIDTH     (12)
#define Pointer_img_HEIGHT    (12)
#define Pointer_img_SIZE      (662)
/*********************************
 * Bitmap Structure
 * Label: Pressbar_img
 * Description:  33x199 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Pressbar_img;
#define Pressbar_img_WIDTH     (33)
#define Pressbar_img_HEIGHT    (199)
#define Pressbar_img_SIZE      (7085)
/*********************************
 * Bitmap Structure
 * Label: NoLimit
 * Description:  50x31 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER NoLimit;
#define NoLimit_WIDTH     (50)
#define NoLimit_HEIGHT    (31)
#define NoLimit_SIZE      (2068)
/*********************************
 * Bitmap Structure
 * Label: NoLimit_press
 * Description:  50x31 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER NoLimit_press;
#define NoLimit_press_WIDTH     (50)
#define NoLimit_press_HEIGHT    (31)
#define NoLimit_press_SIZE      (2068)
/*********************************
 * Bitmap Structure
 * Label: Bat8
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat8;
#define Bat8_WIDTH     (24)
#define Bat8_HEIGHT    (30)
#define Bat8_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: Bat1
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat1;
#define Bat1_WIDTH     (24)
#define Bat1_HEIGHT    (30)
#define Bat1_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: Bat10
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat10;
#define Bat10_WIDTH     (24)
#define Bat10_HEIGHT    (30)
#define Bat10_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: Bat2
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat2;
#define Bat2_WIDTH     (24)
#define Bat2_HEIGHT    (30)
#define Bat2_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: Bat3
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat3;
#define Bat3_WIDTH     (24)
#define Bat3_HEIGHT    (30)
#define Bat3_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: Bat4
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat4;
#define Bat4_WIDTH     (24)
#define Bat4_HEIGHT    (30)
#define Bat4_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: Bat5
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat5;
#define Bat5_WIDTH     (24)
#define Bat5_HEIGHT    (30)
#define Bat5_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: Bat6
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat6;
#define Bat6_WIDTH     (24)
#define Bat6_HEIGHT    (30)
#define Bat6_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: Bat7
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat7;
#define Bat7_WIDTH     (24)
#define Bat7_HEIGHT    (30)
#define Bat7_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: Bat9
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Bat9;
#define Bat9_WIDTH     (24)
#define Bat9_HEIGHT    (30)
#define Bat9_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: setting
 * Description:  29x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER setting;
#define setting_WIDTH     (29)
#define setting_HEIGHT    (30)
#define setting_SIZE      (1388)
/*********************************
 * Bitmap Structure
 * Label: Speaker0
 * Description:  36x36 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Speaker0;
#define Speaker0_WIDTH     (36)
#define Speaker0_HEIGHT    (36)
#define Speaker0_SIZE      (1814)
/*********************************
 * Bitmap Structure
 * Label: Speaker1
 * Description:  36x36 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Speaker1;
#define Speaker1_WIDTH     (36)
#define Speaker1_HEIGHT    (36)
#define Speaker1_SIZE      (1814)
/*********************************
 * Bitmap Structure
 * Label: Speaker2
 * Description:  36x36 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER Speaker2;
#define Speaker2_WIDTH     (36)
#define Speaker2_HEIGHT    (36)
#define Speaker2_SIZE      (1814)
/*********************************
 * Bitmap Structure
 * Label: BatAC
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER BatAC;
#define BatAC_WIDTH     (24)
#define BatAC_HEIGHT    (30)
#define BatAC_SIZE      (1238)
/*********************************
 * Bitmap Structure
 * Label: BBat_img
 * Description:  33x123 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER BBat_img;
#define BBat_img_WIDTH     (33)
#define BBat_img_HEIGHT    (123)
#define BBat_img_SIZE      (4577)
/*********************************
 * Bitmap Structure
 * Label: BBat1_img
 * Description:  33x123 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER BBat1_img;
#define BBat1_img_WIDTH     (33)
#define BBat1_img_HEIGHT    (123)
#define BBat1_img_SIZE      (4577)
/*********************************
 * Bitmap Structure
 * Label: KVO
 * Description:  40x30 pixels, 8-bits per pixel
 ***********************************/
extern const GFX_IMAGE_HEADER KVO;
#define KVO_WIDTH     (40)
#define KVO_HEIGHT    (30)
#define KVO_SIZE      (1718)
/*****************************************************************************
 * SECTION:  Fonts
 *****************************************************************************/

/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_Bold_18
 * Description:  Height: 21 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
extern const FONT_EXTERNAL Arial_Narrow_Bold_18;
#define Arial_Narrow_Bold_18_SIZE    (3349)
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_26
 * Description:  Height: 31 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
extern const FONT_EXTERNAL Arial_Narrow_26;
#define Arial_Narrow_26_SIZE    (5689)
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_24
 * Description:  Height: 29 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
extern const FONT_EXTERNAL Arial_Narrow_24;
#define Arial_Narrow_24_SIZE    (5231)
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_Bold_28
 * Description:  Height: 33 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
extern const FONT_EXTERNAL Arial_Narrow_Bold_28;
#define Arial_Narrow_Bold_28_SIZE    (6559)
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_14
 * Description:  Height: 17 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
extern const FONT_EXTERNAL Arial_Narrow_14;
#define Arial_Narrow_14_SIZE    (2139)
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_Bold_72
 * Description:  Height: 84 pixels, 1 bit per pixel, Range: '.' to ':'
 ***********************************/
extern const FONT_EXTERNAL Arial_Narrow_Bold_72;
#define Arial_Narrow_Bold_72_SIZE    (4848)
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_36
 * Description:  Height: 42 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
extern const FONT_EXTERNAL Arial_Narrow_36;
#define Arial_Narrow_36_SIZE    (9334)
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_86
 * Description:  Height: 100 pixels, 1 bit per pixel, Range: '.' to ':'
 ***********************************/
extern const FONT_EXTERNAL Arial_Narrow_86;
#define Arial_Narrow_86_SIZE    (5960)
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_Bold_86
 * Description:  Height: 100 pixels, 1 bit per pixel, Range: '.' to ':'
 ***********************************/
extern const FONT_EXTERNAL Arial_Narrow_Bold_86;
#define Arial_Narrow_Bold_86_SIZE    (5960)
#endif

