#include "AcechanteComponent.h"
#include "algorithm"
#include "../components/Transform.h"
#include "../components/MovementComponent.h"
#include "../components/IconComponent.h"
#include "../components/RenderComponent.h"

void AcechanteComponent::inRange(const std::list<Entity*>& enemyGroup)
{
	for (const auto& enemy : enemyGroup) {
		IconComponent* ic = mngr_->getComponent<IconComponent>(enemy);
		if (getDistance(mngr_->getComponent<Transform>(enemy)->getPosition()) < range_ && getDistance(mngr_->getComponent<Transform>(enemy)->getPosition()) != 0) {
			mngr_->getComponent<MovementComponent>(enemy)->activateAcceleration(velAcceleration_, true);			
			if (ic == nullptr)	ic = mngr_->addComponent<IconComponent>(enemy, _ACECHANTE);//Agregarselo si no lo tiene
			if (ic->getIconType() == _ACECHANTE) {
				if (!ic->hasIcon()) {//Crearlo si no lo tiene
					Entity* icon = mngr_->addEntity(_grp_ICONS);
					mngr_->addComponent<RenderComponent>(icon, slimeBulletTexture);
					Transform* tr = mngr_->addComponent<Transform>(icon);
					Transform* targetTR = mngr_->getComponent<Transform>(enemy);
					tr->setPosition(*(targetTR->getPosition()));
					tr->setScale(*(targetTR->getScale()) / 6);

					ic->setHasIcon(true);
					ic->setIcon(icon);
				}
			}			
			std::cout << getDistance(mngr_->getComponent<Transform>(enemy)->getPosition()) << std::endl;
		}
		else {
			if (ic != nullptr && ic->hasIcon() && ic->getIconType() == _ACECHANTE) {//Eliminarlo si no se encuentra en la distancia
				ic->setHasIcon(false);
				mngr_->setAlive(ic->getIcon(), false);
			}
		}
	}
}

float AcechanteComponent::getDistance(Vector2D otherPos)
{
	Vector2D myPos = mngr_->getComponent<Transform>(ent_)->getPosition();
	return sqrt(pow(myPos.getX() - otherPos.getX(), 2) + pow(myPos.getY() - otherPos.getY(), 2));
}
