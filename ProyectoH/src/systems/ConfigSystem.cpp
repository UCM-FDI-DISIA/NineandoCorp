#include "ConfigSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"


ConfigSystem::~ConfigSystem()
{
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_CONFIG)) {
		mngr_->setAlive(en, false);
	}
	mngr_->refresh();
	mngr_->deleteAllHandlers(_hdlr_BUTTON_CONFIG);
}
void ConfigSystem::initSystem() {
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	SDL_Color textColor = { 255, 255, 255, 255 };
	//BACKGROUND
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = { sdlutils().width() - 100.0f , sdlutils().height() - 250.0f };
	bS->addImage(pAux, sAux, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	
	// GENERAL
	bS->addText("GENERAL", textColor, { sdlutils().width() / 4.0f, sdlutils().height() / 4.5f }, { 300.0f, 75.0f });
	bS->addText("SOUNDS", textColor, { sdlutils().width() - sdlutils().width() / 4.0f, sdlutils().height() / 4.5f }, { 300.0f, 75.0f });
	
	//RESOLUCION
	pAux = Vector2D(sdlutils().width() / 4.0f, sdlutils().height() / 3.0f);
	sAux = { 300.0f, 70.0f };
	bS->addButton(pAux, sAux, gameTextures::resolution, gameTextures::resolution_hover, ButtonTypes::changeResolution);
	
	//PANTALLA COMPLETA
	bS->addText("FULL SCREEN", textColor, { sdlutils().width() / 4.0f - 35.0f, sdlutils().height() / 2.25f }, { 225.0f, 50.0f });
	pAux = Vector2D(sdlutils().width() / 4.0f + 125.0f, sdlutils().height() / 2.25f);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::full_screen);

	//CONTROLES
	bS->addText("CONTROLS", textColor, { sdlutils().width() / 4.0f, sdlutils().height() / 1.85f - 10 }, { 225.0f, 50.0f });
	pAux = Vector2D(sdlutils().width() / 4.0f - 180, sdlutils().height() / 1.85f + 50);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::back_selector);
	bS->addText("Move Left", textColor, { sdlutils().width() / 4.0f - 70, sdlutils().height() / 1.85f + 50 }, { 155.0f, 25.0f });

	pAux = Vector2D(sdlutils().width() / 4.0f - 180, sdlutils().height() / 1.85f + 110);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::back_selector);
	bS->addText("Move Right", textColor, { sdlutils().width() / 4.0f - 70, sdlutils().height() / 1.85f + 110 }, { 165.0f, 25.0f });

	pAux = Vector2D(sdlutils().width() / 4.0f - 180, sdlutils().height() / 1.85f + 170);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::back_selector);
	bS->addText("Move Up", textColor, { sdlutils().width() / 4.0f -70, sdlutils().height() / 1.85f + 170 }, { 145.0f, 25.0f });

	pAux = Vector2D(sdlutils().width() / 4.0f - 180, sdlutils().height() / 1.85f + 230);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::back_selector);
	bS->addText("Move Down", textColor, { sdlutils().width() / 4.0f - 70, sdlutils().height() / 1.85f + 230 }, { 160.0f, 25.0f });

	pAux = Vector2D(sdlutils().width() / 4.0f + 40, sdlutils().height() / 1.85f + 50);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::back_selector);
	bS->addText("Drag and drop tower", textColor, { sdlutils().width() / 4.0f + 160, sdlutils().height() / 1.85f + 50 }, { 180.0f, 25.0f });

	pAux = Vector2D(sdlutils().width() / 4.0f + 40, sdlutils().height() / 1.85f + 110);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::back_selector);
	bS->addText("Remove Tower", textColor, { sdlutils().width() / 4.0f + 160, sdlutils().height() / 1.85f + 110 }, { 165.0f, 25.0f });

	pAux = Vector2D(sdlutils().width() / 4.0f + 40, sdlutils().height() / 1.85f + 170);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::back_selector);
	bS->addText("Pause", textColor, { sdlutils().width() / 4.0f + 160, sdlutils().height() / 1.85f + 170 }, { 80.0f, 25.0f });

	pAux = Vector2D(sdlutils().width() / 4.0f + 40, sdlutils().height() / 1.85f + 230);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::back_selector);
	bS->addText("Play", textColor, { sdlutils().width() / 4.0f +160, sdlutils().height() / 1.85f + 230 }, { 70.0f, 25.0f });

	//SOUNDS
	bS->addText("GENERAL", textColor, { sdlutils().width() - sdlutils().width() / 4.0f, sdlutils().height() / 3.0f }, { 225.0f, 50.0f });
	bS->addImage({ sdlutils().width() - sdlutils().width() / 4.0f, sdlutils().height() / 3.0f + 75 }, { 20.0f, 200.0f }, 90.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	bS->addSlider({ sdlutils().width() - sdlutils().width() / 4.0f, sdlutils().height() / 3.0f + 75}, { 50.0f, 50.0f }, gameTextures::close, _grp_HUD_FOREGROUND,general);
	
	bS->addText("EFFECTS", textColor, { sdlutils().width() - sdlutils().width() / 4.0f, sdlutils().height() / 2.0f }, { 225.0f, 50.0f });
	bS->addImage({ sdlutils().width() - sdlutils().width() / 4.0f, sdlutils().height() / 2.0f + 75 }, { 20.0f, 200.0f }, 90.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	bS->addSlider({ sdlutils().width() - sdlutils().width() / 4.0f, sdlutils().height() / 2.0f + 75 }, { 50.0f, 50.0f }, gameTextures::close, _grp_HUD_FOREGROUND, effects);
	
	bS->addText("MUSIC", textColor, { sdlutils().width() - sdlutils().width() / 4.0f,sdlutils().height()- sdlutils().height() / 3.0f }, { 180.0f, 50.0f });
	bS->addImage({ sdlutils().width() - sdlutils().width() / 4.0f, sdlutils().height() - sdlutils().height() / 3.0f + 75 }, { 20.0f, 200.0f }, 90.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	bS->addSlider({ sdlutils().width() - sdlutils().width() / 4.0f, sdlutils().height() - sdlutils().height() / 3.0f + 75 }, { 50.0f, 50.0f }, gameTextures::close, _grp_HUD_FOREGROUND, music);
	
	////boton cerrar
	pAux =  Vector2D(sdlutils().width() / 2.0f, sdlutils().height()/2.0f);
	sAux = { 70.0f, 70.0f };
	bS->addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);
	
	
}
void ConfigSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _m_CHANGE_RESOLUTION:
		createResolutions();
		break;
	}
}
void ConfigSystem::createResolutions() {
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	bS->addButton({ sdlutils().width() / 4.0f + 250, sdlutils().height() / 3.0f - 45 }, { 150.0f, 35.0f }, gameTextures::backToMenu_button, gameTextures::backToMenu_button_hover, ButtonTypes::changeResolution);
	bS->addButton({ sdlutils().width() / 4.0f + 250, sdlutils().height() / 3.0f }, { 150.0f, 35.0f }, gameTextures::backToMenu_button, gameTextures::backToMenu_button_hover, ButtonTypes::changeResolution);
	bS->addButton({ sdlutils().width() / 4.0f + 250, sdlutils().height() / 3.0f + 45 }, { 150.0f, 35.0f }, gameTextures::backToMenu_button, gameTextures::backToMenu_button_hover, ButtonTypes::changeResolution);
}

