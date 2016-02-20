#include "main.h"
#include <stdio.h>
#include "LogiLedDefs.h"

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <tchar.h>
#include <vector>

#include "Logger.h"

#include "../CUESDK/include/CUESDK.h"

CorsairLedId g_CorsairKeyFromLogi[144] = { CLI_Invalid };
CorsairLedId g_corsairKeyFromLogiKeyName[144] = { CLI_Invalid };

auto coloursVector = std::vector<CorsairLedColor>();

static bool g_hasInitialised = false;

void InitCorsairToLogiMap()
{
	g_CorsairKeyFromLogi[0] = CLK_Escape;
	g_CorsairKeyFromLogi[1] = CLK_F1;
	g_CorsairKeyFromLogi[2] = CLK_F2;
	g_CorsairKeyFromLogi[3] = CLK_F3;
	g_CorsairKeyFromLogi[4] = CLK_F4;
	g_CorsairKeyFromLogi[5] = CLK_F5;
	g_CorsairKeyFromLogi[6] = CLK_F6;
	g_CorsairKeyFromLogi[7] = CLK_F7;
	g_CorsairKeyFromLogi[8] = CLK_F8;
	g_CorsairKeyFromLogi[9] = CLK_F9;
	g_CorsairKeyFromLogi[10] = CLK_F10;
	g_CorsairKeyFromLogi[11] = CLK_F11;
	g_CorsairKeyFromLogi[12] = CLK_F12;
	g_CorsairKeyFromLogi[13] = CLK_PrintScreen;
	g_CorsairKeyFromLogi[14] = CLK_ScrollLock;
	g_CorsairKeyFromLogi[15] = CLK_PauseBreak;
	g_CorsairKeyFromLogi[16] = CLK_Stop;
	g_CorsairKeyFromLogi[17] = CLK_ScanPreviousTrack;
	g_CorsairKeyFromLogi[18] = CLK_PlayPause;
	g_CorsairKeyFromLogi[19] = CLK_ScanNextTrack;
	g_CorsairKeyFromLogi[20] = CLI_Invalid;

	g_CorsairKeyFromLogi[21] = CLK_GraveAccentAndTilde;
	g_CorsairKeyFromLogi[22] = CLK_1;
	g_CorsairKeyFromLogi[23] = CLK_2;
	g_CorsairKeyFromLogi[24] = CLK_3;
	g_CorsairKeyFromLogi[25] = CLK_4;
	g_CorsairKeyFromLogi[26] = CLK_5;
	g_CorsairKeyFromLogi[27] = CLK_6;
	g_CorsairKeyFromLogi[28] = CLK_7;
	g_CorsairKeyFromLogi[29] = CLK_8;
	g_CorsairKeyFromLogi[30] = CLK_9;
	g_CorsairKeyFromLogi[31] = CLK_0;
	g_CorsairKeyFromLogi[32] = CLK_MinusAndUnderscore;
	g_CorsairKeyFromLogi[33] = CLK_EqualsAndPlus;
	g_CorsairKeyFromLogi[34] = CLK_Backspace;
	g_CorsairKeyFromLogi[35] = CLK_Insert;
	g_CorsairKeyFromLogi[36] = CLK_Home;
	g_CorsairKeyFromLogi[37] = CLK_PageUp;
	g_CorsairKeyFromLogi[38] = CLK_NumLock;
	g_CorsairKeyFromLogi[39] = CLK_KeypadSlash;
	g_CorsairKeyFromLogi[40] = CLK_KeypadAsterisk;
	g_CorsairKeyFromLogi[41] = CLK_KeypadMinus;

	g_CorsairKeyFromLogi[42] = CLK_Tab;
	g_CorsairKeyFromLogi[43] = CLK_Q;
	g_CorsairKeyFromLogi[44] = CLK_W;
	g_CorsairKeyFromLogi[45] = CLK_E;
	g_CorsairKeyFromLogi[46] = CLK_R;
	g_CorsairKeyFromLogi[47] = CLK_T;
	g_CorsairKeyFromLogi[48] = CLK_Y;
	g_CorsairKeyFromLogi[49] = CLK_U;
	g_CorsairKeyFromLogi[50] = CLK_I;
	g_CorsairKeyFromLogi[51] = CLK_O;
	g_CorsairKeyFromLogi[52] = CLK_P;
	g_CorsairKeyFromLogi[53] = CLK_BracketLeft;
	g_CorsairKeyFromLogi[54] = CLK_BracketRight;
	g_CorsairKeyFromLogi[55] = CLK_Backslash;
	g_CorsairKeyFromLogi[56] = CLK_Delete;
	g_CorsairKeyFromLogi[57] = CLK_End;
	g_CorsairKeyFromLogi[58] = CLK_PageDown;
	g_CorsairKeyFromLogi[59] = CLK_Keypad7;
	g_CorsairKeyFromLogi[60] = CLK_Keypad8;
	g_CorsairKeyFromLogi[61] = CLK_Keypad9;
	g_CorsairKeyFromLogi[62] = CLK_KeypadPlus;

	g_CorsairKeyFromLogi[63] = CLK_CapsLock;
	g_CorsairKeyFromLogi[64] = CLK_A;
	g_CorsairKeyFromLogi[65] = CLK_S;
	g_CorsairKeyFromLogi[66] = CLK_D;
	g_CorsairKeyFromLogi[67] = CLK_F;
	g_CorsairKeyFromLogi[68] = CLK_G;
	g_CorsairKeyFromLogi[69] = CLK_H;
	g_CorsairKeyFromLogi[70] = CLK_J;
	g_CorsairKeyFromLogi[71] = CLK_K;
	g_CorsairKeyFromLogi[72] = CLK_L;
	g_CorsairKeyFromLogi[73] = CLK_SemicolonAndColon;
	g_CorsairKeyFromLogi[74] = CLK_ApostropheAndDoubleQuote;
	g_CorsairKeyFromLogi[75] = CLK_NonUsTilde;
	g_CorsairKeyFromLogi[76] = CLK_Enter;
	g_CorsairKeyFromLogi[77] = CLI_Invalid;
	g_CorsairKeyFromLogi[78] = CLI_Invalid;
	g_CorsairKeyFromLogi[79] = CLI_Invalid;
	g_CorsairKeyFromLogi[80] = CLI_Invalid;
	g_CorsairKeyFromLogi[81] = CLK_Keypad4;
	g_CorsairKeyFromLogi[82] = CLK_Keypad5;
	g_CorsairKeyFromLogi[83] = CLK_Keypad6;

	g_CorsairKeyFromLogi[84] = CLK_LeftShift;
	g_CorsairKeyFromLogi[85] = CLK_Z;
	g_CorsairKeyFromLogi[86] = CLK_X;
	g_CorsairKeyFromLogi[87] = CLK_C;
	g_CorsairKeyFromLogi[88] = CLK_V;
	g_CorsairKeyFromLogi[89] = CLK_B;
	g_CorsairKeyFromLogi[90] = CLK_N;
	g_CorsairKeyFromLogi[91] = CLK_M;
	g_CorsairKeyFromLogi[92] = CLK_CommaAndLessThan;
	g_CorsairKeyFromLogi[93] = CLK_PeriodAndBiggerThan;
	g_CorsairKeyFromLogi[94] = CLK_SlashAndQuestionMark;
	g_CorsairKeyFromLogi[95] = CLK_RightShift;
	g_CorsairKeyFromLogi[96] = CLK_UpArrow;
	g_CorsairKeyFromLogi[97] = CLK_Keypad1;
	g_CorsairKeyFromLogi[98] = CLK_Keypad2;
	g_CorsairKeyFromLogi[99] = CLK_Keypad3;
	g_CorsairKeyFromLogi[100] = CLK_KeypadEnter;
	g_CorsairKeyFromLogi[101] = CLI_Invalid;
	g_CorsairKeyFromLogi[102] = CLI_Invalid;
	g_CorsairKeyFromLogi[103] = CLI_Invalid;
	g_CorsairKeyFromLogi[104] = CLI_Invalid;

	g_CorsairKeyFromLogi[105] = CLK_LeftCtrl;
	g_CorsairKeyFromLogi[106] = CLK_LeftGui;
	g_CorsairKeyFromLogi[107] = CLK_LeftAlt;
	g_CorsairKeyFromLogi[108] = CLK_Space;
	g_CorsairKeyFromLogi[109] = CLK_RightAlt;
	g_CorsairKeyFromLogi[110] = CLK_RightGui;
	g_CorsairKeyFromLogi[111] = CLK_Application;
	g_CorsairKeyFromLogi[112] = CLK_RightCtrl;
	g_CorsairKeyFromLogi[113] = CLK_LeftArrow;
	g_CorsairKeyFromLogi[114] = CLK_DownArrow;
	g_CorsairKeyFromLogi[115] = CLK_RightArrow;
	g_CorsairKeyFromLogi[116] = CLI_Invalid;
	g_CorsairKeyFromLogi[117] = CLI_Invalid;
	g_CorsairKeyFromLogi[118] = CLI_Invalid;
	g_CorsairKeyFromLogi[119] = CLI_Invalid;
	g_CorsairKeyFromLogi[120] = CLI_Invalid;
	g_CorsairKeyFromLogi[121] = CLI_Invalid;
	g_CorsairKeyFromLogi[122] = CLI_Invalid;
	g_CorsairKeyFromLogi[123] = CLK_Keypad0;
	g_CorsairKeyFromLogi[124] = CLK_KeypadPeriodAndDelete;
	g_CorsairKeyFromLogi[125] = CLI_Invalid;
}
void InitCorsairToLogiKeyNameMap()
{
	g_corsairKeyFromLogiKeyName[LogiLed::ESC] = CLK_Escape;
	g_corsairKeyFromLogiKeyName[LogiLed::F1] = CLK_F1;
	g_corsairKeyFromLogiKeyName[LogiLed::F2] = CLK_F2;
	g_corsairKeyFromLogiKeyName[LogiLed::F3] = CLK_F3;
	g_corsairKeyFromLogiKeyName[LogiLed::F4] = CLK_F4;
	g_corsairKeyFromLogiKeyName[LogiLed::F5] = CLK_F5;
	g_corsairKeyFromLogiKeyName[LogiLed::F6] = CLK_F6;
	g_corsairKeyFromLogiKeyName[LogiLed::F7] = CLK_F7;
	g_corsairKeyFromLogiKeyName[LogiLed::F8] = CLK_F8;
	g_corsairKeyFromLogiKeyName[LogiLed::F9] = CLK_F9;
	g_corsairKeyFromLogiKeyName[LogiLed::F10] = CLK_F10;
	g_corsairKeyFromLogiKeyName[LogiLed::F11] = CLK_F11;
	g_corsairKeyFromLogiKeyName[LogiLed::F12] = CLK_F12;
	g_corsairKeyFromLogiKeyName[LogiLed::PRINT_SCREEN] = CLK_PrintScreen;
	g_corsairKeyFromLogiKeyName[LogiLed::SCROLL_LOCK] = CLK_ScrollLock;
	g_corsairKeyFromLogiKeyName[LogiLed::PAUSE_BREAK] = CLK_PauseBreak;
	g_corsairKeyFromLogiKeyName[LogiLed::TILDE] = CLK_NonUsTilde; // UNKNOWN
	g_corsairKeyFromLogiKeyName[LogiLed::ONE] = CLK_1;
	g_corsairKeyFromLogiKeyName[LogiLed::TWO] = CLK_2;
	g_corsairKeyFromLogiKeyName[LogiLed::THREE] = CLK_3;
	g_corsairKeyFromLogiKeyName[LogiLed::FOUR] = CLK_4;
	g_corsairKeyFromLogiKeyName[LogiLed::FIVE] = CLK_5;
	g_corsairKeyFromLogiKeyName[LogiLed::SIX] = CLK_6;
	g_corsairKeyFromLogiKeyName[LogiLed::SEVEN] = CLK_7;
	g_corsairKeyFromLogiKeyName[LogiLed::EIGHT] = CLK_8;
	g_corsairKeyFromLogiKeyName[LogiLed::NINE] = CLK_9;
	g_corsairKeyFromLogiKeyName[LogiLed::ZERO] = CLK_0;
	g_corsairKeyFromLogiKeyName[LogiLed::MINUS] = CLK_MinusAndUnderscore;
	g_corsairKeyFromLogiKeyName[LogiLed::EQUALS] = CLK_EqualsAndPlus;
	g_corsairKeyFromLogiKeyName[LogiLed::BACKSPACE] = CLK_Backspace;
	g_corsairKeyFromLogiKeyName[LogiLed::INSERT] = CLK_Insert;
	g_corsairKeyFromLogiKeyName[LogiLed::HOME] = CLK_Home;
	g_corsairKeyFromLogiKeyName[LogiLed::PAGE_UP] = CLK_PageUp;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_LOCK] = CLK_NumLock;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_SLASH] = CLK_KeypadSlash;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_ASTERISK] = CLK_KeypadAsterisk;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_MINUS] = CLK_KeypadMinus;
	g_corsairKeyFromLogiKeyName[LogiLed::TAB] = CLK_Tab;
	g_corsairKeyFromLogiKeyName[LogiLed::Q] = CLK_Q;
	g_corsairKeyFromLogiKeyName[LogiLed::W] = CLK_W;
	g_corsairKeyFromLogiKeyName[LogiLed::E] = CLK_E;
	g_corsairKeyFromLogiKeyName[LogiLed::R] = CLK_R;
	g_corsairKeyFromLogiKeyName[LogiLed::T] = CLK_T;
	g_corsairKeyFromLogiKeyName[LogiLed::Y] = CLK_Y;
	g_corsairKeyFromLogiKeyName[LogiLed::U] = CLK_U;
	g_corsairKeyFromLogiKeyName[LogiLed::I] = CLK_I;
	g_corsairKeyFromLogiKeyName[LogiLed::O] = CLK_O;
	g_corsairKeyFromLogiKeyName[LogiLed::P] = CLK_P;
	g_corsairKeyFromLogiKeyName[LogiLed::OPEN_BRACKET] = CLK_BracketLeft;
	g_corsairKeyFromLogiKeyName[LogiLed::CLOSE_BRACKET] = CLK_BracketRight;
	g_corsairKeyFromLogiKeyName[LogiLed::BACKSLASH] = CLK_Backslash;
	g_corsairKeyFromLogiKeyName[LogiLed::KEYBOARD_DELETE] = CLK_Delete;
	g_corsairKeyFromLogiKeyName[LogiLed::END] = CLK_End;
	g_corsairKeyFromLogiKeyName[LogiLed::PAGE_DOWN] = CLK_PageDown;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_SEVEN] = CLK_Keypad7;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_EIGHT] = CLK_Keypad8;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_NINE] = CLK_Keypad9;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_PLUS] = CLK_KeypadPlus;
	g_corsairKeyFromLogiKeyName[LogiLed::CAPS_LOCK] = CLK_CapsLock;
	g_corsairKeyFromLogiKeyName[LogiLed::A] = CLK_A;
	g_corsairKeyFromLogiKeyName[LogiLed::S] = CLK_S;
	g_corsairKeyFromLogiKeyName[LogiLed::D] = CLK_D;
	g_corsairKeyFromLogiKeyName[LogiLed::F] = CLK_F;
	g_corsairKeyFromLogiKeyName[LogiLed::G] = CLK_G;
	g_corsairKeyFromLogiKeyName[LogiLed::H] = CLK_H;
	g_corsairKeyFromLogiKeyName[LogiLed::J] = CLK_J;
	g_corsairKeyFromLogiKeyName[LogiLed::K] = CLK_K;
	g_corsairKeyFromLogiKeyName[LogiLed::L] = CLK_L;
	g_corsairKeyFromLogiKeyName[LogiLed::SEMICOLON] = CLK_SemicolonAndColon;
	g_corsairKeyFromLogiKeyName[LogiLed::APOSTROPHE] = CLK_ApostropheAndDoubleQuote;
	g_corsairKeyFromLogiKeyName[LogiLed::ENTER] = CLK_Enter;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_FOUR] = CLK_Keypad4;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_FIVE] = CLK_Keypad5;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_SIX] = CLK_Keypad6;
	g_corsairKeyFromLogiKeyName[LogiLed::LEFT_SHIFT] = CLK_LeftShift;
	g_corsairKeyFromLogiKeyName[LogiLed::Z] = CLK_Z;
	g_corsairKeyFromLogiKeyName[LogiLed::X] = CLK_X;
	g_corsairKeyFromLogiKeyName[LogiLed::C] = CLK_C;
	g_corsairKeyFromLogiKeyName[LogiLed::V] = CLK_V;
	g_corsairKeyFromLogiKeyName[LogiLed::B] = CLK_B;
	g_corsairKeyFromLogiKeyName[LogiLed::N] = CLK_N;
	g_corsairKeyFromLogiKeyName[LogiLed::M] = CLK_M;
	g_corsairKeyFromLogiKeyName[LogiLed::COMMA] = CLK_CommaAndLessThan;
	g_corsairKeyFromLogiKeyName[LogiLed::PERIOD] = CLK_PeriodAndBiggerThan;
	g_corsairKeyFromLogiKeyName[LogiLed::FORWARD_SLASH] = CLK_SlashAndQuestionMark;
	g_corsairKeyFromLogiKeyName[LogiLed::RIGHT_SHIFT] = CLK_RightShift;
	g_corsairKeyFromLogiKeyName[LogiLed::ARROW_UP] = CLK_UpArrow;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_ONE] = CLK_Keypad1;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_TWO] = CLK_Keypad2;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_THREE] = CLK_Keypad3;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_ENTER] = CLK_KeypadEnter;
	g_corsairKeyFromLogiKeyName[LogiLed::LEFT_CONTROL] = CLK_LeftCtrl;
	g_corsairKeyFromLogiKeyName[LogiLed::LEFT_WINDOWS] = CLK_LeftGui;
	g_corsairKeyFromLogiKeyName[LogiLed::LEFT_ALT] = CLK_LeftAlt;
	g_corsairKeyFromLogiKeyName[LogiLed::SPACE] = CLK_Space;
	g_corsairKeyFromLogiKeyName[LogiLed::RIGHT_ALT] = CLK_RightAlt;
	g_corsairKeyFromLogiKeyName[LogiLed::RIGHT_WINDOWS] = CLK_RightGui;
	g_corsairKeyFromLogiKeyName[LogiLed::APPLICATION_SELECT] = CLK_Application;
	g_corsairKeyFromLogiKeyName[LogiLed::RIGHT_CONTROL] = CLK_RightCtrl;
	g_corsairKeyFromLogiKeyName[LogiLed::ARROW_LEFT] = CLK_LeftArrow;
	g_corsairKeyFromLogiKeyName[LogiLed::ARROW_DOWN] = CLK_DownArrow;
	g_corsairKeyFromLogiKeyName[LogiLed::ARROW_RIGHT] = CLK_RightArrow;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_ZERO] = CLK_Keypad0;
	g_corsairKeyFromLogiKeyName[LogiLed::NUM_PERIOD] = CLK_KeypadPeriodAndDelete;
}


void cleanup()
{
	/*CorsairRGB::Keyboard::RestoreLighting();

	CorsairRGB::Keyboard::Shutdown();*/
	//CorsairRGB::Mouse::Shutdown();

	coloursVector.clear();

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

		CLogger::SetLogLevel(LogLevel::All);

		CLogger::OutputLog_s("Attached to process.", LogLevel::Debug);

		InitCorsairToLogiMap();
		InitCorsairToLogiKeyNameMap();

	}
	break;

	case DLL_PROCESS_DETACH:
	{
		cleanup();

		CLogger::OutputLog_s("Detached from process.", LogLevel::Debug);
	}
	break;
	}

	return true;
}

bool LogiLedInit()
{
	CLogger::OutputLog_s("Logitech LED init called.", LogLevel::Debug);

	if (g_hasInitialised)
	{
		// Already initialised.
		return true;
	}

	CorsairProtocolDetails _proto = CorsairPerformProtocolHandshake();

	CLogger::OutputLog("CUESDK Initialised. SDK Version: %s", LogLevel::Information, _proto.sdkVersion);

	unsigned int deviceCount = CorsairGetDeviceCount();
	CLogger::OutputLog("Found %u Corsair devices.", LogLevel::Information, deviceCount);
	for (unsigned int i = 0; i < deviceCount; ++i)
	{
		if (auto deviceInfo = CorsairGetDeviceInfo(i))
		{
			CLogger::OutputLog("Corsair Device %u: %s.", LogLevel::Information, i, deviceInfo->model);

			switch (deviceInfo->type) 
			{
			case CDT_Mouse: {
				auto numberOfKeys = deviceInfo->physicalLayout - CPL_Zones1 + 1;
				for (auto i = 0; i < numberOfKeys; i++) {
					auto ledId = static_cast<CorsairLedId>(CLM_1 + i);
					coloursVector.push_back(CorsairLedColor{ ledId, 0, 0, 0 });
				}
			} break;
			case CDT_Keyboard: 
			{
				auto ledPositions = CorsairGetLedPositions();
				if (ledPositions) {
					for (auto i = 0; i < ledPositions->numberOfLed; i++) {
						auto ledId = ledPositions->pLedPosition[i].ledId;
						coloursVector.push_back(CorsairLedColor{ ledId, 0, 0, 0 });
					}
				}
			} break;
			case CDT_Headset: 
			{
				coloursVector.push_back(CorsairLedColor{ CLH_LeftLogo, 0, 0, 0 });
				coloursVector.push_back(CorsairLedColor{ CLH_RightLogo, 0, 0, 0 });
			} break;
			}
		}
	}

	g_hasInitialised = true;

	return true;
}

bool LogiLedGetSdkVersion(int *majorNum, int *minorNum, int *buildNum)
{
	CLogger::OutputLog("LogiLedGetSdkVersion called.", LogLevel::Debug);

	// Mimic the SDK version
	*majorNum = 8;
	*minorNum = 75;
	*buildNum = 30;

	return true;
}

bool LogiLedSetTargetDevice(int targetDevice)
{
	CLogger::OutputLog("LogiLedSetTargetDevice called (%i)", LogLevel::Debug, targetDevice);

	// Logitech SDK says this function returns false if LogiLedInit hasn't been called
	return g_hasInitialised;
}

bool LogiLedSaveCurrentLighting()
{
	CLogger::OutputLog("LogiLedSaveCurrentLighting called (%i)", LogLevel::Debug);
	return true;
}

bool LogiLedSetLighting(int redPercentage, int greenPercentage, int bluePercentage)
{
	// Commented because this spams
	//CLogger::OutputLog("LogiLedSetLighting called (%i %i %i)", LogLevel::Debug, redPercentage, greenPercentage, bluePercentage);

	unsigned char redValue = (unsigned char)((float)(redPercentage / 100.0f) * 255);
	unsigned char greenValue = (unsigned char)((float)(greenPercentage / 100.0f) * 255);
	unsigned char blueValue = (unsigned char)((float)(bluePercentage / 100.0f) * 255);

	for (auto &ledColour : coloursVector)
	{
		ledColour.r = redValue;
		ledColour.g = greenValue;
		ledColour.b = blueValue;
	}

	CorsairSetLedsColorsAsync((int)coloursVector.size(), coloursVector.data(), nullptr, nullptr);

	return true;
}

bool LogiLedRestoreLighting()
{
	CLogger::OutputLog("LogiLedRestoreLighting called", LogLevel::Debug);
	return true;
}

bool LogiLedFlashLighting(int redPercentage, int greenPercentage, int bluePercentage, int milliSecondsDuration, int milliSecondsInterval)
{
	CLogger::OutputLog("LogiLedFlashLighting called (%i %i %i %i %i)", LogLevel::Debug, redPercentage, greenPercentage, bluePercentage, milliSecondsDuration, milliSecondsInterval);

	return true;
}

bool LogiLedPulseLighting(int redPercentage, int greenPercentage, int bluePercentage, int milliSecondsDuration, int milliSecondsInterval)
{
	CLogger::OutputLog("LogiLedPulseLighting called (%i %i %i %i %i)", LogLevel::Debug, redPercentage, greenPercentage, bluePercentage, milliSecondsDuration, milliSecondsInterval);

	return true;
}

bool LogiLedStopEffects()
{
	CLogger::OutputLog_s("LogiLedStopEffects called", LogLevel::Debug);
	return true;
}

bool LogiLedSetLightingFromBitmap(unsigned char bitmap[])
{
	CLogger::OutputLog_s("LogiLedSetLightingFromBitmap called", LogLevel::Debug);

	// TODO
	for (unsigned int i = 0; i < LOGI_LED_BITMAP_WIDTH * LOGI_LED_BITMAP_HEIGHT; ++i)
	{
		auto &ledColour = coloursVector[g_CorsairKeyFromLogi[i]];
		ledColour.r = bitmap[(i * LOGI_LED_BITMAP_BYTES_PER_KEY)];
		ledColour.g = bitmap[(i * LOGI_LED_BITMAP_BYTES_PER_KEY) + 1];
		ledColour.b = bitmap[(i * LOGI_LED_BITMAP_BYTES_PER_KEY) + 2];
	}

	CorsairSetLedsColorsAsync((int)coloursVector.size(), coloursVector.data(), nullptr, nullptr);

	return true;
}

bool LogiLedSetLightingForKeyWithScanCode(int keyCode, int redPercentage, int greenPercentage, int bluePercentage)
{
	CLogger::OutputLog("LogiLedSetLightingForKeyWithScanCode called [Key: %i] (%i %i %i)", LogLevel::Debug, keyCode, redPercentage, greenPercentage, bluePercentage);

	return true;
}

bool LogiLedSetLightingForKeyWithHidCode(int keyCode, int redPercentage, int greenPercentage, int bluePercentage)
{
	CLogger::OutputLog("LogiLedSetLightingForKeyWithHidCode called [Key: %i] (%i %i %i)", LogLevel::Debug, keyCode, redPercentage, greenPercentage, bluePercentage);

	return true;
}

bool LogiLedSetLightingForKeyWithQuartzCode(int keyCode, int redPercentage, int greenPercentage, int bluePercentage)
{
	CLogger::OutputLog("LogiLedSetLightingForKeyWithQuartzCode called [Key: %i] (%i %i %i)", LogLevel::Debug, keyCode, redPercentage, greenPercentage, bluePercentage);

	return true;
}

bool LogiLedSetLightingForKeyWithKeyName(LogiLed::KeyName keyName, int redPercentage, int greenPercentage, int bluePercentage)
{
	//CLogger::OutputLog("LogiLedSetLightingForKeyWithKeyName called [Key: %i] (%i %i %i)", LogLevel::Debug, keyName, redPercentage, greenPercentage, bluePercentage);

	unsigned char redValue = (unsigned char)((float)(redPercentage / 100.0f) * 255);
	unsigned char greenValue = (unsigned char)((float)(greenPercentage / 100.0f) * 255);
	unsigned char blueValue = (unsigned char)((float)(bluePercentage / 100.0f) * 255);

	CorsairLedColor _col;
	_col.ledId = g_corsairKeyFromLogiKeyName[keyName];
	_col.r = redValue;
	_col.g = greenValue;
	_col.b = blueValue;
	CorsairSetLedsColorsAsync(1, &_col, nullptr, nullptr);

	return true;
}

bool LogiLedSaveLightingForKey(LogiLed::KeyName keyName)
{
	CLogger::OutputLog("LogiLedSaveLightingForKey called [Key: %i]", LogLevel::Debug, keyName);

	return true;
}

bool LogiLedRestoreLightingForKey(LogiLed::KeyName keyName)
{
	CLogger::OutputLog("LogiLedRestoreLightingForKey called [Key: %i]", LogLevel::Debug, keyName);

	return true;
}

bool LogiLedFlashSingleKey(LogiLed::KeyName keyName, int redPercentage, int greenPercentage, int bluePercentage, int msDuration, int msInterval)
{
	CLogger::OutputLog("LogiLedFlashSingleKey called [Key: %i] (%i %i %i %i %i)", LogLevel::Debug, keyName, redPercentage, greenPercentage, bluePercentage, msDuration, msInterval);

	return true;
}

bool LogiLedPulseSingleKey(LogiLed::KeyName keyName, int startRedPercentage, int startGreenPercentage, int startBluePercentage, int finishRedPercentage, int finishGreenPercentage, int finishBluePercentage, int msDuration, bool isInfinite)
{
	CLogger::OutputLog("LogiLedPulseSingleKey called [Key: %i] (%i %i %i %i %i %i %i %i)", LogLevel::Debug, keyName, startRedPercentage, startGreenPercentage, startBluePercentage, finishRedPercentage, finishGreenPercentage, finishBluePercentage, msDuration, isInfinite);

	return true;
}

bool LogiLedStopEffectsOnKey(LogiLed::KeyName keyName)
{
	CLogger::OutputLog("LogiLedStopEffectsOnKey called [Key: %i]", LogLevel::Debug, keyName);

	return true;
}

void LogiLedShutdown()
{
	CLogger::OutputLog_s("LogiLedShutdown called.", LogLevel::Debug);

	//cleanup();

	coloursVector.clear();

	g_hasInitialised = false;
	
}