#ifndef StateBaseAI_H_
#define StateBaseAI_H_

#include "Engine/Engine.h"
#include "Collision.h"
#include "ItemManager.h"

class StateBaseAI
{
public:
	StateBaseAI();
	~StateBaseAI();

	void Update();
	void Draw();

private:
	void Wait();//�ҋ@
	void Move();//�ړ�
	void GetItem();//�A�C�e�����

	Vec2 m_pos;
	float m_speed;
	float m_angle;//�p�x
	Vec2 m_size;
	int m_timer;
	int m_step;
	Vec2 m_direction;
	int m_item_number;
	const float m_fan_length = 150.0f;
	const float m_fan_degree = 90.0f;

	Collision collision;
};

#endif
