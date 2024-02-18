#pragma once
#include "../ecs/Component.h"

// Correspondant texture to each type of entity
enum gameTextures {
	hillTexture, roadTexture, mountainTexture, lakeTexture, lakeEdgeTexture, bulletTexture, square, gmTxtrSize
};

class RenderComponent : public Component
{
private:
	gameTextures texture;
public:
	static const cmpId id = cmpId::_RENDER;

	RenderComponent(gameTextures texture) : texture(texture) {};

	gameTextures getTexture() { return texture; };
};

