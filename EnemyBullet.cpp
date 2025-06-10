#include "EnemyBullet.h"
#include "Screen.h"
#include <cassert>
#include <DxLib.h>


namespace
{
	static const float BULLET_IMAGE_WIDTH{ 13 };
	static const float BULLET_IMAGE_HEIGHT{ 33 };
	static const float BULLET_INIT_SPEED{ 600.0f };
	static const char BULLET_IMAGE_PATH[]{ "Assets/beams.png" };
}

EnemyBullet::EnemyBullet(const float _x, const float _y) :
	GameObject{ true, true },
	hImage_{ -1 },
	pos_{ _x, _y },
	speed_{ BULLET_INIT_SPEED },
	//isAlive_{ true },
	isFired_{ false },
	imageSize_{ BULLET_IMAGE_WIDTH, BULLET_IMAGE_HEIGHT }
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH);
	assert(hImage_ > 0  // ’e‚Ì‰æ‘œ‚Í“Ç‚Ýž‚Ü‚ê‚Ä‚¢‚é
		&& "’e‚Ì‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚½‚æ");

	//GetGraphSize(hImage_, &imageSizeX_, &imageSizeY_);
	//x_ -= BULLET_IMAGE_WIDTH / 2;
	//pos_.y -= BULLET_IMAGE_HEIGHT / 2;
}

EnemyBullet::~EnemyBullet()
{
	DeleteGraph(hImage_);
}

void EnemyBullet::Update()
{
	if (isFired_ == false)
	{
		return;
	}

	float dt{ Screen::GetDeltaTime() };
	pos_.y += dt * speed_;

	if (pos_.y > Screen::WIN_HEIGHT)
	{
		isFired_ = false;
	}
}

void EnemyBullet::Draw()
{
	if (isFired_ == false)
	{
		return;
	}

	DrawExtendGraphF(pos_.x - +imageSize_.x / 2, pos_.y, pos_.x + imageSize_.x / 2, pos_.y + imageSize_.y, hImage_, TRUE);
}

void EnemyBullet::Fire(const float _x, const float _y)
{
	SetPosition(_x, _y);
	isFired_ = true;
}
