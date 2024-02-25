#include "DirtTower.h"

DirtTower::DirtTower(float range, float reloadTime, int damage)
	: AttackComponent::AttackComponent(range, reloadTime, damage, true) {}