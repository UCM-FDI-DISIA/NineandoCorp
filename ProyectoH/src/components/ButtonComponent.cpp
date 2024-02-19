#include "ButtonComponent.h"
#include "../ecs/Manager.h"

void ButtonComponent::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
}

ButtonTypes ButtonComponent::isPressed(Vector2D mousePos) {
	auto pos = tr_->getPosition();
	auto Height = tr_->getHeight();
	auto Width = tr_->getWidth();
	//calculate the corners of zone
	float leftX = pos->getX() - Width / 2;
	float rightX = pos->getX() + Width / 2;
	float topY = pos->getY() + Height / 2;
	float bottomY = pos->getY() - Height / 2;
	if ((mousePos.getX() >= leftX && mousePos.getX() <= rightX) && (mousePos.getY() >= bottomY && mousePos.getY() <= topY)) {
		return id_;
	}
}