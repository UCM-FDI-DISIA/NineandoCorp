#pragma once
#include "../ecs/Component.h"
class TowerComponent : public Component {
public:
	static const cmpId id = cmpId::_TOWER;

	TowerComponent(twrId tId, Height h, Cell* cell,int sell = 0) : 
		tId_(tId), // 
		height_(h), // 
		cell_(cell), //
		sellMoney_(sell) {}

	virtual ~TowerComponent() {

	}
	inline Height getTowerHeight() const { return height_; }

	inline int getSellMoney() const { return sellMoney_; }

	inline twrId getTowerId() const { return tId_; }

	inline Cell* getCell() const { return cell_;}

private:
	Height height_;
	int sellMoney_;
	twrId tId_;
	Cell* cell_;
};