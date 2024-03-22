#pragma once
#include "../game/GameState.h"
#include "../systems/RenderSystem.h"
#include "../systems/mapSystem.h"
#include "../systems/EnemySystem.h"
#include "../systems/TowerSystem.h"
#include "../systems/HUDSystem.h"
#include "../systems/CollisionSystem.h"
#include "../systems/ParticleSystem.h"
#include "../components/MovementComponent.h"
#include "../components/RouteComponent.h"
#include "../systems/ButtonSystem.h"

class PlayState : public GameState
{
public:
	PlayState();
	virtual ~PlayState() { delete mngr_; };

	void update() override;
};

