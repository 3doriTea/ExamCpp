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
	float x{};
	float y{};
	float sign{};

	if (_larp < 0.25f)
	{
		// if 0/4 <= _larp < 1/4 then top right parts
		/*
		* 
		*/
		x = _larp / 0.25f;
		sign = false;
		y = Hart(x, sign);
	}
	else if (_larp < 0.5f)
	{
		// if 1/4 <= _larp < 2/4 then bottom right parts
		/*
		* 
		*/
		x = 1 - (_larp - 0.25) / 0.25f;
		sign = true;
		y = Hart(x, sign);
	}
	else if (_larp < 0.75f)
	{
		// if 2/4 <= _larp < 3/4 then bottom left parts
		/*
		* 
		*/
		x = (_larp - 0.5) / 0.25f;
		sign = true;
		y = Hart(x, sign);
	}
	else
	{
		// if 3/4 <= _larp < 4/4 then top left parts
		/*
		* 
		*/
		x = 1 - (_larp - 0.75) / 0.25f;
		sign = false;
		y = Hart(x, sign);
	}

	// ”ÍˆÍ‹·‚¢ver
	/*return
	{
		x * Screen::WIN_WIDTH / (_larp > 0.5f ? -4 : 4) + Screen::WIN_WIDTH / 2,
		y * Screen::WIN_WIDTH / -6 + Screen::WIN_HEIGHT / 2,
	};*/

	return
	{
		x * Screen::WIN_WIDTH / (_larp > 0.5f ? -2 : 2) + Screen::WIN_WIDTH / 2,
		y * Screen::WIN_WIDTH / -4 + Screen::WIN_HEIGHT / 2 - 100,
	};
}
