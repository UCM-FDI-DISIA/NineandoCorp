#include "ButtonComponent.h"
#include "../ecs/Manager.h"

void ButtonComponent::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
}

ButtonTypes ButtonComponent::isPressed(Vector2D mousePos) {
	auto pos = tr_->getPosition();
	auto height = tr_->getHeight();
	auto width = tr_->getWidth();
	//calculate the corners of zone
	float leftX = pos->getX();
	float rightX = pos->getX() + width;
	float bottomY = pos->getY() + height;
	float topY = pos->getY();
	if ((mousePos.getX() >= leftX && mousePos.getX() <= rightX) && (mousePos.getY() <= bottomY && mousePos.getY() >= topY)) {
		return id_;
	}
	else return ButtonTypes::none;
}