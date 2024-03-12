#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
#include "..//utils/Vector2D.h"
#include "BulletComponent.h"
#include <vector>
#include <list>

class Entity;
class HealthComponent;
class AttackComponent : public Component
{
public:
	static const cmpId id = cmpId::_ATTACK;

	AttackComponent(float range, float reloadTime, int damage, bool shootBullets);
	virtual void initComponent();
	
;
	void doDamageTo(Entity* e, float damage);
	void targetEnemy(const std::list<Entity*>& targetGroup);

	//Getters
	float getDamage() const;
	float getBaseDamage() const;
	float getRange() const;
	bool isLoaded()const;
	Entity* getTarget() const;
	float getTimeToShoot()const;
	float getReloadTime()const;
	float getElapsedTime()const;

	//Setters
	void setDamage(int dmg);
	void setRange(float rng);
	void setReloadTime(float time);
	void setLoaded(bool ld);
	void setTimeToShoot(float t);
	void setElapsedTime(float elapsed);
	void setTarget(Entity* e) { target_ = e; };

protected:
	
	float reloadTime_;//Tiempo de recarga
	int baseDamage_;//Dano inicial
	int damage_;//Dano actual; puede ser modificado por potenciadores o inhibidores
	Entity* target_;//target principal

	float getDistance(Vector2D targetPos);
	float range_;//Rango de deteccion
	float timeToShoot_;//Tiempo por dispaor
	float elapsedTime_;

	bool loaded_;
};

