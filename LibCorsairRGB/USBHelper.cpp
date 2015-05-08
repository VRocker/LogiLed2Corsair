#include "USBHelper.h"
#include <hidsdi.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include <string.h>
#include <sstream>

#include <tchar.h>

bool IsMatchingDevice(wchar_t *pDeviceID, unsigned int uiVID, unsigned int uiPID, unsigned int uiMI)
{
	unsigned int uiLocalVID = 0, uiLocalPID = 0, uiLocalMI = 0;

	wchar_t* pszNextToken;
	LPWSTR pszToken = wcstok_s(pDeviceID, L"\\#&", &pszNextToken);
	while (pszToken)
	{
		std::wstring tokenStr(pszToken);
		if (tokenStr.find(L"VID_", 0, 4) != std::wstring::npos)
		{
			std::wistringstream iss(tokenStr.substr(4));
			iss >> std::hex >> uiLocalVID;
		}
		else if (tokenStr.find(L"PID_", 0, 4) != std::wstring::npos)
		{
			std::wistringstream iss(tokenStr.substr(4));
			iss >> std::hex >> uiLocalPID;
		}
		else if (tokenStr.find(L"MI_", 0, 3) != std::wstring::npos)
		{
			std::wistringstream iss(tokenStr.substr(3));
			iss >> std::hex >> uiLocalMI;
		}

		pszToken = wcstok_s(0, L"\\#&", &pszNextToken);
	}

	if (uiVID != uiLocalVID || uiPID != uiLocalPID || uiMI != uiLocalMI)
		return false;

	return true;
}

HANDLE USBHelper::GetDeviceHandle(unsigned int uiVID, unsigned int uiPID, unsigned int uiMI)
{
	const GUID GUID_DEVINTERFACE_HID = { 0x4D1E55B2L, 0xF16F, 0x11CF, 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 };
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_HID, 0, 0, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	if (hDevInfo == INVALID_HANDLE_VALUE)
		return INVALID_HANDLE_VALUE;

	HANDLE hReturn = INVALID_HANDLE_VALUE;

	SP_DEVINFO_DATA deviceData = { 0 };
	deviceData.cbSize = sizeof(SP_DEVINFO_DATA);

	for (unsigned int i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &deviceData); ++i)
	{
		wchar_t wszDeviceID[MAX_DEVICE_ID_LEN];
		if (CM_Get_Device_IDW(deviceData.DevInst, wszDeviceID, MAX_DEVICE_ID_LEN, 0))
			continue;

		if (!IsMatchingDevice(wszDeviceID, uiVID, uiPID, uiMI))
			continue;

		SP_INTERFACE_DEVICE_DATA interfaceData = { 0 };
		interfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);

		if (!SetupDiEnumDeviceInterfaces(hDevInfo, &deviceData, &GUID_DEVINTERFACE_HID, 0, &interfaceData))
			break;

		DWORD dwRequiredSize = 0;
		SetupDiGetDeviceInterfaceDetail(hDevInfo, &interfaceData, 0, 0, &dwRequiredSize, 0);

		SP_INTERFACE_DEVICE_DETAIL_DATA *pData = (SP_INTERFACE_DEVICE_DETAIL_DATA *)new unsigned char[dwRequiredSize];
		pData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

		if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &interfaceData, pData, dwRequiredSize, 0, 0))
		{
			delete [] pData;
			break;
		}

		HANDLE hDevice = CreateFile(pData->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		if (hDevice == INVALID_HANDLE_VALUE)
		{
			delete [] pData;
			break;
		}

		/*int interfaceId = -1;
		if (pData->DevicePath) 
		{
			wchar_t *interface_component = wcsstr(pData->DevicePath, L"&mi_");
			if (interface_component) {
				wchar_t *hex_str = interface_component + 4;
				wchar_t *endptr = NULL;
				interfaceId = wcstol(hex_str, &endptr, 16);
				if (endptr == hex_str) {
					// The parsing failed. Set interface_number to -1.
					interfaceId = -1;
				}
			}
		}


		HIDD_ATTRIBUTES Attributes;
		Attributes.Size = sizeof(Attributes);

		HidD_GetAttributes(hDevice, &Attributes);

		if ((Attributes.VendorID == uiVID) && (Attributes.ProductID == uiPID) && (interfaceId == uiMI))
		{
			hReturn = hDevice;
			HidD_SetFeature(hReturn, 0, 0);

			break;
		}
		else
		{
			CloseHandle(hDevice);
			hDevice = INVALID_HANDLE_VALUE;
		}*/

		hReturn = hDevice;
		HidD_SetFeature(hReturn, 0, 0);

		break;
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);

	return hReturn;
}

void USBHelper::SendData(HANDLE device, unsigned char* dataPkt)
{
	unsigned char usbPkt[65] = { 0 };
	for (unsigned int i = 1; i < 65; ++i)
		usbPkt[i] = dataPkt[i - 1];

	//HidD_SetFeature(device, usbPkt, 65);
	DWORD written = 0;
	WriteFile(device, usbPkt, 65, &written, 0);
}

void USBHelper::SendMData(HANDLE device, unsigned char* dataPkt)
{
	unsigned char usbPkt[65] = { 0 };
	for (unsigned int i = 1; i < 65; ++i)
		usbPkt[i] = dataPkt[i - 1];

	HidD_SetFeature(device, usbPkt, 65);
}
