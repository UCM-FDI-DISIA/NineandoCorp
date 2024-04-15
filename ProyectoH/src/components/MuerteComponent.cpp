#include "MuerteComponent.h"
#include "Transform.h"
#include "EnemyProyectileComponent.h"
#include "RenderComponent.h"

Entity* MuerteComponent::ThrowPotion(Entity* target, Entity* src, float speed, Vector2D spawnPos, gameTextures texture, Vector2D bulletScale)
{
	Entity* potion = mngr_->addEntity(_grp_ENEMY_PROYECTILE);//crea bala
	Transform* t = mngr_->addComponent<Transform>(potion);//transform
	t->setPosition(spawnPos);
	t->setScale(bulletScale);
	mngr_->addComponent<EnemyProyectileComponent>(potion, t, target, src, 0, speed);//bullet component
	mngr_->addComponent<RenderComponent>(potion, texture);//habra que hacer switch
	return potion;
}
