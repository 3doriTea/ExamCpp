#include "Global.h"
#include "Screen.h"


void SceneChange(SceneType next)
{
	nextScene = next;
}

Point GetHartsPoint(const float _larp)
{
	float x = std::fmodf(_larp * 4.0f, 2.0f) - 1.0f;
	float y = Hart(x, std::fmodf(_larp, 0.5f) > 0.25f);

	return
	{
		x * Screen::WIN_WIDTH / (_larp > 0.5f ? -4 : 4) + Screen::WIN_WIDTH / 2,
		y * Screen::WIN_WIDTH / -6 + Screen::WIN_HEIGHT / 2,
	};
}
