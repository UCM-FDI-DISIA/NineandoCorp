#pragma once
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

enum ButtonTypes {
	pruebaButton,backButton,none, playButtonMenu
};

class ButtonComponent : public Component
{
	
public:
	static const cmpId id = cmpId::_BUTTON;

	ButtonComponent( ButtonTypes id) : id_(id), tr_(nullptr) {}
	~ButtonComponent() {}

	void initComponent() override;

	ButtonTypes isPressed(Vector2D mousePos);

private:
	Transform* tr_;
	ButtonTypes id_;

};

