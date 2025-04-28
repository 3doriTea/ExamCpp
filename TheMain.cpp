#include "DxLib.h"
#include "Input.h"
#include "Player.h"
#include "Screen.h"

namespace
{
	const int BACKGROUND_COLOR[3] { 0, 0, 0 };

	LONGLONG crrTime;
	LONGLONG prevTime;
}

float Screen::deltaTime = 0.0f;

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(Screen::WIN_WIDTH, Screen::WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(
		BACKGROUND_COLOR[0],
		BACKGROUND_COLOR[1],
		BACKGROUND_COLOR[2]);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "ウィンドウのテスト");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowHiPerformanceCount();
	prevTime = GetNowHiPerformanceCount();

	Player* player{ new Player };

	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate();  // キーの更新をする

		crrTime = GetNowHiPerformanceCount();
		Screen::deltaTime = (crrTime - prevTime) * 0.0001f;

		prevTime = crrTime;

		//ここにやりたい処理を書く
		player->Update();
		player->Draw();

		ScreenFlip();
		WaitTimer(16);
		

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	delete player;

	DxLib_End();
	return 0;
}
