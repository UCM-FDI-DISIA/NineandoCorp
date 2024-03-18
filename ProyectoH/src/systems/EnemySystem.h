#pragma once
#include "..//ecs/System.h"
#include "..//components/Transform.h"
#include "..//components/HealthComponent.h"
#include "..//components/AttackComponent.h"
#include "..//sdlutils/VirtualTimer.h"
#include "../game/Game.h"
class EnemySystem: public System
{

public:

	static constexpr sysId_type id = _sys_ENEMIES;
	EnemySystem();
	virtual ~EnemySystem();
	void update() override;
	void initSystem() override;
	void receive(const Message& m) override;
	void onRoundOver();
	void onRoundStart(unsigned int n_grp);
	void onWaveStart(unsigned int level, unsigned int wave);
	void collideswithEnemy();

protected:

	std::vector<Transform*> enemiesTransforms;
	std::vector<Entity*> spawnsVector;
	bool active_;
};

