#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>
#include "pspuartprx.h"
#include "callback.h"

PSP_MODULE_INFO("BluetoothController", 0, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);


// constants for bluetooth controller
char inBytes[100];
const char* cmd_AT = "AT+";
const char* cmd_REST = "AT+REST";
const char* cmd_GMR = "AT+GMR";
const char* cmd_STATUS = "AT+STATUS";
const char* cmd_DISCON = "AT+DISCON";
const char* cmd_SCAN = "AT+SCAN";
const char* cmd_ADDLINKADD = "AT+ADDLINKADD=0x"; // NOTE: must be exactly 12 characters for hex string
const char* cmd_ADDLINKNAME = "AT+ADDLINKNAME=";
const char* cmd_VMLINK = "AT+VMLINK?";
const char* cmd_DELVMLINK = "AT+DELVMLINK";


int main(void)
{
	setupExitCallback(); // callback for home button exit.
	int baud=9600;
	sceDisplayWaitVblankStart();
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	pspDebugScreenInit();
	pspDebugScreenPrintf("Atempting to load pspuart in kernel mode\n");
	
	SceUID mod = pspSdkLoadStartModule("pspuartprx.prx", PSP_MEMORY_PARTITION_KERNEL);
    if (mod < 0)
    {
        pspDebugScreenPrintf(" Error 0x%08X loading/starting pspuartprx.prx.\n", mod);
        sceKernelDelayThread(3*1000*1000);
        sceKernelExitGame();
    }


	pspDebugScreenPrintf("pspuartprx module loaded !!!\n");
	pspUARTInit(baud); // initialize sio port and set baud rate
	pspDebugScreenPrintf("INIT UART DONE!!!\n");
	pspDebugScreenPrintf("UP to send char\n");
	pspDebugScreenPrintf("Down to read char\n");

	while(isRunning()) // get from callback function
	{
	SceCtrlData pad;

		sceCtrlReadBufferPositive(&pad, 1);
		if(pad.Buttons & PSP_CTRL_UP) {
				
			pspDebugScreenPrintf("Sending single char A at baud rate:%d \n", baud);
			pspUARTPrint("Hello PSP World");
			sceKernelDelayThread(50000);
		}
		if(pad.Buttons & PSP_CTRL_DOWN) {
				
			pspDebugScreenPrintf("Reading Char at baud rate: %d\n", baud);
			
			int ch = pspUARTRead(); // read a single character from serial port
			if((ch >= 0) && (ch != '\r'))
			{
					pspDebugScreenPrintf("%c", ch);
			}
			sceKernelDelayThread(50000);
		}
		if(pad.Buttons & PSP_CTRL_CROSS)
		{
				break;
		}

	}

	sceKernelExitGame();
	return 0;
}