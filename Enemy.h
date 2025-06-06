#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	enum EnemyType
	{
		ZAKO,
		MID,
		KIGHT,
		BOSS,
		MAX
	};

public:
	Enemy(const EnemyType _type, const int _id);
	Enemy(
		const EnemyType _type,
		const int _id,
		const float _x,
		const float _y,
		const float _speed);
	~Enemy();

	virtual void Update() override;
	virtual void Draw() override;

	void SetPosition(const float _x, const float _y);
	void SetId(int _id) { id_ = _id; }
	int GettId() const { return id_; }

	void GetPosition(float* _pX, float* _pY) const
	{
		*_pX = x_;
		*_pY = y_;
	}

	Rect GetRect() const;

private:
	int id_;  // Ž¯•ÊŽq
	int hImage_;

	const float INIT_X_;
	const float INIT_Y_;
	float x_;
	float y_;
	float speed_;
	int margin_;  // —]”’
	float offsetX_;

	Point imageSize_;

	EnemyType type_;

	float angle_;
};
