/*****************************************************************************
 * FileName:        new.c
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
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
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
 * SECTION: IPU Buffer Size Check
 *****************************************************************************/
#if (GFX_COMPRESSED_BUFFER_SIZE < 4136)
#warning The GFX_COMPRESSED_BUFFER_SIZE defined in hardware profile is smaller than the compressed size of the IPU resources.
#endif

#if (GFX_DECOMPRESSED_BUFFER_SIZE < 38034)
#warning The GFX_DECOMPRESSED_BUFFER_SIZE defined in hardware profile is smaller than the decompressed size of the IPU resources.
#endif

/*****************************************************************************
 * SECTION:  BITMAPS
 *****************************************************************************/

/*********************************
 * Bitmap Structure
 * Label: Intro
 * Description:  226x166 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Intro =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00000000 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    226,
    166,
    2082,
    38036,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Param_btn
 * Description:  224x26 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Param_btn =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00000830 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    224,
    26,
    86,
    6344,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Wait1
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Wait1 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00000890 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    28,
    28,
    672,
    1304,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Wait2
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Wait2 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00000B30 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    28,
    28,
    700,
    1304,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Wait3
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Wait3 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00000DF0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    28,
    28,
    673,
    1304,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Wait4
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Wait4 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000010A0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    28,
    28,
    692,
    1304,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Param_btn_press
 * Description:  224x26 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Param_btn_press =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00001360 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    224,
    26,
    86,
    6344,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Larrow_press
 * Description:  55x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Larrow_press =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000013C0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    55,
    30,
    388,
    2172,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Rarrow_press
 * Description:  55x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Rarrow_press =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00001550 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    55,
    30,
    382,
    2172,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Larrow
 * Description:  55x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Larrow =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000016D0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    55,
    30,
    281,
    2172,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Rarrow
 * Description:  55x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Rarrow =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000017F0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    55,
    30,
    277,
    2172,
    8
};

/*********************************
 * Bitmap Structure
 * Label: drug_Adrenaline
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER drug_Adrenaline =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00001910 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    102,
    54,
    383,
    6028,
    8
};

/*********************************
 * Bitmap Structure
 * Label: drug_Midazolam
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER drug_Midazolam =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00001A90 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    102,
    54,
    447,
    6028,
    8
};

/*********************************
 * Bitmap Structure
 * Label: drug_Morph_Midaz
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER drug_Morph_Midaz =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00001C50 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    102,
    54,
    479,
    6028,
    8
};

/*********************************
 * Bitmap Structure
 * Label: drug_NoName
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER drug_NoName =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00001E30 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    102,
    54,
    338,
    6028,
    8
};

/*********************************
 * Bitmap Structure
 * Label: drug_Noradrenaline
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER drug_Noradrenaline =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00001F90 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    102,
    54,
    891,
    6028,
    8
};

/*********************************
 * Bitmap Structure
 * Label: drug_Remitentanil
 * Description:  102x54 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER drug_Remitentanil =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00002310 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    102,
    54,
    358,
    6028,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Wait5
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Wait5 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00002480 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    28,
    28,
    663,
    1304,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Wait6
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Wait6 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00002720 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    28,
    28,
    712,
    1304,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Wait7
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Wait7 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000029F0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    28,
    28,
    673,
    1304,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Wait8
 * Description:  28x28 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Wait8 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00002CA0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    28,
    28,
    698,
    1304,
    8
};

/*********************************
 * Bitmap Structure
 * Label: prog_ContROV
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER prog_ContROV =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00002F60 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    110,
    72,
    1115,
    8440,
    8
};

/*********************************
 * Bitmap Structure
 * Label: prog_ContVOT
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER prog_ContVOT =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000033C0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    110,
    72,
    1181,
    8440,
    8
};

/*********************************
 * Bitmap Structure
 * Label: prog_IntROV
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER prog_IntROV =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00003860 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    110,
    72,
    993,
    8440,
    8
};

/*********************************
 * Bitmap Structure
 * Label: prog_IntVOT
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER prog_IntVOT =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00003C50 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    110,
    72,
    991,
    8440,
    8
};

/*********************************
 * Bitmap Structure
 * Label: prog_PCA
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER prog_PCA =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00004030 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    110,
    72,
    556,
    8440,
    8
};

/*********************************
 * Bitmap Structure
 * Label: prog_Step
 * Description:  110x72 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER prog_Step =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00004260 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    110,
    72,
    530,
    8440,
    8
};

/*********************************
 * Bitmap Structure
 * Label: clock_img
 * Description:  128x128 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER clock_img =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00004480 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    128,
    128,
    4136,
    16904,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Pointer_img
 * Description:  12x12 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Pointer_img =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000054B0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    12,
    12,
    133,
    664,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Pressbar_img
 * Description:  33x199 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Pressbar_img =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00005540 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    33,
    199,
    118,
    7088,
    8
};

/*********************************
 * Bitmap Structure
 * Label: NoLimit
 * Description:  50x31 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER NoLimit =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000055C0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    50,
    31,
    298,
    2072,
    8
};

/*********************************
 * Bitmap Structure
 * Label: NoLimit_press
 * Description:  50x31 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER NoLimit_press =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000056F0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    50,
    31,
    257,
    2072,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat8
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat8 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00005800 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    328,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat1
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat1 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00005950 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    370,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat10
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat10 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00005AD0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    288,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat2
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat2 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00005BF0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    403,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat3
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat3 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00005D90 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    388,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat4
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat4 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00005F20 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    382,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat5
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat5 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000060A0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    374,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat6
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat6 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00006220 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    353,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat7
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat7 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00006390 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    330,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Bat9
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Bat9 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000064E0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    360,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: setting
 * Description:  29x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER setting =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00006650 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    29,
    30,
    1386,
    1392,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Speaker0
 * Description:  36x36 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Speaker0 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00006BC0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    36,
    36,
    483,
    1816,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Speaker1
 * Description:  36x36 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Speaker1 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00006DB0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    36,
    36,
    681,
    1816,
    8
};

/*********************************
 * Bitmap Structure
 * Label: Speaker2
 * Description:  36x36 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER Speaker2 =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00007060 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    36,
    36,
    905,
    1816,
    8
};

/*********************************
 * Bitmap Structure
 * Label: BatAC
 * Description:  24x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER BatAC =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000073F0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    24,
    30,
    481,
    1240,
    8
};

/*********************************
 * Bitmap Structure
 * Label: BBat_img
 * Description:  33x123 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER BBat_img =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x000075E0 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    33,
    123,
    72,
    4580,
    8
};

/*********************************
 * Bitmap Structure
 * Label: BBat1_img
 * Description:  33x123 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER BBat1_img =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00007630 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    33,
    123,
    72,
    4580,
    8
};

/*********************************
 * Bitmap Structure
 * Label: KVO
 * Description:  40x30 pixels, 8-bits per pixel
 ***********************************/
const GFX_IMAGE_HEADER KVO =
{
    (EDS_EPMP | IMAGE_MBITMAP | COMP_IPU),
    2,
    {    .edsAddress = (__eds__ char *) (0x00007680 + GFX_EPMP_CS2_BASE_ADDRESS)   },
    40,
    30,
    287,
    1720,
    8
};

/*****************************************************************************
 * SECTION:  FONTS
 *****************************************************************************/

/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_Bold_18
 * Description:  Height: 21 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
FONT_EXTERNAL Arial_Narrow_Bold_18 = 
{
    (EDS_EPMP | COMP_NONE),
    0x0002,
    (0x000077A0 + GFX_EPMP_CS2_BASE_ADDRESS)
};
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_26
 * Description:  Height: 31 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
FONT_EXTERNAL Arial_Narrow_26 = 
{
    (EDS_EPMP | COMP_NONE),
    0x0002,
    (0x000084C0 + GFX_EPMP_CS2_BASE_ADDRESS)
};
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_24
 * Description:  Height: 29 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
FONT_EXTERNAL Arial_Narrow_24 = 
{
    (EDS_EPMP | COMP_NONE),
    0x0002,
    (0x00009B00 + GFX_EPMP_CS2_BASE_ADDRESS)
};
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_Bold_28
 * Description:  Height: 33 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
FONT_EXTERNAL Arial_Narrow_Bold_28 = 
{
    (EDS_EPMP | COMP_NONE),
    0x0002,
    (0x0000AF70 + GFX_EPMP_CS2_BASE_ADDRESS)
};
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_14
 * Description:  Height: 17 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
FONT_EXTERNAL Arial_Narrow_14 = 
{
    (EDS_EPMP | COMP_NONE),
    0x0002,
    (0x0000C910 + GFX_EPMP_CS2_BASE_ADDRESS)
};
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_Bold_72
 * Description:  Height: 84 pixels, 1 bit per pixel, Range: '.' to ':'
 ***********************************/
FONT_EXTERNAL Arial_Narrow_Bold_72 = 
{
    (EDS_EPMP | COMP_NONE),
    0x0002,
    (0x0000D170 + GFX_EPMP_CS2_BASE_ADDRESS)
};
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_36
 * Description:  Height: 42 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
FONT_EXTERNAL Arial_Narrow_36 = 
{
    (EDS_EPMP | COMP_NONE),
    0x0002,
    (0x0000E460 + GFX_EPMP_CS2_BASE_ADDRESS)
};
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_86
 * Description:  Height: 100 pixels, 1 bit per pixel, Range: '.' to ':'
 ***********************************/
FONT_EXTERNAL Arial_Narrow_86 = 
{
    (EDS_EPMP | COMP_NONE),
    0x0002,
    (0x000108E0 + GFX_EPMP_CS2_BASE_ADDRESS)
};
/*********************************
 * Installed Font Structure
 * Label: Arial_Narrow_Bold_86
 * Description:  Height: 100 pixels, 1 bit per pixel, Range: '.' to ':'
 ***********************************/
FONT_EXTERNAL Arial_Narrow_Bold_86 = 
{
    (EDS_EPMP | COMP_NONE),
    0x0002,
    (0x00012030 + GFX_EPMP_CS2_BASE_ADDRESS)
};
