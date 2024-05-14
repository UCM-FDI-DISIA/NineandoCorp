#include "MeteorologySystem.h"

#include "../ecs/Manager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/RenderComponent.h"
#include "../game/Game.h"



MeteorologySystem::MeteorologySystem():
thundersInterval_(0.1),
meteoriteInterval_(0.2),
elapsedSpawn_(0),
quantity_(0),
eventActive_(false),
objectsSpawned_(0),
currentWaves_(0),
wavesToNextevent_(0)
{
	mActive = true;
	imgEvent_ = nullptr;
}

MeteorologySystem::~MeteorologySystem() {

}

void MeteorologySystem::setIcon() {
	gameTextures tex = gameTextures::tsunami_icon;
	switch (nextEvent_)
	{
	case MeteorologySystem::TSUNAMI:
		break;
	case MeteorologySystem::STORM:
		tex = gameTextures::thunder_icon;
		break;
	case MeteorologySystem::METEORITES:
		tex = gameTextures::meteorite_icon;
		break;
	case MeteorologySystem::TORNADO:
		tex = gameTextures::tornado_icon;
		break;
	case MeteorologySystem::EARTHQUAKE:
		tex = gameTextures::earthquake_icon;
		break;
	default:
		break;
	}
	imgEvent_ = mngr_->addEntity(_grp_HUD_BACKGROUND);
	mngr_->addComponent<RenderComponent>(imgEvent_, tex);
	auto t = mngr_->addComponent<Transform>(imgEvent_);
	t->setPosition(Vector2D(0.0, 40.0));
	t->setScale(Vector2D(70.0, 70.0));
}


void MeteorologySystem::initSystem() {//Primer fenomeno
	auto& rand = sdlutils().rand();
	setNextEvent(rand.nextInt(4, 5),(MeteorologyEvent)rand.nextInt(0, 5));
	showWarningMessage();
}

void MeteorologySystem::showWarningMessage() {
	int waves = (int)(wavesToNextevent_ - currentWaves_);
	Message m;
	m.id = _m_ADD_TEXT;
	m.add_text_data.txt = "WARNING " + to_string(waves) + " WAVES";
	m.add_text_data.color = { 255, 255 ,255, 255 };
	Vector2D txtScale = Vector2D(550.0f, 60.0f);
	m.add_text_data.pos = Vector2D(600.0, 100.0) - (txtScale / 2);
	m.add_text_data.scale = txtScale;
	m.add_text_data.time = 3;
	mngr_->send(m);
	gameTextures tex = gameTextures::tsunami_icon;
	switch (nextEvent_)
	{
	case MeteorologySystem::TSUNAMI:
		break;
	case MeteorologySystem::STORM:
		tex = gameTextures::thunder_icon;
		break;
	case MeteorologySystem::METEORITES:
		tex = gameTextures::meteorite_icon;
		break;
	case MeteorologySystem::TORNADO:
		tex = gameTextures::tornado_icon;
		break;
	case MeteorologySystem::EARTHQUAKE:
		tex = gameTextures::earthquake_icon;
		break;
	default:
		break;
	}
	Message m1;
	m1.id = _m_ANIM_CREATE;
	m1.anim_create.animSpeed = 5;
	m1.anim_create.cols = 1;
	m1.anim_create.rows = 1;
	m1.anim_create.frameInit = 0;
	m1.anim_create.frameEnd = 1;
	m1.anim_create.scale = Vector2D(200, 200);
	m1.anim_create.iterationsToDelete = 8;
	m1.anim_create.tex = tex;
	m1.anim_create.width = 256;
	m1.anim_create.height = 256;
	m1.anim_create.idGrp = _grp_HUD_BACKGROUND;
	m1.anim_create.pos = Vector2D(600, 200) - (m1.anim_create.scale / 2);
	mngr_->send(m1);
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
			mActive = !m.start_pause.onPause;
			break;
		default:
			break;
		}
		break;
	case _m_WAVE_START:
		if (m.start_wave.play) {
			currentWaves_++;
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
	
	auto& rand = sdlutils().rand();
	auto x = (float)rand.nextInt(400, 700);
	auto y = (float)rand.nextInt(300, 700);
	auto r = rand.nextInt(1, 6);
	auto ruta = &sdlutils().rutes().at("nube" + to_string(r));
	auto rutaPantalla = RouteTranslate(ruta->points);


	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.animSpeed = 1;
	m.anim_create.idGrp = _grp_AREAOFATTACK;
	m.anim_create.iterationsToDelete = 1;
	m.anim_create.scale = { x, y};
	m.anim_create.cols = 1;
	m.anim_create.rows = 1;
	m.anim_create.tex = gameTextures::cloud;
	m.anim_create.frameInit = 0;
	m.anim_create.frameEnd = 1;
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
		m.anim_create.idGrp = _grp_NATURALS_EFFECTS_LOW;
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
	m.anim_create.animSpeed = 4;
	m.anim_create.idGrp = _grp_NATURALS_EFFECTS_HIGH;
	m.anim_create.iterationsToDelete = 1;
	m.anim_create.scale = { 150, 400 };
	m.anim_create.cols = 1;
	m.anim_create.rows = 11;
	m.anim_create.tex = gameTextures::meteorites;
	m.anim_create.frameInit = 0;
	m.anim_create.frameEnd = 18;
	m.anim_create.height = 256;
	m.anim_create.width = 96;
	m.anim_create.pos = Vector2D(x,y);
	mngr_->send(m);
}

void MeteorologySystem::generateStorm(int num) {
	for (size_t i = 0; i < 10; i++)
	{
		generateCloud();
	}
	
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
	m.anim_create.idGrp = _grp_NATURALS_EFFECTS_HIGH;
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

void MeteorologySystem::generateAnimTornado() {
	auto ruta = &sdlutils().rutes().at("tornado");
	auto rutaPantalla = RouteTranslate(ruta->points);
	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.animSpeed = 4;
	m.anim_create.idGrp = _grp_NATURALS_EFFECTS_HIGH;
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
		m.anim_create.animSpeed = 3;
		m.anim_create.idGrp = _grp_NATURALS_EFFECTS_LOW;
		m.anim_create.iterationsToDelete = 1;
		m.anim_create.scale = { 200, 200 };
		m.anim_create.cols = 1;
		m.anim_create.rows = 5;
		m.anim_create.tex = gameTextures::tsunami;
		m.anim_create.frameInit = 0;
		m.anim_create.frameEnd = 4;
		m.anim_create.height = 600;
		m.anim_create.width = 660;
		m.anim_create.route = rutaPantalla;
		m.anim_create.pos = rutaPantalla[0];
		mngr_->send(m);
	}
	objectsSpawned_++;
	
}

void MeteorologySystem::setNextEvent(int waves, MeteorologyEvent event) {//metodo para setear cuando quieres un evento
	wavesToNextevent_ = waves;
	nextEvent_ = event;
	setIcon();
}

void MeteorologySystem::update() {

	sdlutils().soundEffects().at("Tsunami").setChannelVolume(game().CalculoVolumenEfectos(), 5);

	if (mActive) {

		if (!eventActive_) {//Tiempo para el siguiente evento
			int waves = (int)(wavesToNextevent_ - currentWaves_);
			Message m;
			m.id = _m_ADD_TEXT;
			m.add_text_data.txt = "WAVES:  " + to_string(waves);
			m.add_text_data.color = { 255, 255 ,255, 255 };
			Vector2D txtScale = Vector2D(80.0f, 20.0f);
			m.add_text_data.pos = Vector2D(110.0, 80.0) - (txtScale / 2);
			m.add_text_data.scale = txtScale;
			m.add_text_data.time = 0.01;
			mngr_->send(m);
		}

		if (currentWaves_ >= wavesToNextevent_ && !eventActive_) {//comienza el evento

			eventActive_ = true;

			switch (nextEvent_)
			{
			case MeteorologySystem::TSUNAMI:
				sdlutils().soundEffects().at("Tsunami").play(0, 5);
				generateNetMap();
				break;
			case MeteorologySystem::STORM:
				sdlutils().soundEffects().at("Rayo").play(0, 5);
				generateNetMap();
				generateStorm(250);
				break;
			case MeteorologySystem::METEORITES:
				sdlutils().soundEffects().at("Meteorito").play(0, 5);
				generateNetMap();
				generateMeteorites(125);
				break;
			case MeteorologySystem::TORNADO:
				sdlutils().soundEffects().at("Tornado").play(0, 5);
				generateNetMap();
				break;
			case MeteorologySystem::EARTHQUAKE:
				sdlutils().soundEffects().at("Terremoto").play(0, 5);
				generateNetMap();
				quantity_ = 50;
				break;
			default:
				break;
			}
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
				currentWaves_ = 0;
				objectsSpawned_ = 0;
				elapsedSpawn_ = 0;
				quantity_ = 0;
				if (imgEvent_ != nullptr && mngr_->isAlive(imgEvent_)) { mngr_->setAlive(imgEvent_, false); }
				auto& rand = sdlutils().rand();
				setNextEvent(wavesToNextEvent_, (MeteorologyEvent)rand.nextInt(0, 5));
				showWarningMessage();
				sdlutils().soundEffects().at("Tsunami").haltChannel(5);
			}
		}
	}
}
