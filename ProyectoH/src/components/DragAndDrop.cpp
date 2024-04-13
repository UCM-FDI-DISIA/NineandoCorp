#include "DragAndDrop.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include <cassert>
#include "../sdlutils/InputHandler.h"

DragAndDrop::DragAndDrop(twrId id, int cost, Height h) :
	tId_(id), //
	dragging_(false), //
	tr_(nullptr), //
	canDrop_(true), //
	height_(h), //
	cost(cost){
}
DragAndDrop::~DragAndDrop() {

}

void DragAndDrop::initComponent(){
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void DragAndDrop::drop(const Vector2D& pos, Height h, Cell* cell){
	if (canDrop_) {
		Message m;
		m.id = _m_ADD_TOWER;
		m.add_tower_data.towerId = tId_; 
		m.add_tower_data.pos = pos; 
		m.add_tower_data.height = height_;
		m.add_tower_data.sellMoney = cost / 0.75;
		m.add_tower_data.cell = cell;
		mngr_->send(m);
	
		Message m2;
		m2.id = _m_ADD_MONEY;
		m2.money_data.money = -cost;
		m2.money_data.Hmoney = 0;
		mngr_->send(m2);

		dragging_ = false;
	}
}


void DragAndDrop::drag(const Vector2D& tilePos) {
	tr_->setScale(setScaleToIcon(tId_));
	tr_->setPosition(adjustPosToTile(tilePos));
}



Vector2D DragAndDrop::adjustPosToTile(const Vector2D& initPos) {
	auto mS = mngr_->getSystem<mapSystem>();
	const Vector2D scale = tr_->getScale();
	auto tileSize = mS->getTileSize();

	//Ajuste a la casilla
	Vector2D endPos = initPos - Vector2D((3 * mS->getTileSize().getX() / 4), scale.getY() - (3 * mS->getTileSize().getY() / 8) - mS->getTileSize().getY() / 2);

	//Ajuste individual para cada torre
	switch (tId_)
	{
	case _twr_BULLET:
		endPos = endPos - Vector2D(4.0f, -7.0f);
		break;
	case _twr_CRISTAL:
		endPos = endPos - Vector2D(8.0f, 8.0f);
		break;
	case _twr_SLIME:
		break;
	case _twr_DIEGO:
		endPos = endPos - Vector2D(3.0f, -10.0f);
		break;
	case _twr_FENIX:
		endPos = endPos - Vector2D(6.0f, -10.0f);
		break;
	case _twr_CLAY:
		break;
	case _twr_POWER:
		break;
	default:
		break;
	}
	return endPos;
}

Vector2D DragAndDrop::setScaleToIcon(twrId tId)
{
	Vector2D scale;
	auto tS = mngr_->getSystem<TowerSystem>();

	switch (tId)
	{
	case _twr_BULLET:
		scale.set(tS->floatAt("BulletScaleX"), tS->floatAt("BulletScaleY"));
		break;
	case _twr_CRISTAL:
		scale.set(tS->floatAt("CristalScaleX"), tS->floatAt("CristalScaleY"));
		break;
	case _twr_SLIME:
		scale.set(tS->floatAt("SlimeScaleX"), tS->floatAt("SlimeScaleY"));
		break;
	case _twr_DIEGO:
		scale.set(tS->floatAt("SniperScaleX"), tS->floatAt("SniperScaleY"));
		break;
	case _twr_FENIX:
		scale.set(tS->floatAt("FenixScaleX"), tS->floatAt("FenixScaleY"));
		break;
	case _twr_CLAY:
		scale.set(tS->floatAt("ClayScaleX"), tS->floatAt("ClayScaleY"));
		break;
	case _twr_POWER:
		scale.set(tS->floatAt("PotenciadorScaleX"), tS->floatAt("PotenciadorScaleY"));
		break;
	case _twr_NEXUS:
		break;
	default:
		break;
	}
	return scale;
}





