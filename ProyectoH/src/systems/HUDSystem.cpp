#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

HUDSystem::HUDSystem() :
	buttonsSpace_length_() , //
	infoSpace_length_(){
}
HUDSystem::~HUDSystem(){
}

void HUDSystem::initSystem() {
	buttonsSpace_length_ = sdlutils().width() - 200; 

	float heightH = (float)sdlutils().height() - 80.0f;
	//float xAux = (float)(sdlutils().width() - 150)  / 7;


	float xAux = (float)(buttonsSpace_length_ - 150 ) / 7;
	float separation = 150.0f;
	Vector2D bSize = Vector2D(100.0f, 100.0f);
	addImage({ (float)sdlutils().width() / 2 , heightH },
		{ (float)sdlutils().width() + 30.0f, 200.0f },
		0.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);

	// bullet tower
	addButton({ xAux, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ xAux, heightH },
		{ 55.0f, 80.0f }, 
		gameTextures::bullet_tower_image, gameTextures::bullet_tower_image,
		ButtonTypes::none);

	// cristal tower
	addButton({ xAux * 2, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ xAux * 2, heightH },
		{ 55.0f, 80.0f },
		gameTextures::crystal_tower_image, gameTextures::crystal_tower_image,
		ButtonTypes::none);

	//phoenix_tower
	addButton({ xAux * 3, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ xAux * 3, heightH },
		{ 60.0f, 80.0f },
		gameTextures::phoenix_tower_image, gameTextures::phoenix_tower_image,
		ButtonTypes::none);

	//dirt_tower
	addButton({ xAux * 4, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ xAux * 4, heightH },
		{ 60.0f, 80.0f },
		gameTextures::clay_tower_image, gameTextures::clay_tower_image,
		ButtonTypes::none);

	//sniper_tower
	addButton({ xAux * 5, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ xAux* 5, heightH },
		{ 45.0f, 80.0f },
		gameTextures::sniper_tower_image, gameTextures::sniper_tower_image,
		ButtonTypes::none);

	//slime_tower
	addButton({ xAux * 6, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ xAux * 6, heightH },
		{ 60.0f, 80.0f },
		gameTextures::slime_tower_image, gameTextures::slime_tower_image,
		ButtonTypes::none);

	//boost_tower
	addButton({ xAux * 7, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::none);
	addButton({ xAux * 7, heightH },
		{ 55.0f, 80.0f },
		gameTextures::power_tower_image, gameTextures::power_tower_image,
		ButtonTypes::none);
	
}

void HUDSystem::receive(const Message& m) {

}
void HUDSystem::update() {
	manageButtons();
}



