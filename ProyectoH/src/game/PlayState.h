#pragma once
#include "GameState.h"
#include "../systems/RenderSystem.h"
#include "../systems/mapSystem.h"

class PlayState : public GameState
{
public:
	PlayState();
	virtual ~PlayState() {};

	void handleInput() override;
	void update() override;
	Entity* enemy = mngr_->addEntity(_grp_ENEMIES);
};

