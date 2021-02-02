#include "Game.h"
#include <time.h>
#include <stdlib.h>

Game::Game()
{
	ItemManager::Instance()->Init();
	m_timer = 0;
	srand((unsigned int)time(NULL));
}

Game::~Game()
{

}

void Game::Update()
{
	//ƒAƒCƒeƒ€‚Ì¶¬
	m_timer++;
	if (m_timer >= 120)
	{
		ItemManager::Instance()->CreateItem(Vec2(rand() % 590, rand() % 430));

		m_timer = 0;
	}

	r_AI.Update();
	s_AI.Update();
}

void Game::Draw()
{
	Engine::StartDrawing(0);

	ItemManager::Instance()->Draw();
	r_AI.Draw();
	s_AI.Draw();

	Engine::FinishDrawing();
}