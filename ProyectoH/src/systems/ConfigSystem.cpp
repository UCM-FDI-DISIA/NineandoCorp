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
	typesResolutions = { {1440, 1080}, {1400,1050},{1280,1024} };
	
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
	if(!bS->getFullScreen())
		bS->addButton(pAux, sAux, gameTextures::button, gameTextures::button_hover, ButtonTypes::full_screen);
	else
		bS->addButton(pAux, sAux, gameTextures::check, gameTextures::check_hover, ButtonTypes::full_screen);
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
		createResolutions(m.settings_data.resolutions);
		break;
	}
}
void ConfigSystem::createResolutions(int resolutions_) {
	std::map<std::string, gameTextures> textureResolutions = {
		{"resolution1", gameTextures::resolution1},
		{"resolution1_hover", gameTextures::resolution1_hover},
		{"resolution2", gameTextures::resolution2},
		{"resolution2_hover", gameTextures::resolution2_hover},
		{"resolution3", gameTextures::resolution3},
		{"resolution3_hover", gameTextures::resolution3_hover},
	};
	
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	for (int i = 1; i <= resolutions_; i++)
	{
		std::string resolImg = "resolution" + to_string(i);
		std::string resolHovImg = "resolution" + to_string(i) + "_hover";
		auto it = textureResolutions.find(resolImg);
		auto itHov = textureResolutions.find(resolHovImg);
		bS->addButton({ sdlutils().width() / 4.0f + 250, sdlutils().height() / 3.0f - 45 + (i -1) * 45 }, { 150.0f, 35.0f }, it->second, itHov->second, ButtonTypes::changeResolution,0, typesResolutions[i-1].getX(), typesResolutions[i - 1].getY());
	}
}

