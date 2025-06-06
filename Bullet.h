#pragma once
#include "GameObject.h"

namespace
{
	static const size_t BULLETS_CAPACITY{ 10 };
}

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const float _x, const float _y);
	~Bullet();

	void Update() override;
	void Draw() override;

	bool IsFire() const { return isFired_; }

	void Fire(const float _x, const float _y);
	void SetPosition(const float _x, const float _y);

	void GetPosition(float* _pX, float* _pY) const
	{
		*_pX = x_;
		*_pY = y_;
	}

	Rect GetRect() const
	{
		return { x_, y_, imageSize_.x, imageSize_.y };
	}

	void SetIsFired(bool _isFired)
	{
		isFired_ = _isFired;
	}

private:
	int hImage_;
	float x_;
	float y_;
	float speed_;
	Point imageSize_;
	// int imageSizeX_;
	// int imageSizeY_;
	bool isFired_;  // ”­ŽË’† true / false

	static Bullet* bullets[];
};
