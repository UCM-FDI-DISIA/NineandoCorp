#include "MuerteComponent.h"
#include "Transform.h"
#include "PotionComponent.h"
#include "RenderComponent.h"

Entity* MuerteComponent::ThrowPotion(Entity* target, Entity* src, float speed, Vector2D spawnPos, gameTextures texture, Vector2D bulletScale)
{
	Entity* bullet = mngr_->addEntity(_grp_ENEMY_PROYECTILE);//crea bala
	Transform* t = mngr_->addComponent<Transform>(bullet);//transform
	t->setPosition(spawnPos);
	t->setScale(bulletScale);
	mngr_->addComponent<PotionComponent>(bullet, t, target, src, speed);//bullet component
	mngr_->addComponent<RenderComponent>(bullet, texture);//habra que hacer switch
	return bullet;
}
