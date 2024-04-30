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
	Vector2D scaleAux = { 450.0f , 300.0f };

	background = bS->addImage(posAux, scaleAux,
		90.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, background);

	scaleAux = { 210.0f, 70.0f };//escala de los botones

	posAux = posAux + Vector2D( 0.0f, -150.0f);
	resume = bS->addButton(posAux, scaleAux, 
		gameTextures::resume_button, gameTextures::resume_button_hover, ButtonTypes::resume_main);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, resume);

	posAux = posAux + Vector2D(0.0f, 100.0f);
	backToMenu = bS->addButton(posAux, scaleAux, 
		gameTextures::backToMenu_button, gameTextures::backToMenu_button_hover, ButtonTypes::backToMenu_warning_button);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, backToMenu);

	posAux = posAux + Vector2D(0.0f, 100.0f);
	settings = bS->addButton(posAux, scaleAux,
		gameTextures::settings, gameTextures::settings_hover, ButtonTypes::config);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, settings);

	posAux = posAux + Vector2D(0.0f, 100.0f);
	exitGame = bS->addButton(posAux, scaleAux, 
		gameTextures::exitGame_button, gameTextures::exitGame_button_hover, ButtonTypes::exit_warning_button);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, exitGame);

	//icono arriba a la derecha
	scaleAux = { 50.0f, 50.0f };
	posAux = { (float)sdlutils().width() - 50.0f , 50.0f };
	resumeIcon = bS->addButton(posAux, scaleAux,
		gameTextures::resume_icon_button, gameTextures::resume_icon_button_hover, ButtonTypes::resume_main);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, resumeIcon);
}

void PauseSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _m_WARNING:
		WarningPanel(m.warning_info.text, m.warning_info.butTyp);
		break;
	default:
		break;
	}
}

void PauseSystem::update() {
}

void  PauseSystem::WarningPanel(string text, ButtonTypes butTyp) {
	SetActivePauseButons(false);
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();

	Vector2D posAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D scaleAux = { 400.0f , 250.0f };

	Entity* background = bS->addImage(posAux, scaleAux,
		0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, background);

	scaleAux = { 150.0f, 75.0f };
	posAux = posAux + Vector2D(-100.0f, 50.0f);
	Entity* exitGame = bS->addButton(posAux, scaleAux,
		gameTextures::exitGame_button, gameTextures::exitGame_button_hover, butTyp);
	mngr_->setHandler(_hdlr_BUTTON_PAUSE, exitGame);

	scaleAux = { 250.0f, 50.0f };
	posAux = { sdlutils().width() / 2.0f - 20.0f, sdlutils().height() / 2.0f - 40.0f };
	SDL_Color color = { 255, 255, 255, 255 };
	bS->addText(text, color, posAux, scaleAux);
}

void  PauseSystem::SetActivePauseButons(bool mActive) {
	mngr_->getComponent<ButtonComponent>(resume)->setActive(mActive);
	mngr_->getComponent<ButtonComponent>(settings)->setActive(mActive);
	mngr_->getComponent<ButtonComponent>(resumeIcon)->setActive(mActive);
	mngr_->getComponent<ButtonComponent>(exitGame)->setActive(mActive);
	mngr_->getComponent<ButtonComponent>(backToMenu)->setActive(mActive);
}

void PauseSystem::addText(const Vector2D& pos, const Vector2D& scale, const double rot, grpId_type grpId) {

	Entity* textEntity = mngr_->addEntity(grpId);

	Transform* textTransform = mngr_->addComponent<Transform>(textEntity);
	textTransform->setPosition(pos);
	textTransform->setScale(scale);
	textTransform->setRotation(rot);

	mngr_->addComponent<RenderComponent>(textEntity, nexus_level_text);
}