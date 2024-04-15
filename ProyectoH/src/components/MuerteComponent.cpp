#include "MuerteComponent.h"

void MuerteComponent::ThrowPotion()
{
	Message m;
	m.entity_to_attack.targetId = _hdlr_LOW_TOWERS;
	mngr_->send(m, true);
}
