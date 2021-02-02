#include "RuleBaseAI.h"
#include <time.h>
#include <math.h>

RuleBaseAI::RuleBaseAI()
{
	m_pos = Vec2(350.0f, 200.0f);
	m_speed = 1.0f;
	m_angle = 0.0f;
	m_timer = 0.0f;
	m_step = 0;
	m_size = Vec2(45.0f, 45.0f);
	m_direction = Vec2(0.0f, 0.0f);

	NowRules = Rule::Noen;
	ItemNumber = 0;
	FanItemNumber = 0;
	CircleItemNumber = 0;

	HitFan = false;
	HitCircle = false;
	HitLastTime = Rule::Noen;

	srand((unsigned int)time(NULL));
}

RuleBaseAI::~RuleBaseAI()
{

}

void RuleBaseAI::Update()
{
	Vec2 Center = Vec2(m_pos.X + m_size.X / 2, m_pos.Y + m_size.Y / 2);

	switch (m_step)
	{
	case 0:
		Wait();
		break;
	case 1:
		Move();
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

void RuleBaseAI::Draw()
{
	Vec2 Center = Vec2(m_pos.X + m_size.X / 2, m_pos.Y + m_size.Y / 2);

	Engine::DrawTexture(m_pos.X, m_pos.Y, "Enemy");

	//‰~
	Engine::DrawFan(Center, 360.0f, CircleRadius, m_angle, 0x900000ff);
	//î
	Engine::DrawFan(Center, FanDegree, FanLengh, m_angle, 0x90ff0000);
}

//‘Ò‹@
void RuleBaseAI::Wait()
{
	m_timer++;
	if (m_timer >= 120)
	{
		NowRules = Rule::Noen;
		HitFan = false;
		HitCircle = false;
		m_timer = 298;
		m_step = 1;
	}
}

//ˆÚ“®
void RuleBaseAI::Move()
{
	if (NowRules == Rule::Noen)
	{
		NowRules = OnOff();

		m_timer++;

		if (m_timer >= 300)
		{
			//Šp“x
			m_angle = rand() % 360;

			//ƒ‰ƒWƒAƒ“•ÏŠ·
			float rad = m_angle * 3.14 / 180;

			m_direction = Vec2(cosf(rad), sinf(rad));

			m_timer = 0;
		}

		//ˆÚ“®
		m_pos.X += m_direction.X * m_speed;
		m_pos.Y += m_direction.Y * m_speed;

		//‰æ–ÊŠO‚Ö‚ÌˆÚ“®‚ð–hŽ~
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
	}
	else if (NowRules == Rule::HitFanArea || NowRules == Rule::HitCircleArea)
	{
		//ƒxƒNƒgƒ‹‚ÌŽZo
		Vec2 Vector = 
			Vec2((ItemManager::Instance()->item[ItemNumber].GetPos().X) - (m_pos.X + m_size.X / 2),
				(ItemManager::Instance()->item[ItemNumber].GetPos().Y) - (m_pos.Y + m_size.Y / 2));
		
		//’PˆÊƒxƒNƒgƒ‹‚ÌŽZo
		float Length = sqrt(Vector.X * Vector.X + Vector.Y * Vector.Y);
		Vec2 Normal = Vec2(Vector.X / Length, Vector.Y / Length);

		//ˆÚ“®
		m_pos.X += Normal.X * m_speed;
		m_pos.Y += Normal.Y * m_speed;

		//ˆÚ“®I—¹
		if (ItemManager::Instance()->item[ItemNumber].GetIsActive() == false)
		{
			m_timer = 0;
			m_step = 0;
		}

		//Œü‚¢‚Ä‚¢‚éŠp“x
		m_angle = atan(Vector.Y / Vector.X) * (180.0f / 3.14);
		if (Vector.X < 0)
		{
			m_angle += 180;
		}
	}
}

Rule RuleBaseAI::OnOff()
{
	Vec2 Center = Vec2(m_pos.X + m_size.X / 2, m_pos.Y + m_size.Y / 2);
	Vec2 CirclePos = Vec2(Center.X - CircleRadius, Center.Y - CircleRadius);
	Vec2 CircleSize = Vec2(CircleRadius, CircleRadius);

	//î‚Ì’Tõ”ÍˆÍ
	for (int i = 0; i < 5; i++)
	{
		if (collision.OnCollisionArcAndPoint(Center, ItemManager::Instance()->item[i].GetPos(),
			FanDegree, m_angle, FanLengh) == true)
		{
			FanItemNumber = i;
			HitFan = true;
			break;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (collision.OnCollisionCircleAndPoint(CirclePos, CircleSize,
			ItemManager::Instance()->item[i].GetPos()) == true)
		{
			CircleItemNumber = i;
			HitCircle = true;
			break;
		}
	}

	if (HitFan == true && HitCircle == true)
	{
		if (HitLastTime != Rule::HitFanArea)
		{
			ItemNumber = FanItemNumber;
			HitLastTime = Rule::HitFanArea;
			return Rule::HitFanArea;
		}
		else
		{
			ItemNumber = CircleItemNumber;
			HitLastTime = Rule::HitCircleArea;
			return Rule::HitCircleArea;
		}
	}
	else if (HitFan == true)
	{
		ItemNumber = FanItemNumber;
		return Rule::HitFanArea;
	}
	else if (HitCircle == true)
	{
		ItemNumber = CircleItemNumber;
		return Rule::HitCircleArea;
	}

	return Rule::Noen;
}