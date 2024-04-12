#include "DiegoSniperTower.h"

DiegoSniperTower::DiegoSniperTower(float range, float critProbability, float critDamagePercentage, float reloadTime, int damage) 
	: AttackComponent::AttackComponent(range, reloadTime, damage, false), critDamageIncrease_(critDamagePercentage), critProbability_(critProbability){}


void DiegoSniperTower::levelUp(int level) {
	/*switch (level) {
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
	}*/
}