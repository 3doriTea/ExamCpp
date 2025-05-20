#include "Bullet.h"
#include <cassert>
#include <DxLib.h>
#include "Screen.h"

namespace
{
	static const float BULLET_IMAGE_WIDTH{ 13 };
	static const float BULLET_IMAGE_HEIGHT{ 33 };
	static const float BULLET_INIT_SPEED{ 6000.0f };
	static const char BULLET_IMAGE_PATH[]{ "Assets/laserBlue07.png" };
}

Bullet::Bullet() :
	Bullet{ 0, 0 }
{
	DeleteGraph(hImage_);
}

Bullet::Bullet(const float _x, const float _y) :
	hImage_{ -1 },
	x_{ _x },
	y_{ _y },
	speed_{ BULLET_INIT_SPEED },
	isAlive_{ true },
	imageSizeX_{ -1 },
	imageSizeY_{ -1 }
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH);
	assert(hImage_ > 0  // ’e‚Ì‰æ‘œ‚Í“Ç‚İ‚Ü‚ê‚Ä‚¢‚é
		&& "’e‚Ì‰æ‘œ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚½‚æ");

	GetGraphSize(hImage_, &imageSizeX_, &imageSizeY_);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (isAlive_ == false)
	{
		return;
	}

	float dt{ Screen::GetDeltaTime() };
	y_ -= dt * speed_;
	
	if (y_ < -imageSizeY_)
	{
		isAlive_ = false;
	}
}

void Bullet::Draw()
{
	if (isAlive_ == false)
	{
		return;
	}

	DrawExtendGraph(x_ , y_, x_ + imageSizeX_, y_ + imageSizeY_, hImage_, TRUE);
}

void Bullet::SetPosition(const float _x, const float _y)
{
	x_ = _x;
	y_ = _y;
}
