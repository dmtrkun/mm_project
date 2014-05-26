/*****************************************************************************
 *****************************************************************************/

#ifndef _ALARM_H
#define _ALARM_H
#include "GDD_Screens.h"

#ifdef ALARM_PUB
#define ALARMPUB
#else
#define ALARMPUB extern
#endif

#define EEPROM_ERR			0
#define RTC_ERR			1


//#define HW_ERRTYPE	0

#define NO_ERR				0
#define HRDWR_ERR			1
#define DOOR_ALRM			2
#define AIR_ALRM			3
#define MOTOR_ALRM 			4
#define DOWNOCC_ALRM		5
#define PARAOCC_ALRM		6
#define UPOCC_ALRM			7
#define BATLOW_ALRM			8
#define BATEMPTY_ALRM		9
#define NOBAT_ALRM			10
#define KVO_ALRM			11
#define HOLD_ALRM			12
#define NOAC_ALRM			13
#define NOSET_ALRM			14

#define YELLOW_ALARM_MASK  0x2900   //0010 1001 0000 0000
#define RED_ALARM_MASK  	 0x56FE   //0101 0110 1111 1110

#if 1
/**red window*/
#define BATEMPTY_ALRM_SCR	0
#define DOOR_ALRM_SCR			1
#define AIR_ALRM_SCR			2
#define ACCAIR_ALRM_SCR		3
#define DOWNOCC_ALRM_SCR	4	//Down occlusion
#define UPOCC_ALRM_SCR		5	//Up occlusion
#define MOTOR_ALRM_SCR		6	//Pump stuck
#define PARAOCC_ALRM_SCR	7 	//Para situation
#define NOSET_ALRM_SCR		8
#define RATEZERO_ALRM_SCR	9
/**yellow window*/
#define BATLOW_ALRM_SCR		10 //Battery low
#define ACFAIL_ALRM_SCR		11
#define HIPRESS_ALRM_SCR	12
#define KVO_ALRM_SCR			13 //VTBI done
#define HOLD_ALRM_SCR			14 //Hold alarm
#define HARWARE_ALRM_SCR	15 //Hardware Error

#define NO_BTN				0
#define RESTART_BTN			1
#define MUTE_BTN			2
#define EXIT_BTN			4
#define WAIT_ICON			8
#define BAT_ICON			16


typedef struct 
{
	const XCHAR* title;
	const XCHAR* name;
	const XCHAR* descr;
	const XCHAR* solut;
	unsigned char btns;
	unsigned char tout;
	unsigned char statbit_forclear;
	WORD bckgr_color;
}ALARM_SPECS_t;

#ifdef ALARM_PUB
const XCHAR* Alarm_title[] =
{
"ERROR",
"INFUSION STOPPED!",
"WARNING!"
};
const XCHAR Alarm_title0[] ={"ERROR"};
const XCHAR Alarm_title1[] ={"INFUSION STOPPED!"};
const XCHAR Alarm_title2[] ={"WARNING!"};

const XCHAR Alarm_descr0[] ={">The internal battery\r\n  is exhausted"};
const XCHAR Alarm_descr1[] ={">DOOR WAS OPENED\r\n  DURING AN INFUSION"};
const XCHAR Alarm_descr2[] ={">SINGLE AIR BUBBLE EXCEEDS\r\n  ALARM LIMIT\r\n>SET NOT FITTED CORRECTLY\r\n  INTO AIR DETECTOR"};
const XCHAR Alarm_descr3[] ={">ACCUMULATED AIR BUBBLE\r\n  EXCEEDS ALARM LIMIT\r\n>SET NOT FITTED CORRECTLY\r\n  INTO AIR DETECTOR"};
const XCHAR Alarm_descr4[] ={">A BLOCKAGE HAS OCCURED\r\n  DOWNSTREAM"};
const XCHAR Alarm_descr5[] ={">A BLOCKAGE HAS OCCURED\r\n  UPSTREAM"};
const XCHAR Alarm_descr6[] ={">INTERNAL ERROR\r\n  HAS OCCURED"};
const XCHAR Alarm_descr7[] ={">MAY BE THE SET DISCONNECTED\r\n  FROM THE PATIENT"};
const XCHAR Alarm_descr8[] ={">NO INFUSION SET FITTED"};
const XCHAR Alarm_descr9[] ={">LESS THEN 30 MINUTES\r\n  OF BATTERY LIFE\r\n  REMAINING"};
const XCHAR Alarm_descr10[] ={"BATTERY TIME\r\n  REMAINING"};
const XCHAR Alarm_descr11[] ={">THE PRESSURE TO PATIENT\r\n  INCREASING"};
const XCHAR Alarm_descr12[] ={"\r\n\r\n         (KEEP VIEN OPEN)"};
const XCHAR Alarm_descr13[] ={">CONTENS OF EEPROM\r\n  OR RTC WAS\r\n  REPLACED BY DEFAULT"};
const XCHAR Alarm_descr14[] ={">PUMP ON HOLD\r\n  MORE THEN 2 MINUTES"};

const XCHAR Alarm_solut0[] ={">CONNECT THE PUMP\r\n  TO MAINS IMMEDIATELY"};
const XCHAR Alarm_solut1[] ={">CLOSE DOOR"};
const XCHAR Alarm_solut2[] ={">CHECK SET FOR AIR\r\n>REMOVE AIR ACCORDING\r\n  TO HOSPITAL POLICE"};
const XCHAR Alarm_solut3[] ={">CHECK FLUID PATH\r\n  BETWEEN PUMP AND PATIENT"};
const XCHAR Alarm_solut4[] ={">CHECK SET, CLAMPS\r\n  ABOVE THE PUMP"};
const XCHAR Alarm_solut5[] ={">REMOVE PUMP FROM USE"};
const XCHAR Alarm_solut6[] ={">CONNECT THE SET TO\r\n  PATIENT, ACCORDING\r\n  TO HOSPITAL POLICE"};
const XCHAR Alarm_solut7[] ={">FIT INFUSION SET"};
const XCHAR Alarm_solut8[] ={">SET RATE"};
const XCHAR Alarm_solut9[] ={">CONNECT THE PUMP\r\n  TO MAINS\r\n>CHECK POWER CABLE"};
const XCHAR Alarm_solut10[] ={"\r\n>KVO = "};
const XCHAR Alarm_solut11[] ={">SEND PUMP TO\r\n  CALIBRATION"};
const XCHAR Alarm_solut12[] ={">RESTART INFUSION\r\n  OR TURN OFF THE PUMP"};

ALARM_SPECS_t Alarm_Specs[] = 
{
	{Alarm_title1, "BATTERY\r\nEMPTY",			Alarm_descr0, 	Alarm_solut0,	RESTART_BTN|MUTE_BTN,		0,BATEMPTY_ALRM,	RED	},
	{Alarm_title1, "DOOR OPEN",					Alarm_descr1, 	Alarm_solut1,	RESTART_BTN|MUTE_BTN,		0,0, 				RED	},
	{Alarm_title1, "AIR IN LINE",   			Alarm_descr2, 	Alarm_solut2,	RESTART_BTN|MUTE_BTN,		0,AIR_ALRM, 		RED	},
	{Alarm_title1, "AIR IN LINE",   			Alarm_descr3, 	Alarm_solut2,	RESTART_BTN|MUTE_BTN,		0,AIR_ALRM, 		RED	},
	{Alarm_title1, "DOWN\r\nOCCLUSION",			Alarm_descr4, 	Alarm_solut3,	RESTART_BTN|MUTE_BTN,		0,DOWNOCC_ALRM, 	RED	},
	{Alarm_title1, "UP\r\nOCCLUSION",  			Alarm_descr5, 	Alarm_solut4,	RESTART_BTN|MUTE_BTN,		0,UPOCC_ALRM, 		RED	},
	{Alarm_title1, "PUMP STUCK",   	  			Alarm_descr6, 	Alarm_solut5,	RESTART_BTN|MUTE_BTN,		0,MOTOR_ALRM, 		RED	},
	{Alarm_title1, "PARA\r\nSITUATION",			Alarm_descr7, 	Alarm_solut6,	RESTART_BTN|MUTE_BTN,		0,PARAOCC_ALRM, 	RED	},
	{Alarm_title1, "NO SET",   		   			Alarm_descr8, 	Alarm_solut7,	EXIT_BTN|MUTE_BTN,			0,NOSET_ALRM,				RED	},
	{Alarm_title1, "RATE = 0.0ml/hr",  			NULL,			Alarm_solut8,	EXIT_BTN|MUTE_BTN,			0,0, 				RED	},
	{Alarm_title2, "BATTERY\r\nLOW",			Alarm_descr9, 	Alarm_solut9,	NO_BTN|WAIT_ICON|BAT_ICON,	3,BATLOW_ALRM, 		YELLOW_RUN},
	{Alarm_title2, "PUMP WORK\r\nON BATTERY",	Alarm_descr10,	Alarm_solut9,	NO_BTN|WAIT_ICON|BAT_ICON,	3,NOAC_ALRM, 		YELLOW_RUN},
	{Alarm_title2, "HIGH\r\nPRESSOR", 			Alarm_descr11, 	Alarm_solut3,	NO_BTN|WAIT_ICON|BAT_ICON,	3,0, 				YELLOW_RUN},
	{Alarm_title2, "VTBI DONE\r\nINFUSING KVO",	Alarm_descr12, 	Alarm_solut10,	NO_BTN|WAIT_ICON|BAT_ICON,	3,KVO_ALRM, 		YELLOW_RUN},
	{Alarm_title1, "PUMP\r\nON HOLD",			Alarm_descr14, 	Alarm_solut12,	RESTART_BTN|MUTE_BTN,		0,HOLD_ALRM, 		RED	},
	{Alarm_title0, "HARDWARE\r\nERROR",			Alarm_descr13, 	Alarm_solut11,	EXIT_BTN|MUTE_BTN,			0,HRDWR_ERR, 		RED	},

};                                                                          

#else
extern	 ALARM_SPECS_t Alarm_Specs[];
#endif

#endif

ALARMPUB	void SetError(unsigned char err, unsigned char type);
ALARMPUB	unsigned char GetError(void);
void ClearError(void);


ALARMPUB	 void CreateAlarm(void);
ALARMPUB	 void CreatePrimitivesForAlarm(void);
ALARMPUB	 WORD msgAlarm(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);

#endif // _ALARM_H
