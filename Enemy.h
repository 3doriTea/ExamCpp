#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(
		const char* imageFileName_,
		const float _x,
		const float _y,
		const float _speed);
	~Enemy();

	virtual void Update() override;
	virtual void Draw() override;

	void SetPosition(const float _x, const float _y);

private:
	int hImage_;

	float x_;
	float y_;
	float speed_;

	bool isAlive_;  // ¶‚«‚Ä‚¢‚é true / false
};
