#include "EnemyProyectileComponent.h"
#include "FramedImage.h"

EnemyProyectileComponent::EnemyProyectileComponent(Transform* tr, Entity* target, Entity* src, int damage, float speed):t(tr), target_(target), src_(src), damage_(damage), speed_(speed)
{
}

void EnemyProyectileComponent::doDamageTo(Entity* e, float damage) {
	Message m;
	m.id = _m_ENTITY_TO_ATTACK;
	m.entity_to_attack.src = src_;
	m.entity_to_attack.damage = damage;
	m.entity_to_attack.e = e;
	m.entity_to_attack.targetId = _hdlr_LOW_TOWERS;
	mngr_->send(m);
}

void EnemyProyectileComponent::OnTravelEnds() {
	mngr_->setAlive(ent_, false);
}

//Utiliza el FramedImage para acceder al centro de la imagen de la entidad objetivo para que la bala se dirija ahi
void EnemyProyectileComponent::setDir() {
	FramedImage* fi = mngr_->getComponent<FramedImage>(target_);
	auto tr = mngr_->getComponent<Transform>(target_);
	Vector2D targetPos = *(tr->getPosition());
	if (fi != nullptr) {
		Vector2D offset = { (float)fi->getSize().getX() / 5, (float)fi->getSize().getY() / 5 };//Se dirige hacia el centro del rect
		targetPos = targetPos + offset;
	}
	Vector2D vel = targetPos - *(t->getPosition());
	vel = vel.normalize();
	Vector2D norm = { 1, 0 };
	float dot = norm.getX() * vel.getX() + norm.getY() * vel.getY();
	float det = norm.getX() * vel.getY() + norm.getY() * vel.getX();
	float angle = atan2(det, dot);
	t->setVelocity(vel * speed_);
}