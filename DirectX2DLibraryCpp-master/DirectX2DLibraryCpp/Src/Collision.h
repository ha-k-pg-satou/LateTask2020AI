#ifndef Collision_H_
#define Collision_H_

#include "Engine/Engine.h"

class Collision
{
public:
	Collision();
	~Collision();

	//‰~‚Æ“_‚Ì“–‚½‚è”»’è
	bool OnCollisionCircleAndPoint(Vec2 obj1_pos, Vec2 obj1_size, Vec2 obj2_pos);
	//î‚Æ“_‚Ì“–‚½‚è”»’è
	bool OnCollisionArcAndPoint(Vec2 fan_pos, Vec2 point_pos, float arc_degree, float rotate_degree, float fan_length);
private:
};

#endif
