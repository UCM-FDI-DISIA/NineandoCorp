#pragma once


#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../utils/Vector2D.h"
#include "../ecs/ecs.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Types.hpp>
#include <tmxlite/Tileset.hpp>

class MeteorologySystem : public System
{
public:
	enum MeteorologyEvent{TSUNAMI, STORM, METEORITES, TORNADO, EARTHQUAKE};
	static constexpr sysId_type id = _sys_METEOROLOGY;
	MeteorologySystem();
	~MeteorologySystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update();
private:

	void generateMeteorites(int num);
	void generateMeteorite();
	void generateAnimTornado();
	void generateStorm(int thunderNum);
	void generateThunder();
	void generateTsunami();
	void generateNetMap();
	void generateAnimEarthquake();
	std::vector<Vector2D> RouteTranslate(std::vector<Vector2D> route);
	void addRectTo(Entity* t, rectId id);

	float timeToNextEvent_;
	float elapsedTime_;
	float elapsedSpawn_;
	float minTimeInterval_;
	float maxTimeInterval_;
	float meteoriteInterval_;
	float thundersInterval_;
	int quantity_;
	int objectsSpawned_;
	bool eventActive_;
	bool mActive; //mantiene activo el update

	std::vector<std::vector<Vector2D>> routesToEarthquake;
	int spawn = 0;
	int pos = 0;
	Vector2D tileSize_;
	NetMap* net;


	MeteorologyEvent nextEvent_;
};
