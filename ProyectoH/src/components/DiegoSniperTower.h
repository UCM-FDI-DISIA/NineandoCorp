#pragma once
#include "AttackComponent.h"

class DiegoSniperTower : public AttackComponent
{
public:
	DiegoSniperTower(float range, float critProbability, float critDamagePercentage, float reloadTime, int damage);
	float getCritProb() const;
	float getCritDamage() const;
	void setCritProb(float prob);
	void setCritDamage(float percentage);
	void levelUp(int level);
private:
	float critProbability_;
	float critDamageIncrease_;
};

