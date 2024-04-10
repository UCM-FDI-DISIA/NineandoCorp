#include "EnhancerTower.h"

EnhancerTower::EnhancerTower(float range, float damageIncrease, float healthIncrease) :
	range_(range), damageIncreasePercentage_(damageIncrease), towersHPboost_(healthIncrease){}

float EnhancerTower::getDamageIncreasePercentage() const { return damageIncreasePercentage_; }

float EnhancerTower::getTowersHPboost() const { return towersHPboost_; }

float EnhancerTower::getRange() const { return range_; }

void EnhancerTower::setDamageIncreasePercentage(float damage) { damageIncreasePercentage_ = damage; }

void EnhancerTower::setTowersHPboost(float hp) { towersHPboost_ = hp; }

void EnhancerTower::levelUp(int level) {
	switch (level) {
		case 1:
			setDamageIncreasePercentage(sdlutils().floatConst().at("PotenciadoraDano1"));
			break;
		case 2:
			setTowersHPboost(sdlutils().floatConst().at("PotenciadoraAumentoVida"));
			break;
		case 3:
			setDamageIncreasePercentage(sdlutils().floatConst().at("PotenciadoraDano2"));
			break;
		case 4:
			isMaxLevel_ = true;
			setDamageIncreasePercentage(sdlutils().floatConst().at("PotenciadoraDano3"));
			setTowersHPboost(sdlutils().floatConst().at("PotenciadoraVida2"));
			break;
		default:
			break;
	}
}