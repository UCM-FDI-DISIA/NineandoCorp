#include "BulletTower.h"
#include "..//ecs/Entity.h"


BulletTower::BulletTower(float range, float reloadTime, int damage) 
	: AttackComponent::AttackComponent(range, reloadTime, damage){}

void BulletTower::update() {
	AttackComponent::update();
	//if (ent_->getComponent<TowerInfo>().info_.level == ent_->getComponent<TowerInfo>().info_.maxlevel) {
	//	targetEnemy(mngr_->targetGroup, secondTarget_);
	//	shoot();//Si esta a nivel maximo lockea otro target y dispara dos balas
	//}
}

void BulletTower::shoot() {
	//Entity* bullet = new Entity();
    //mngr_->addEntity(bullet);
}

