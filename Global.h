#pragma once
#include <cmath>
#include <DxLib.h>


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

float Hart(const float _x, const bool _sign);

struct Point
{
	float x;
	float y;

	static inline float Distance(const Point _a, const Point _b)
	{
		return std::sqrtf((_a.x - _b.x) * (_a.x - _b.x) + (_a.y - _b.y) * (_a.y - _b.y));
	}

	inline Point& operator/=(const float _value)
	{
		x /= _value;
		y /= _value;
		return *this;
	}
	inline Point& operator+=(const Point _p)
	{
		x += _p.x;
		y += _p.y;
		return *this;
	}
	inline Point& operator-=(const Point _p)
	{
		x -= _p.x;
		y -= _p.y;
		return *this;
	}
};

inline Point operator+(const Point _p1, const Point _p2)
{
	return Point{ _p1 } += _p2;
}

inline Point operator-(const Point _p1, const Point _p2)
{
	return Point{ _p1 } -= _p2;
}

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
