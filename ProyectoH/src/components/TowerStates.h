#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
class TowerStates: public Component
{
public:
	static const cmpId id = cmpId::_TOWERSTATES;
	TowerStates() :cegado_(false), tiempoCegado_(0.0f){};
	void setCegado(bool e, float t) {
		cegado_ = e; tiempoCegado_ = t;
	}
private:
	bool cegado_;
	float tiempoCegado_;
};

