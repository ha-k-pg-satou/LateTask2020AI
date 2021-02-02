#ifndef Game_H_
#define Game_H_

#include "Engine/Engine.h"
#include "ItemManager.h"
#include "RuleBaseAI.h"
#include "StateBaseAI.h"

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Draw();
private:
	int m_timer;

	RuleBaseAI r_AI;
	StateBaseAI s_AI;
	Collision collision;
};

#endif
