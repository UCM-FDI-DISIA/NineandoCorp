#include "DiegoSniperTower.h"

DiegoSniperTower::DiegoSniperTower(float range, float critProbability, float critDamagePercentage, float reloadTime, int damage) 
	: AttackComponent::AttackComponent(range, reloadTime, damage, false), critDamageIncrease_(critDamagePercentage), critProbability_(critProbability){}

