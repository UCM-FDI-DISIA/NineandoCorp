#pragma once
#include "Transform.h"

enum ButtonTypes {
	pruebaButton,backButton
};

class ButtonComponent : public Component
{
	//constructora
	//desrtuctora
	//metodo ifpressed
public:
	ButtonComponent( ButtonTypes id) : id_(id), tr_(nullptr) {}
	~ButtonComponent() {}

	void initComponent() override;

	ButtonTypes isPressed(Vector2D mousePos);

private:
	Transform* tr_;
	ButtonTypes id_;

};

