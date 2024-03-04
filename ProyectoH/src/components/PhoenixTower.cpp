#include "PhoenixTower.h"

PhoenixTower::PhoenixTower(float damage, float coolingTime, float shootingTime) :damage_(damage), coolingTime_(coolingTime), shootingTime_(shootingTime) {}

void PhoenixTower::levelUp(int level) {
	switch (level) {
	case 1:
		damage_ = 4.0f;
		break;
	case 2:
		coolingTime_ = 1.5f;
		break;
	case 3:
		damage_ = 5;
		coolingTime_ = 1.0f;
		break;
	case 4:
		coolingTime_ = 0.0f;
		//Falta anadir la opcion de aumentar el rango del fuego
		break;
	}
}