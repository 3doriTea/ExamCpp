#pragma once
#include <vector>
#include "GameObject.h"

class Player;
class Enemy;
// 前方宣言はゲーム会社の人に喜ばれるらし 

class Stage : public GameObject
{
public:
	Stage();
	~Stage();

	void Update() override;
	void Draw() override;

private:
	bool isPlayerDown_;
	Player* player_;
	std::vector<Enemy*> enemies_;
	int hImage_;
	int onEnemyCount_;
	float toOverTimeLeft_;
};

