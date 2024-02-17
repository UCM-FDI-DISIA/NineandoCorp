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
	float getDamage() const;
	float getRange() const;
	void setDamage(int dmg);
	void setRange(float rng);
	void doDamageTo(HealthComponent* healthcmp);
protected:
	void targetEnemy(const std::vector<Entity*>& targetGroup, Entity* targetToLock);
	float reloadTime_;
	float elapsedTime_;
	int damage_;
	Entity* target_;//target principal
private:
	virtual void shoot(Entity* targetToShoot) {};
	float getDistance(Vector2D targetPos);
	float range_;
	float timeToShoot_;
	bool loaded_;
	bool shootBullets_;
	VirtualTimer timer_;//contador para tiempo de ataque
};

