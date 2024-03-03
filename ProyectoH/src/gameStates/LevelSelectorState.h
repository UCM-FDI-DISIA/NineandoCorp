#pragma once
#include "../game/GameState.h"

#include "../systems/LevelSelectorSystem.h"
#include "../systems/MainMenuSystem.h"

class LevelSelectorState : public GameState
{
public:
	LevelSelectorState(Manager* mngr);
	virtual ~LevelSelectorState();
};

