#pragma once
#include "GameState.h"
#include "../systems/RenderSystem.h"
#include "../systems/mapSystem.h"
#include "../systems/TowerSystem.h"

class PlayState : public GameState
{
public:
	PlayState();
	virtual ~PlayState() {};

	void update() override;
};

