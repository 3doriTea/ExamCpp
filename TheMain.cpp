#include "DxLib.h"
#include "Input.h"
#include "Player.h"
#include "Screen.h"
#include "Enemy.h"

namespace
{
	const int BACKGROUND_COLOR[3] { 0, 0, 0 };

	LONGLONG crrTime;
	LONGLONG prevTime;

	constexpr int ENEMY_COUNT{ 10 };

	static const float ENEMY_SPAWAN_OFFSET { 100.0f };
	static const float ENEMY_SPAWAN_DISTANCE { 50.0f };
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

	Enemy* enemys = { new Enemy[ENEMY_COUNT]{} };

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		enemys[i].SetPosition(ENEMY_SPAWAN_OFFSET + i * ENEMY_SPAWAN_DISTANCE, 100.0f);
	}

	Player* player{ new Player{} };
	Enemy* enemy{ new Enemy{ "Assets/tiny_ship10.png", 100.0f, 100.0f, 100.0f } };

	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate();  // キーの更新をする

		crrTime = GetNowHiPerformanceCount();
		Screen::deltaTime = (crrTime - prevTime) * 0.0000001f;

		prevTime = crrTime;

		//ここにやりたい処理を書く
		player->Update();
		enemy->Update();

		player->Draw();
		enemy->Draw();

		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			enemys[i].Update();
			enemys[i].Draw();
		}

		ScreenFlip();
		WaitTimer(16);
		

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	delete player;
	delete enemy;

	delete[] enemys;

	/*for (int i = 0; i < ENEMY_COUNT; i++)
	{

	}*/

	DxLib_End();
	return 0;
}
