#include "main.h"
#include <stdio.h>
#include "LogiLedDefs.h"

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>

#include <ppl.h>

#include "Logger.h"

#include "../LibCorsairRGB/Keyboard.h"
#include "../LibCorsairRGB/Mouse.h"

CorsairRGB::Keys g_CorsairKeyFromLogi[144] = { CorsairRGB::Keys::missing };

static bool g_hasInitialised = false;

void InitCorsairToLogiMap()
{
	g_CorsairKeyFromLogi[0] = CorsairRGB::Keys::escape;
	g_CorsairKeyFromLogi[1] = CorsairRGB::Keys::f1;
	g_CorsairKeyFromLogi[2] = CorsairRGB::Keys::f2;
	g_CorsairKeyFromLogi[3] = CorsairRGB::Keys::f3;
	g_CorsairKeyFromLogi[4] = CorsairRGB::Keys::f4;
	g_CorsairKeyFromLogi[5] = CorsairRGB::Keys::f5;
	g_CorsairKeyFromLogi[6] = CorsairRGB::Keys::f6;
	g_CorsairKeyFromLogi[7] = CorsairRGB::Keys::f7;
	g_CorsairKeyFromLogi[8] = CorsairRGB::Keys::f8;
	g_CorsairKeyFromLogi[9] = CorsairRGB::Keys::f9;
	g_CorsairKeyFromLogi[10] = CorsairRGB::Keys::f10;
	g_CorsairKeyFromLogi[11] = CorsairRGB::Keys::f11;
	g_CorsairKeyFromLogi[12] = CorsairRGB::Keys::f12;
	g_CorsairKeyFromLogi[13] = CorsairRGB::Keys::printscreen;
	g_CorsairKeyFromLogi[14] = CorsairRGB::Keys::scolllock;
	g_CorsairKeyFromLogi[15] = CorsairRGB::Keys::pausebreak;
	g_CorsairKeyFromLogi[16] = CorsairRGB::Keys::mediastop;
	g_CorsairKeyFromLogi[17] = CorsairRGB::Keys::mediaprev;
	g_CorsairKeyFromLogi[18] = CorsairRGB::Keys::mediaplaypause;
	g_CorsairKeyFromLogi[19] = CorsairRGB::Keys::medianext;
	g_CorsairKeyFromLogi[20] = CorsairRGB::Keys::missing;

	g_CorsairKeyFromLogi[21] = CorsairRGB::Keys::grave;
	g_CorsairKeyFromLogi[22] = CorsairRGB::Keys::num1;
	g_CorsairKeyFromLogi[23] = CorsairRGB::Keys::num2;
	g_CorsairKeyFromLogi[24] = CorsairRGB::Keys::num3;
	g_CorsairKeyFromLogi[25] = CorsairRGB::Keys::num4;
	g_CorsairKeyFromLogi[26] = CorsairRGB::Keys::num5;
	g_CorsairKeyFromLogi[27] = CorsairRGB::Keys::num6;
	g_CorsairKeyFromLogi[28] = CorsairRGB::Keys::num7;
	g_CorsairKeyFromLogi[29] = CorsairRGB::Keys::num8;
	g_CorsairKeyFromLogi[30] = CorsairRGB::Keys::num9;
	g_CorsairKeyFromLogi[31] = CorsairRGB::Keys::num0;
	g_CorsairKeyFromLogi[32] = CorsairRGB::Keys::minus;
	g_CorsairKeyFromLogi[33] = CorsairRGB::Keys::equals;
	g_CorsairKeyFromLogi[34] = CorsairRGB::Keys::backspace;
	g_CorsairKeyFromLogi[35] = CorsairRGB::Keys::insert;
	g_CorsairKeyFromLogi[36] = CorsairRGB::Keys::home;
	g_CorsairKeyFromLogi[37] = CorsairRGB::Keys::pageup;
	g_CorsairKeyFromLogi[38] = CorsairRGB::Keys::numlock;
	g_CorsairKeyFromLogi[39] = CorsairRGB::Keys::numpaddivide;
	g_CorsairKeyFromLogi[40] = CorsairRGB::Keys::numpadmultiply;
	g_CorsairKeyFromLogi[41] = CorsairRGB::Keys::numpadminus;

	g_CorsairKeyFromLogi[42] = CorsairRGB::Keys::tab;
	g_CorsairKeyFromLogi[43] = CorsairRGB::Keys::q;
	g_CorsairKeyFromLogi[44] = CorsairRGB::Keys::w;
	g_CorsairKeyFromLogi[45] = CorsairRGB::Keys::e;
	g_CorsairKeyFromLogi[46] = CorsairRGB::Keys::r;
	g_CorsairKeyFromLogi[47] = CorsairRGB::Keys::t;
	g_CorsairKeyFromLogi[48] = CorsairRGB::Keys::y;
	g_CorsairKeyFromLogi[49] = CorsairRGB::Keys::u;
	g_CorsairKeyFromLogi[50] = CorsairRGB::Keys::i;
	g_CorsairKeyFromLogi[51] = CorsairRGB::Keys::o;
	g_CorsairKeyFromLogi[52] = CorsairRGB::Keys::p;
	g_CorsairKeyFromLogi[53] = CorsairRGB::Keys::lsquare;
	g_CorsairKeyFromLogi[54] = CorsairRGB::Keys::rsquare;
	g_CorsairKeyFromLogi[55] = CorsairRGB::Keys::backslash;
	g_CorsairKeyFromLogi[56] = CorsairRGB::Keys::del;
	g_CorsairKeyFromLogi[57] = CorsairRGB::Keys::end;
	g_CorsairKeyFromLogi[58] = CorsairRGB::Keys::pagedown;
	g_CorsairKeyFromLogi[59] = CorsairRGB::Keys::numpad7;
	g_CorsairKeyFromLogi[60] = CorsairRGB::Keys::numpad8;
	g_CorsairKeyFromLogi[61] = CorsairRGB::Keys::numpad9;
	g_CorsairKeyFromLogi[62] = CorsairRGB::Keys::numpadplus;

	g_CorsairKeyFromLogi[63] = CorsairRGB::Keys::capslock;
	g_CorsairKeyFromLogi[64] = CorsairRGB::Keys::a;
	g_CorsairKeyFromLogi[65] = CorsairRGB::Keys::s;
	g_CorsairKeyFromLogi[66] = CorsairRGB::Keys::d;
	g_CorsairKeyFromLogi[67] = CorsairRGB::Keys::f;
	g_CorsairKeyFromLogi[68] = CorsairRGB::Keys::g;
	g_CorsairKeyFromLogi[69] = CorsairRGB::Keys::h;
	g_CorsairKeyFromLogi[70] = CorsairRGB::Keys::j;
	g_CorsairKeyFromLogi[71] = CorsairRGB::Keys::k;
	g_CorsairKeyFromLogi[72] = CorsairRGB::Keys::l;
	g_CorsairKeyFromLogi[73] = CorsairRGB::Keys::semicolon;
	g_CorsairKeyFromLogi[74] = CorsairRGB::Keys::apostrophe;
	g_CorsairKeyFromLogi[75] = CorsairRGB::Keys::hash;
	g_CorsairKeyFromLogi[76] = CorsairRGB::Keys::enter;
	g_CorsairKeyFromLogi[77] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[78] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[79] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[80] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[81] = CorsairRGB::Keys::numpad4;
	g_CorsairKeyFromLogi[82] = CorsairRGB::Keys::numpad5;
	g_CorsairKeyFromLogi[83] = CorsairRGB::Keys::numpad6;

	g_CorsairKeyFromLogi[84] = CorsairRGB::Keys::lshift;
	g_CorsairKeyFromLogi[85] = CorsairRGB::Keys::z;
	g_CorsairKeyFromLogi[86] = CorsairRGB::Keys::x;
	g_CorsairKeyFromLogi[87] = CorsairRGB::Keys::c;
	g_CorsairKeyFromLogi[88] = CorsairRGB::Keys::v;
	g_CorsairKeyFromLogi[89] = CorsairRGB::Keys::b;
	g_CorsairKeyFromLogi[90] = CorsairRGB::Keys::n;
	g_CorsairKeyFromLogi[91] = CorsairRGB::Keys::m;
	g_CorsairKeyFromLogi[92] = CorsairRGB::Keys::comma;
	g_CorsairKeyFromLogi[93] = CorsairRGB::Keys::period;
	g_CorsairKeyFromLogi[94] = CorsairRGB::Keys::forwardslash;
	g_CorsairKeyFromLogi[95] = CorsairRGB::Keys::rshift;
	g_CorsairKeyFromLogi[96] = CorsairRGB::Keys::arrowup;
	g_CorsairKeyFromLogi[97] = CorsairRGB::Keys::numpad1;
	g_CorsairKeyFromLogi[98] = CorsairRGB::Keys::numpad2;
	g_CorsairKeyFromLogi[99] = CorsairRGB::Keys::numpad3;
	g_CorsairKeyFromLogi[100] = CorsairRGB::Keys::numpadenter;
	g_CorsairKeyFromLogi[101] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[102] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[103] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[104] = CorsairRGB::Keys::missing;

	g_CorsairKeyFromLogi[105] = CorsairRGB::Keys::lctrl;
	g_CorsairKeyFromLogi[106] = CorsairRGB::Keys::lwinkey;
	g_CorsairKeyFromLogi[107] = CorsairRGB::Keys::alt;
	g_CorsairKeyFromLogi[108] = CorsairRGB::Keys::space;
	g_CorsairKeyFromLogi[109] = CorsairRGB::Keys::altgr;
	g_CorsairKeyFromLogi[110] = CorsairRGB::Keys::rwinkey;
	g_CorsairKeyFromLogi[111] = CorsairRGB::Keys::contextmenu;
	g_CorsairKeyFromLogi[112] = CorsairRGB::Keys::rctrl;
	g_CorsairKeyFromLogi[113] = CorsairRGB::Keys::arrowleft;
	g_CorsairKeyFromLogi[114] = CorsairRGB::Keys::arrowdown;
	g_CorsairKeyFromLogi[115] = CorsairRGB::Keys::arrowright;
	g_CorsairKeyFromLogi[116] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[117] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[118] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[119] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[120] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[121] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[122] = CorsairRGB::Keys::missing;
	g_CorsairKeyFromLogi[123] = CorsairRGB::Keys::numpad0;
	g_CorsairKeyFromLogi[124] = CorsairRGB::Keys::numpaddecimal;
	g_CorsairKeyFromLogi[125] = CorsairRGB::Keys::missing;
}

void cleanup()
{
	CorsairRGB::Keyboard::RestoreLighting();

	CorsairRGB::Keyboard::Shutdown();
	CorsairRGB::Mouse::Shutdown();

	CLogger::EndLogging();
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD fdwReason, LPVOID)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		atexit(cleanup);

		CLogger::InitLogging("Log.txt");

		CLogger::SetLogLevel(LogLevel::Debug);

		CLogger::OutputLog_s("Attached to process.", LogLevel::Information);

		InitCorsairToLogiMap();


	}
	break;

	case DLL_PROCESS_DETACH:
	{
		cleanup();

		CLogger::OutputLog_s("Detached from process.", LogLevel::Information);
	}
	break;
	}

	return true;
}

bool LogiLedInit()
{
	CLogger::OutputLog_s("Logitech LED init called.", LogLevel::Information);

	CorsairRGB::Keyboard::Init();
	CorsairRGB::Mouse::Init();

	// Make sure we start off with a blank canvas
	for (unsigned char key = 0; key < 144; key++) {
		CorsairRGB::Keyboard::SetKey((CorsairRGB::Keys)key, 0, 0, 0);
	}

	for (unsigned char key = 0; key < 4; key++) {
		CorsairRGB::Mouse::SetLight((CorsairRGB::Mouse::LightIDs)key, 0, 0, 0);
	}

	CorsairRGB::Keyboard::FlushLightBuffer();
	CorsairRGB::Mouse::FlushLightBuffer();

	g_hasInitialised = true;

	return true;
}

bool LogiLedGetSdkVersion(int *majorNum, int *minorNum, int *buildNum)
{
	CLogger::OutputLog("LogiLedGetSdkVersion called.", LogLevel::Information);

	// Mimic the SDK version
	*majorNum = 8;
	*minorNum = 58;
	*buildNum = 183;

	return true;
}

bool LogiLedSetTargetDevice(int targetDevice)
{
	CLogger::OutputLog("LogiLedSetTargetDevice called (%i)", LogLevel::Information, targetDevice);

	// Logitech SDK says this function returns false if LogiLedInit hasn't been called
	return g_hasInitialised;
}

bool LogiLedSaveCurrentLighting()
{
	CLogger::OutputLog("LogiLedSaveCurrentLighting called (%i)", LogLevel::Information);
	return true;
}

bool LogiLedSetLighting(int redPercentage, int greenPercentage, int bluePercentage)
{
	// Commented because this spams
	//CLogger::OutputLog("LogiLedSetLighting called (%i %i %i)", LogLevel::Information, redPercentage, greenPercentage, bluePercentage);

	unsigned char redValue = (float)(redPercentage / 100.0f) * 255;
	unsigned char greenValue = (float)(greenPercentage / 100.0f) * 255;
	unsigned char blueValue = (float)(bluePercentage / 100.0f) * 255;

	for (unsigned char key = 0; key < 144; key++)
	{
		CorsairRGB::Keyboard::SetKey((CorsairRGB::Keys)key, redValue, greenValue, blueValue);
	}


	for (unsigned char key = 0; key < 4; key++)
	{
		CorsairRGB::Mouse::SetLight((CorsairRGB::Mouse::LightIDs)key, redValue, greenValue, blueValue);
	}

	CorsairRGB::Keyboard::FlushLightBuffer();
	CorsairRGB::Mouse::FlushLightBuffer();

	return true;
}

bool LogiLedRestoreLighting()
{
	CLogger::OutputLog("LogiLedRestoreLighting called", LogLevel::Information);

	CorsairRGB::Keyboard::RestoreLighting();
	return true;
}

bool LogiLedFlashLighting(int redPercentage, int greenPercentage, int bluePercentage, int milliSecondsDuration, int milliSecondsInterval)
{
	CLogger::OutputLog("LogiLedFlashLighting called (%i %i %i %i %i)", LogLevel::Information, redPercentage, greenPercentage, bluePercentage, milliSecondsDuration, milliSecondsInterval);

	return true;
}

bool LogiLedPulseLighting(int redPercentage, int greenPercentage, int bluePercentage, int milliSecondsDuration, int milliSecondsInterval)
{
	CLogger::OutputLog("LogiLedPulseLighting called (%i %i %i %i %i)", LogLevel::Information, redPercentage, greenPercentage, bluePercentage, milliSecondsDuration, milliSecondsInterval);

	return true;
}

bool LogiLedStopEffects()
{
	CLogger::OutputLog_s("LogiLedStopEffects called", LogLevel::Information);
	return true;
}

bool LogiLedSetLightingFromBitmap(unsigned char bitmap[])
{
	CLogger::OutputLog_s("LogiLedSetLightingFromBitmap called", LogLevel::Information);

	for (unsigned int i = 0; i < LOGI_LED_BITMAP_WIDTH * LOGI_LED_BITMAP_HEIGHT; ++i)
	{
		CorsairRGB::Keyboard::SetKey(g_CorsairKeyFromLogi[i], bitmap[(i * LOGI_LED_BITMAP_BYTES_PER_KEY)], bitmap[(i * LOGI_LED_BITMAP_BYTES_PER_KEY) + 1], bitmap[(i * LOGI_LED_BITMAP_BYTES_PER_KEY) + 2]);
	}

	// Set the top light to the character colour
	CorsairRGB::Mouse::SetLight(CorsairRGB::Mouse::LightIDs::Top, bitmap[(0 * LOGI_LED_BITMAP_BYTES_PER_KEY)], bitmap[(0 * LOGI_LED_BITMAP_BYTES_PER_KEY) + 1], bitmap[(0 * LOGI_LED_BITMAP_BYTES_PER_KEY) + 2]);
	// Set the front light to the F1 colour
	CorsairRGB::Mouse::SetLight(CorsairRGB::Mouse::LightIDs::Front, bitmap[(1 * LOGI_LED_BITMAP_BYTES_PER_KEY)], bitmap[(1 * LOGI_LED_BITMAP_BYTES_PER_KEY) + 1], bitmap[(1 * LOGI_LED_BITMAP_BYTES_PER_KEY) + 2]);
	// Set the back light to the F7 colour
	CorsairRGB::Mouse::SetLight(CorsairRGB::Mouse::LightIDs::Back, bitmap[(7 * LOGI_LED_BITMAP_BYTES_PER_KEY)], bitmap[(7 * LOGI_LED_BITMAP_BYTES_PER_KEY) + 1], bitmap[(7 * LOGI_LED_BITMAP_BYTES_PER_KEY) + 2]);

	CorsairRGB::Keyboard::FlushLightBuffer();
	CorsairRGB::Mouse::FlushLightBuffer();

	return true;
}

bool LogiLedSetLightingForKeyWithScanCode(int keyCode, int redPercentage, int greenPercentage, int bluePercentage)
{
	CLogger::OutputLog("LogiLedSetLightingForKeyWithScanCode called [Key: %i] (%i %i %i)", LogLevel::Information, keyCode, redPercentage, greenPercentage, bluePercentage);

	return true;
}

bool LogiLedSetLightingForKeyWithHidCode(int keyCode, int redPercentage, int greenPercentage, int bluePercentage)
{
	CLogger::OutputLog("LogiLedSetLightingForKeyWithHidCode called [Key: %i] (%i %i %i)", LogLevel::Information, keyCode, redPercentage, greenPercentage, bluePercentage);

	return true;
}

bool LogiLedSetLightingForKeyWithQuartzCode(int keyCode, int redPercentage, int greenPercentage, int bluePercentage)
{
	CLogger::OutputLog("LogiLedSetLightingForKeyWithQuartzCode called [Key: %i] (%i %i %i)", LogLevel::Information, keyCode, redPercentage, greenPercentage, bluePercentage);

	return true;
}

bool LogiLedSetLightingForKeyWithKeyName(LogiLed::KeyName keyName, int redPercentage, int greenPercentage, int bluePercentage)
{
	CLogger::OutputLog("LogiLedSetLightingForKeyWithKeyName called [Key: %i] (%i %i %i)", LogLevel::Information, keyName, redPercentage, greenPercentage, bluePercentage);

	return true;
}

void LogiLedShutdown()
{
	CLogger::OutputLog_s("LogiLedShutdown called.", LogLevel::Information);

	cleanup();

	g_hasInitialised = false;
}