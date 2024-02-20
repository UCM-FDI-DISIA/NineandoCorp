#pragma once
#include "GameState.h"
#include "../systems/MainMenuSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/mapSystem.h"


class MainMenuState : public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState() {};
};

