#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

// Correspondant texture to each type of entity


class RenderComponent : public Component
{
private:
	gameTextures texture;
	SDL_RendererFlip flip_;
public:
	static const cmpId id = cmpId::_RENDER;

	bool isActive;

	RenderComponent(gameTextures texture) : texture(texture), isActive(true){
		flip_ = SDL_FLIP_NONE;
	};

	gameTextures getTexture() const { return texture; };
	inline void setTexture(gameTextures t) {
		texture = t;
	}

	void setFlip(SDL_RendererFlip flip) {
		flip_ = flip;
	}

	SDL_RendererFlip getFlip() const {
		return flip_;
	}

};

