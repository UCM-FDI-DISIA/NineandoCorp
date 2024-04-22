#pragma once
#include "AttackComponent.h"

class DiegoSniperTower : public AttackComponent
{
public:
	static const cmpId id = cmpId::_DIEGOTOWER;
	DiegoSniperTower(float range, float critProbability, float critDamagePercentage, float reloadTime, int damage);
	float getCritProb() const { return critProbability_; };
	float getCritDamage() const { return critDamageIncrease_; };
	void setCritProb(float prob) { critProbability_ = prob; };
	void setCritDamage(float percentage) { critDamageIncrease_ = percentage; };
private:
	float critProbability_;
	float critDamageIncrease_;
};

