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
	void onAttackTower(Entity* e, int dmg); //Hace daño a la torre mandada por mensaje
	void addTower(twrId type, Vector2D pos, Height height);
	int intAt(basic_string<char> s) { return sdlutils().intConst().at(s); }
	float floatAt(basic_string<char> s) { return sdlutils().floatConst().at(s); }

protected:
	Entity* shootBullet(Entity* target, Entity* src, float damage, float speed, Vector2D spawnPos, gameTextures texture,Vector2D bulletScale, twrId id);
	Entity* addShield(Vector2D pos);
	Entity* shootFire(Vector2D spawn, float rot, float dmg);
	void clearShieldsArea(Entity* e);
	void eliminateDestroyedTowers(Entity* t);
	std::vector<Entity*> towers;
	bool active_;

	Entity* square;
};

