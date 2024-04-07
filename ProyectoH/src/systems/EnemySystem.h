#pragma once
#include "..//ecs/System.h"
#include "..//components/Transform.h"
#include "..//components/HealthComponent.h"
#include "..//components/AttackComponent.h"
#include "..//sdlutils/VirtualTimer.h"
#include "../game/Game.h"
#include "../systems/mapSystem.h"
#include "..//components/generateEnemies.h"
#include "..//components/DefensorRealComponent.h"


class EnemySystem: public System
{
private:
	unsigned int wave = 1;
	unsigned int level = 1;
	int numSpawns;
	void enemyDeathAnim(Vector2D pos);
public:

	static constexpr sysId_type id = _sys_ENEMIES;
	EnemySystem();
	virtual ~EnemySystem();
	void update() override;
	void initSystem() override;
	void receive(const Message& m) override;

	void onRoundOver();
	void onRoundStart(int n_grp, unsigned int level);
	void onWaveStart();
	void collideswithEnemy();
	void AddMoney(enmId type);
	

	std::vector<Vector2D> RouteTranslate(std::vector<Vector2D> route);
	
	unsigned int getWave() { return wave; }
	void setWave() { wave++; }
protected:
	Entity* addField(Vector2D pos);

	std::vector<Transform*> enemiesTransforms;
	std::vector<Entity*> spawnsVector;
	NetMap* netmap;
	bool mActive;
	bool generateEnemies_ = false;
	bool stopGenerate = false;

};

