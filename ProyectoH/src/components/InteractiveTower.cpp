#include "InteractiveTower.h"
#include "../ecs/Manager.h"
void InteractiveTower::initComponent()
{
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void InteractiveTower::update() {
	Vector2D mPos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };

	if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1 
	 && isOnRect(mPos)) 
	{
		std::cout << " OKOKOK" << std::endl; 
	}
}
