#include "DragAndDrop.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include <cassert>
#include "../sdlutils/InputHandler.h"

DragAndDrop::DragAndDrop() :
	currState(State::NONE),
	tr_(nullptr){

}
DragAndDrop::~DragAndDrop() {

}

void DragAndDrop::initComponent() {

	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

/*void DragAndDrop::update() {
	auto& ihdlr = ih();
	float mouseX = ihdlr.getMousePos().first;

	float mouseY = ihdlr.getMousePos().second;

	tr_->getPosition()->set(mouseX, mouseY);
	
}*/

/*void DragAndDrop::handleInput() {
	auto& ihdlr = ih();

	if (ihdlr.mouseButtonEvent()) {
		if (ihdlr.getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
			drop();
		}
	}
}*/