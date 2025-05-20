#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const float _x, const float _y);
	~Bullet();

	void Update() override;
	void Draw() override;

	void SetPosition(const float _x, const float _y);

private:
	int hImage_;
	float x_;
	float y_;
	float speed_;
	bool isAlive_;
	int imageSizeX_;
	int imageSizeY_;
};
