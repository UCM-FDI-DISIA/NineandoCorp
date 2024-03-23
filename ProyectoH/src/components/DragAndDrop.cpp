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

void DragAndDrop::drop(const Vector2D& pos, Height h, const Vector2D& scale){

	tr_->setScale({ 110.0f , 120.0f });
	Message m;
	m.id = _m_ADD_TOWER;
	m.add_tower_data.towerId = tId_; 
	m.add_tower_data.pos = getPosFromTile(pos); 
	m.add_tower_data.height = h; 
	m.add_tower_data.scale = tr_->getScale();
	mngr_->send(m); 
}


void DragAndDrop::drag() {
	auto mS = mngr_->getSystem<mapSystem>();
	auto net = mS->getMalla();
	tr_->setScale({ 120.0f , 126.0f});
	Vector2D mPos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
	Vector2D scale = tr_->getScale();
	Vector2D tilePos = net->searchCell(mPos)->position;
	tr_->setPosition(getPosFromTile(mPos));

}

Vector2D DragAndDrop::getPosFromTile(const Vector2D&  pos) {
	auto mS = mngr_->getSystem<mapSystem>();
	auto net = mS->getMalla();
	Vector2D scale = tr_->getScale();
	Vector2D tilePos = net->searchCell(pos)->position;
	return tilePos - Vector2D((3 * mS->getTileSize().getX() / 4) + 10, scale.getY() - (3 * mS->getTileSize().getY() / 8) - (mS->getTileSize().getY() / 2) + 2);
}



