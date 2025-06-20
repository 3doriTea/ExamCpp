#pragma once
#include "GameObject.h"

class Over : public GameObject
{
public:
	Over();
	~Over();

	void Update() override;
	void Draw() override;

private:
	int hImage_;
};
