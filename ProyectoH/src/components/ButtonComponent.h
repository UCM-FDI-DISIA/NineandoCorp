#pragma once
#include "../ecs/Component.h"
enum ButtonTypes {
	pruebaButton,backButton
};
class ButtonComponent :public Component
{
	//constructora
	//desrtuctora
	//metodo ifpressed
public:
	SDL_Texture* texture;
	Button() {}
	//get the x and y of the top left corner sprite 
	Button(int x, int y);
	Button::Button(int x, int y)
	{
		static SDL_Texture * t = IMG_LoadTexture(ren, "Buttons.png")
	}
	~Button() {}


};

