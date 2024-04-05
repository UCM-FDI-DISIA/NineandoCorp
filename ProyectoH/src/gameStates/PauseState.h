#pragma once
#include "../game/GameState.h"

#include "../systems/RenderSystem.h"
#include "../systems/HUDSystem.h"
#include "../systems/MainControlSystem.h"
#include "../systems/ButtonSystem.h"
#include "../systems/PauseSystem.h"

class PauseState : public GameState
{
public:
	PauseState(Manager* mngr = nullptr);
	virtual ~PauseState();
};

