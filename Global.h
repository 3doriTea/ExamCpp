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

inline float Larp(const float _value, const float _max)
{
	return _value / _max;
}

struct Point
{
	float x;
	float y;

	inline float Size() const
	{
		return std::sqrtf(x * x + y * y);
	}

	static inline Point Norm(const Point _p)
	{
		return Point{ _p } /= _p.Size();
	}

	static inline float Distance(const Point _a, const Point _b)
	{
		Point diff{ _a };
		diff -= _b;
		return diff.Size();
	}
	
	inline Point& operator/=(const float _value)
	{
		x /= _value;
		y /= _value;
		return *this;
	}
	inline Point& operator*=(const float _value)
	{
		x *= _value;
		y *= _value;
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

inline Point operator*(const Point _p, const float _value)
{
	return Point{ _p } *= _value;
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
