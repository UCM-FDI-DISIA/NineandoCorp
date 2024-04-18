#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "HealthComponent.h"

class BulletComponent : public Component {
protected:
	Transform* t;//Transform de la bala
	Entity* targetEntity_;//Entidad enemigo
	Entity* srcEntity;//Entidad origen
	int damage_;//Dano de la bala
	float speed_;//Velocidad de la bala
	hdlrId srcId;

public:
	static const cmpId id = cmpId::_BULLET;

	BulletComponent(Transform* tr, Entity* target, Entity* src, int damage, float speed, hdlrId src_);
	BulletComponent() {};
	void doDamageTo(Entity* e, float damage);
	void setDir();
	void onTravelEnds();

	float getDamage()const { return damage_; }
		
	Entity* getTarget()const { return targetEntity_; }

};