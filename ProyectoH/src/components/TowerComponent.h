#pragma once
#include "../ecs/Component.h"
class TowerComponent : public Component {
public:
	static const cmpId id = cmpId::_TOWER;

	TowerComponent(twrId tId, Height h, int sell = 0) : 
		tId_(tId), // 
		height_(h), // 
		sellMoney_(sell) {}

	virtual ~TowerComponent() {

	}
	inline Height getTowerHeight() const { return height_; }

	inline int getSellMoney() const { return sellMoney_; }

	inline twrId getTowerId() const { return tId_; }

private:
	Height height_;
	int sellMoney_;
	twrId tId_;
};