#include "Title.h"
#include <DxLib.h>
#include "Screen.h"
#include "Input.h"
#include "Global.h"


namespace
{
	static const char TITLE[] { "ƒ^ƒCƒgƒ‹" };
	static const unsigned int TITLE_COLOR{ 0xffffff };
}

Title::Title()
{
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
}

void Title::Draw()
{
	DrawBox(0, 0, Screen::WIN_WIDTH, Screen::WIN_HEIGHT, 0x000000, TRUE);

	static const int TITLE_STRING_WDITH{ GetDrawFormatStringWidth(TITLE) };
	DrawFormatString(
		Screen::WIN_WIDTH / 2 - TITLE_STRING_WDITH / 2,
		Screen::WIN_HEIGHT / 2,
		TITLE_COLOR,
		TITLE);

	/*for (float x = 0; x < 1; x += 0.001f)
	{
		Point p = GetHartsPoint(x);
		DrawCircle(
			p.x, p.y,
			1, 0xffffff);
	}*/

	int x{};
	GetMousePoint(&x, nullptr);

	Point p = GetHartsPoint(static_cast<float>(x) / Screen::WIN_WIDTH);
	DrawCircle(
		p.x, p.y,
		20, 0x00ff00);
}
