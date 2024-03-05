#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

// Correspondant texture to each type of entity
enum gameTextures {
	//map
	tileSet, hillTexture, roadTexture, mountainTexture, lakeTexture1, lakeTexture2, lakeTexture3, lakeTexture4,
	lakeTexture5, lakeTexture6, lakeTexture7, lakeTexture8, lakeTexture9, lakeTexture10,
	lakeTexture11,
	//UI
	play, play_hover, box, box_hover, large_box, none_box, none_box_hover,
	close, close_hover, enemies_button, enemies_button_hover, 
	menu_background, upgrade, upgrade_hover, logo,  
	cristal_tower_image, bullet_tower_image, slime_tower_image,
	sniper_tower_image, phoenix_tower_image, dirt_tower_image,
	power_tower_image, nexus_level_3_image,
	// towers
	square, bulletTowerTexture, cristalTowerTexture, phoenixTowerTexture,
	slimeTowerTexture, boosterTowerTexture, sniperTowerTexture, clayTowerTexture, nexusTexture,
	
	//enemies

	//others
	bulletTexture, 


	gmTxtrSize
};

class RenderComponent : public Component
{
private:
	gameTextures texture;
public:
	static const cmpId id = cmpId::_RENDER;

	RenderComponent(gameTextures texture) : texture(texture){};

	gameTextures getTexture() { return texture; };
	inline void setTexture(gameTextures t) {
		texture = t;
	}

};

