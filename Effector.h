#pragma once
#include "GameObject.h"

class Effector : public GameObject
{
public:
	Effector(const Point& _point);
	~Effector();

	void Update() override;
	void Draw() override;

	void DrawCell(const int _id);

private:
	Point position_;
	float radius_;
	float timeLeft_;

	static int hImage_;
};
