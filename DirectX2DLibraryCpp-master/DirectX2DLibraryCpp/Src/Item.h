#ifndef Item_H_
#define Item_H_

#include "Common/Vec.h"

class Item
{
public:
	void Init(Vec2 pos);
	void Draw();
	bool GetIsActive();
	void SetIsActive(bool is_active);
	Vec2 GetPos();
	void SetPos(Vec2 pos);
private:
	Vec2 m_pos;
	bool m_is_active;
};

#endif
