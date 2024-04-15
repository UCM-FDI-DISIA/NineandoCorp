#pragma once
#include "BulletComponent.h"

class EnemyProyectileComponent : public Component
{
protected:
	Transform* t;//Transform de la bala
	Entity* targetEntity_;//Entidad enemigo
	Entity* srcEntity;//Entidad origen
	int damage_;//Dano de la bala
	float speed_;//Velocidad de la bala

public:
	static const cmpId id = cmpId::_ENEMYPROYECTILE;

	EnemyProyectileComponent(Transform* tr, Entity* target, Entity* src, int damage, float speed);
	virtual	~EnemyProyectileComponent() {};
	void doDamageTo(Entity* e, float damage);
	void setDir();
	void onTravelEnds();

	float getDamage()const { return damage_; }

	Entity* getTarget()const { return targetEntity_; }

};

