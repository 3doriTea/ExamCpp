#pragma once
#include "GameObject.h"
#include "EnemyBullet.h"

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

	void MoveAt(const Point _position, const float _speed);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_id"></param>
	/// <returns></returns>
	static Enemy* GetAliveEnemy(const int _id);

	static void SetAvoidPoints(const std::vector<Point>& _points) { avoidPoints_ = _points; }
	static void SetPlayerPoint(const Point _point);

	static std::vector<Point> avoidPoints_;
	static EnemyBullet* GetActiveBullet();
	static inline std::vector<EnemyBullet*> GetAllBullets()
	{
		return bullets_;
	}

	/// <summary>
	/// 突撃部隊に参加してくれる勇気ある機体を募る
	/// </summary>
	/// <param name="_parentId">ついていく先</param>
	/// <param name="_countMax">募集機体数</param>
	/// <returns>募りに成功したか</returns>
	static bool BringEnemyFrom(const int _parentId, const int _countMax);

	/// <summary>
	/// 敵の静的情報をリセット
	/// </summary>
	static void Reset()
	{
		bullets_.clear();
		enemies_.clear();
	};

private:
	Point GetNormalMovePoint()
	{
		return
		{
			INIT_Y_ + std::sinf(animAngle_) * 50.0f + offsetY_,
			INIT_X_ + (std::sinf(animAngle_) * 60.0f) + offsetX_,
		};
	}

	int id_;  // 識別子
	int hImage_;
	int parentId_;

	const float INIT_X_;
	const float INIT_Y_;
	float x_;
	float y_;
	float animAngle_;  // アニメーション時の角度
	float speed_;
	int margin_;  // 余白
	float offsetX_;
	float offsetY_;
	float shotCoolTime_;

	bool isToGoHome_;  // 家に帰っている

	static int dropPointX_;  // 降下攻撃のx座標

	Point imageSize_;

	EnemyType type_;

	static float groupTimeLeft_;
	float angle2_;
	static int groupRootId_;  // グルーブの一番親のid
	static std::vector<Enemy*> enemies_;
	static std::vector<EnemyBullet*> bullets_;
	static Point targetPoint_;  // 狙う座標
	static Point currPlayerPoint_;  // 今のプレイヤーの場所
	static Point prevPlayerPoint_;  // 前のプレイヤーの場所
};
