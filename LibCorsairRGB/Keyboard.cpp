#include "Keyboard.h"
#include "CorsairDefines.h"

#include "USBHelper.h"
#include <stdio.h>

namespace CorsairRGB
{
	namespace Keyboard
	{
		Keymaps g_currentKeyMap = Keymaps::UK;

		HANDLE g_deviceHandle = INVALID_HANDLE_VALUE;

		char g_redVal[144] = { 0 };
		char g_greenVal[144] = { 0 };
		char g_blueVal[144] = { 0 };

		bool Init()
		{
			if (g_deviceHandle != INVALID_HANDLE_VALUE)
				return false;

			printf("Initialising...\n");

			printf("Searching for Corsair K65 RGB keyboard...");
			g_deviceHandle = USBHelper::GetDeviceHandle(CORSAIR_RGB_VID, CORSAIR_K65_RGB_PID, 0x3);
			if (g_deviceHandle == INVALID_HANDLE_VALUE)
			{
				printf("NOT FOUND\n");
				printf("Searching for Corsair K70 RGB keyboard...");
				g_deviceHandle = USBHelper::GetDeviceHandle(CORSAIR_RGB_VID, CORSAIR_K70_RGB_PID, 0x3);
				if (g_deviceHandle == INVALID_HANDLE_VALUE)
				{
					printf("NOT FOUND\n");
					printf("Searching for Corsair K95 RGB keyboard...");
					g_deviceHandle = USBHelper::GetDeviceHandle(CORSAIR_RGB_VID, CORSAIR_K95_RGB_PID, 0x3);
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

		void SetKey(Keys key, const unsigned char rIn, const unsigned char gIn, const unsigned char bIn)
		{
			unsigned char keyCode = 0;
			switch (g_currentKeyMap)
			{
			case Keymaps::UK:
				keyCode = UKKeyMap[(unsigned int)key];
				break;

			case Keymaps::US:
				keyCode = USKeyMap[(unsigned int)key];
				break;
			}

			SetKeyCode(keyCode, rIn, gIn, bIn);
		}

		void SetKeyCode(const unsigned char keyCode, const unsigned char rIn, const unsigned char gIn, const unsigned char bIn)
		{
			if (keyCode == 0xFF)
				return;

			unsigned char r = (unsigned char)((7.0f / 255.0f) * rIn);
			unsigned char g = (unsigned char)((7.0f / 255.0f) * gIn);
			unsigned char b = (unsigned char)((7.0f / 255.0f) * bIn);

			if (r > 7)
				r = 7;
			if (g > 7)
				g = 7;
			if (b > 7)
				b = 7;

			g_redVal[keyCode] = 7 - r;
			g_greenVal[keyCode] = 7 - g;
			g_blueVal[keyCode] = 7 - b;
		}

		void FlushLightBuffer(void)
		{
			if (g_deviceHandle == INVALID_HANDLE_VALUE)
				return;

			unsigned char data_pkt[5][64] = { 0 };

			data_pkt[0][0] = 0x7F;
			data_pkt[0][1] = 0x01;
			data_pkt[0][2] = 0x3C;

			data_pkt[1][0] = 0x7F;
			data_pkt[1][1] = 0x02;
			data_pkt[1][2] = 0x3C;

			data_pkt[2][0] = 0x7F;
			data_pkt[2][1] = 0x03;
			data_pkt[2][2] = 0x3C;

			data_pkt[3][0] = 0x7F;
			data_pkt[3][1] = 0x04;
			data_pkt[3][2] = 0x24;

			data_pkt[4][0] = 0x07;
			data_pkt[4][1] = 0x27;
			data_pkt[4][4] = 0xD8;

			for (unsigned int i = 0; i < 60; i++) {
				data_pkt[0][i + 4] = g_redVal[i * 2 + 1] << 4 | g_redVal[i * 2];
			}

			for (unsigned int i = 0; i < 12; i++) {
				data_pkt[1][i + 4] = g_redVal[i * 2 + 121] << 4 | g_redVal[i * 2 + 120];
			}

			for (unsigned int i = 0; i < 48; i++) {
				data_pkt[1][i + 16] = g_greenVal[i * 2 + 1] << 4 | g_greenVal[i * 2];
			}

			for (unsigned int i = 0; i < 24; i++) {
				data_pkt[2][i + 4] = g_greenVal[i * 2 + 97] << 4 | g_greenVal[i * 2 + 96];
			}

			for (unsigned int i = 0; i < 36; i++) {
				data_pkt[2][i + 28] = g_blueVal[i * 2 + 1] << 4 | g_blueVal[i * 2];
			}

			for (unsigned int i = 0; i < 36; i++) {
				data_pkt[3][i + 4] = g_blueVal[i * 2 + 73] << 4 | g_blueVal[i * 2 + 72];
			}

			USBHelper::SendData(g_deviceHandle, data_pkt[0]);
			USBHelper::SendData(g_deviceHandle, data_pkt[1]);
			USBHelper::SendData(g_deviceHandle, data_pkt[2]);
			USBHelper::SendData(g_deviceHandle, data_pkt[3]);
			USBHelper::SendData(g_deviceHandle, data_pkt[4]);
		}

		void RestoreLighting(void)
		{
			unsigned char dataPkt[2][64] = {
				{ 0x07, 0x05, 0x02, 0x00, 0x03, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
				{ 0x07, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
			};

			USBHelper::SendData(g_deviceHandle, dataPkt[0]);
			USBHelper::SendData(g_deviceHandle, dataPkt[1]);
		}
	};
};