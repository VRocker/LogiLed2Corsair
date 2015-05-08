# LogiLed2Corsair

A DLL to convert Logitech LED API calls to Corsair RGB keyboards such as the K70 RGB

# Project Status

Currently only LogiLedInit, LogiLedRestoreLighting, LogiLedSetLightingFromBitmap and LogiLedShutdown are implemented. Other calls will be implemented later on.
I have tested this on the Corsair K70 RGB keyboard but it should work on the K95 and maybe the K65 too. Future plans are to hook up Corsair mice as well, such as the M65 RGB.

# How to build

A Visual Studio 2013 project file is included. 

# How to use

To use this in games such as GTAV, create a new registry key at HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{a6519e67-7632-4375-afdf-caa889744403}\ServerBinary and place the path to the DLL as the default key. This should be safe for online use as GTA tries to load this DLL anyway. Rememeber to use the 64bit build!
To use in other games it may be possible to rename this to LogitechLED.dll and overwrite any existing DLLs. Fairly sure LoL has this.

If any lighting issues are experienced, close the CUE utility before launching the game. From testing it seems that the game overrides CUE while it's running for me though so it might work fine.

# Thanks

Interfacing with the Corsair keyboard is all thanks to this repo: https://github.com/Palmr/LibCorsairRGB as i based the one i use on this. 
Credit also goes to https://github.com/CalcProgrammer1/CorsairKeyboardSpectrograph for the code to interface with USB in windows without using libusb

