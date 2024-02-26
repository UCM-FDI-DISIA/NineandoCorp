#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

// Correspondant texture to each type of entity
enum gameTextures {
	tileSet, bulletTexture, play, playHover,square, bulletTowerTexture, cristalTowerTexture, phoenixTowerTexture,
	slimeTowerTexture, boosterTowerTexture, sniperTowerTexture, clayTowerTexture,gmTxtrSize
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

