#include "Enemy.h"
#include <cassert>
#include <DxLib.h>

namespace
{
	int IMAGE_WIDTH{ 48 };
	int IMAGE_HEIGHT{ 48 };
}

Enemy::Enemy() :
	Enemy{ "Assets/tiny_ship10.png", 0.0f, 0.0f, 100.0f}
{
}

Enemy::Enemy(
	const char* _imageFileName,
	const float _x,
	const float _y,
	const float _speed) :
	GameObject{},
	hImage_{ -1 },
	x_{ 0.0f },
	y_{ 0.0f },
	speed_{ 0.0f },
	isAlive_{ true }
{
	hImage_ = LoadGraph(_imageFileName);
	assert(hImage_ > -1  // ‰æ‘œ‚Í³‚µ‚­“Ç‚İ‚ß‚Ä‚¢‚é
		&& "‰æ‘œ‚ª“Ç‚İ‚ß‚Ä‚¢‚È‚¢");

	y_ = _x;
	x_ = _y;
	speed_ = _speed;
}

Enemy::~Enemy()
{
	DeleteGraph(hImage_);
}

void Enemy::Update()
{
	
}

void Enemy::Draw()
{
	DrawExtendGraph(
		x_, y_,
		x_ + IMAGE_WIDTH, y_ + IMAGE_HEIGHT,
		hImage_, TRUE);
}

void Enemy::SetPosition(const float _x, const float _y)
{
	x_ = _x;
	y_ = _y;
}
