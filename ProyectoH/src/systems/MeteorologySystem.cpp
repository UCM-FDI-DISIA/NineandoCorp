#include "MeteorologySystem.h"

#include "../ecs/Manager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../game/Game.h"

MeteorologySystem::MeteorologySystem(): minTimeInterval_(0.0),
maxTimeInterval_(1.0), 
elapsedTime_(0) ,
thundersInterval_(0.5),
meteoriteInterval_(1.5),
elapsedSpawn_(0),
quantity_(0),
eventActive_(false),
objectsSpawned_(0)
{
	auto& rand = sdlutils().rand();
	timeToNextEvent_ = rand.nextInt(minTimeInterval_, maxTimeInterval_);
	nextEvent_ = (MeteorologyEvent)rand.nextInt(1, 2);
}

MeteorologySystem::~MeteorologySystem() {

}


void MeteorologySystem::initSystem() {

}

void  MeteorologySystem::receive(const Message& m) {
	switch (m.id) {
	case _m_RETURN_ENTITY:
		switch (nextEvent_)
		{
		case MeteorologySystem::TSUNAMI:
			break;
		case MeteorologySystem::STORM:
			break;
		case MeteorologySystem::METEORITES:
			break;
		case MeteorologySystem::TORNADO:
			break;
		case MeteorologySystem::EARTHQUAKE:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void MeteorologySystem::generateEarthquake(float area) {

}

void MeteorologySystem::generateMeteorites(int num) {

	quantity_ = num;

}

void MeteorologySystem::generateMeteorite() {

	auto& rand = sdlutils().rand();

	auto x = rand.nextInt(50, 750);
	auto y = rand.nextInt(50, 750);


}

void MeteorologySystem::generateStorm(int num) {

	quantity_ = num;
}

void MeteorologySystem::generateThunder() {

	auto& rand = sdlutils().rand();

	auto x = rand.nextInt(50, 750);
	auto y = rand.nextInt(50, 750);

	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.animSpeed = 4;
	m.anim_create.idGrp = _grp_TOWERS_AND_ENEMIES;
	m.anim_create.iterationsToDelete = 1;
	m.anim_create.scale = { 200, 300 };
	m.anim_create.cols = 1;
	m.anim_create.rows = 6;
	m.anim_create.tex = gameTextures::thunder;
	m.anim_create.frameInit = 0;
	m.anim_create.frameEnd = 5;
	m.anim_create.height = 512;
	m.anim_create.width = 256;
	m.anim_create.pos = Vector2D(x, y);
	mngr_->send(m);

}

void MeteorologySystem::generateTornado() {

}

void MeteorologySystem::generateTsunami() {

}

void MeteorologySystem::update() {
	

	if (!eventActive_) { elapsedTime_ += game().getDeltaTime(); }

	if (elapsedTime_ > timeToNextEvent_ && !eventActive_) {//comienza el evento

		eventActive_ = true;

		switch (nextEvent_)
		{
		case MeteorologySystem::TSUNAMI:
			break;
		case MeteorologySystem::STORM:
			generateStorm(50);
			break;
		case MeteorologySystem::METEORITES:
			generateMeteorites(10);
			break;
		case MeteorologySystem::TORNADO:
			break;
		case MeteorologySystem::EARTHQUAKE:		
			break;
		default:
			break;
		}
		elapsedTime_ = 0.0;
	}

	if (eventActive_) {//evento activo
		bool eventOver = false;

		elapsedSpawn_ += game().getDeltaTime();

		switch (nextEvent_)
		{
		case MeteorologySystem::TSUNAMI:
			generateTsunami();
			eventOver = true;
			break;
		case MeteorologySystem::STORM:
			if (elapsedSpawn_ > thundersInterval_ && objectsSpawned_ < quantity_) {
				objectsSpawned_++;
				generateThunder();
				elapsedSpawn_ = 0;
			}
			else if(objectsSpawned_ >= quantity_) { eventOver = true; }
			break;
		case MeteorologySystem::METEORITES:
			if (elapsedSpawn_ > meteoriteInterval_ && objectsSpawned_ < quantity_) {
				objectsSpawned_++;
				generateMeteorite();
				elapsedSpawn_ = 0;
			}
			else if(objectsSpawned_ >= quantity_) { eventOver = true; }
			break;
		case MeteorologySystem::TORNADO:
			generateTornado();
			eventOver = true;
			break;
		case MeteorologySystem::EARTHQUAKE:
			generateEarthquake(400.0);
			eventOver = true;
			break;
		default:
			break;
		}

		if (eventOver) {//acaba el evento
			eventActive_ = false;
			auto& rand = sdlutils().rand();
			elapsedTime_ = 0.0;
			timeToNextEvent_ = rand.nextInt(minTimeInterval_, maxTimeInterval_);
			nextEvent_ = (MeteorologyEvent)rand.nextInt(0, 5);
			objectsSpawned_ = 0;
			elapsedSpawn_ = 0;
			quantity_ = 0;
		}
	}
}
