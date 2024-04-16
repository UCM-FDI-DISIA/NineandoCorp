#pragma once
#include "../game/GameState.h"

#include "../systems/ConfigSystem.h"
#include "../systems/MainMenuSystem.h"
#include "../systems/ButtonSystem.h"

class ConfigState : public GameState
{
public:
	ConfigState(Manager* mngr);
	virtual ~ConfigState();
};

