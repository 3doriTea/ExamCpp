#include "Global.h"
#include "Screen.h"
#include <DxLib.h>


void SceneChange(SceneType next)
{
	nextScene = next;
}

float Hart(const float _x, const bool _sign)
{
	return (std::powf(std::fabsf(_x), 2.0f / 3.0f) + (_sign ? -1 : 1) * std::sqrtf(1.0f - _x * _x));
}

Point GetHartsPoint(const float _larp)
{
	printfDx("larp=%f to ", _larp);

	float x = std::fmodf(_larp * 4.0f, 2.0f) - 1.0f;
	bool sign = static_cast<bool>(std::fmodf(_larp, 0.5f) > 0.25f);
	printfDx(sign ? "s+ " : "s- ");
	float y = Hart(x, sign);
	if (!std::isfinite(y))
	{
	}
	printfDx("x:%f, y:%f", x, y);
	printfDx("\n");

	return
	{
		x * Screen::WIN_WIDTH / (_larp > 0.5f ? -4 : 4) + Screen::WIN_WIDTH / 2,
		y * Screen::WIN_WIDTH / -6 + Screen::WIN_HEIGHT / 2,
	};
}
