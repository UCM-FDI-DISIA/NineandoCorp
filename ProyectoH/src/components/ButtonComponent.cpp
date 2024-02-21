#include "ButtonComponent.h"
#include "../ecs/Manager.h"

void ButtonComponent::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
}

ButtonTypes ButtonComponent::isPressed(Vector2D mousePos) {
	if (hover(mousePos)) return id_;
	else return ButtonTypes::none;
}

bool ButtonComponent::hover(Vector2D mousePos) {
	auto pos = tr_->getPosition();
	auto height = tr_->getHeight();
	auto width = tr_->getWidth();
	//calculate the corners of zone
	float leftX = pos->getX();
	float rightX = pos->getX() + width;
	float bottomY = pos->getY() + height;
	float topY = pos->getY();
	return((mousePos.getX() >= leftX && mousePos.getX() <= rightX) && (mousePos.getY() <= bottomY && mousePos.getY() >= topY));
}