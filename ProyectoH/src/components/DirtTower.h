#pragma once
#include "..//components/AttackComponent.h"

class DirtTower : public AttackComponent
{
public:
	static const cmpId id = cmpId::_DIRTTOWER;

	DirtTower();
	void levelUp(int level);

private:
	int reflectDamage_ = 0;
};

