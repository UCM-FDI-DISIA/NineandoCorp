#pragma once
#include "../game/GameState.h"
#include "../systems/RenderSystem.h"
#include "../systems/mapSystem.h"
#include "../systems/EnemySystem.h"
#include "../systems/TowerSystem.h"
#include "../systems/HUDSystem.h"
#include "../components/MovementComponent.h"
#include "../components/RouteComponent.h"

class PlayState : public GameState
{
public:
	PlayState();
	virtual ~PlayState() { delete mngr_; };
};

