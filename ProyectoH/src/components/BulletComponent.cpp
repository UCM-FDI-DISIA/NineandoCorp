#include "BulletComponent.h"

BulletComponent::BulletComponent(Transform* tr, Entity* target, int damage) :t(tr), targetEntity_(target), damage_(damage) {
	//initComponent();
	Vector2D vel = *(mngr_->getComponent<Transform>(targetEntity_)->getPosition()) - *(t->getPosition());
	t->setVelocity(vel);
}

void BulletComponent::initComponent() {
	t = mngr_->getComponent<Transform>(ent_);
}

void BulletComponent::doDamageTo(Entity* target, int damage){
	Message m;
	m.id = _m_ENTITY_TO_ATTACK;
	m.entity_to_attack.e = target;
	m.entity_to_attack.damage = damage;
	mngr_->send(m);
}

void BulletComponent::onTravelEnds() {
	mngr_->setAlive(ent_, false);
}