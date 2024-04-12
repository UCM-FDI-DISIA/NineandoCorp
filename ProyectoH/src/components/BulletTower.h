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

	bool isMaxLevel() const{ return isMaxLevel_; }
	Entity* getSecondTarget() const{ return secondTarget_; }

private:
	Entity* secondTarget_;//Para la mejora maxima de la torre; 2 objetivos 
	bool isMaxLevel_;
};

