#include "DragAndDrop.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include <cassert>
#include "../sdlutils/InputHandler.h"
#include "../systems/TowerSystem.h"

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
	
			auto tS = mngr_->getSystem<TowerSystem>();
			auto net = tS->getNet();
			Vector2D mPos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
			tr_->setPosition(net->searchCell(mPos.getX(), mPos.getY())->position - Vector2D(tr_->getScale()->getX() / 2, tr_->getScale()->getX() / 2));

			//Posteriormente ajustar posicion a malla del mapa
}



