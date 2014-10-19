/*****************************************************************************
 *****************************************************************************/
#define TASKUSB_PUB
#include "include.h"

#include "framework/usb/usb.h"
#include "framework/usb/usb_device_cdc.h"
#include "usb_config.h"
#include "framework/usb/usb_device.h"

extern unsigned char OUTPacket[];	//User application buffer for receiving and holding OUT packets sent from the host
extern unsigned char INPacket[];		//User application buffer for sending IN packets to the host

/*********************************************************************
 * Function:        void taskUSB(void* pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *                  
 * Output:          Does not return
 *
 * Side Effects:    None
 *
 * Overview:        
 *
 * Note:            
 ********************************************************************/
void taskUSB(void* pvParameter)
{
    BYTE numBytesRead;
//	static GRAPHICS_MSG msg;

    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.
	   
	while (1) {

    //Blink the LEDs according to the USB device status
//	    BlinkUSBStatus();
    // User Application USB tasks
     	vTaskDelay( 50 / portTICK_RATE_MS );   // Wait 50ms
    	
		if(USB_BUS_SENSE && (USBGetDeviceState() == DETACHED_STATE))
        {
            USBDeviceAttach();
        }
		
		if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;

    	if(USBUSARTIsTxTrfReady())
    	{
			
			numBytesRead = getsUSBUSART((char*)OUTPacket,64);
			BYTE len;
			len  = process_req(OUTPacket, numBytesRead, INPacket);	 
			putUSBUSART((char*)INPacket,len);
			
			
			
			
#if 0			
			if(numBytesRead != 0)
			{
				BYTE i;
	        
				for(i=0;i<numBytesRead;i++)
				{
					switch(OUTPacket[i])
					{
						case 0x0A:
						case 0x0D:
							INPacket[i] = OUTPacket[i];
							break;
						default:
							INPacket[i] = OUTPacket[i] + 1;
							break;
					}
				}
				putUSBUSART(INPacket,numBytesRead);
			}
#endif		
		}
	    CDCTxService();
	}	
}
