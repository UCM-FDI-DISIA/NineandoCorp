#include "MeteorologySystem.h"

#include "../ecs/Manager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/RenderComponent.h"
#include "../game/Game.h"



MeteorologySystem::MeteorologySystem(): minTimeInterval_(10.0),
maxTimeInterval_(12.0), 
elapsedTime_(0) ,
thundersInterval_(0.5),
meteoriteInterval_(1.5),
elapsedSpawn_(0),
quantity_(0),
eventActive_(false),
objectsSpawned_(0)
{
	mActive = true;
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
			addRectTo(m.return_entity.ent, rectId::_TSUNAMI);
			break;
		case MeteorologySystem::STORM:
			addRectTo(m.return_entity.ent, rectId::_THUNDER);
			break;
		case MeteorologySystem::METEORITES:
			addRectTo(m.return_entity.ent, rectId::_METEORITE);
			break;
		case MeteorologySystem::TORNADO:
			addRectTo(m.return_entity.ent, rectId::_TORNADO);
			break;
		case MeteorologySystem::EARTHQUAKE:
			addRectTo(m.return_entity.ent, rectId::_EARTHQUAKE);
			break;
		case _m_PAUSE:
			mActive = !mActive;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void MeteorologySystem::addRectTo(Entity* e, rectId id) {
	Message m;
	m.id = _m_ADD_RECT;
	m.rect_data.id = id;
	m.rect_data.entity = e;
	mngr_->send(m);
}

void MeteorologySystem::generateCloud() {
	auto ruta = &sdlutils().rutes().at("tornado");
	auto rutaPantalla = RouteTranslate(ruta->points);
	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.animSpeed = 1;
	m.anim_create.idGrp = _grp_AREAOFATTACK;
	m.anim_create.iterationsToDelete = 40;
	m.anim_create.scale = { 1000, 1000 };
	m.anim_create.cols = 1;
	m.anim_create.rows = 1;
	m.anim_create.tex = gameTextures::cloud;
	m.anim_create.frameInit = 0;
	m.anim_create.frameEnd = 0;
	m.anim_create.height = 256;
	m.anim_create.width = 256;
	m.anim_create.route = rutaPantalla;
	m.anim_create.pos = rutaPantalla[0];
	mngr_->send(m);
}

void MeteorologySystem::generateNetMap() {
	auto mS = mngr_->getSystem<mapSystem>();
	net = mS->getMalla();
	tileSize_ = mS->getTileSize();
	quantity_ = tileSize_.getX() * tileSize_.getY();
	
}
void MeteorologySystem::generateAnimEarthquake() {
	auto& rand = sdlutils().rand();

	for (size_t k = 0; k < 15; k++)
	{
		auto i = rand.nextInt(1, (int)tileSize_.getX() / 2 - 3);
		auto j = rand.nextInt(1, (int)tileSize_.getY() - 3);

		auto position = net->getCell(i, j)->position;
		auto x = position.getX();
		auto y = position.getY();
		auto anim = rand.nextInt(0, 3);
		auto animInit = 6 * anim;
		auto animEnd = 6 * anim + 5;
		Message m;
		m.id = _m_ANIM_CREATE;
		m.anim_create.animSpeed = 3;
		m.anim_create.idGrp = _grp_NATURALS_EFFECTS;
		m.anim_create.iterationsToDelete = 4;
		m.anim_create.scale = { 200, 100 };
		m.anim_create.cols = 3;
		m.anim_create.rows = 6;
		m.anim_create.tex = gameTextures::earthquake;
		m.anim_create.frameInit = animInit;
		m.anim_create.frameEnd = animEnd;
		m.anim_create.height = 74;
		m.anim_create.width = 150;
		m.anim_create.pos = Vector2D(x, y);
		mngr_->send(m);
	}
}
void MeteorologySystem::generateMeteorites(int num) {

	quantity_ = num;

}

void MeteorologySystem::generateMeteorite() {

	auto& rand = sdlutils().rand();

	auto i = rand.nextInt(0, tileSize_.getX() / 2 - 1);
	auto j = rand.nextInt(0, tileSize_.getY() - 1);

	auto position = net->getCell(i, j)->position;
	auto x = position.getX();
	auto y = position.getY();

	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.animSpeed = 9;
	m.anim_create.idGrp = _grp_NATURALS_EFFECTS;
	m.anim_create.iterationsToDelete = 1;
	m.anim_create.scale = { 200, 200 };
	m.anim_create.cols = 4;
	m.anim_create.rows = 5;
	m.anim_create.tex = gameTextures::meteorites;
	m.anim_create.frameInit = 0;
	m.anim_create.frameEnd = 18;
	m.anim_create.height = 96;
	m.anim_create.width = 96;
	m.anim_create.pos = Vector2D(x,y);
	mngr_->send(m);
}

void MeteorologySystem::generateStorm(int num) {

	quantity_ = num;
}

void MeteorologySystem::generateThunder() {

	auto& rand = sdlutils().rand();

	auto i = rand.nextInt(0, tileSize_.getX() / 2 - 1);
	auto j = rand.nextInt(0, tileSize_.getY() - 1);

	auto position = net->getCell(i, j)->position;
	auto x = position.getX();
	auto y = position.getY();

	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.animSpeed = 4;
	m.anim_create.idGrp = _grp_NATURALS_EFFECTS;
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

	//generateCloud();
}

void MeteorologySystem::generateAnimTornado() {
	auto ruta = &sdlutils().rutes().at("tornado");
	auto rutaPantalla = RouteTranslate(ruta->points);
	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.animSpeed = 4;
	m.anim_create.idGrp = _grp_NATURALS_EFFECTS;
	m.anim_create.iterationsToDelete = 47;
	m.anim_create.scale = { 200, 300 };
	m.anim_create.cols = 24;
	m.anim_create.rows = 6;
	m.anim_create.tex = gameTextures::tornado;
	m.anim_create.frameInit = 60;
	m.anim_create.frameEnd = 64;
	m.anim_create.height = 32;
	m.anim_create.width = 32;
	m.anim_create.route = rutaPantalla;
	m.anim_create.pos = rutaPantalla[0];
	mngr_->send(m);
	objectsSpawned_++;
}
std::vector<Vector2D> MeteorologySystem::RouteTranslate(std::vector<Vector2D> route) {
	std::vector<Vector2D> route_aux = route;
	for (int i = 0; i < route.size(); i++) {
		route_aux[i] = net->getCell(route[i].getX(), route[i].getY())->position;
	}
	return route_aux;
}
void MeteorologySystem::generateTsunami() {
	for (size_t n = 0; n < tileSize_.getX() / 2 - 1; n++) {
		auto i = n;
		auto j = tileSize_.getY() - 2;

		vector<Vector2D> ruta;
		ruta.push_back(Vector2D(i, j));
		ruta.push_back(Vector2D(i, 1));
		auto rutaPantalla = RouteTranslate(ruta);
		Message m;
		m.id = _m_ANIM_CREATE;
		m.anim_create.animSpeed = 9;
		m.anim_create.idGrp = _grp_NATURALS_EFFECTS;
		m.anim_create.iterationsToDelete = 1;
		m.anim_create.scale = { 200, 200 };
		m.anim_create.cols = 4;
		m.anim_create.rows = 5;
		m.anim_create.tex = gameTextures::tsunami;
		m.anim_create.frameInit = 0;
		m.anim_create.frameEnd = 18;
		m.anim_create.height = 96;
		m.anim_create.width = 96;
		m.anim_create.route = rutaPantalla;
		m.anim_create.pos = rutaPantalla[0];
		mngr_->send(m);
	}
	objectsSpawned_++;
	
}

void MeteorologySystem::update() {

	if (mActive) {

		if (!eventActive_) { elapsedTime_ += game().getDeltaTime(); }

		if (elapsedTime_ > timeToNextEvent_ && !eventActive_) {//comienza el evento

			eventActive_ = true;

			switch (nextEvent_)
			{
			case MeteorologySystem::TSUNAMI:
				generateNetMap();
				break;
			case MeteorologySystem::STORM:
				generateNetMap();
				generateStorm(50);
				break;
			case MeteorologySystem::METEORITES:
				generateNetMap();
				generateMeteorites(50);
				break;
			case MeteorologySystem::TORNADO:
				generateNetMap();
				break;
			case MeteorologySystem::EARTHQUAKE:
				generateNetMap();
				quantity_ = 50;
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
				quantity_ = 1;
				if (objectsSpawned_ < quantity_) {
					generateTsunami();
				}
				
				break;
			case MeteorologySystem::STORM:
				if (elapsedSpawn_ > thundersInterval_ && objectsSpawned_ < quantity_) {
					objectsSpawned_++;
					generateThunder();
					elapsedSpawn_ = 0;
				}
				else if (objectsSpawned_ >= quantity_) { eventOver = true; }
				break;
			case MeteorologySystem::METEORITES:
				if (elapsedSpawn_ > meteoriteInterval_ && objectsSpawned_ < quantity_) {
					objectsSpawned_++;
					generateMeteorite();
					elapsedSpawn_ = 0;
				}
				else if (objectsSpawned_ >= quantity_) { eventOver = true; }
				break;
			case MeteorologySystem::TORNADO:
				quantity_ = 1;
				if (objectsSpawned_ < quantity_) {
					generateAnimTornado();
				}
				if (elapsedSpawn_ > 25.0) { eventOver = true; }
				break;
			case MeteorologySystem::EARTHQUAKE:

				if (elapsedSpawn_ > 0.3 && objectsSpawned_ < quantity_) {
					generateAnimEarthquake();
					objectsSpawned_++;
					elapsedSpawn_ = 0;
				}
				if (objectsSpawned_ >= quantity_) { 
					Message m;
					m.id = _m_RESET_SPEED;
					m.reset_speed.speed = 0.0;
					mngr_->send(m);
					eventOver = true; 
				}
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
}
