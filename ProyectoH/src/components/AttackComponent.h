#pragma once
#include "..//ecs/Component.h"
#include "..//sdlutils/VirtualTimer.h"
#include "..//utils/Vector2D.h"
#include <vector>

class Entity;
class HealthComponent;
class AttackComponent : public Component
{
public:
	AttackComponent(float range, float reloadTime, int damage, bool shootBullets);
	virtual void update() override;
	virtual void initComponent();
	float getDamage() const;
	float getRange() const;
	void setDamage();
	void setRange();
	void doDamageTo(HealthComponent* healthcmp);
protected:
	void targetEnemy(const std::vector<Entity*>& targetGroup, Entity* targetToLock);
	float reloadTime_;
	float elapsedTime_;
private:
	virtual void shoot(Entity* targetToShoot) {};
	float getDistance(Vector2D targetPos);
	float range_;
	float timeToShoot_;
	bool loaded_;
	bool shootBullets_;
	int damage_;
	Entity* target_;//target principal
	VirtualTimer timer_;//contador para tiempo de ataque
};

