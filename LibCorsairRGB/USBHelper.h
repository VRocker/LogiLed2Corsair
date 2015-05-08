#pragma once

#define WIN32_LEAN_AND_MEAN  

#include <Windows.h>

class USBHelper
{
public:
	static HANDLE GetDeviceHandle(unsigned int uiVID, unsigned int uiPID, unsigned int uiMI);

	static void SendData(HANDLE device, unsigned char* dataPkt);
	// Mouse doesn't like using WriteFile so we're using hid for the moment
	static void SendMData(HANDLE device, unsigned char* dataPkt);
};

