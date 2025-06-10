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
	angle2_{ 0.0f }
{
	static const char* ENEMY_IMAGE_FILES[]
	{
		"Assets/tiny_ship10.png",
		"Assets/tiny_ship16.png",
		"Assets/tiny_ship18.png",
		"Assets/tiny_ship9.png",
	};

	hImage_ = LoadGraph(ENEMY_IMAGE_FILES[(int)_type]);
	assert(hImage_ > -1  // ‰æ‘œ‚Í³‚µ‚­“Ç‚Ýž‚ß‚Ä‚¢‚é
		&& "‰æ‘œ‚ª“Ç‚Ýž‚ß‚Ä‚¢‚È‚¢");

	angle_ = (_id % 16) * ((DX_PI_F * 2.0f) / 16.0f);
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
