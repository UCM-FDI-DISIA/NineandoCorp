#pragma once
#include "GameState.h"
#include "../systems/RenderSystem.h"
#include "../systems/HUDSystem.h"
#include "../systems/mapSystem.h"

class PlayState : public GameState
{
public:
	PlayState();
	virtual ~PlayState() {};

	void handleInput() override;
	void update() override;
};

