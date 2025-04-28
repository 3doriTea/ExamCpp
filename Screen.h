#pragma once

namespace Screen
{
	// XGA SIZE
	const int WIN_WIDTH{ 1024 };
	const int WIN_HEIGHT{ 768 };

	const int USE_COLOR_BIT{ 32 };

	/*using Color = unsigned int;

	const Color BACKGROUND_COLOR{};

	const int BACKGROUND_COLOR[3]{ 0x00, 0x00, 0x00 };*/
	extern float deltaTime;  // ƒtƒŒ[ƒ€ŠÔŠÔ

	inline float GetDeltaTime()
	{
		return deltaTime;
	}

}
