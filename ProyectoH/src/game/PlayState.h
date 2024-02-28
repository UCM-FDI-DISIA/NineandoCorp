#pragma once
#include "GameState.h"
#include "../systems/RenderSystem.h"
#include "../systems/mapSystem.h"
#include "../systems/EnemySystem.h"
#include "../systems/TowerSystem.h"
#include "../components/MovementComponent.h"
#include "../components/RouteComponent.h"

class PlayState : public GameState
{
public:
	PlayState();
	virtual ~PlayState() {};

	void handleInput();
	void update() override;
	//Entity* enemy = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
};

