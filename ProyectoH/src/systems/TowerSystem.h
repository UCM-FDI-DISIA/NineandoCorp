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
#include "../components/IconComponent.h"
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
	/// <summary>
	/// Ataca a torre
	/// </summary>
	/// <param name="e">Torre atacada</param>
	/// <param name="dmg">Dano que debe recibir la torre</param>
	void onAttackTower(Entity* e, int dmg, Entity* src); //Hace da�o a la torre mandada por mensaje

	/// <summary>
	/// Anade una torre al sistema, con un tipo, una posicion y una elevacion. A cada torre le anade un render component, un 
	/// framed image, un transform, su componente especifico, un health component y un upgrade tower component, con sus atributos correspondientes sacados de un json.
	/// Las torres se meten en los handlers en funcion de su elevacion
	/// </summary>
	/// <param name="type">Tipo de la torre que definira sus mecanicas y su aspecto</param>
	/// <param name="pos">Posicion en la que se coloca la torre</param>
	/// <param name="height">Elevacion de la torre; puede ser alta o baja</param>
	void addTower(twrId type, const Vector2D& pos, Height height, int sellMoney, Cell* cell);

	int intAt(basic_string<char> s) const { return sdlutils().intConst().at(s); }
	float floatAt(basic_string<char> s) const { return sdlutils().floatConst().at(s); }

	inline void addTowerToInteract(Entity* e) { towersToInteract.push_back(e); }

	Entity* getFrontTower();

	void removeTower(Entity* twr);

protected:

	void enableAllInteractiveTowers(bool b);
	/// <summary>
	/// Spawnea una bala con una posicion, una direccion, un dano y una velocidad
	/// </summary>
	/// <param name="target">Entidad objetivo de la bala</param>
	/// <param name="src">Entidad origen de la bala</param>
	/// <param name="damage">Dano</param>
	/// <param name="speed">Velocidad</param>
	/// <param name="spawnPos">Posicion de spawn, que deberia ser la de la posicion del canon de la torre</param>
	Entity* shootBullet(Entity* target, Entity* src, float damage, float speed, Vector2D spawnPos, gameTextures texture,Vector2D bulletScale, twrId id);
	Entity* addShield(Vector2D pos);	
	void createShieldExplosion(Vector2D pos);
	void createBulletExplosion(Vector2D pos);
	void clearShieldsArea(Entity* e);
	/// <summary>
	/// Debe spawnear una entidad con un fireComponent que tenga un rect y se detecte la colision con enemigos en un collision system
	/// </summary>
	/// <param name="shootingTime">Tiempo en el que esta disparando fuego la torre de fenix</param>
	/// <param name="damage">Dano por segundo causado por la torre de fenix</param>
	Entity* shootFire(Vector2D spawn, float rot, float dmg, Entity* src);
	void eliminateDestroyedTowers(Entity* t);
	std::vector<Entity*> towers;
	bool mActive;
	Entity* square;

	std::vector<Entity*> towersToInteract;
	SDL_Rect* cameraOffset_;

};

