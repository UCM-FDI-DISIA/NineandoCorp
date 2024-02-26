#pragma once
#include "GameState.h"
#include "../systems/RenderSystem.h"
#include "../systems/mapSystem.h"
#include "../systems/TowerSystem.h"

class PlayState : public GameState
{
public:
	PlayState(Manager* mngr);
	virtual ~PlayState() {};

	void update() override;
};

