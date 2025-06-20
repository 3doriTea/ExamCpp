#pragma once
#include "GameObject.h"

class Title : public GameObject
{
public:
	Title();
	~Title();

	void Update() override;
	void Draw() override;
private:
	int hImage_;
	float timeLeft_;
};
