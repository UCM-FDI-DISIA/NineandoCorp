#pragma once
#include "..//ecs/System.h"
#include "..//components/Transform.h"
class EnemySystem: public System
{

public:

	EnemySystem();
	virtual ~EnemySystem();
	void update() override;
	void initSystem() override;
	void receive(const Message& m) override;
	void onRoundOver();
	void onRoundStart();
	void collideswithEnemy();

protected:

	static constexpr sysId_type id = _sys_ENEMY;
	std::vector<Transform*> enemiesTransforms;
	bool active_;
};

