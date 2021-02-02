#include "StateBaseAI.h"
#include <time.h>
#include <math.h>

StateBaseAI::StateBaseAI()
{
	m_pos = Vec2(250.0f, 200.0f);
	m_speed = 1.0f;
	m_size = Vec2(45.0f, 45.0f);
	m_timer = 0;
	m_step = 0;
	m_direction = Vec2(0.0f, 0.0f);
	m_item_number = 0;

	srand((unsigned int)time(NULL));
}

StateBaseAI::~StateBaseAI()
{

}

void StateBaseAI::Update()
{
	switch (m_step)
	{
	case 0:
		Wait();
		break;
	case 1:
		Move();
		break;
	case 2:
		GetItem();
		break;
	default:
		break;
	}

	for (int i = 0; i < 5; i++)
	{
		if (collision.OnCollisionCircleAndPoint(m_pos, m_size, ItemManager::Instance()->item[i].GetPos()) == true)
		{
			ItemManager::Instance()->item[i].SetIsActive(false);
		}
	}
}

void StateBaseAI::Draw()
{
	Vec2 center = Vec2(m_pos.X + m_size.X / 2, m_pos.Y + m_size.Y / 2);

	Engine::DrawTexture(m_pos.X, m_pos.Y, "Enemy");

	//扇の描画
	Engine::DrawFan(center, m_fan_degree, m_fan_length, m_angle, 0x90ff0000);
}

void StateBaseAI::Wait()
{
	m_timer++;
	if (m_timer >= 120)
	{
		m_step = 1;
		m_timer = -1;
	}

	Vec2 center = Vec2(m_pos.X + m_size.X / 2, m_pos.Y + m_size.Y / 2);

	if (ItemManager::Instance()->item[m_item_number].GetIsActive() == true)
	{
		for (int i = 0; i < 5; i++)
		{
			if (collision.OnCollisionArcAndPoint(center, ItemManager::Instance()->item[i].GetPos(),
				m_fan_degree, m_angle, m_fan_length) == true)
			{
				m_item_number = i;
				m_step = 2;
				break;
			}
		}
	}
}

void StateBaseAI::Move()
{
	m_timer++;
	if (m_timer == 0)
	{
		//角度
		m_angle = rand() % 360;

		//ラジアン変換
		float rad = m_angle * 3.14 / 180;

		m_direction = Vec2(cosf(rad), sinf(rad));
	}

	//移動
	m_pos.X += m_direction.X * m_speed;
	m_pos.Y += m_direction.Y * m_speed;

	//画面外への移動を防止
	if (m_pos.X < 0.0f)
	{
		m_pos.X = 0.0f;
	}
	if (m_pos.X > 592.0f)
	{
		m_pos.X = 592.0f;
	}
	if (m_pos.Y < 0.0f)
	{
		m_pos.Y = 0.0f;
	}
	if (m_pos.Y > 432.0f)
	{
		m_pos.Y = 432.0f;
	}

	if (m_timer >= 180)
	{
		m_timer = 0;
		m_step = 0;
	}

	Vec2 center = Vec2(m_pos.X + m_size.X / 2, m_pos.Y + m_size.Y / 2);

	for (int i = 0; i < 5; i++)
	{
		if (collision.OnCollisionArcAndPoint(center, ItemManager::Instance()->item[i].GetPos(),
			m_fan_degree, m_angle, m_fan_length) == true)
		{
			m_item_number = i;
			m_step = 2;
			break;
		}
	}
}

void StateBaseAI::GetItem()
{
	//ベクトルの算出
	Vec2 Vector =
		Vec2((ItemManager::Instance()->item[m_item_number].GetPos().X) - (m_pos.X + m_size.X / 2),
			(ItemManager::Instance()->item[m_item_number].GetPos().Y) - (m_pos.Y + m_size.Y / 2));

	//単位ベクトルの算出
	float Length = sqrt(Vector.X * Vector.X + Vector.Y * Vector.Y);
	Vec2 Normal = Vec2(Vector.X / Length, Vector.Y / Length);

	//移動
	m_pos.X += Normal.X * m_speed;
	m_pos.Y += Normal.Y * m_speed;

	//距離
	Vec2 Distance = Vec2(ItemManager::Instance()->item[m_item_number].GetPos().X - m_pos.X,
						ItemManager::Instance()->item[m_item_number].GetPos().Y - m_pos.Y);
	//向いている方向
	m_angle = atan(Vector.Y / Vector.X) * (180.0f / 3.14);
	if (Vector.X < 0)
	{
		m_angle += 180;
	}

	//移動終了
	if (ItemManager::Instance()->item[m_item_number].GetIsActive() == false)
	{
		m_timer = -1;
		m_step = 0;
	}
}