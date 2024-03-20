#pragma once
#include "../game/GameState.h"

#include "../systems/MainMenuSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/HUDSystem.h"
#include "../systems/MainControlSystem.h"
#include "../systems/ButtonSystem.h"

class PauseState : public GameState
{
public:
	PauseState(Manager* mngr = nullptr);
	virtual ~PauseState();
};

