#pragma once
#include "GameObject.h"

class EnemyBullet : public GameObject
{
public:
	EnemyBullet() :
		EnemyBullet(0, 0)
	{}
	EnemyBullet(const float _x, const float _y);
	~EnemyBullet();
	void Update() override;
	void Draw() override;

	bool IsFire() const { return isFired_; }

	void Fire(const float _x, const float _y);
	void SetPosition(const float _x, const float _y)
	{
		pos_.x = _x;
		pos_.y = _y;
	}

	void GetPosition(float* _pX, float* _pY) const
	{
		*_pX = pos_.x;
		*_pY = pos_.y;
	}

	Rect GetRect() const
	{
		return { pos_.x, pos_.y, imageSize_.x, imageSize_.y };
	}

	void SetIsFired(bool _isFired)
	{
		isFired_ = _isFired;
	}

private:
	int hImage_;
	Point pos_;
	float speed_;
	Point imageSize_;
	bool isFired_;  // ”­ŽË’† true / false
};
