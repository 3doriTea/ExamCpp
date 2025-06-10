#include "Enemy.h"
#include <cassert>
#include <DxLib.h>
#include <cmath>
#include "Screen.h"
#include "Easings.h"

namespace
{
	int IMAGE_WIDTH{ 48 };
	int IMAGE_HEIGHT{ 48 };
	static const float BULLET_COOL_TIME_SEC{ 0.1f };
	static const int BULLET_COUNT{ 5 };  // íeÇÃêî
}

Enemy::Enemy(const EnemyType _type, const int _id) :
	Enemy{ _type, _id, 0.0f, 0.0f, 100.0f}
{
}

Enemy::Enemy(
	const EnemyType _type,
	const int _id,
	const float _x,
	const float _y,
	const float _speed) :
	GameObject{},
	id_{ _id },
	hImage_{ -1 },
	x_{ _x },
	y_{ _y },
	INIT_X_{ _x },
	INIT_Y_{ _y },
	speed_{ _speed },
	margin_{ 0 },
	type_{ MAX },
	offsetX_{ 0.0f },
	offsetY_{ 0.0f },
	imageSize_{ static_cast<float>(IMAGE_WIDTH), static_cast<float>(IMAGE_HEIGHT) },
	angle2_{ 0.0f },
	shotCoolTime_{ 0 }
{
	static const char* ENEMY_IMAGE_FILES[]
	{
		"Assets/tiny_ship10.png",
		"Assets/tiny_ship16.png",
		"Assets/tiny_ship18.png",
		"Assets/tiny_ship9.png",
	};

	hImage_ = LoadGraph(ENEMY_IMAGE_FILES[(int)_type]);
	assert(hImage_ > -1  // âÊëúÇÕê≥ÇµÇ≠ì«Ç›çûÇﬂÇƒÇ¢ÇÈ
		&& "âÊëúÇ™ì«Ç›çûÇﬂÇƒÇ¢Ç»Ç¢");

	angle_ = (_id % 16) * ((DX_PI_F * 2.0f) / 16.0f);

	if (bullets_.size() == 0)
	{
		bullets_.resize(BULLET_COUNT);
		for (int i = 0; i < BULLET_COUNT; i++)
		{
			bullets_[i] = new EnemyBullet{};
		}
	}
}

Enemy::~Enemy()
{
	DeleteGraph(hImage_);
}

void Enemy::Update()
{
	//return;
	angle_ += Screen::GetDeltaTime() * 2.0f;
	if (angle_ >= DX_PI_F * 2.0f)
	{
		angle_ -= DX_PI_F * 2.0f;
	}

	y_ = INIT_Y_ + std::sinf(angle_) * 50.0f + offsetY_;
	x_ = INIT_X_ + (std::sinf(angle_) * 60.0f) + offsetX_;

	margin_ = static_cast<int>(std::sinf(angle_) * 3.0f);

	offsetX_ += Ease::OutElastic(std::fmodf(angle_, DX_PI_F) / DX_PI_F) *
	(std::sinf(angle_ - (id_ % 16) * ((DX_PI_F * 2.0f) / 16.0f)) > 0.0f
		? 4.0f
		: -4.0f);
	float downMove{ std::sinf(angle_) };
	downMove *= downMove < 0 ? 0.01f : 0.1f;
	offsetY_ += downMove;

	static int shotCurr{};
	shotCoolTime_ -= Screen::GetDeltaTime();
	if (shotCurr <= 0)
	{
		if (shotCoolTime_ <= 0)
		{
			shotCoolTime_ += BULLET_COOL_TIME_SEC;
			shotCurr = GetRand(id_);
			EnemyBullet* bullet = GetActiveBullet();
			if (bullet != nullptr)
			{
				bullet->Fire(x_ + (IMAGE_WIDTH / 2) - 3, y_);
			}
		}
	}
	shotCurr--;
}

void Enemy::Draw()
{
	/*DrawExtendGraphF(
		x_ + margin_, y_ + margin_,
		x_ + IMAGE_WIDTH - margin_, y_ + IMAGE_HEIGHT - margin_,
		hImage_, TRUE);*/
	DrawExtendGraphF(
		x_, y_,
		x_ + IMAGE_WIDTH, y_ + IMAGE_HEIGHT,
		hImage_, TRUE);
}

void Enemy::SetPosition(const float _x, const float _y)
{
	x_ = _x;
	y_ = _y;
}

Rect Enemy::GetRect() const
{
	return { x_, y_, (float)IMAGE_WIDTH, (float)IMAGE_HEIGHT };
}

EnemyBullet* Enemy::GetActiveBullet()
{
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		if (bullets_[i]->IsFire() == false)
		{
			return bullets_[i];
		}
	}

	return nullptr;
}

std::vector<Point> Enemy::avoidPoints_{};
std::vector<EnemyBullet*> Enemy::bullets_{};
