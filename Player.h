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

	/// <summary>
	/// 試しにダメージを与える
	/// </summary>
	/// <returns>ダメージを与えれた true / false</returns>
	bool TryTakeDamage();
	/// <summary>
	/// 壊されている？
	/// </summary>
	/// <returns>壊されている true / false</returns>
	bool IsBroken() const { return life_ <= 0; }

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

	float noDamageTimeleft_;  // ダメージを受けない時間
	int life_;        // ライフ
	int hImage_;      // 画像のハンドル
	float x_;         // 座標 x
	float y_;         // 座標 y
	float speed_;     // 移動速度
	int imageSizeX_;  // 画像のサイズ x
	int imageSizeY_;  // 画像のサイズ y

	std::vector<Bullet*> bullets_;
};
