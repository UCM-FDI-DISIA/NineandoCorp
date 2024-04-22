#pragma once
#include "BulletComponent.h"

class EnemyProyectileComponent : public Component
{
protected:
	Transform* t;
	Entity* target_;
	Entity* src_;
	int damage_;
	float speed_;
public:
	static const cmpId id = cmpId::_ENEMYPROYECTILE;

	EnemyProyectileComponent(Transform* tr, Entity* target, Entity* src, int damage, float speed);
	void doDamageTo(Entity* e, float damage);

	void setDir();
	void OnTravelEnds();

	float getDamage()const { return damage_; }

	Entity* getTarget() { return target_; }

};

