#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

// Correspondant texture to each type of entity
enum gameTextures {
	//map
	tileSet,
	//UI
	play, play_hover, box, box_hover, large_box, 
	close, close_hover, enemies_button, enemies_button_hover, 
	menu_background, upgrade, upgrade_hover, logo,  
	cristal_tower_image, bullet_tower_image, slime_tower_image,
	sniper_tower_image, phoenix_tower_image, dirt_tower_image,
	power_tower_image, nexus_level_3_image,
	// towers
	square, bulletTowerTexture, cristalTowerTexture, phoenixTowerTexture,
	slimeTowerTexture, boosterTowerTexture, sniperTowerTexture, clayTowerTexture, nexusTexture, fireTexture,
	
	//enemies
	goblin, maldito, elfo, golem, angel, maestro, acechante, defensor, demonioAlado,
	demonioInfernal, mensajero, CMaldito, principito, monje, muerte,

	//texts
	nexus_level_text,
	
	//others
	bulletTexture,sniperBulletTexture,slimeBulletTexture,slimeArea,


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

