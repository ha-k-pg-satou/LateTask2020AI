#include "ItemManager.h"
#include "Engine/Engine.h"

void ItemManager::Init()
{
	for (int i = 0; i < 5; i++)
	{
		item[i].Init(Vec2(0.0f, 0.0f));
	}
}

void ItemManager::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		if (item[i].GetIsActive() == false)
		{
			continue;
		}

		item[i].Draw();
	}
}

Item* ItemManager::CreateItem(Vec2 pos)
{
	for (int i = 0; i < 5; i++)
	{
		if (item[i].GetIsActive() == false)
		{
			item[i].Init(pos);
			item[i].SetIsActive(true);
			return &item[i];
		}
	}

	return nullptr;
}