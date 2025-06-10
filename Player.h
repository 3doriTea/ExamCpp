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

	int hImage_;      // 画像のハンドル
	float x_;         // 座標 x
	float y_;         // 座標 y
	float speed_;     // 移動速度
	int imageSizeX_;  // 画像のサイズ x
	int imageSizeY_;  // 画像のサイズ y

	std::vector<Bullet*> bullets_;
};
