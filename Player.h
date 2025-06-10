#pragma once
#include "GameObject.h"
#include <vector>

class Bullet;

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update() override;
	void Draw() override;

	Rect GetRect() const
	{
		return { x_, y_, (float)imageSizeX_, (float)imageSizeY_ };
	}

	inline std::vector<Bullet*> GetAllBullets() const
	{
		return bullets_;
	}

private:
	Bullet* GetActiveBullet();

	int hImage_;      // �摜�̃n���h��
	float x_;         // ���W x
	float y_;         // ���W y
	float speed_;     // �ړ����x
	int imageSizeX_;  // �摜�̃T�C�Y x
	int imageSizeY_;  // �摜�̃T�C�Y y

	std::vector<Bullet*> bullets_;
};
