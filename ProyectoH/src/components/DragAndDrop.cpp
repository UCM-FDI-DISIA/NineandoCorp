#include "DragAndDrop.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include <cassert>
#include "../sdlutils/InputHandler.h"

DragAndDrop::DragAndDrop() :
	dragging_(false), //
	tr_(nullptr) {

}
DragAndDrop::~DragAndDrop() {

}

void DragAndDrop::initComponent(){
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void DragAndDrop::drag() {
	Vector2D mPos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
	tr_->setPosition(mPos);

	//Posteriormente ajustar posicion a malla del mapa

}



