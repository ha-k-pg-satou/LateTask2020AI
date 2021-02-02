#ifndef RuleBaseAI_H_
#define RuleBaseAI_H_

#include "Engine/Engine.h"
#include "Collision.h"
#include "ItemManager.h"

enum class Rule
{
	HitFanArea,
	HitCircleArea,
	Noen,
};

class RuleBaseAI
{
public:
	RuleBaseAI();
	~RuleBaseAI();

	void Update();
	void Draw();
private:
	//�ҋ@
	void Wait();
	//�ړ�
	void Move();

	//�I���E�I�t�@
	Rule OnOff();

	Vec2 m_pos;
	float m_speed;
	float m_angle;
	int m_timer;
	int m_step;
	Vec2 m_size;
	//�ړ����̌���
	Vec2 m_direction;

	Rule NowRules;//���݂̃��[��
	int ItemNumber;//���������A�C�e���̔ԍ�
	int FanItemNumber;//��̔��������A�C�e���̔ԍ�
	int CircleItemNumber;//�~�̔��������A�C�e���̔ԍ�

	bool HitFan;
	bool HitCircle;
	Rule HitLastTime;

	const float FanLengh = 200.0f;
	const float FanDegree = 90.0f;
	const float CircleRadius = 80.0f;

	Collision collision;

	Vec2 ItemPos[5];
};

#endif
