#pragma once

#include "keymaps.h"

namespace CorsairRGB
{
	namespace Keyboard
	{
		bool Init();
		void Shutdown();

		void SetKey(Keys key, const unsigned char rIn, const unsigned char gIn, const unsigned char bIn);
		void SetKeyCode(const unsigned char keyCode, const unsigned char rIn, const unsigned char gIn, const unsigned char bIn);

		void FlushLightBuffer(void);

		void RestoreLighting(void);
	};
};