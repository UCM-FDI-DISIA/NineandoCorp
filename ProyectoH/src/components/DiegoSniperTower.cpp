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
		setDamage(sdlutils().floatConst().at("DiegoSniperDano1"));
		break;
	case 2:
		setCritDamage(sdlutils().floatConst().at("DiegoSniperCritDano1"));
		setCritProb(sdlutils().floatConst().at("DiegoSniperCritProb1"));
		break;
	case 3:
		setTimeToShoot(getTimeToShoot()- sdlutils().floatConst().at("DiegoSniperRecargaUpdate1"));
		break;
	case 4:
		setCritProb(sdlutils().floatConst().at("DiegoSniperCritProb2"));
		setTimeToShoot(getTimeToShoot() - sdlutils().floatConst().at("DiegoSniperRecargaUpdate1"));
		break;
	default:
		break;
	}
}