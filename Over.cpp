#include "Over.h"
#include <DxLib.h>
#include "Screen.h"
#include "Global.h"
#include "Input.h"
#include <cassert>


namespace
{
	static const char OVER_IMAGE_FILE[]{ "Assets/GameOver.png" };
	static const char OVER_TEXT[]{ "ゲームオーバー" };
	static const unsigned int TEXT_COLOR{ 0xffffff };
	static const unsigned int BACKGROUND_COLOR{ 0x000000 };
}

Over::Over()
{
	hImage_ = LoadGraph(OVER_IMAGE_FILE);
	assert(hImage_ > 0
		&& "ゲームオーバの画像読み込みに失敗");
}

Over::~Over()
{
}

void Over::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		SceneChange(SceneType::Title);
	}
}

void Over::Draw()
{
	/*int width{}, height{}, lineCount{};
	GetDrawFormatStringSize(&width, &height, &lineCount, OVER_TEXT);

	int textDrawX{ Screen::WIN_WIDTH / 2 - width / 2 }, textDrawY{ Screen::WIN_HEIGHT / 2 };
	DrawBox(
		textDrawX, textDrawY,
		textDrawX + width, textDrawY + height, BACKGROUND_COLOR, TRUE);
	DrawFormatString(textDrawX, textDrawY, TEXT_COLOR, OVER_TEXT);*/


	DrawGraph(0, 0, hImage_, TRUE);
}
