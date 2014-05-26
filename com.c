/*
*/

#define COM_PUB
#include "include.h"


unsigned char get_data_req(unsigned char  *dst,unsigned int addr)
{
	unsigned char  *src;
	unsigned char  param_len, len = 0;
				 
	src = (unsigned char*)ReqTable[addr].DataPtr;
	param_len = ReqTable[addr].Size;
	if(param_len > 1)
	{
		while(param_len > 0)
		{
			*dst = *src;
			dst++;
			src++;
			param_len--;
			len++;
		}
	}
	else
	{
		*dst = *src;
		dst++;
		*dst = 0;
		dst++;
		len += 2;
	}
	return len;
}

unsigned char  set_data_req(unsigned char  *dst,unsigned int addr)
{
    return 0;
}
unsigned char  get_bat_req(unsigned char  *dst,unsigned int addr)
{
//	unsigned char  *src;
//	unsigned char  param_len, len = 0;
				 
	*(unsigned int*)dst = (unsigned int)(BAT_RAW2VOLT(batt_raw)*10);
	return 2;
}
unsigned char  get_raw_req(unsigned char  *dst,unsigned int addr)
{
//    unsigned char  *src;
//	unsigned char  param_len, len = 0;

//    src = (unsigned char *)(&E2pImage + addr*2);
    *dst = *((unsigned char *)(&E2pImage) + addr);
	return 1;
}
unsigned char  set_raw_req(unsigned char  *dst,unsigned int addr)
{
    return 0;
}

unsigned char  proc_RD(unsigned char *RxBufPtr, unsigned char *TxBufPtr)
{
	unsigned char  num_param/*, param_len*/, len = 0;
	unsigned int addr;
//	uchar *src;
	unsigned char  *dst =(unsigned char*)&((MESSAGE_HDR*)TxBufPtr)->MesData;

		addr = ((MESSAGE_HDR*)RxBufPtr)->MesAddr;  /*Get Parameter address*/
		((MESSAGE_HDR*)TxBufPtr)->MesAddr = addr;
#if 0
                if(addr > PRM_MAXADDR)
		{
			((MESSAGE_HDR*)TxBufPtr)->MesData = 1; /*Unknown address*/
			((MESSAGE_HDR*)TxBufPtr)->MesCmd |= 0x80; /*Set Error Flag*/
			return 1;
		}
#endif
                num_param = ((MESSAGE_HDR*)RxBufPtr)->MesData;  /*Number of params for reading*/
		
		while(num_param > 0)
		{
                        if(addr < (PRM_MAXADDR - 1))
                        {
                           if(ReqTable[addr].rdproc !=0)
                               len += ReqTable[addr].rdproc(dst + len, addr);
                        }
                        else
                        {
                           if(ReqTable[PRM_MAXADDR-1].rdproc !=0)
                               len += ReqTable[PRM_MAXADDR-1].rdproc(dst + len, addr - (PRM_MAXADDR-1));
                        }
			num_param--;
			addr++;

#if 0
                        if(addr > PRM_MAXADDR)
			{
				((MESSAGE_HDR*)TxBufPtr)->MesData = 1; /*Unknown address*/
				((MESSAGE_HDR*)TxBufPtr)->MesCmd |= 0x80; /*Set Error Flag*/
				return 1;
			}
#endif
                }
		return len;
}



unsigned char  proc_WR(unsigned char *RxBufPtr, unsigned char len, unsigned char *TxBufPtr)
{
	unsigned char  /*num_param, */param_len;
	unsigned int addr;
	unsigned char *src =(unsigned char *)&((MESSAGE_HDR*)TxBufPtr)->MesData;
	unsigned char *dst;

		addr = ((MESSAGE_HDR*)RxBufPtr)->MesAddr;  /*Get Parameter address*/
		((MESSAGE_HDR*)TxBufPtr)->MesAddr = addr;
		if(addr > PRM_MAXADDR)
		{
			((MESSAGE_HDR*)TxBufPtr)->MesData = 1; /*Unknown address*/
			((MESSAGE_HDR*)TxBufPtr)->MesCmd |= 0x80; /*Set Error Flag*/
			return 1;
		}
//		num_param = ((MESSAGE_HDR*)RxBufPtr)->MesData;  /*Number of params for writing*/
		
		while (len > 0)
		{
			dst = (unsigned char*)ReqTable[addr].DataPtr;
			param_len = ReqTable[addr].Size;
			if(len < param_len)
				break;
			while(param_len > 0)
			{
				*dst = *src;
				dst++;
				src++;
				param_len--;
				len--;
			
			}
 //			num_param--;
			addr++;
			if(addr > PRM_MAXADDR)
			{
				((MESSAGE_HDR*)TxBufPtr)->MesData = 1; /*Unknown address*/
				((MESSAGE_HDR*)TxBufPtr)->MesCmd |= 0x80; /*Set Error Flag*/
				return 1;
			}
		}
		return len;
}





unsigned char process_req(unsigned char *RxBufPtr, unsigned char len, unsigned char *TxBufPtr  )
{
	unsigned char chr;
	volatile unsigned char err = 0;
//	unsigned int addr;

	if(crc16(RxBufPtr, len))		/*Checksum*/
	{
			err++;
			return 0; 
	}
	chr = ((MESSAGE_HDR*)RxBufPtr)->MesCmd; /*Get Message Command*/
	((MESSAGE_HDR*)TxBufPtr)->MesCmd = chr; /*Copy request command to TX buffer*/

	if (chr == READ_CMD) /*Read*/
	{
		chr = proc_RD(RxBufPtr, TxBufPtr);
	}
	else if (chr == WRITE_CMD) /*Write*/
	{
		chr = proc_WR(RxBufPtr, len, TxBufPtr);
	}
				
	((MESSAGE_HDR*)TxBufPtr)->MesLen = chr; /*Set Message len to TX buffer*/
		*((unsigned short*)&TxBufPtr[chr + HEADER_LEN])	= crc16(TxBufPtr, chr + HEADER_LEN);

return chr + HEADER_LEN + 2;
}//func




