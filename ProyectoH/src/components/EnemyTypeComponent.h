#pragma once
#include "../ecs/Manager.h"
#include "../ecs/Component.h"

class EnemyTypeComponent : public Component
{
private:
	enmId type;
public:
	static const cmpId id = cmpId::_ENEMYTYPE;
	EnemyTypeComponent(enmId enemy_type): type(enemy_type){}
	enmId GetEnemyType() { return type; }
};
