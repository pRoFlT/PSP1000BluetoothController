#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>
#include "pspuartprx.h"

PSP_MODULE_INFO("BluetoothController", 0, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

PSP_HEAP_SIZE_KB(2500); // if we want to make heap larger. we may need this for all the serial info

int main(void)
{
	int baud=9600;
	sceDisplayWaitVblankStart();
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

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

	while(1)
	{
	SceCtrlData pad;

		sceCtrlReadBufferPositive(&pad, 1);
		if(pad.Buttons & PSP_CTRL_UP) {
				
			pspDebugScreenPrintf("Sending single char A at baud rate:%d \n", baud);
			pspUARTWrite(65);
			sceKernelDelayThread(500000);
		}
		if(pad.Buttons & PSP_CTRL_DOWN) {
				
			pspDebugScreenPrintf("Reading Char at baud rate: %d\n", baud);
			
			int ch = pspUARTRead(); // read a single character from serial port
			if((ch >= 0) && (ch != '\r'))
			{
					pspDebugScreenPrintf("%c", ch);
			}
			sceKernelDelayThread(500000);
		}
		if(pad.Buttons & PSP_CTRL_CROSS)
		{
				break;
		}

	}

	sceKernelExitGame();
	return 0;
}