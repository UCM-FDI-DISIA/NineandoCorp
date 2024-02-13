#include "AttackComponent.h"
#include "SDL.h"
#include "algorithm"
#include "..//components/Transform.h"

AttackComponent::AttackComponent(float range, float reloadTime, int damage) : range_(range), reloadTime_(reloadTime), damage_(damage){
	target_ = nullptr; elapsedTime_ = 0; timeToShoot_ = reloadTime; 
}

void AttackComponent::update() {
	targetEnemy();
	elapsedTime_ = timer_.currTime();
	if (elapsedTime_ > timeToShoot_) {
		timeToShoot_ += reloadTime_;
		shoot();//Dispara si esta recargado
	}	
}

void AttackComponent::targetEnemy() {//Busca un target
	if (target_ == nullptr) {//Si no hay enemigo targeteado se busca uno
		double closestEnemy = INT32_MAX;
		Entity* target = nullptr;
	/*	for (auto enemy : mngr_->enemigos)
		{
			float distance = getDistance(enemy->getComponent<Transform>().);
			if(distance < range_ && distance < closestEnemy){
				target = enemy;
				closestEnemy = distance;
			}
		}*/		
	}	
	else {
		/*if (getDistance(target_->getComponent<Transform>().getPosition()) > range_) {
			target_ = nullptr;
		}*/
	}
}

float AttackComponent::getDistance(Vector2D targetPos) {
	Vector2D myPos = { 0,0 };//ent_->getComponent<Transform>().getPosition();
	return sqrt(pow(myPos.getX() - targetPos.getX(), 2) + pow(myPos.getY() - targetPos.getY(), 2));
}


