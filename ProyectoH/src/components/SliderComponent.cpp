#include "SliderComponent.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

void SliderComponent::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
}
bool SliderComponent::isPressed(const Vector2D& mousePos) {
	sdlutils().soundEffects().at("button").setChannelVolume(game().CalculoVolumenEfectos(), 1);
	sdlutils().soundEffects().at("button").play(0, 1);
	auto pos = tr_->getPosition();
	auto height = tr_->getHeight();
	auto width = tr_->getWidth();
	//calculate the corners of zone
	float leftX = pos->getX();
	float rightX = pos->getX() + width;
	float bottomY = pos->getY() + height;
	float topY = pos->getY();
	return (mousePos.getX() >= leftX && mousePos.getX() <= rightX) && (mousePos.getY() <= bottomY && mousePos.getY() >= topY);
}

