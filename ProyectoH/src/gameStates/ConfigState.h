#pragma once
#include "../game/GameState.h"

#include "../systems/ConfigSystem.h"
#include "../systems/MainMenuSystem.h"
#include "../systems/ButtonSystem.h"
#include "../systems/PauseSystem.h"

class ConfigState : public GameState
{
public:
	ConfigState(Manager* mngr, bool isPlayState);
	virtual ~ConfigState();
private:
	bool isPlayState;
};

