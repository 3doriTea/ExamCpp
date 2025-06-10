#include "Effector.h"
#include <DxLib.h>
#include "Screen.h"
#include "Easings.h"


namespace
{
	static const int IMAGE_WIDTH{ 100 };
	static const int IMAGE_HEIGHT{ 100 };
	static const float EFFECT_TIME{ 1.0f };// 3.0f };  //”š”­ŽžŠÔ(•b)
	static const int CELL_COLUMN{ 3 };
	static const int CELL_ROW{ 3 };
	static const int CELL_SIZE_X{ 144 / CELL_COLUMN };
	static const int CELL_SIZE_Y{ 144 / CELL_ROW };
	static const char* EFFECT_IMAGE_FILE_NAME{ "Assets/explosion.png" };
}

Effector::Effector(const Point& _point) :
	position_{ _point },
	timeLeft_{ EFFECT_TIME },
	radius_{ 30 }
{
	if (hImage_ == -1)
	{
		hImage_ = LoadGraph(EFFECT_IMAGE_FILE_NAME);
	}
}

Effector::~Effector()
{
}

void Effector::Update()
{
	timeLeft_ -= Screen::GetDeltaTime();
	if (timeLeft_ <= 0.0f)
	{
		isAlive_ = false;
	}
}

void Effector::Draw()
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 200);

	/*DrawCircle(
		(int)position_.x,
		(int)position_.y,
		(int)radius_,
		0xffffff);*/
	
	DrawCell(static_cast<int>(Ease::InOutBounce((EFFECT_TIME - timeLeft_) / EFFECT_TIME) * (CELL_COLUMN * CELL_ROW)));
	//DrawCell(0);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Effector::DrawCell(const int _id)
{
	const int X = _id % CELL_COLUMN;
	const int Y = _id / CELL_COLUMN;

	DrawRectExtendGraphF(
		position_.x - IMAGE_WIDTH / 2, position_.y - IMAGE_HEIGHT / 2,
		position_.x + IMAGE_WIDTH / 2, position_.y + IMAGE_HEIGHT / 2,
		CELL_SIZE_X * X, CELL_SIZE_Y * Y,
		CELL_SIZE_X, CELL_SIZE_Y,
		hImage_, TRUE);
}

int Effector::hImage_{ -1 };
