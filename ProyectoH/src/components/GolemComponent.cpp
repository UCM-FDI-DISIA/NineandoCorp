#include "GolemComponent.h"
#include "../components/HealthComponent.h"
void
GolemComponent::Regenera() {
	HealthComponent* hc = mngr_->getComponent<HealthComponent>(ent_);
	if (hc->getHealth() < hc->getMaxHealth()) {
		mngr_->getComponent<HealthComponent>(ent_)->addHealth(cura_);

	}
	//std::cout << "regenera" << " ";
}