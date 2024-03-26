#pragma once

#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../ecs/ecs.h"


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
	void generateTornado();
	void generateStorm(int thunderNum);
	void generateThunder();
	void generateTsunami();
	void generateEarthquake(float area);

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

	MeteorologyEvent nextEvent_;
};
