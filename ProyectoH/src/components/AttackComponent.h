#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
#include "..//sdlutils/VirtualTimer.h"
#include "..//utils/Vector2D.h"
#include <vector>

class Entity;
class HealthComponent;
class AttackComponent : public Component
{
public:
	static const cmpId id = cmpId::_ATTACK;

	AttackComponent(float range, float reloadTime, int damage, bool shootBullets);
	virtual void initComponent();
	
;
	void doDamageTo(HealthComponent* healthcmp);
	void targetEnemy(const std::vector<Entity*>& targetGroup);
	virtual void shoot(Entity* targetToShoot);

	//Getters
	float getDamage() const;
	float getRange() const;
	bool isLoaded()const;
	Entity* getTarget() const;
	float getTimeToShoot()const;
	bool shouldShoot() const;
	float getReloadTime()const;

	//Setters
	void setDamage(int dmg);
	void setRange(float rng);
	void setLoaded(bool ld);
	void setTimeToShoot(float t);
protected:
	
	float reloadTime_;
	int damage_;
	Entity* target_;//target principal
private:

	float getDistance(Vector2D targetPos);
	float range_;
	float timeToShoot_;
	bool loaded_;
	bool shootBullets_;
};

