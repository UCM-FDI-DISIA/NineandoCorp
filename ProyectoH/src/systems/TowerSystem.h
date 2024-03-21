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
#include "..//components/SlimeTowerComponent.h"
#include "../components/FramedImage.h"
#include "../components/UpgradeTowerComponent.h"
#include "../components/FireComponent.h"
#include "../game/Game.h"
#include <list>
#include <algorithm>




class TowerSystem : public System
{
public:
	static constexpr sysId_type id = _sys_TOWERS;
	TowerSystem();
	~TowerSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update();
	void onAttackTower(Entity* e, int dmg); //Hace da�o a la torre mandada por mensaje

	/// <summary>
	/// instancia torre en escena
	/// </summary>
	/// <param name="type">id de la torre</param>
	/// <param name="pos">posicion</param>
	/// <param name="height">si pertenece a pradera o monta�a</param>
	void addTower(twrId type, const Vector2D& pos, Height height, const Vector2D& scale);
	
	int intAt(basic_string<char> s) { return sdlutils().intConst().at(s); }
	float floatAt(basic_string<char> s) { return sdlutils().floatConst().at(s); }


protected:
	Entity* shootBullet(Entity* target, Entity* src, float damage, float speed, Vector2D spawnPos, gameTextures texture,Vector2D bulletScale, twrId id);
	Entity* shootFire(Vector2D spawn, float rot, float dmg);
	void eliminateDestroyedTowers(Entity* t);
	std::vector<Entity*> towers;
	bool active_;
	Entity* square;
};

