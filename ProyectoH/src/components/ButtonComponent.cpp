#include "ButtonComponent.h"
#include "../ecs/Manager.h"

void ButtonComponent::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
}

ButtonTypes ButtonComponent::isPressed(Vector2D mousePos) {
	auto pos = tr_->getPosition()
	/*auto Height = tr_-*/

}