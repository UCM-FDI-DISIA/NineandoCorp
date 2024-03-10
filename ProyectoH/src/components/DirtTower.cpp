#include "DirtTower.h"

DirtTower::DirtTower()
	: AttackComponent::AttackComponent(0, 0, 0, true) {}

void DirtTower::levelUp(int level) {
	HealthComponent* h = mngr_->getComponent<HealthComponent>(ent_);
	if (h != nullptr) {
		switch (level) {
		case 1:
			h->setMaxHealth(300);		
			break;
		case 2:
			h->setMaxHealth(600);
			break;
		case 3:
			h->setMaxHealth(900);
			break;
		case 4:
			h->setMaxHealth(1200);
			break;
		default:
			break;
		}
		h->setHealth(h->getMaxHealth());
	}	
}