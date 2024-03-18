#pragma once
#include "../ecs/Component.h"
class generateEnemies : public Component {
private:
	std::vector<Vector2D> route;
	int level, wave, grp;
	SDLUtils::spawnGroupData* spawnGroup;
public:
	static const cmpId id = cmpId::_GENERATENEMIES;
	generateEnemies() :Component(), level(1), wave(1), grp(1) {};
	virtual ~generateEnemies(){}
	virtual void initComponent();
	void generateEnemy();

	void setLevel(unsigned int newLevel) { level = newLevel; }
	void setWave(unsigned int newWave) { wave = newWave; }
	void setGrp(unsigned int newGrp) { grp = newGrp; }
	void addGroupEnemies();
};