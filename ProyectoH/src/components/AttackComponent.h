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

	AttackComponent(float range, float reloadTime, int damage, bool towers);
	virtual void initComponent();
	
;
	void doDamageTo(Entity* e, float damage, hdlrId targetId);
	void targetEnemy(const std::list<Entity*>& targetGroup);

	//Getters
	bool getNexo() const { return nexo_; }
	bool getAttackTowers() const { return towers_; };
	float getDamage() const { return damage_; }
	float getBaseDamage() const { return baseDamage_; }
	float getRange() const { return range_; }
	bool isLoaded() const { return loaded_; }
	Entity* getTarget()const { return target_; }
	float getTimeToShoot()const { return timeToShoot_; }
	float getReloadTime()const { return reloadTime_; }
	float getElapsedTime()const { return elapsedTime_; }


	//Setters
	void setDamage(int dmg) { damage_ = dmg; };
	void setRange(float rng) { range_ = rng; };
	void setReloadTime(float time) { reloadTime_ = time; };
	void setLoaded(bool ld) { loaded_ = ld; };
	void setTimeToShoot(float t) { timeToShoot_ = t; };
	void setElapsedTime(float elapsed) { elapsedTime_ = elapsed; };
	void setTarget(Entity* e) { target_ = e; };

	bool getNexo() { return nexo_; }
	bool getAttackTowers() { return towers_; };
	void setNexo(bool n) { nexo_=n; }
	void setAttack(bool a) { isAttacking = a; };
	float getDistance(Vector2D targetPos);


protected:
	
	float reloadTime_;//Tiempo de recarga
	int baseDamage_;//Dano inicial
	int damage_;//Dano actual; puede ser modificado por potenciadores o inhibidores
	Entity* target_;//target principal
	
	float range_;//Rango de deteccion
	float timeToShoot_;//Tiempo por dispaor
	float elapsedTime_;
	bool nexo_;
	bool towers_;
	bool isAttacking;
	bool loaded_;
};

