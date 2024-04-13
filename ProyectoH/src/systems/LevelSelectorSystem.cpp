#include "LevelSelectorSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

LevelSelectorSystem::LevelSelectorSystem( int currentLevel): currentLevel(currentLevel)
{
	mActive = true;
}
LevelSelectorSystem::~LevelSelectorSystem()
{
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_LVLSEL)) {
		mngr_->setAlive(en, false);
	}
	mngr_->refresh();
	mngr_->deleteAllHandlers(_hdlr_BUTTON_LVLSEL);
}

void LevelSelectorSystem::initSystem()
{
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();

	//-------//
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = {  1000.0f , 600.0f };
	bS->addImage(pAux, sAux, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);

	//close button
	pAux = pAux + Vector2D(430.0f, -230.0f);
	sAux = { 70.0f, 70.0f };
	bS->addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

	////play button
	//pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	//sAux = { 350, 110 };
	//bS->addButton(pAux, sAux, gameTextures::play, gameTextures::play_hover, ButtonTypes::level_selected);
	std::map<std::string, gameTextures> textureMap = {
		{"level1", gameTextures::level1},
		{"level2", gameTextures::level2},
		{"level3", gameTextures::level3},
		{"level4", gameTextures::level4},
		{"level5", gameTextures::level5},
		{"level6", gameTextures::level6},
		{"level7", gameTextures::level7},
		{"level8", gameTextures::level8},
		{"level1_hover", gameTextures::level1_hover},
		{"level2_hover", gameTextures::level2_hover},
		{"level3_hover", gameTextures::level3_hover},
		{"level4_hover", gameTextures::level4_hover},
		{"level5_hover", gameTextures::level5_hover},
		{"level6_hover", gameTextures::level6_hover},
		{"level7_hover", gameTextures::level7_hover},
		{"level8_hover", gameTextures::level8_hover},
		{"level1_desactive", gameTextures::level1_desactive},
		{"level2_desactive", gameTextures::level2_desactive},
		{"level3_desactive", gameTextures::level3_desactive},
		{"level4_desactive", gameTextures::level4_desactive},
		{"level5_desactive", gameTextures::level5_desactive},
		{"level6_desactive", gameTextures::level6_desactive},
		{"level7_desactive", gameTextures::level7_desactive},
		{"level8_desactive", gameTextures::level8_desactive},
		
	};
	int levels = 1;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			//level1 button
			pAux = { sdlutils().width() / 2 - 350.0f + 235 * j, sdlutils().height() / 2 - 100.f + 235 * i };
			sAux = { 150, 150 };
			std::string levelImg = "level" + to_string(levels);
			std::string levelHovImg = "level" + to_string(levels) + "_hover";
			std::string levelDesact = "level" + to_string(levels) + "_desactive";


			auto it = textureMap.find(levelImg);
			auto itHov = textureMap.find(levelHovImg);
			auto itDes = textureMap.find(levelDesact);
			Entity* levelBt = nullptr;
			if (it != textureMap.end() && itHov != textureMap.end()) {
				levelBt = bS->addButton(pAux, sAux, it->second, itHov->second, ButtonTypes::level_selected, levels);
				if (levels > currentLevel) {
					mngr_->getComponent<ButtonComponent>(levelBt)->setActive(false);
					mngr_->getComponent<RenderComponent>(levelBt)->setTexture(itDes->second);
				}
			}
			
			levels++;
		}
		
	}
	
}

void LevelSelectorSystem::receive(const Message& m)
{
	
}

void LevelSelectorSystem::update() {
}




