#pragma once
#include <vector>
#include "GameObject.h"

class Player;
class Enemy;
// ‘O•ûéŒ¾‚ÍƒQ[ƒ€‰ïĞ‚Ìl‚ÉŠì‚Î‚ê‚é‚ç‚µ 

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

