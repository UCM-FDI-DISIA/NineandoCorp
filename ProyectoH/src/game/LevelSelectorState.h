#pragma once
#include "GameState.h"

#include "../systems/RenderSystem.h"
#include "../systems/HUDSystem.h"
#include "../systems/MainControlSystem.h"
#include "../systems/LevelSelectorSystem.h"

class LevelSelectorState : public GameState
{
public:
	LevelSelectorState();
	virtual ~LevelSelectorState() {};
};

