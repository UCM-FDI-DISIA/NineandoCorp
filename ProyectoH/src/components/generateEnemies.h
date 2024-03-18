#pragma once
#include "../ecs/Component.h"
#include "..//components/Transform.h"
#include "..//components/HealthComponent.h"
#include "..//components/AttackComponent.h"
#include "..//components/MovementComponent.h"
#include "..//components/RouteComponent.h"
#include "..//components/RenderComponent.h"
#include "..//components/FramedImage.h"

class generateEnemies : public Component {
private:
	std::vector<Vector2D> route;
	int level, wave, grp;
	SDLUtils::spawnGroupData* spawnGroup;
	int nextEnemy = 0;
	enmId type;
public:
	static const cmpId id = cmpId::_GENERATENEMIES;
	generateEnemies() :Component(), level(1), wave(1), grp(1) {};
	virtual ~generateEnemies(){}
	virtual void initComponent();
	void generateEnemy();
	void addEnemy(enmId type, std::vector<Vector2D> route);

	void setLevel(unsigned int newLevel) { level = newLevel; }
	void setWave(unsigned int newWave) { wave = newWave; }
	void setGrp(unsigned int newGrp) { grp = newGrp; }
	void addGroupEnemies();
};