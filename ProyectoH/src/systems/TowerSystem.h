#pragma once
#include "..//ecs/System.h"
#include "..//sdlutils/VirtualTimer.h"
#include "../ecs/Manager.h"
#include "..//components/Transform.h"
#include "../components/AttackComponent.h"
#include "../components/BulletTower.h"
#include "..//components/EnhancerTower.h"
#include "../components/RenderComponent.h"
#include <list>

enum TowerType{FENIX, BULLET, WALL, ENHANCER, DIEGO, SLIME, SHIELD};
enum Height{HIGH, LOW};

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
	void addTower(TowerType type, Vector2D pos, Height height);
	
	//bool collidesWithEnemy();//Devuelve true si una torre colisiona con un enemigo

protected:
	void shootBullet(Entity* target, float damage);
	void eliminateDestroyedTowers(Entity* t);
	std::vector<Entity*> towers;
	//std::vector<Entity*> lowTowers;
	//std::vector<Entity*> enemies;//Falta el mensaje para acceder a los enemigos desde el receive
	bool active_;
	VirtualTimer timer_;
};

