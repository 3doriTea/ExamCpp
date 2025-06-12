#pragma once
#include <cmath>

enum struct SceneType
{
	None = -1,
	Title,
	Play,
	Over,
};

extern SceneType currentScene;
extern SceneType nextScene;

void SceneChange(SceneType next);

static inline float Hart(const float _x, const bool _sign)
{
	return (std::powf(_x, 2.0f / 3.0f) + (_sign ? -1 : 1) * std::sqrtf(1.0f - _x * _x));
}

struct Point
{
	float x;
	float y;

	static inline float Distance(const Point _a, const Point _b)
	{
		return std::sqrtf((_a.x - _b.x) * (_a.x - _b.x) + (_a.y - _b.y) * (_a.y - _b.y));
	}

	Point& operator/=(const float _value)
	{
		x /= _value;
		y /= _value;
		return *this;
	}
};

struct Rect
{
	float x;
	float y;
	float width;
	float height;

	inline Point GetCenter() const
	{
		return { x + width / 2, y + height / 2 };
	}
};

Point GetHartsPoint(const float _larp);
