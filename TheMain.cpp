#include "DxLib.h"
#include "Input.h"
#include "Screen.h"
#include "Stage.h"
#include <vector>

namespace
{
	const int BACKGROUND_COLOR[3] { 0, 0, 0 };

	LONGLONG crrTime;
	LONGLONG prevTime;

	constexpr int ENEMY_COUNT{ 10 };

	static const float ENEMY_SPAWAN_OFFSET { 100.0f };
	static const float ENEMY_SPAWAN_DISTANCE { 50.0f };
}

extern size_t totalGameObjectCount;

std::vector<GameObject*> pGameObjects;
std::vector<GameObject*> pNewGameObjects;

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

	Stage* stage{ new Stage{} };

	#pragma region erase
	//Enemy* enemys = { new Enemy[ENEMY_COUNT]{} };

	//std::vector<Enemy> enemys(ENEMY_COUNT, {});

	/*int i{ 0 };
	for (auto&& enemy : enemys)
	{
		enemy.SetPosition(ENEMY_SPAWAN_OFFSET + i * ENEMY_SPAWAN_DISTANCE, 100.0f);
		i++;
	}*/

	/*for (int i = 0; i < ENEMY_COUNT; i++)
	{
		enemys[i].SetPosition(ENEMY_SPAWAN_OFFSET + i * ENEMY_SPAWAN_DISTANCE, 100.0f);
	}*/

	//Player* player{ new Player{} };
	//Enemy* enemy{ new Enemy{ "Assets/tiny_ship10.png", 100.0f, 100.0f, 100.0f } };
	#pragma endregion

	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate();  // キーの更新をする

		crrTime = GetNowHiPerformanceCount();
		Screen::deltaTime = (crrTime - prevTime) * 0.000001f;

		prevTime = crrTime;

		#pragma region erase
		//ここにやりたい処理を書く
		//player->Update();
		//enemy->Update();

		//player->Draw();
		//enemy->Draw();

		/*for (auto&& enemy : enemys)
		{
			enemy.Update();
			enemy.Draw();
		}*/
		#pragma endregion

		if (pNewGameObjects.size() > 0)
		{
			for (auto&& pGameObject : pNewGameObjects)
			{
				pGameObjects.push_back(pGameObject);
			}
			pNewGameObjects.clear();
		}

		/*stage.Update();
		stage.Draw();*/

		for (auto&& pGameObject : pGameObjects)
		{
			pGameObject->Update();
		}

		for (auto&& pGameObject : pGameObjects)
		{
			pGameObject->Draw();
		}

		for (auto itr = pGameObjects.begin(); itr != pGameObjects.end();)
		{
			if ((*itr)->IsAlive() == false)
			{
				delete (*itr);
				itr = pGameObjects.erase(itr);
			}
			else
			{
				itr++;
			}
		}

		//printfDx("%d\n", totalGameObjectCount);

		ScreenFlip();
		WaitTimer(16);
		

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	#pragma region erase
	/*delete player;
	delete enemy;*/

	//delete[] enemys;

	/*for (int i = 0; i < ENEMY_COUNT; i++)
	{

	}*/
	#pragma endregion

	DxLib_End();
	return 0;
}
