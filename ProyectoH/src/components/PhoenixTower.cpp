#include "PhoenixTower.h"
#include "../ecs/Manager.h"

PhoenixTower::PhoenixTower(float damage, float coolingTime, float shootingTime, float range) :damage_(damage), coolingTime_(coolingTime), shootingTime_(shootingTime), range_(range), elapsedTime_(0), shooting_(false), fire_(nullptr) {}

PhoenixTower::~PhoenixTower() {
	mngr_->setAlive(fire_, false);
}

void PhoenixTower::levelUp(int level) {
	switch (level) {
	case 1:
		damage_ = sdlutils().floatConst().at("FenixDPS1");
		break;
	case 2:
		coolingTime_ = sdlutils().floatConst().at("FenixEnfriamiento1");
		break;
	case 3:
		damage_ = sdlutils().floatConst().at("FenixDPS2");
		coolingTime_ = sdlutils().floatConst().at("FenixEnfriamiento2");
		break;
	case 4:
		coolingTime_ = sdlutils().floatConst().at("FenixEnfriamientoCero");
		//Falta anadir la opcion de aumentar el rango del fuego
		break;
	}
}

void PhoenixTower::removeFire() {
	Message m;
	m.id = _m_REMOVE_RECT;
	m.rect_data.id = _FENIX;
	m.rect_data.rect = fire_;
	mngr_->send(m);
}