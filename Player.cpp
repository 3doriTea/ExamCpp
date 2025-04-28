#include "Player.h"
#include <DxLib.h>
#include <cassert>
#include "Input.h"
#include "Screen.h"

namespace
{
	const int PLAYER_IMAGE_WIDTH{ 48 };  // ‰æ‘œ‚Ì‰¡•
	const int PLAYER_IMAGE_HEIGHT{ 48 };  // ‰æ‘œ‚Ìc•

	const int PLAYER_BOTTOM_MARGIN{ 32 };  // ‰º‚Ì‹ó”’
	
	const float PLAYER_INIT_POSITION_X{ (Screen::WIN_WIDTH / 2) - (PLAYER_IMAGE_WIDTH / 2) };  // ‰æ–Ê‚Ì”¼•ª
	const float PLAYER_INIT_POSITION_Y{ Screen::WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BOTTOM_MARGIN };
	const float PLAYER_INIT_SPEED{ 10.0f };
}

Player::Player() :
	hImage_{ -1 },
	x_{ 0.0f },
	y_{ 0.0f },
	speed_{ 0.0f }
{
	hImage_ = LoadGraph("Assets/tiny_ship5.png");

	x_ = PLAYER_INIT_POSITION_X;
	y_ = PLAYER_INIT_POSITION_Y;
	speed_ = PLAYER_INIT_SPEED;

	assert(hImage_ > -1  // ‰æ‘œ‚Í³‚µ‚­“Ç‚İ‚ß‚Ä‚¢‚é
		&& "‰æ‘œ‚ª“Ç‚İ‚ß‚Ä‚¢‚È‚¢");
}

Player::~Player()
{
}

void Player::Update()
{
	if (Input::IsKeepKeyDown(KEY_INPUT_A))
	{
		x_ -= speed_ * Screen::GetDeltaTime();
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_D))
	{
		x_ += speed_ * Screen::GetDeltaTime();
	}
}

void Player::Draw()
{
	DrawExtendGraph(
		x_, y_,
		x_ + PLAYER_IMAGE_WIDTH, y_ + PLAYER_IMAGE_HEIGHT,
		hImage_, TRUE);

	DrawLine(Screen::WIN_WIDTH / 2, 0, Screen::WIN_WIDTH / 2, Screen::WIN_HEIGHT, 0xff00ff, 2);
}
