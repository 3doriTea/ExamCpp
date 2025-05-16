#include "Stage.h"

#include "Player.h"
#include "Enemy.h"

namespace
{
	const int ENEMY_ROW_COUNT{ 7 };
	const int ENEMY_COLUMN_COUNT{ 10 };
	constexpr int ENEMY_COUNT{ ENEMY_COLUMN_COUNT * ENEMY_ROW_COUNT };
}

Stage::Stage() :
	player_{ nullptr }
{
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

void Stage::Update()
{
	/*player_->Update();
	for (auto&& enemy : enemies_)
	{
		enemy->Update();
	}*/
}

void Stage::Draw()
{
	/*player_->Draw();
	for (auto&& enemy : enemies_)
	{
		enemy->Draw();
	}*/
}
