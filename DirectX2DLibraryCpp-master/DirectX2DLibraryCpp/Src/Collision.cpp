#include "Collision.h"
#include <math.h>

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::OnCollisionCircleAndPoint(Vec2 obj1_pos, Vec2 obj1_size, Vec2 obj2_pos)
{
	//obj1‚Ì’†‰›
	Vec2 center_pos = Vec2(obj1_pos.X + obj1_size.X / 2.0f, obj1_pos.Y + obj1_size.Y / 2.0f);

	//”¼Œa
	float radius = obj1_size.X / 2.0f;

	//‹——£
	float a = center_pos.X - obj2_pos.X;
	float b = center_pos.Y - obj2_pos.Y;
	float distance = sqrt(a * a + b * b);

	//”»’è
	if (distance <= radius)
	{
		//“–‚½‚Á‚Ä‚é
		return true;
	}

	//“–‚½‚Á‚Ä‚È‚¢
	return false;
}

bool Collision::OnCollisionArcAndPoint(Vec2 fan_pos, Vec2 point_pos, float arc_degree, float rotate_degree, float fan_length)
{
	//î‚Æ“_‚Ì‹——£
	float a = fan_pos.X - point_pos.X;
	float b = fan_pos.Y - point_pos.Y;
	float distance = sqrt(a * a + b * b);

	//‰~‚Ì”ÍˆÍ“à‚©‚Ì”»’è
	if (fan_length < distance)
	{
		return false;
	}

	//îŒ^ŠJŽnü‚ÌŠp“x
	float s_rad = D3DXToRadian(rotate_degree - arc_degree / 2);
	//îŒ^I—¹ü‚ÌŠp“x
	float e_rad = D3DXToRadian(rotate_degree + arc_degree / 2);

	//‚»‚ê‚¼‚ê‚Ìsin,cos•ÏŠ·
	float sx = (float)sin(s_rad);
	float sy = (float)cos(s_rad);
	float ex = (float)sin(e_rad);
	float ey = (float)cos(e_rad);

	//Šp“x‚Ì”»’è
	if (sx * ey - ex * sy > 0)
	{
		if (sx * b - a * sy < 0)
		{
			return false;
		}
		if (ex * b - a * ey > 0)
		{
			return false;
		}
		return true;
	}
	else
	{
		if (sx * b - a * sy > 0)
		{
			return true;
		}
		if (ex * b - a * ey < 0)
		{
			return true;
		}
		return false;
	}
}