#include "MeteorologySystem.h"

#include "../ecs/Manager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

MeteorologySystem::MeteorologySystem(): minTimeInterval_(30.0), maxTimeInterval_(90.0), elapsedTime_(0) 
{
	auto& rand = sdlutils().rand();
	timeToNextEvent_ = rand.nextInt(minTimeInterval_, maxTimeInterval_);
}

MeteorologySystem::~MeteorologySystem() {

}


void MeteorologySystem::initSystem() {

}

void  MeteorologySystem::receive(const Message& m) {
	switch (m.id) {
	default:
		break;
	}
}

void MeteorologySystem::generateEarthquake(float area) {

}

void MeteorologySystem::generateMeteorites(int num) {

	auto& rand = sdlutils().rand();

	for (size_t i = 0; i < num; i++)
	{

	}

}

void MeteorologySystem::generateStorm(int num) {

	auto& rand = sdlutils().rand();

	for (size_t i = 0; i < num; i++)
	{

	}
}

void MeteorologySystem::generateTornado() {

}

void MeteorologySystem::generateTsunami() {

}

void MeteorologySystem::update() {
	

	elapsedTime_ += game().getDeltaTime();

	if (elapsedTime_ > timeToNextEvent_) {
		switch (nextEvent_)
		{
		case MeteorologySystem::TSUNAMI:
			generateTsunami();
			break;
		case MeteorologySystem::STORM:
			generateStorm(15);
			break;
		case MeteorologySystem::METEORITES:
			generateMeteorites(10);
			break;
		case MeteorologySystem::TORNADO:
			generateTornado();
			break;
		case MeteorologySystem::EARTHQUAKE:
			generateEarthquake(400.0);
			break;
		default:
			break;
		}
		auto& rand = sdlutils().rand();
		elapsedTime_ = 0.0;
		timeToNextEvent_ = rand.nextInt(minTimeInterval_, maxTimeInterval_);
		nextEvent_ = (MeteorologyEvent)rand.nextInt(0, 5);
	}
}
