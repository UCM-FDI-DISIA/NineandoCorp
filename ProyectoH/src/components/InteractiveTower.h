#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
class InteractiveTower : public Component
{
public: 
	static const cmpId id = cmpId::_INTERACTIVE_TOWER;

	InteractiveTower(SDL_Rect* cameraOffset_) : tr_(nullptr), cameraOffset_(cameraOffset_) , canInteract_(true){}
	~InteractiveTower() {

	}
	void initComponent() override;
	void update();

	/// <summary>
	/// Te compruba si la posicion esta encima de la torre o no 
	/// </summary>
	/// <param name="mPos">posicion del cursor del raton</param>
	/// <returns>true en caso de estar encima, false de lo contrario </returns>
	bool isOnRect(const Vector2D& mPos) {
		SDL_Rect rect = tr_->getRect();
		rect.x += cameraOffset_->x;
		rect.y += cameraOffset_->y;
		return (mPos.getX() >= rect.x && mPos.getX() <= rect.x + rect.w && mPos.getY() >= rect.y && mPos.getY() <= rect.y + rect.h);
	}

	bool canInteract_;
private:  
	Transform* tr_;
	SDL_Rect* cameraOffset_;
};

