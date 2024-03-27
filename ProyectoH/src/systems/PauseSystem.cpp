#include "PauseSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

PauseSystem::PauseSystem() {

}

PauseSystem::~PauseSystem() {
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_PAUSE)) {
		mngr_->setAlive(en, false);
	}
	mngr_->refresh();

	mngr_->deleteAllHandlers(_hdlr_BUTTON_PAUSE);
}

void PauseSystem::initSystem() {
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	
	Vector2D posAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D scaleAux = { 1200.0f , 800.0f };

	bS->addImage(posAux, scaleAux, 0.0, gameTextures::large_box, _grp_GENERAL);
	

	posAux += Vector2D(530.0f, -330.0f);
	scaleAux = { 70.0f, 70.0f };
	bS->addButton(posAux, scaleAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);
}

void PauseSystem::receive(const Message& m) {
}

void PauseSystem::update() {
}

void PauseSystem::addText(const Vector2D& pos, const Vector2D& scale, const double rot, grpId_type grpId) {

	Entity* textEntity = mngr_->addEntity(grpId);

	Transform* textTransform = mngr_->addComponent<Transform>(textEntity);
	textTransform->setPosition(pos);
	textTransform->setScale(scale);
	textTransform->setRotation(rot);

	mngr_->addComponent<RenderComponent>(textEntity, nexus_level_text);
}