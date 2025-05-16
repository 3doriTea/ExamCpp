#pragma once
#include <vector>
#include "GameObject.h"

class Player;
class Enemy;
// �O���錾�̓Q�[����Ђ̐l�Ɋ�΂��炵 

class Stage : public GameObject
{
public:
	Stage();
	~Stage();

	void Update() override;
	void Draw() override;

private:
	Player* player_;
	std::vector<Enemy*> enemies_;
};

