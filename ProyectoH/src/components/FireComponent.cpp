#include "FireComponent.h"

FireComponent::FireComponent(float damage, float rot, Entity* myTower) :
	damage_(damage), rotation_(rot), myTower_(myTower) {}