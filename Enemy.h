#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(const char* imageFileName_);
	~Enemy();

	virtual void Update() override;
	virtual void Draw() override;

private:
	int hImage_;
};

