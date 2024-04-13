#include "PrincipitoComponent.h"
#include "AttackComponent.h"

void PrincipitoComponent::setAttackSpeed() {
	auto ac = mngr_->getComponent<AttackComponent>(ent_);
	if (ac->getReloadTime() > 0.25) {
		ac->setReloadTime(ac->getReloadTime()*0.85f);
	}
	else {
		ac->setReloadTime(0.25f);
	}
}