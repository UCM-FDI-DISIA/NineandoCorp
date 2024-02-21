#pragma once
#include "Transform.h"
#include "RenderComponent.h"

enum ButtonTypes {
	pruebaButton, backButton, none
};

class ButtonComponent : public Component
{
	
public:
	static const cmpId id = cmpId::_BUTTON;

	ButtonComponent( ButtonTypes id) : id_(id), tr_(nullptr) {}
	~ButtonComponent() {}

	void initComponent() override;
	inline void setHover(gameTextures h) {
		hoverTexture = h;
	}
	inline void setTexture(gameTextures t) {
		texture = t;
	}

	ButtonTypes isPressed(Vector2D mousePos);

	bool hover(Vector2D mousePos);

	inline gameTextures getHover() { return hoverTexture; }
	inline gameTextures getTexture() { return texture; }

private:
	Transform* tr_;
	ButtonTypes id_;
	gameTextures hoverTexture;
	gameTextures texture;

};

