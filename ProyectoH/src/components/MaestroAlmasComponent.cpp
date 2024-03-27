#include "MaestroAlmasComponent.h"
#include "../components/TowerStates.h"
void
MaestroAlmasComponent::CiegaTorre(Entity* t) {
	TowerStates* ts = mngr_->getComponent<TowerStates>(t);
	ts->setCegado(true,ceguera_);
}