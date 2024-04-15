#include "PauseSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

PauseSystem::PauseSystem() {

}

PauseSystem::~PauseSystem() {
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_PAUSE)) {
		mngr_->setAlive(en, false);
		mngr_->deleteHandler(_hdlr_BUTTON_PLAY, en);
	}
	mngr_->refresh();

	mngr_->deleteAllHandlers(_hdlr_BUTTON_PAUSE);
}

void PauseSystem::initSystem() {
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	
	Vector2D posAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D scaleAux = { 350.0f , 300.0f };

	Entity* background = bS->addImage(posAux, scaleAux,
		90.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, background);

	scaleAux = { 210.0f, 70.0f };//escala de los botones

	posAux = posAux + Vector2D( 0.0f, -100.0f);
	Entity* resume = bS->addButton(posAux, scaleAux, 
		gameTextures::resume_button, gameTextures::resume_button_hover, ButtonTypes::resume_main);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, resume);

	posAux = posAux + Vector2D(0.0f, 100.0f);
	Entity* backToMenu = bS->addButton(posAux, scaleAux, 
		gameTextures::backToMenu_button, gameTextures::backToMenu_button_hover, ButtonTypes::none);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, backToMenu);

	posAux = posAux + Vector2D(0.0f, 100.0f);
	Entity* exitGame = bS->addButton(posAux, scaleAux, 
		gameTextures::exitGame_button, gameTextures::exitGame_button_hover, ButtonTypes::exit_button);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, exitGame);

	//icono arriba a la derecha
	scaleAux = { 50.0f, 50.0f };
	posAux = { (float)sdlutils().width() - 50.0f , 50.0f };
	Entity* resumeIcon = bS->addButton(posAux, scaleAux,
		gameTextures::resume_icon_button, gameTextures::resume_icon_button_hover, ButtonTypes::resume_main);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, resumeIcon);
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