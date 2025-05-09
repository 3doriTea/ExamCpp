#pragma once

struct Vector2Ref
{
	Vector2Ref(float& _xRef, float& _yRef);
	~Vector2Ref();

	float& x_;
	float& y_;
};
