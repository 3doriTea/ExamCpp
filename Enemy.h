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

private:
	int id_;  // ¯•Êq
	int hImage_;

	const float INIT_X_;
	const float INIT_Y_;
	float x_;
	float y_;
	float speed_;
	int margin_;  // —]”’
	float offsetX_;

	EnemyType type_;

	float angle_;

	bool isAlive_;  // ¶‚«‚Ä‚¢‚é true / false
};
