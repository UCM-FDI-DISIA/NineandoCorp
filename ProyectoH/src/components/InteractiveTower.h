#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
class InteractiveTower : public Component
{
public: 
	static const cmpId id = cmpId::_INTERACTIVE_TOWER;

	InteractiveTower() : tr_(nullptr) {}
	~InteractiveTower() {

	}
	void initComponent() override;
	void update();

	bool isOnRect(const Vector2D& mPos) {
		SDL_Rect rect = tr_->getRect();
		return (mPos.getX() >= rect.x && mPos.getX() <= rect.x + rect.w && mPos.getY() >= rect.y && mPos.getY() <= rect.y + rect.h);
	}

private:  
	Transform* tr_;


};

