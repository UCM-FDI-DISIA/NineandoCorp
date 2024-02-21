#pragma once
#include "..//ecs/System.h"
#include "..//components/Transform.h"
#include "..//sdlutils/VirtualTimer.h"
#include "../components/AttackComponent.h"
#include "../components/BulletTower.h"
#include "../ecs/Manager.h"


class TowerSystem : public System
{
public:
	static constexpr sysId_type id = _sys_TOWERS;
	TowerSystem();
	~TowerSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update();
	void onRoundOver();
	void onRoundStart();
	//bool collidesWithEnemy();//Devuelve true si una torre colisiona con un enemigo

protected:

	std::vector<Transform*> towerTransforms;
	bool active_;
	VirtualTimer timer_;
};

