#include "TowerAttackComponent.h"
#include "SDL.h"
#include "algorithm"

TowerAttackComponent::TowerAttackComponent(float range, float reloadTime, int damage) : range(range), reloadTime(reloadTime), damage(damage){
	enemy = nullptr; elapsedTime = 0; timeToShoot = reloadTime; 
}

void TowerAttackComponent::update() {
	elapsedTime = timer.currTime();
	if (elapsedTime > timeToShoot) {
		timeToShoot += reloadTime;
		shoot();//Dispara si esta recargado
	}
	targetEnemy();
}

void TowerAttackComponent::targetEnemy() {
	//if (enemy == nullptr) {//Si no hay enemigo targeteado se busca uno
	//	float closestEnemy = 100000;
	//	Entity* target = nullptr;
	//	for (auto enemy : mngr_->enemigos)
	//	{
	//		float distance = getDistance(enemy->getComponent<Transform>().getPosition());
	//		if(distance < range && distance < closestEnemy){
	//			target = enemy;
	//			closestEnemy = distance;
	//		}
	//	}		
	//}	
	//else {
	//	if (getDistance(enemy->getComponent<Transform>().getPosition()) > range) {
	//		enemy = nullptr;
	//	}
	//}
}

float TowerAttackComponent::getDistance(Vector2D enemyPos) {
	Vector2D myPos = { 0,0 };//ent_->getComponent<Transform>().getPosition();
	return sqrt(pow(myPos.getX() - enemyPos.getX(), 2) + pow(myPos.getY() - enemyPos.getY(), 2));
}


