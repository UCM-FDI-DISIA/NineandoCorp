#include "BulletComponent.h"
#include "FramedImage.h"


BulletComponent::BulletComponent(Transform* tr, Entity* target, Entity* src, int damage, float speed,hdlrId src_):t(tr), targetEntity_(target), srcEntity(src), damage_(damage), speed_(speed),srcId(src_) {	
}

/// <summary>
/// Provoca dano a la entidad que se le pasa con el dano
/// </summary>
/// <param name="e">Entidad que recibe el dano</param>
/// <param name="damage">Dano producido por la bala</param>
void BulletComponent::doDamageTo(Entity* e, float damage){
	Message m;
	m.id = _m_ENTITY_TO_ATTACK;
	m.entity_to_attack.src = srcEntity;
	m.entity_to_attack.e = e;
	m.entity_to_attack.damage = damage;
	m.entity_to_attack.targetId = _hdlr_ENEMIES;
	m.entity_to_attack.srcId = srcId;
	mngr_->send(m);//Este mensaje lo recibe el enemy system
	onTravelEnds();
}
//Mata la bala
void BulletComponent::onTravelEnds() {
	mngr_->setAlive(ent_, false);
}
//Utiliza el FramedImage para acceder al centro de la imagen de la entidad objetivo para que la bala se dirija ahi
void BulletComponent::setDir() {
	FramedImage* fi = mngr_->getComponent<FramedImage>(targetEntity_);
	auto tr = mngr_->getComponent<Transform>(targetEntity_);
	Vector2D targetPos = *(tr->getPosition());
	if (fi != nullptr) { 
		Vector2D offset = { (float)fi->getSize().getX() / 5, (float)fi->getSize().getY() / 5};//Se dirige hacia el centro del rect
		targetPos = targetPos + offset;
	}
	Vector2D vel = targetPos - *(t->getPosition());
	vel = vel.normalize();
	Vector2D norm = { 1, 0 };
	float dot =	norm.getX() * vel.getX() + norm.getY() * vel.getY();
	float det = norm.getX() * vel.getY() + norm.getY() * vel.getX();
	float angle = atan2(det, dot);
	t->setRotation(180*angle/3.14);
	t->setVelocity(vel*speed_);
}