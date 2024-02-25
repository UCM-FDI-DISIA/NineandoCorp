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
		setDamageIncreasePercentage(10);
		break;
	case 2:
		setTowersHPboost(30);
		break;
	case 3:
		setDamageIncreasePercentage(15);
		break;
	case 4:
		isMaxLevel_ = true;
		setDamageIncreasePercentage(20);
		setTowersHPboost(50);
		break;
	default:
		break;
	}
}