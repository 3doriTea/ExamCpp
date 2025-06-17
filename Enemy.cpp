#include "Enemy.h"
#include <cassert>
#include <DxLib.h>
#include <cmath>
#include "Screen.h"
#include "Easings.h"


namespace
{
	int IMAGE_WIDTH{ 48 };
	int IMAGE_HEIGHT{ 48 };
	static const float BULLET_COOL_TIME_SEC{ 0.1f };
	static const int BULLET_COUNT{ 5 };  // �e�̐�
	static const int MAKE_GROUP_FRAME_INTERVAL{ 60 * 10 };
	static const float GROUP_ANIM_TIME{ 10.0f };
	static const float GROUP_SPEED{ 300.0f };

	static const int GROUP_ELEMENT_COUNT{ 5 };
}

Enemy::Enemy(const EnemyType _type, const int _id) :
	Enemy{ _type, _id, 0.0f, 0.0f, 100.0f}
{
}

Enemy::Enemy(
	const EnemyType _type,
	const int _id,
	const float _x,
	const float _y,
	const float _speed) :
	GameObject{},
	id_{ _id },
	hImage_{ -1 },
	x_{ _x },
	y_{ _y },
	INIT_X_{ _x },
	INIT_Y_{ _y },
	speed_{ _speed },
	margin_{ 0 },
	type_{ MAX },
	offsetX_{ 0.0f },
	offsetY_{ 0.0f },
	imageSize_{ static_cast<float>(IMAGE_WIDTH), static_cast<float>(IMAGE_HEIGHT) },
	angle2_{ 0.0f },
	shotCoolTime_{ 0 },
	parentId_{ -1 },
	isToGoHome_{ false }
{
	// ���S�̂��߂�
	if (enemies_.size() <= id_)
	{
		enemies_.resize(id_ + 1);
		enemies_[id_] = this;
	}
	static const char* ENEMY_IMAGE_FILES[]
	{
		"Assets/tiny_ship10.png",
		"Assets/tiny_ship16.png",
		"Assets/tiny_ship18.png",
		"Assets/tiny_ship9.png",
	};

	hImage_ = LoadGraph(ENEMY_IMAGE_FILES[(int)_type]);
	assert(hImage_ > -1  // �摜�͐������ǂݍ��߂Ă���
		&& "�摜���ǂݍ��߂Ă��Ȃ�");

	animAngle_ = (_id % 16) * ((DX_PI_F * 2.0f) / 16.0f);

	if (bullets_.size() == 0)
	{
		bullets_.resize(BULLET_COUNT);
		for (int i = 0; i < BULLET_COUNT; i++)
		{
			bullets_[i] = new EnemyBullet{};
		}
	}
}

Enemy::~Enemy()
{
	DeleteGraph(hImage_);
	enemies_[id_] = nullptr;
	if (groupRootId_ == id_)
	{
		groupRootId_ = -1;
	}
}

void Enemy::Update()
{
	shotCoolTime_ -= Screen::GetDeltaTime();

	// �O���[�u�̃��[�_�[�̏���
	if (groupRootId_ == id_)
	{
		animAngle_ = DX_TWO_PI_F * (groupTimeLeft_ / GROUP_ANIM_TIME);
		float value = std::cosf(animAngle_);
		
		Point toMovePoint = GetHartsPoint(value / 2.0f + 0.5f) += Point{ static_cast<float>(dropPointX_) - Screen::WIN_WIDTH / 2, 0 };
		MoveAt(toMovePoint, GROUP_SPEED);

		if (Point::Distance(toMovePoint, { x_, y_ }) <= 1.0f)
		{
			groupTimeLeft_ -= Screen::GetDeltaTime();
		}

		if (groupTimeLeft_ <= 0.0f)
		{
			groupRootId_ = -1;
			isToGoHome_ = true;  // �A��I
		}
		return;
	}
	// �O���[�v�̃����o�[�̏���
	if (parentId_ != -1)
	{
		if (groupRootId_ == -1)  // �O���[�v���U
		{
			parentId_ = -1;
			//printfDx("���[�_���񂾁Iby%d\n", id_);
			isToGoHome_ = true;
			return;
		}
		Enemy* pPearent = GetAliveEnemy(parentId_);
		if (pPearent == nullptr)  // �e�����񂾂Ȃ���U
		{
			parentId_ = -1;
			isToGoHome_ = true;
			return;
		}

		animAngle_ = std::fmodf(pPearent->animAngle_ - (DX_TWO_PI_F / 360.0f) * 5.0f, DX_TWO_PI_F);

		float value = std::cosf(animAngle_);

		Point toMovePoint = GetHartsPoint(value / 2.0f + 0.5f) += Point{ static_cast<float>(dropPointX_) - Screen::WIN_WIDTH / 2, 0 };
		MoveAt(toMovePoint, GROUP_SPEED);

		if (shotCoolTime_ <= 0
			&& GetRect().GetCenter().x - targetPoint_.x <= 3)
		{
			shotCoolTime_ += BULLET_COOL_TIME_SEC;  // ��x��������N�[���^�C�����Z
			EnemyBullet* bullet = GetActiveBullet();  // �����ˉ\�Ȓe���擾
			if (bullet != nullptr)  // ����Ό���
			{
				bullet->Fire(x_ + (IMAGE_WIDTH / 2) - 3, y_);
			}
		}
		return;
	}
	// ���ʂ̏���

	Point movePoint = GetNormalMovePoint();  // ���̈ړ���
	
	// �A��r��
	if (isToGoHome_)
	{
		MoveAt(movePoint, GROUP_SPEED);
		if (Point::Distance({ x_, y_ }, movePoint) < 5.0f)
		{
			isToGoHome_ = false;  // �A����I�I�I
		}
		return;
	}

	animAngle_ += Screen::GetDeltaTime() * 2.0f;
	if (animAngle_ >= DX_PI_F * 2.0f)
	{
		animAngle_ -= DX_PI_F * 2.0f;
	}


	y_ = movePoint.x;
	x_ = movePoint.y;

	margin_ = static_cast<int>(std::sinf(animAngle_) * 3.0f);

	offsetX_ += Ease::OutElastic(std::fmodf(animAngle_, DX_PI_F) / DX_PI_F) *
	(std::sinf(animAngle_ - (id_ % 16) * ((DX_PI_F * 2.0f) / 16.0f)) > 0.0f
		? 4.0f
		: -4.0f);
	float downMove{ std::sinf(animAngle_) };
	downMove *= downMove < 0 ? 0.01f : 0.1f;
	offsetY_ += downMove;

	// ���e�񂵃Q�[���̂悤�Ȋ���
	static int shotCurr{};  // �e�����Ă���G���^�������_���Ɍ����߂̃J�E���g�_�E���^�C�}���ǂ�
	static int toGroupCurr{ MAKE_GROUP_FRAME_INTERVAL };  // �������O���[�v�쐬�̂��
	if (shotCurr <= 0  // �J�E���g�_�E�����ǂ���0�ȉ��ɏo���킵���G������
		&& shotCoolTime_ <= 0)  // ���A���˃N�[���^�C����0�ȉ��̂Ƃ�
	{
		shotCoolTime_ += BULLET_COOL_TIME_SEC;  // ��x��������N�[���^�C�����Z
		shotCurr = GetRand(id_);  // ���˂����玟�̃����_���ȃJ�E���g�_�E���^�C�����Z�b�g

		if (groupRootId_ == -1  // ���݂̃O���[�v���ł��Ă��Ȃ�
			&& toGroupCurr <= 0  // ���A�O���[�v�쐬�J�E���g�_�E���^�C�}���ǂ���0�ȉ��Ȃ�A�O���[�v�쐬����
			&& BringEnemyFrom(id_, GROUP_ELEMENT_COUNT) == true) // ���A�������S��n�̏W�߂Đ���
		{
			groupRootId_ = id_;
			groupTimeLeft_ = GROUP_ANIM_TIME;
			dropPointX_ = targetPoint_.x;
		}
		else  // �O���[�v�쐬���Ȃ��ꍇ�A����
		{
			EnemyBullet* bullet = GetActiveBullet();  // �����ˉ\�Ȓe���擾
			if (bullet != nullptr)  // ����Ό���
			{
				bullet->Fire(x_ + (IMAGE_WIDTH / 2) - 3, y_);
			}
		}
		// �����łȂ��ꍇ�A���̓G��0�ȉ�����
	}
	if (groupRootId_ == -1)
	{
		toGroupCurr--;  // �e�����Ă���G�����ԂɌ��炵�Ă���
	}
	shotCurr--;     // ���݃O���[�v���ł��Ă��Ȃ��Ȃ�A�e�����Ă���G�����ԂɌ��炵�Ă���
}

void Enemy::Draw()
{
	/*DrawExtendGraphF(
		x_ + margin_, y_ + margin_,
		x_ + IMAGE_WIDTH - margin_, y_ + IMAGE_HEIGHT - margin_,
		hImage_, TRUE);*/
	DrawExtendGraphF(
		x_, y_,
		x_ + IMAGE_WIDTH, y_ + IMAGE_HEIGHT,
		hImage_, TRUE);
}

void Enemy::SetPosition(const float _x, const float _y)
{
	x_ = _x;
	y_ = _y;
}

Rect Enemy::GetRect() const
{
	return { x_, y_, (float)IMAGE_WIDTH, (float)IMAGE_HEIGHT };
}

void Enemy::MoveAt(const Point _position, const float _speed)
{
	Point diff{ _position.x - x_, _position.y - y_ };
	if (diff.Size() <= (_speed * Screen::GetDeltaTime()))  // �������X�s�[�h�͈͓̔��Ȃ�
	{
		x_ = _position.x;
		y_ = _position.y;
		return;
	}
	Point unitV = Point::Norm(diff);
	unitV *= (_speed * Screen::GetDeltaTime());
	x_ += unitV.x;
	y_ += unitV.y;
}

Enemy* Enemy::GetAliveEnemy(const int _id)
{
	return enemies_[_id];
}

void Enemy::SetPlayerPoint(const Point _point)
{
	prevPlayerPoint_ = currPlayerPoint_;
	currPlayerPoint_ = _point;
	targetPoint_ = currPlayerPoint_ + (currPlayerPoint_ - prevPlayerPoint_);
}

EnemyBullet* Enemy::GetActiveBullet()
{
	return nullptr;
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		if (bullets_[i]->IsFire() == false)
		{
			return bullets_[i];
		}
	}

	return nullptr;
}

bool Enemy::BringEnemyFrom(const int _parentId, const int _countMax)
{
	//_parentId
	// �T������

	for (auto& enemy : enemies_)  // TODO: ����S�G�����񂷂�͔̂���� ���X�g���猸�炵�Ă��������������������ǁc
	{
		if (enemy == nullptr)
		{
			continue;  // ����ł�Ȃ玟
		}
		if (enemy->parentId_ != -1)
		{
			continue;  // �e������Ȃ玟
		}

		// ���""��""�m��
		enemy->parentId_ = _parentId;
		if (_countMax <= 1)  // �l���W�܂�؂����Ȃ琬���I
		{
			return true;  // ���������W�܂��Ă���e�����ɕ�
		}
		// �l���W�܂��Ă��Ȃ��Ȃ��W������
		if (BringEnemyFrom(enemy->id_, _countMax - 1))
		{
			return true;  // ��W���������Ȃ琬����e�����ɓ`����
		}
		else
		{
			enemy->parentId_ = -1;  // ��W��ł����W�܂�Ȃ������̂Ȃ���U
			return false;
		}
	}  // �ɂȓG��������Ȃ�����

	return false;  // ���s�����W�܂��Ă���e�����ɕ�
}

float Enemy::groupTimeLeft_{ 0.0f };
int Enemy::groupRootId_{ -1 };
int Enemy::dropPointX_{ 0 };
std::vector<Point> Enemy::avoidPoints_{};
std::vector<EnemyBullet*> Enemy::bullets_{};
std::vector<Enemy*> Enemy::enemies_{};
Point Enemy::prevPlayerPoint_{};
Point Enemy::currPlayerPoint_{};
Point Enemy::targetPoint_{};
