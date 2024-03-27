#pragma once
#include "../game/GameState.h"

#include "../systems/EnemyBookSystem.h"
#include "../systems/MainMenuSystem.h"
#include "../systems/ButtonSystem.h"

class EnemyBookState : public GameState
{
public:
	EnemyBookState(Manager* mngr);
	virtual ~EnemyBookState();
};

