#pragma once
#include "..//ecs/System.h"
#include "../systems/mapSystem.h"
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
#include "../game/Game.h"
#include "../utils/NetMap.h"
#include <list>
#include <algorithm>



const float BULLET_SPEED = 500.0f, FENIX_SPEED = 100.0f, DIEGO_SPEED = 600.0f, SLIME_SPEED = 100.0f, DIEGO_OFFSET = 25.0f;

class TowerSystem : public System
{
public:
	static constexpr sysId_type id = _sys_TOWERS;
	TowerSystem(NetMap* malla);
	~TowerSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update();
	void onRoundOver();
	void onRoundStart();
	void onAttackTower(Entity* e, int dmg); //Hace da�o a la torre mandada por mensaje

	/// <summary>
	/// instancia torre en escena
	/// </summary>
	/// <param name="type">id de la torre</param>
	/// <param name="pos">posicion</param>
	/// <param name="height">si pertenece a pradera o monta�a</param>
	void addTower(twrId type, Vector2D pos, Height height);
	inline NetMap* getNet() { return net; };
	
	//bool collidesWithEnemy();//Devuelve true si una torre colisiona con un enemigo

protected:
	void shootBullet(Entity* target, Entity* src, float damage, float speed, Vector2D spawnPos, gameTextures texture,Vector2D bulletScale);
	void shootFire(float shootingTime, int damage);
	void eliminateDestroyedTowers(Entity* t);
	NetMap* net;
	std::vector<Entity*> towers;
	//std::vector<Entity*> lowTowers;
	//std::vector<Entity*> enemies;//Falta el mensaje para acceder a los enemigos desde el receive
	bool active_;

	Entity* square;
};

