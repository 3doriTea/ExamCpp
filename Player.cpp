#include "Player.h"
#include <DxLib.h>
#include <cassert>
#include "Input.h"
#include "Screen.h"
#include "Bullet.h"

namespace
{
	static const int PLAYER_IMAGE_WIDTH{ 48 };  // âÊëúÇÃâ°ïù
	static const int PLAYER_IMAGE_HEIGHT{ 48 };  // âÊëúÇÃècïù

	static const int PLAYER_BOTTOM_MARGIN{ 32 };  // â∫ÇÃãÛîí
	
	static const float PLAYER_INIT_POSITION_X{ (Screen::WIN_WIDTH / 2) - (PLAYER_IMAGE_WIDTH / 2) };  // âÊñ ÇÃîºï™
	static const float PLAYER_INIT_POSITION_Y{ Screen::WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BOTTOM_MARGIN };
	static const float PLAYER_INIT_SPEED{ 400.0f };
	static const float BULLET_COOL_TIME_SEC{ 0.1f };
	static const int BULLET_COUNT{ 5 };  // íeÇÃêî
}

Player::Player() :
	hImage_{ -1 },
	x_{ 0.0f },
	y_{ 0.0f },
	speed_{ 100.0f },
	bullets_(BULLET_COUNT)
{
	hImage_ = LoadGraph("Assets/tiny_ship5.png");
	assert(hImage_ > -1  // âÊëúÇÕê≥ÇµÇ≠ì«Ç›çûÇﬂÇƒÇ¢ÇÈ
		&& "âÊëúÇ™ì«Ç›çûÇﬂÇƒÇ¢Ç»Ç¢");

	GetGraphSize(hImage_, &imageSizeX_, &imageSizeY_);

	imageSizeX_ = PLAYER_IMAGE_WIDTH;
	imageSizeY_ = PLAYER_IMAGE_HEIGHT;

	x_ = PLAYER_INIT_POSITION_X;
	y_ = PLAYER_INIT_POSITION_Y;
	speed_ = PLAYER_INIT_SPEED;

	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullets_[i] = new Bullet{};
	}
}

Player::~Player()
{
}

void Player::Update()
{
	if (Input::IsKeepKeyDown(KEY_INPUT_A))
	{
		x_ -= speed_ * Screen::GetDeltaTime();
		if (x_ < 0)
		{
			x_ = 0;
		}
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_D))
	{
		x_ += speed_ * Screen::GetDeltaTime();
		if (x_ > Screen::WIN_WIDTH - PLAYER_IMAGE_WIDTH)
		{
			x_ = Screen::WIN_WIDTH - PLAYER_IMAGE_WIDTH;
		}
	}

	static float coolTimeLeftSec{ 0.0f };
	if (coolTimeLeftSec <= 0.0f)
	{
		if (Input::IsKeepKeyDown(KEY_INPUT_SPACE))
		{
			coolTimeLeftSec = BULLET_COOL_TIME_SEC;
			
			Bullet* bullet = GetActiveBullet();
			if (bullet != nullptr)
			{
				bullet->Fire(x_ + (PLAYER_IMAGE_WIDTH / 2) - 3, y_);
			}
			//new Bullet{ x_ + (PLAYER_IMAGE_WIDTH / 2), y_ };
		}
	}
	else
	{
		coolTimeLeftSec -= Screen::GetDeltaTime();
	}
}

void Player::Draw()
{
	DrawExtendGraph(
		static_cast<int>(x_), static_cast<int>(y_),
		static_cast<int>(x_) + PLAYER_IMAGE_WIDTH, static_cast<int>(y_) + PLAYER_IMAGE_HEIGHT,
		hImage_, TRUE);

	//DrawLine(Screen::WIN_WIDTH / 2, 0, Screen::WIN_WIDTH / 2, Screen::WIN_HEIGHT, 0xff00ff, 2);
}

Bullet* Player::GetActiveBullet()
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
