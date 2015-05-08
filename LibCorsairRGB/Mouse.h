#pragma once

namespace CorsairRGB
{
	namespace Mouse
	{
		enum class LightIDs
		{
			Front,
			Back,
			Top,
			Unknown
		};

		bool Init();
		void Shutdown();

		void SetLight(LightIDs light, const unsigned char rIn, const unsigned char gIn, const unsigned char bIn);

		void FlushLightBuffer(void);

	};
};

