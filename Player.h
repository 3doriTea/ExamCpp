#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update() override;
	void Draw() override;

private:
	int hImage_;   // 画像のハンドル
	float x_;      // 座標 x
	float y_;      // 座標 y
	float speed_;  // 移動速度
};
