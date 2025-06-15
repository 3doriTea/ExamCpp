#include "Stage.h"
#include <cmath>
#include <DxLib.h>
#include "Screen.h"
#include <cassert>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Effector.h"


namespace
{
	static const int ENEMY_IMAGE_WIDTH{ 48 };
	const int ENEMY_ROW_COUNT{ 7 };
	const int ENEMY_COLUMN_COUNT{ 10 };
	constexpr int ENEMY_COUNT{ ENEMY_COLUMN_COUNT * ENEMY_ROW_COUNT };
	const int ENEMY_ALIGN_X{ 50 };
	const int ENEMY_ALIGN_Y{ 50 };
	const float TO_OVER_TIME_SEC{ 1.5f };  // ÉQÅ[ÉÄÉIÅ[ÉoÅ[Ç∑ÇÈÇ‹Ç≈Ç…óvÇ∑ÇÈä‘
}

Stage::Stage() :
	player_{ nullptr },
	toOverTimeLeft_{ TO_OVER_TIME_SEC }
{
	hImage_ = LoadGraph("Assets/bg.png");
	assert(hImage_ >= 0
		&& "îwåiâÊëúÇÃì«Ç›çûÇ›Ç…é∏îs @Stage::Stage");


	player_ = new Player{};
	enemies_ = std::vector<Enemy*>(ENEMY_COUNT, nullptr);

	const int OFFSET_X = (Screen::WIN_WIDTH - (ENEMY_ALIGN_X * ENEMY_COLUMN_COUNT)) / 2;
	const int OFFSET_Y = 40.0f;
	onEnemyCount_ = ENEMY_COUNT;
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
			enemyType,
			i,
			static_cast<float>(OFFSET_X + x * ENEMY_ALIGN_X),
			static_cast<float>(OFFSET_Y + y * ENEMY_ALIGN_Y),
			0.0f
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
	if (onEnemyCount_ <= 0)
	{
		toOverTimeLeft_ -= Screen::GetDeltaTime();
		if (toOverTimeLeft_ <= 0)
		{
			Enemy::Reset();
			SceneChange(SceneType::Over);
		}
		return;
	}

	Enemy::SetPlayerPoint(player_->GetRect().GetCenter());

	std::vector<Bullet*> pBullets = player_->GetAllBullets();
	for (auto& pBullet : pBullets)
	{
		if (!pBullet->IsFire())
		{
			continue;
		}
		for (auto& pEnemy : enemies_)
		{
			if (!pEnemy->IsAlive())
			{
				continue;
			}

			//Point bulletPosition = pBullet->GetRect().GetCenter();
			if (IsHit(pEnemy->GetRect(), pBullet->GetRect()))
			{
				pEnemy->SetIsAlive(false);
				pBullet->SetIsFired(false);
				onEnemyCount_--;
				new Effector{ {pBullet->GetRect().x, pBullet->GetRect().y} };
				break;
			}
		}
	}
}

void Stage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawExtendGraph(0, 0, Screen::WIN_WIDTH, Screen::WIN_HEIGHT, hImage_, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(0, 0, Screen::WIN_WIDTH, Screen::WIN_HEIGHT, 0x000000, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	/*player_->Draw();
	for (auto&& enemy : enemies_)
	{
		enemy->Draw();
	}*/
}
