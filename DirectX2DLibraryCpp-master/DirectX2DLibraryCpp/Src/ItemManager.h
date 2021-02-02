#ifndef ItemManager_H_
#define ItemManager_H_

#include "Item.h"
#include "Common/Vec.h"

class ItemManager
{
public:
	static ItemManager* Instance()
	{
		static ItemManager instance;

		return &instance;
	}

	void Init();
	void Draw();
	Item* CreateItem(Vec2 pos);

	Item item[5];
private:
	ItemManager(){}
};

#endif
