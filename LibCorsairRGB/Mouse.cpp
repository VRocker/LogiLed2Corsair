#include "Mouse.h"
#include "CorsairDefines.h"

#include "USBHelper.h"
#include <stdio.h>

namespace CorsairRGB
{
	namespace Mouse
	{
		HANDLE g_deviceHandle = INVALID_HANDLE_VALUE;

		char g_redVal[4] = { 0 };
		char g_greenVal[4] = { 0 };
		char g_blueVal[4] = { 0 };

		bool Init()
		{
			if (g_deviceHandle != INVALID_HANDLE_VALUE)
				return false;

			printf("Initialising...\n");

			printf("Searching for Corsair M65 RGB mouse...");
			g_deviceHandle = USBHelper::GetDeviceHandle(CORSAIR_RGB_VID, CORSAIR_RGB_M65_PID, 0x3);
			if (g_deviceHandle == INVALID_HANDLE_VALUE)
			{
				printf("NOT FOUND\n");
				printf("Searching for Corsair Sabre Optical mouse...");
				g_deviceHandle = USBHelper::GetDeviceHandle(CORSAIR_RGB_VID, CORSAIR_RGB_SABRE1_PID, 0x3);
				if (g_deviceHandle == INVALID_HANDLE_VALUE)
				{
					printf("NOT FOUND\n");
					printf("Searching for Corsair Sabre Laser mouse...");
					g_deviceHandle = USBHelper::GetDeviceHandle(CORSAIR_RGB_VID, CORSAIR_RGB_SABRE2_PID, 0x3);
					if (g_deviceHandle == INVALID_HANDLE_VALUE)
						printf("NOT FOUND\n");
				}
				else
					printf("FOUND\n");
			}
			else
				printf("FOUND\n");

			return g_deviceHandle != INVALID_HANDLE_VALUE ? true : false;
		}

		void Shutdown()
		{
			printf("Shutting down...");
			if (g_deviceHandle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(g_deviceHandle);
				g_deviceHandle = INVALID_HANDLE_VALUE;

				printf("DONE\n");
			}
			else
				printf("NOT INITIALISED\n");
		}

		void SetLight(LightIDs light, const unsigned char rIn, const unsigned char gIn, const unsigned char bIn)
		{
			if (light > LightIDs::Unknown)
				return;

			g_redVal[(unsigned int)light] = rIn;
			g_greenVal[(unsigned int)light] = gIn;
			g_blueVal[(unsigned int)light] = bIn;
		}

		void FlushLightBuffer(void)
		{
			if (g_deviceHandle == INVALID_HANDLE_VALUE)
				return;

			unsigned char dataPkt[64] = { 0 };

			dataPkt[0] = 0x07;
			dataPkt[1] = 0x22;
			dataPkt[2] = 0x04;
			dataPkt[3] = 0x01;

			// Light 1
			dataPkt[4] = 0x01;
			dataPkt[5] = g_redVal[0];
			dataPkt[6] = g_greenVal[0];
			dataPkt[7] = g_blueVal[0];

			// Light 2
			dataPkt[8] = 0x02;
			dataPkt[9] = g_redVal[1];
			dataPkt[10] = g_greenVal[1];
			dataPkt[11] = g_blueVal[1];

			// Light 3
			dataPkt[12] = 0x03;
			dataPkt[13] = g_redVal[2];
			dataPkt[14] = g_greenVal[2];
			dataPkt[15] = g_blueVal[2];

			// Random 4 of greatness. Maybe a mouse has 4 lights?
			dataPkt[16] = 0x04;
			dataPkt[17] = g_redVal[3];
			dataPkt[18] = g_greenVal[3];
			dataPkt[19] = g_blueVal[3];

			USBHelper::SendMData(g_deviceHandle, dataPkt);
		}
	};
};