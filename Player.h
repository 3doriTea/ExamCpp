#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update() override;
	void Draw() override;

private:
	int hImage_;   // �摜�̃n���h��
	float x_;      // ���W x
	float y_;      // ���W y
	float speed_;  // �ړ����x
};
