#include "Player.h"
#include <DxLib.h>
#include <cassert>
#include "Input.h"
#include "Screen.h"
#include "Bullet.h"

namespace
{
	static const int PLAYER_IMAGE_WIDTH{ 48 };  // 画像の横幅
	static const int PLAYER_IMAGE_HEIGHT{ 48 };  // 画像の縦幅

	static const int PLAYER_BOTTOM_MARGIN{ 32 };  // 下の空白
	
	static const float PLAYER_INIT_POSITION_X{ (Screen::WIN_WIDTH / 2) - (PLAYER_IMAGE_WIDTH / 2) };  // 画面の半分
	static const float PLAYER_INIT_POSITION_Y{ Screen::WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BOTTOM_MARGIN };
	static const float PLAYER_INIT_SPEED{ 400.0f };
	static const float BULLET_COOL_TIME_SEC{ 0.1f };
	static const int BULLET_COUNT{ 5 };  // 弾の数
	static const float ON_HIT_NO_DAMAGE_TIME{ 3.0f };

	// 無敵時間のチカチカ
	static const float NO_DAMAGE_EFFECT_SHOW{ 0.03f };  // チカチカの表示時間
	static const float NO_DAMAGE_EFFECT_HIDE{ 0.05f };  // チカチカの消失時間
	static const int NO_DAMAGE_EFFECT_ALPHA_PARAM{ 30 };  // チカチカの透明度

	static const int PLAYER_LIFE{ 3 };  // ダメージに耐えうる回数
}

Player::Player() :
	hImage_{ -1 },
	x_{ 0.0f },
	y_{ 0.0f },
	speed_{ 100.0f },
	bullets_(BULLET_COUNT),
	noDamageTimeleft_{ 0.0f },
	life_{ PLAYER_LIFE }
{
	hImage_ = LoadGraph("Assets/tiny_ship5.png");
	assert(hImage_ > -1  // 画像は正しく読み込めている
		&& "画像が読み込めていない");

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
	if (IsBroken())
	{
		return;  // 壊れているなら操作させない！
	}

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

	if (noDamageTimeleft_ >= 0.0f)
	{
		noDamageTimeleft_ -= Screen::GetDeltaTime();
	}
}

void Player::Draw()
{
	if (noDamageTimeleft_ >= 0.0f)
	{
		if (std::fmodf(noDamageTimeleft_, (NO_DAMAGE_EFFECT_SHOW + NO_DAMAGE_EFFECT_HIDE)) < NO_DAMAGE_EFFECT_SHOW)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, NO_DAMAGE_EFFECT_ALPHA_PARAM);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	DrawExtendGraph(
		static_cast<int>(x_), static_cast<int>(y_),
		static_cast<int>(x_) + PLAYER_IMAGE_WIDTH, static_cast<int>(y_) + PLAYER_IMAGE_HEIGHT,
		hImage_, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawLine(Screen::WIN_WIDTH / 2, 0, Screen::WIN_WIDTH / 2, Screen::WIN_HEIGHT, 0xff00ff, 2);
}

bool Player::TryTakeDamage()
{
	if (noDamageTimeleft_ >= 0.0f)
	{
		return false;  // 無敵時間ならダメージ与えるのに失敗
	}

	// ライフ減らして～
	life_--;
	if (life_ < 0)
	{
		life_ = 0;
	}
	// 無敵時間もセット
	noDamageTimeleft_ = ON_HIT_NO_DAMAGE_TIME;

	return true;  // ダメージ与えるのに成功
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
