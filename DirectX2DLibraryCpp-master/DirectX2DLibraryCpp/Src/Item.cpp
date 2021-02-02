#include "Item.h"
#include "Engine/Engine.h"

void Item::Init(Vec2 pos)
{
	m_pos = pos;
	m_is_active = false;
}

void Item::Draw()
{
	Engine::DrawTexture(m_pos.X, m_pos.Y, "Item");
}

bool Item::GetIsActive()
{
	return m_is_active;
}

void Item::SetIsActive(bool is_active)
{
	m_is_active = is_active;
}

Vec2 Item::GetPos()
{
	return m_pos;
}

void Item::SetPos(Vec2 pos)
{
	m_pos = pos;
}