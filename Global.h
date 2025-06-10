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

struct Point
{
	float x;
	float y;

	static inline float Distance(const Point _a, const Point _b)
	{
		return std::sqrtf((_a.x - _b.x) * (_a.x - _b.x) + (_a.y - _b.y) * (_a.y - _b.y));
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
