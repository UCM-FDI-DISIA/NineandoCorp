#include "MensajeroMuerteComponent.h"
#include "AttackComponent.h"
#include "Transform.h"
#include "algorithm"


void MensajeroMuerteComponent::changeGroup(hdlrId_type h) {
	if (!fantasma_) {
		mngr_->deleteHandler(_hdlr_ENEMIES, ent_);
		mngr_->setHandler(_hdlr_GHOST_ENEMIES, ent_);
		fantasma_ = !fantasma_;
	}
	else{
		mngr_->deleteHandler(_hdlr_GHOST_ENEMIES, ent_);
		mngr_->setHandler(_hdlr_ENEMIES, ent_);
		fantasma_ = !fantasma_;
	}
}
bool MensajeroMuerteComponent::Detect(const std::list<Entity*>& g) {
	for (auto e : g) {
		auto tr = mngr_->getComponent<Transform>(e);
		auto rslt = *(tr->getPosition()) - *(mngr_->getComponent<Transform>(ent_)->getPosition());
		auto p =sqrt(pow(rslt.getX(),2) + pow(rslt.getY(), 2));
		return mngr_->getComponent<AttackComponent>(ent_)->getRange() >= p;
	}
}
