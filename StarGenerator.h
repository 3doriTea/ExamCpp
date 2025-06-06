#pragma once
#include "GameObject.h"

class StarGenerator : public GameObject
{
public:
	StarGenerator();
	~StarGenerator();

	void Update() override;
	void Draw() override;
};
