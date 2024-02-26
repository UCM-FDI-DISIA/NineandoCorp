#include "DiegoSniperTower.h"

DiegoSniperTower::DiegoSniperTower(float range, float critProbability, float critDamagePercentage, float reloadTime, int damage) 
	: AttackComponent::AttackComponent(range, reloadTime, damage, true), critDamageIncrease_(critDamagePercentage), critProbability_(critProbability){}

float DiegoSniperTower::getCritDamage() const { return critDamageIncrease_; }

float DiegoSniperTower::getCritProb() const { return critProbability_; }

void DiegoSniperTower::setCritDamage(float percentage) { critDamageIncrease_ = percentage; }

void DiegoSniperTower::setCritProb(float prob) { critProbability_ = prob; }

void DiegoSniperTower::levelUp(int level) {
	switch (level) {
	case 1:
		setDamage(75);
		break;
	case 2:
		setCritDamage(1.5f);
		setCritProb(0.2f);
		break;
	case 3:
		setReloadTime(2.5f);
		break;
	case 4:
		setCritProb(0.3f);
		setReloadTime(2.0f);
		break;
	default:
}