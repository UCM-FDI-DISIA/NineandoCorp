#include "PhoenixTower.h"
#include "../ecs/Manager.h"

PhoenixTower::PhoenixTower(float damage, float coolingTime, float shootingTime, float range) :damage_(damage), coolingTime_(coolingTime), shootingTime_(shootingTime), range_(range), elapsedTime_(0), shooting_(false), fire_(nullptr), target_(nullptr), rotation_(0) {}

PhoenixTower::~PhoenixTower() {
	//mngr_->setAlive(fire_, false);
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

void PhoenixTower::targetEnemy(const std::list<Entity*>& targetGroup) {
	if (target_ == nullptr) {//Si no hay enemigo targeteado se busca uno
		double closestEnemy = INT32_MAX;
		for (const auto& enemy : targetGroup)
		{
			if (mngr_->hasComponent<Transform>(enemy)) {
				float distance = getDistance(mngr_->getComponent<Transform>(enemy)->getPosition());
				if (distance < range_ && distance < closestEnemy) {//Si esta en rango y es el enemigo mas cercano
					target_ = enemy;
					closestEnemy = distance;
				}
			}
		}
	}
	else if (target_ != nullptr && mngr_->isAlive(target_)) {
		target_ = nullptr;
	}
}

float PhoenixTower::getDistance(Vector2D targetPos) {//Distancia al target
	Vector2D myPos = mngr_->getComponent<Transform>(ent_)->getPosition();
	return sqrt(pow(myPos.getX() - targetPos.getX(), 2) + pow(myPos.getY() - targetPos.getY(), 2));
}


void PhoenixTower::removeFire() {
	Message m;
	m.id = _m_REMOVE_RECT;
	m.rect_data.id = _FENIX;
	m.rect_data.entity = fire_;
	mngr_->send(m);
	setFire(nullptr);
}