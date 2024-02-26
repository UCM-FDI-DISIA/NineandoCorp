#include "BulletComponent.h"

BulletComponent::BulletComponent(Transform* tr, Entity* target, int damage, float speed):t(tr), targetEntity_(target), damage_(damage), speed_(speed){
	//initComponent();
	
}

//void BulletComponent::initComponent() {
//	t = mngr_->getComponent<Transform>(ent_);
//}

void BulletComponent::doDamageTo(Entity* e, float damage){
	Message m;
	m.id = _m_ENTITY_TO_ATTACK;
	m.entity_to_attack.e = e;
	m.entity_to_attack.damage = damage;
	mngr_->send(m);
}

void BulletComponent::onTravelEnds() {
	mngr_->setAlive(ent_, false);
}

void BulletComponent::setDir() {
	Vector2D vel = *(mngr_->getComponent<Transform>(targetEntity_)->getPosition()) - *(t->getPosition());
	vel = vel.normalize() * speed_;
	t->setVelocity(vel);
}