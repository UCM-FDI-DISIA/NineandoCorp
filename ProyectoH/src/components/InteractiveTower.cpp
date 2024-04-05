#include "InteractiveTower.h"
#include "../ecs/Manager.h"
#include "../components/UpgradeTowerComponent.h"
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
		Message m; 
		m.id = _m_TOWER_CLICKED;
		m.tower_clicked_data.tower = ent_;
		mngr_->send(m);
	}
}
