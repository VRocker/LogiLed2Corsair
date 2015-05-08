#pragma once

#define WIN32_LEAN_AND_MEAN  

#include <Windows.h>

class USBHelper
{
public:
	static HANDLE GetDeviceHandle(unsigned int uiVID, unsigned int uiPID, unsigned int uiMI);

	static void SendData(HANDLE device, unsigned char* dataPkt);
};

