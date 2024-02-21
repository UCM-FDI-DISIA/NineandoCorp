#pragma once
#include "../ecs/Component.h"

// Correspondant texture to each type of entity
enum gameTextures {
	hillTexture, roadTexture, mountainTexture, lakeTexture1, lakeTexture2, lakeTexture3, lakeTexture4,
	lakeTexture5, lakeTexture6, lakeTexture7, lakeTexture8, lakeTexture9, lakeTexture10,
	lakeTexture11, bulletTexture, square, play, playHover,gmTxtrSize
};

class RenderComponent : public Component
{
private:
	gameTextures texture;
	
public:
	static const cmpId id = cmpId::_RENDER;

	RenderComponent(gameTextures texture) : texture(texture) {};

	gameTextures getTexture() { return texture; };

	inline void setTexture(gameTextures t) {
		texture = t;
	}
};

