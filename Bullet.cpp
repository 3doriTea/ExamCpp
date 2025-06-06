#include "Bullet.h"
#include <cassert>
#include <DxLib.h>
#include "Screen.h"


namespace
{
	static const float BULLET_IMAGE_WIDTH{ 13 };
	static const float BULLET_IMAGE_HEIGHT{ 33 };
	static const float BULLET_INIT_SPEED{ 600.0f };
	static const char BULLET_IMAGE_PATH[]{ "Assets/laserBlue07.png" };
}

Bullet::Bullet() :
	Bullet{ 0, 0 }
{
}

Bullet::Bullet(const float _x, const float _y) :
	GameObject{ true, true },
	hImage_{ -1 },
	x_{ _x },
	y_{ _y },
	speed_{ BULLET_INIT_SPEED },
	//isAlive_{ true },
	isFired_{ false },
	imageSize_{ BULLET_IMAGE_WIDTH, BULLET_IMAGE_HEIGHT }
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH);
	assert(hImage_ > 0  // ’e‚Ì‰æ‘œ‚Í“Ç‚İ‚Ü‚ê‚Ä‚¢‚é
		&& "’e‚Ì‰æ‘œ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚½‚æ");

	//GetGraphSize(hImage_, &imageSizeX_, &imageSizeY_);
	x_ -= BULLET_IMAGE_WIDTH / 2 - 1;
	y_ -= BULLET_IMAGE_HEIGHT / 2;
}

Bullet::~Bullet()
{
	DeleteGraph(hImage_);
}

void Bullet::Update()
{
	if (isFired_ == false)
	{
		return;
	}

	float dt{ Screen::GetDeltaTime() };
	y_ -= dt * speed_;
	
	if (y_ < -imageSize_.y)
	{
		isFired_ = false;
	}
}

void Bullet::Draw()
{
	if (isFired_ == false)
	{
		return;
	}

	printfDx("x:%d, y:%d ::%d\n", (int)x_, (int)y_, isFired_);

	DrawExtendGraphF(x_ , y_, x_ + imageSize_.x, y_ + imageSize_.y, hImage_, TRUE);
}

void Bullet::Fire(const float _x, const float _y)
{
	SetPosition(_x, _y);
	isFired_ = true;
}

void Bullet::SetPosition(const float _x, const float _y)
{
	x_ = _x;
	y_ = _y;
}
