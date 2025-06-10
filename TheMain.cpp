#include "DxLib.h"
#include "Input.h"
#include "Screen.h"
#include "Stage.h"
#include "Title.h"
#include "Over.h"
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

SceneType currentScene;
SceneType nextScene;

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

	currentScene = SceneType::None;

	while (true)
	{
		//ClearDrawScreen();
		Input::KeyStateUpdate();  // キーの更新をする

		crrTime = GetNowHiPerformanceCount();
		Screen::deltaTime = (crrTime - prevTime) * 0.000001f;

		prevTime = crrTime;

		if (pNewGameObjects.size() > 0)
		{
			for (auto&& pGameObject : pNewGameObjects)
			{
				pGameObjects.push_back(pGameObject);
			}
			pNewGameObjects.clear();
		}

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

		ScreenFlip();
		WaitTimer(16);

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;

		if (nextScene != currentScene)
		{
			for (auto&& pGameObject : pGameObjects)
			{
				delete pGameObject;
			}
			pGameObjects.clear();
			switch (nextScene)
			{
			case SceneType::Title:
				new Title{};
				break;
			case SceneType::Play:
			{
				Stage* stage{ new Stage{} };
			}
			break;
			case SceneType::Over:
				new Over{};
				break;
			default:
				break;
			}
			currentScene = nextScene;
		}
	}

	DxLib_End();
	return 0;
}
