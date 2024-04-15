#pragma once
#include "../ecs/Component.h"
#include "..//components/Transform.h"
#include "..//components/HealthComponent.h"
#include "..//components/AttackComponent.h"
#include "..//components/MovementComponent.h"
#include "..//components/RouteComponent.h"
#include "..//components/RenderComponent.h"
#include "..//components/FramedImage.h"
#include "..//components/MaestroAlmasComponent.h"
#include "..//components/MensajeroMuerteComponent.h"
#include "..//components/CaballeroMalditoComponent.h"
#include "..//components/AcechanteComponent.h"
#include "..//components/GolemComponent.h"
#include "..//components/AngelComponent.h"
#include "..//components/PrincipitoComponent.h"
#include "..//components/EnemyTypeComponent.h"
#include "..//components/MuerteComponent.h"
#include "../game/Game.h"

class generateEnemies : public Component {
private:
	std::vector<Vector2D> route;
	int level, wave, grp;
	SDLUtils::spawnGroupData* spawnGroup;
	int nextEnemy;
	int totalEnemies_;
	int pos;
	enmId type;

	double elapsedTime;
public:
	static const cmpId id = cmpId::_GENERATENEMIES;
	generateEnemies() :Component(), level(1), wave(1), grp(1), nextEnemy(0), totalEnemies_(0), pos(0), elapsedTime(0), spawnGroup(nullptr), type(enmId()) {};
	virtual ~generateEnemies(){}
	virtual void initComponent();
	void generateEnemy();
	void addEnemy(enmId type, std::vector<Vector2D> route);

	void setLevel(unsigned int newLevel) { level = newLevel; }
	void setWave(unsigned int newWave) { wave = newWave; }
	void setGrp(unsigned int newGrp) { grp = newGrp; }
	void setRoute(std::vector<Vector2D> newRoute) { route = newRoute; }
	vector<Vector2D> getRoute() const { return route; };
	void addGroupEnemies();
	void RoutesCorrection(Transform* tr, std::vector<Vector2D>& route, float divHeight, float divWidth);
	SDLUtils::spawnGroupData* getSpawnGroup() const { return spawnGroup; }
	double getElapsedTime() const { return elapsedTime; }
	void setElapsedTime(double time) { elapsedTime = time; }
	void next_Enemy() { totalEnemies_++; }
	int getNumEnemies() const { return totalEnemies_; }
	void resetNumEnemies() {
		totalEnemies_ = 0;
		pos = 0;
		nextEnemy = 0;
	}

	int totalEnemies() const;
};