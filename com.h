/*
*/

#ifndef COM_H
#define COM_H

//#include "include.h"
//#include <avr/eeprom.h>

#ifdef COM_PUB
#define COMPUB
#else
#define COMPUB extern
#endif

/*
				feild 00 Cmd
					1 Byte
					0x03 read
					0x16 write (only 1 parameter)

				feild 01 MesLen in Bytes - length of Payload 
					1 Byte

				feild 02 Parameter Address
					2 Byte
					0x0000 Version
					0x0002 sec
					0x0003 min

				feild 03 Payload
					function:                       Write					Read
					Direction:		Req		Resp			Req			Resp 								 
					Value:			Parameter Data    Number of param	Number of param		Parameter Data
 					Payloadlen:		up to 250 bytes   Always 1 byte		Always 1 byte		up to 250 bytes

				feild 04 CRC
 					2 byte

*/
#define	READ_CMD			0x03 // read command
#define	WRITE_CMD			0x16 // write command
#define	READCMD_LEN		1
#define	HEADER_LEN		4 		//length of message header


typedef struct MESSAGE_HDR
{
	unsigned char	MesCmd;
	unsigned char	MesLen;
	unsigned int	MesAddr;
	unsigned char	MesData;
}MESSAGE_HDR;

typedef unsigned char (*func)(unsigned char*,unsigned int);

typedef struct REQ_TABL
{
    func rdproc;
    func wrproc;
    unsigned char*	DataPtr;		/*Pointer to Data*/
    unsigned char		Size;			/*Size in bytes*/
}REQ_TABL;

COMPUB unsigned char if_addr;
COMPUB unsigned char process_req( unsigned char *RxBufPtr, unsigned char len, unsigned char *TxBufPtr );
COMPUB unsigned char get_data_req(unsigned char*,unsigned int);
COMPUB unsigned char get_bat_req(unsigned char*,unsigned int);
COMPUB unsigned char set_data_req(unsigned char*,unsigned int);
COMPUB unsigned char  get_raw_req(unsigned char  *dst,unsigned int addr);
COMPUB unsigned char  set_raw_req(unsigned char  *dst,unsigned int addr);




#define PRM_MAXADDR		18

#ifdef COM_PUB
const unsigned int ver = VERSION;
const unsigned char dev_name[10] ={"VL 667"};
COMPUB const REQ_TABL ReqTable[PRM_MAXADDR] = {
/*0*/	{&get_data_req, &set_data_req,(unsigned char*)&ver,                     sizeof(ver)			},
/*1*/	{&get_data_req, &set_data_req,(unsigned char*)&dev_name,                sizeof(dev_name)        	},
/*2*/	{&get_data_req, &set_data_req,(unsigned char*)&if_addr,                 sizeof(if_addr)			},
/*3*/	{&get_data_req, &set_data_req,(unsigned char*)&remain_infusetime,	sizeof(remain_infusetime)       },
/*4*/	{&get_data_req, &set_data_req,(unsigned char*)&vol_para,		50                              }, //vol para
/*5*/	{&get_data_req, &set_data_req,(unsigned char*)&press1_mmHg,		sizeof(press1_mmHg)           },
/*6*/	{&get_data_req, &set_data_req,(unsigned char*)&press2_mmHg,		sizeof(press2_mmHg)          },
/*7*/	{&get_data_req, &set_data_req,(unsigned char*)&vol_para.drug_type, 	sizeof(vol_para.drug_type)      },
/*8*/	{&get_bat_req,	0,						0, 														sizeof(batt_raw)					},	//battery
///*9*/		{&get_data_req, &set_data_req,(unsigned char*)&ac_raw,		sizeof(ac_raw)				},
/*9*/	{&get_data_req, 0,0, 							sizeof(unsigned char)			},
///*10*/	{&get_data_req, &set_data_req,(unsigned char*)&alarm_cntr,	sizeof(alarm_cntr)			},
/*10*/	{&get_data_req, 0,0, 							sizeof(unsigned char)                   },
/*11*/	{&get_data_req, &set_data_req,(unsigned char*)&press1_mmHg, 		sizeof(press1_mmHg)			},
/*12*/	{&get_data_req, &set_data_req,(unsigned char*)&press2_mmHg, 		sizeof(press2_mmHg)			},
/*13*/	{&get_data_req, &set_data_req,(unsigned char*)&E2pImage, 		50                                      },   //First Part of eeprom
/*14*/	{&get_data_req, &set_data_req,(unsigned char*)&E2pImage + 50, 		50                                      },  //Sec part of eeprom
/*15*/	{&get_data_req, &set_data_req,(unsigned char*)&E2pImage + 2*50,         50                                      },   //Drugs,drugs List of eeprom
/*16*/	{&get_data_req, &set_data_req,(unsigned char*)&E2pImage_ptr,            sizeof(E2pImage_ptr)  			}, //Depart list of eeprom
/*17*/	{&get_raw_req,  &set_raw_req, (unsigned char*)&E2pImage,         	sizeof(E2pImage)  			}, //Rest of eeprom

#if 0
/*18*/	{&get_data_req, &set_data_req,(unsigned char*)&set_press1, 		sizeof(set_press1)			},   
/*19*/	{&get_data_req, &set_data_req,(unsigned char*)&set_press2, 		sizeof(set_press2)			},
/*20*/	{&get_data_req, &set_data_req,(unsigned char*)&occlus_lmt, 		sizeof(occlus_lmt)			},
/*21*/	{&get_data_req, &set_data_req,(unsigned char*)&upocclus_lmt, 		sizeof(upocclus_lmt)			}
/*22*/
#endif
//	19,(uchar*)&drug_list, sizeof(drug_list),
};	 
#else
extern const unsigned int ver;
extern const unsigned char dev_name[];
extern const REQ_TABL ReqTable[];
#endif



#endif

