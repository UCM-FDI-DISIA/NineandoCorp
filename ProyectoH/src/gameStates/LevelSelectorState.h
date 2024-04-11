#pragma once
#include "../game/GameState.h"

#include "../systems/LevelSelectorSystem.h"
#include "../systems/MainMenuSystem.h"
#include "../systems/ButtonSystem.h"

class LevelSelectorState : public GameState
{
public:
	LevelSelectorState(Manager* mngr, int level_);
	virtual ~LevelSelectorState();
};

