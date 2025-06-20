#include "Title.h"
#include <DxLib.h>
#include "Screen.h"
#include "Input.h"
#include "Global.h"
#include <cassert>
#include "Easings.h"


namespace
{
	static const char TITLE_IMAGE_FILE[]{ "Assets/Title.png" };
	static const float SHOW_TIME_SEC{ 1.32324f };  // 表示する時間(秒)
	static const float HIDE_TIME_SEC{ 0.85325f };  // 表示する時間(秒)
}

Title::Title() :
	timeLeft_{ 0.0f }
{
	hImage_ = LoadGraph(TITLE_IMAGE_FILE);
	assert(hImage_ > 0
		&& "タイトルの画像読み込みに失敗");
}

Title::~Title()
{
}

void Title::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		SceneChange(SceneType::Play);
	}

	timeLeft_ -= Screen::GetDeltaTime();
	if (timeLeft_ <= 0.0f)
	{
		timeLeft_ += SHOW_TIME_SEC + HIDE_TIME_SEC;
	}
}

void Title::Draw()
{
	DrawBox(0, 0, Screen::WIN_WIDTH, Screen::WIN_HEIGHT, 0x000000, TRUE);
	DrawGraph(0, 0, hImage_, TRUE);
	if (timeLeft_ <= HIDE_TIME_SEC)
	{
		int alpha{ static_cast<int>(255.0f * Ease::OutBounce(1.0f - timeLeft_ / HIDE_TIME_SEC)) };
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(
			0, Screen::WIN_HEIGHT / 2,
			Screen::WIN_WIDTH, Screen::WIN_HEIGHT,
			0x000000, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
