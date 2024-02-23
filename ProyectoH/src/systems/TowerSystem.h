#pragma once
#include "..//ecs/System.h"
#include "..//components/Transform.h"
#include "..//sdlutils/VirtualTimer.h"
#include "../components/AttackComponent.h"
#include "../components/BulletTower.h"
#include "../components/RenderComponent.h"
#include "../ecs/Manager.h"
#include <list>

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
	void addTower();
	void shootBullet(Entity* target, float damage);
	//bool collidesWithEnemy();//Devuelve true si una torre colisiona con un enemigo

protected:

	std::vector<Entity*> towers;
	std::vector<Entity*> enemies;//Falta el mensaje para acceder a los enemigos desde el receive
	bool active_;
	VirtualTimer timer_;
};

