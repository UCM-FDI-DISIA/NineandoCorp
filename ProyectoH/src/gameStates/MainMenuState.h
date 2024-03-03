#pragma once
#include "../game/GameState.h"

#include "../systems/MainMenuSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/HUDSystem.h"
#include "../systems/MainControlSystem.h"


class MainMenuState : public GameState
{
public:
	MainMenuState(Manager* mngr = nullptr);
	virtual ~MainMenuState();
};

