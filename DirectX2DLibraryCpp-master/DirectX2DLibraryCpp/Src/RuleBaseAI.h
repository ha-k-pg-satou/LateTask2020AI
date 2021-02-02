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
	//待機
	void Wait();
	//移動
	void Move();

	//オン・オフ法
	Rule OnOff();

	Vec2 m_pos;
	float m_speed;
	float m_angle;
	int m_timer;
	int m_step;
	Vec2 m_size;
	//移動時の向き
	Vec2 m_direction;

	Rule NowRules;//現在のルール
	int ItemNumber;//発見したアイテムの番号
	int FanItemNumber;//扇の発見したアイテムの番号
	int CircleItemNumber;//円の発見したアイテムの番号

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
