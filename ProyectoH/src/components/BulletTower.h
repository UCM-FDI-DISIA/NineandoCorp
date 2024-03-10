#pragma once
#include "..//components/AttackComponent.h"
#include "BulletComponent.h"

class Entity;
class BulletTower : public AttackComponent
{
public:
	BulletTower(float range, float reloadTime, int damage);
	void levelUp(int level);
	void targetSecondEnemy(const std::list<Entity*>& targetGroup);

	bool isMaxLevel() { return isMaxLevel_; }
	Entity* getSecondTarget() { return secondTarget_; }

private:
	Entity* secondTarget_;//Para la mejora maxima de la torre; 2 objetivos 
	float timeToShoot2_;//Tiempo de disparo al segundo objetivo
	bool isMaxLevel_;
};

