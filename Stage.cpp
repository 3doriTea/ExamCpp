#include "Stage.h"
#include <cmath>
#include <DxLib.h>
#include "Screen.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Effector.h"


namespace
{
	const int ENEMY_ROW_COUNT{ 7 };
	const int ENEMY_COLUMN_COUNT{ 10 };
	constexpr int ENEMY_COUNT{ ENEMY_COLUMN_COUNT * ENEMY_ROW_COUNT };
}

Stage::Stage() :
	player_{ nullptr }
{
	hImage_ = LoadGraph("Assets/bg.png");

	player_ = new Player{};
	enemies_ = std::vector<Enemy*>(ENEMY_COUNT, nullptr);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		int x = i / ENEMY_ROW_COUNT;
		int y = i % ENEMY_ROW_COUNT;
		Enemy::EnemyType enemyType
		{
			y == 0 ? Enemy::EnemyType::BOSS
			: y == 1 ? Enemy::EnemyType::KIGHT
			: y == 2 ? Enemy::EnemyType::MID
			: Enemy::EnemyType::ZAKO
		};

		enemies_[i] = new Enemy
		{
			enemyType, i, 100.0f + x * 50.0f, 100.0f + y * 50.0f, 0.0f
		};
		//enemies_[i]->SetPosition(100 + x * 50, 100 + y * 50);
	}
}

Stage::~Stage()
{
}

static bool IsHit(const Point _a, const Point _b, const float _hitDistance)
{
	return std::sqrtf(_a.x * _a.x + _b.x * _b.x) <= _hitDistance;
}

static bool IsHit(const Rect& _a, const Rect& _b)
{
	Point centerA{ _a.GetCenter() };
	Point centerB{ _b.GetCenter() };

	Point diff{ centerA.x - centerB.x, centerA.y - centerB.y };

	if ((_a.width + _b.width) / 2 > std::fabsf(diff.x)
		&& (_a.height + _b.height) / 2 > std::fabsf(diff.y))
	{
		return true;
	}

	return false;
}

void Stage::Update()
{
	//for (auto&& pEnemy : enemies_)
	//{
	//	Point enemyPosition = pEnemy->GetRect().GetCenter();
	//	std::vector<Bullet*> pBullets = player_->GetAllBullets();
	//	for (auto&& pBullet : pBullets)
	//	{
	//		Point bulletPosition = pBullet->GetRect().GetCenter();
	//		if (IsHit(enemyPosition, bulletPosition, 100.0f))
	//		{
	//			pEnemy->SetIsAlive(false);
	//			pBullet->SetIsFired(false);
	//			break;
	//		}
	//	}
	//}

	//for (auto& pEnemy : enemies_)
	//{
	//	//Point enemyPosition = pEnemy->GetRect().GetCenter();
	//	std::vector<Bullet*> pBullets = player_->GetAllBullets();
	//	for (auto& pBullet : pBullets)
	//	{
	//		if (!pBullet->IsFire())
	//		{
	//			continue;
	//		}
	//		//Point bulletPosition = pBullet->GetRect().GetCenter();
	//		if (IsHit(pEnemy->GetRect(), pBullet->GetRect()))
	//		{
	//			pEnemy->SetIsAlive(false);
	//			pBullet->SetIsFired(false);
	//			break;
	//		}
	//	}
	//}

	std::vector<Bullet*> pBullets = player_->GetAllBullets();
	for (auto& pBullet : pBullets)
	{
		if (!pBullet->IsFire())
		{
			continue;
		}

		for (auto& pEnemy : enemies_)
		{
			//Point bulletPosition = pBullet->GetRect().GetCenter();
			if (IsHit(pEnemy->GetRect(), pBullet->GetRect()))
			{
				pEnemy->SetIsAlive(false);
				pBullet->SetIsFired(false);
				new Effector{ {pBullet->GetRect().x, pBullet->GetRect().y} };
				break;
			}
		}
	}

	/*player_->Update();
	for (auto&& enemy : enemies_)
	{
		enemy->Update();
	}*/
}

void Stage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawExtendGraph(0, 0, Screen::WIN_WIDTH, Screen::WIN_HEIGHT, hImage_, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	/*player_->Draw();
	for (auto&& enemy : enemies_)
	{
		enemy->Draw();
	}*/
}
