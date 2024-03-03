#pragma once
#include "..//ecs/System.h"
#include "..//sdlutils/VirtualTimer.h"
#include "../ecs/Manager.h"
#include "..//components/Transform.h"
#include "../components/AttackComponent.h"
#include "../components/BulletTower.h"
#include "..//components/EnhancerTower.h"
#include "..//components/CrystalTower.h"
#include "..//components/RenderComponent.h"
#include "..//components/DiegoSniperTower.h"
#include "..//components/PhoenixTower.h"
#include "..//components/DirtTower.h"
#include "../components/FramedImage.h"
#include "../components/UpgradeTowerComponent.h"
#include <list>
#include <algorithm>

enum Height{HIGH, LOW};

const float BULLET_SPEED = 1000.0f, FENIX_SPEED = 100.0f, DIEGO_SPEED = 400.0f, SLIME_SPEED = 100.0f, DIEGO_OFFSET = 25.0f;

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
	void onAttackTower(Entity* e, int dmg); //Hace daño a la torre mandada por mensaje
	void addTower(twrId type, Vector2D pos, Height height);
	
	//bool collidesWithEnemy();//Devuelve true si una torre colisiona con un enemigo

protected:
	void shootBullet(Entity* target, float damage, float speed, Vector2D spawnPos);
	void eliminateDestroyedTowers(Entity* t);
	std::vector<Entity*> towers;
	//std::vector<Entity*> lowTowers;
	//std::vector<Entity*> enemies;//Falta el mensaje para acceder a los enemigos desde el receive
	bool active_;
	VirtualTimer timer_;
};

