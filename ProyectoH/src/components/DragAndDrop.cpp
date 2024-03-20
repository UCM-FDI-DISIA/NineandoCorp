#include "DragAndDrop.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include <cassert>
#include "../sdlutils/InputHandler.h"

DragAndDrop::DragAndDrop(twrId id) :
	tId_(id), //
	dragging_(false), //
	tr_(nullptr) {

}
DragAndDrop::~DragAndDrop() {

}

void DragAndDrop::initComponent(){
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void DragAndDrop::drop(const Vector2D& pos, Height h){
	Message m;
	m.id = _m_ADD_TOWER;
	m.add_tower_data.towerId = tId_; 
	m.add_tower_data.pos = pos; 
	m.add_tower_data.height = h; 
	mngr_->send(m); 
}


void DragAndDrop::drag() {
	auto tS = mngr_->getSystem<TowerSystem>();
	auto net = tS->getNet();
	Vector2D mPos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
	tr_->setPosition(net->searchCell(mPos.getX(), mPos.getY())->position - Vector2D(tr_->getScale()->getX() / 2, tr_->getScale()->getX() / 2));

			//Posteriormente ajustar posicion a malla del mapa
}



