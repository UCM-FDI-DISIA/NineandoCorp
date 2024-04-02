#include "GolemComponent.h"
#include "../components/HealthComponent.h"
void
GolemComponent::Regenera() {
	mngr_->getComponent<HealthComponent>(ent_)->addHealth(cura_);
	std::cout << "regenera" << " ";
}