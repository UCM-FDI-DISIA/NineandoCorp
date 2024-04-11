#include "EnemySystem.h"
#include "..//components/MovementComponent.h"
#include "..//components/RouteComponent.h"
#include "..//components/HealthComponent.h"
#include "..//components/generateEnemies.h"
#include "../ecs/Manager.h"
#include "..//components/AcechanteComponent.h"
#include "../components/MaestroAlmasComponent.h"
#include "../components/AngelComponent.h"
#include "../components/IconComponent.h"
#include "../components/GolemComponent.h"
#include "../components/LimitedTime.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/EnemyBookSystem.h"


EnemySystem::EnemySystem() {
	mActive = true;
}
EnemySystem::~EnemySystem() {

}


void EnemySystem::initSystem() {


}
void  EnemySystem::receive(const Message& m) {
	switch (m.id) {
	case _m_START_GAME:
		netmap = m.start_game_data.netmap;
		level = m.start_game_data.level;
		numSpawns = sdlutils().numSpawns().at("nivel" + to_string(level));
		onRoundStart(numSpawns, level);
		break;
	case _m_WAVE_START:
		generateEnemies_ = m.start_wave.play;
		if (generateEnemies_) {
			onWaveStart();
			wave++;
			stopGenerate = false;
		}
		
		break;
	case _m_PAUSE:
		mActive = !mActive;
		break;
	case _m_RESET_SPEED:
		for (const auto& enemy : mngr_->getHandler(_hdlr_ENEMIES))
		{
			MovementComponent* mc = mngr_->getComponent<MovementComponent>(enemy);
			if (mc != nullptr) { mc->activateSlow(m.reset_speed.speed, false); }
		}
		break;
	case _m_ENTITY_TO_ATTACK:
		if (m.entity_to_attack.targetId == _hdlr_ENEMIES && m.entity_to_attack.e != nullptr && mngr_->isAlive(m.entity_to_attack.e)) {
			HealthComponent* h = mngr_->getComponent<HealthComponent>(m.entity_to_attack.e);
			if (h->subtractHealth(m.entity_to_attack.damage)) {
				enemyDeathAnim(*mngr_->getComponent<Transform>(m.entity_to_attack.e)->getPosition());
				mngr_->deleteHandler(_hdlr_ENEMIES, m.entity_to_attack.e);
				auto enemytype = mngr_->getComponent<EnemyTypeComponent>(m.entity_to_attack.e);
				if (enemytype->GetEnemyType() == _enm_DREAL) {
					addField(*(mngr_->getComponent<Transform>(m.entity_to_attack.e)->getPosition()));
				}
				else if (enemytype->GetEnemyType() == _enm_CMALDITO) {
					Entity* mal = m.entity_to_attack.e;
					RouteComponent* rc = mngr_->getComponent<RouteComponent>(mal);
					generateMalditos(*(mngr_->getComponent<Transform>(mal)->getPosition()), rc->getDestiny(), rc->getRoute());
				}
				AddMoney(enemytype->GetEnemyType());
				if (mngr_->hasComponent<AttackComponent>(m.entity_to_attack.src))mngr_->getComponent<AttackComponent>(m.entity_to_attack.src)->setTarget(nullptr);
			};
		}
		break;
	case _m_OVER_GAME:
		onRoundOver();
		break;
	case _m_DECREASE_SPEED:
		if (m.decrease_speed.e != nullptr) {
			MovementComponent* mc = mngr_->getComponent<MovementComponent>(m.decrease_speed.e);
			if (mc != nullptr) {
				mc->activateSlow(m.decrease_speed.slowPercentage, true);
			}
		}
		break;
	case _m_CHANGE_ROUTE:
		if (m.change_route.enemy != nullptr && mngr_->isAlive(m.change_route.enemy)) {
			auto& rand = sdlutils().rand();
			auto r = rand.nextInt(0, spawnsVector.size());//elige ruta random dependiendo del nivel
			RouteComponent* rc = mngr_->getComponent<RouteComponent>(m.change_route.enemy);
			Transform* t = mngr_->getComponent<Transform>(m.change_route.enemy);
			auto gen = mngr_->getComponent<generateEnemies>(spawnsVector[r]);
			auto route = gen->getRoute();
		    gen->RoutesCorrection(t, route, 1.5f, 1.5f);
			rc->changeRoute(route);
		}
		break;
	}
}

void EnemySystem::enemyDeathAnim(Vector2D pos) {
	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.idGrp = _grp_TOWERS_AND_ENEMIES;
	m.anim_create.animSpeed = 15;
	m.anim_create.iterationsToDelete = 1;
	m.anim_create.pos = pos;
	m.anim_create.frameInit = 0;
	m.anim_create.frameEnd = 64;
	m.anim_create.cols = 10;
	m.anim_create.rows = 7;
	m.anim_create.scale = { 100, 100 };
	m.anim_create.width = 100;
	m.anim_create.height = 100;
	m.anim_create.tex = gameTextures::enemyDeath;
	mngr_->send(m);
}

/// <summary>
/// Al comienzo del nivel creamos los spawns determinados por nivel
/// </summary>
/// <param name="n_grp">numero de spawn por nivel</param>
/// <param name="level">nivel actual</param>
void EnemySystem::onRoundStart( int n_grp, unsigned int level) {
	for (auto i = 0; i < n_grp; i++)
	{
		auto e = mngr_->addEntity(_grp_SPAWN);
		auto tr = mngr_->addComponent<generateEnemies>(e);
		std::string routeName = "ruta" + std::to_string(i + 1) + "Nivel" + std::to_string(level);
		auto route_e = &sdlutils().rutes().at(routeName);
		auto route = RouteTranslate(route_e->points);
		tr->setRoute(route);
		spawnsVector.push_back(e);
	}
}
/// <summary>
/// Al comienzo de cada oleada asigno a cada spawn el grupo de enemigos que tien que generar
/// </summary>
void EnemySystem::onWaveStart() {
	for (auto i = 0; i < spawnsVector.size(); i++)
	{
		mngr_->getComponent<generateEnemies>(spawnsVector[i])->resetNumEnemies();
		mngr_->getComponent<generateEnemies>(spawnsVector[i])->setLevel(level);
		mngr_->getComponent<generateEnemies>(spawnsVector[i])->setWave(wave);
		mngr_->getComponent<generateEnemies>(spawnsVector[i])->setGrp(i + 1);
		mngr_->getComponent<generateEnemies>(spawnsVector[i])->addGroupEnemies();

	}
}
void EnemySystem::onRoundOver() {
	spawnsVector.clear();
}
/// <summary>
/// Transforma la ruta del json en las posiciones correspondientes
/// </summary>
/// <param name="route"></param>
/// <returns></returns>
std::vector<Vector2D> EnemySystem::RouteTranslate(std::vector<Vector2D> route) {
	std::vector<Vector2D> route_aux = route;
	for (int i = 0; i < route.size(); i++) {
		route_aux[i] = netmap->getCell(route[i].getX(), route[i].getY())->position;
	}
	return route_aux;
}

void EnemySystem::AddMoney(enmId type) {
	int money = 0;
	switch (type)
	{
	case _enm_MALMAS:
		money = 30;
		break;
	case _enm_AELECTRICO:
		money = 30;
		break;
	case _enm_MALDITO:
		money = 15;
		break;
	case _enm_GOLEM:
		money = 100;
		break;
	case _enm_DALADO:
		money = 5;
		break;
	case _enm_GOBLIN:
		money = 5;
		break;
	case _enm_ELFO:
		money = 15;
		break;
	case _enm_MMUERTE:
		money = 50;
		break;
	case _enm_ANGEL:
		money = 25;
		break;
	case _enm_DINFERNAL:
		money = 75;
		break;
	case _enm_DREAL:
		money = 30;
		break;
	case _enm_CMALDITO:
		money = 0;
		break;
	case _enm_PRINCIPITO:
		money = 0;
		break;
	case _enm_MONJE:
		money = 0;
		break;
	case _enm_MUERTE:
		money = 0;
		break;
	default:
		break;
	}
	Message m;
	m.id = _m_ADD_MONEY;
	m.money_data.money = money;
	mngr_->send(m);
}


void EnemySystem::update()
{
	if (mActive) {
		const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);
		const auto& towers = mngr_->getHandler(_hdlr_LOW_TOWERS);
		if (generateEnemies_) {
			if (enemies.empty() && stopGenerate) {
				if (wave > sdlutils().waves().at("nivel" + std::to_string(level))) {
					Message m;
					m.id = _m_ROUND_OVER;
					mngr_->send(m, true);
				}
				else {
					Message m;
					m.id = _m_WAVE_START;
					m.start_wave.play = false;
					mngr_->send(m, true);
				}
			}
			else {
				//Genero los enemigos segun el tiempo especificado en el json
				for (auto& s : spawnsVector) {
					auto spawn = mngr_->getComponent<generateEnemies>(s);
					if (spawn->totalEnemies()!= 0 && spawn->getElapsedTime() >= spawn->getSpawnGroup()->timeSpawn && spawn->getNumEnemies() < spawn->totalEnemies() ) {
						spawn->generateEnemy();
						spawn->next_Enemy();
						spawn->setElapsedTime(0.0);
					}
					else if (spawn->getNumEnemies() >= spawn->totalEnemies())
					{
						stopGenerate = true;
					}
					else {
						spawn->setElapsedTime(spawn->getElapsedTime() + game().getDeltaTime());
					}
				}
			}
			
		}
		for (auto& e : enemies) {
			//std::cout << enemies.size();
			RouteComponent* rc = mngr_->getComponent<RouteComponent>(e);
			MovementComponent* mc = mngr_->getComponent<MovementComponent>(e);
			AttackComponent* ac = mngr_->getComponent<AttackComponent>(e);
			bool para = false;

			MaestroAlmasComponent* ma = mngr_->getComponent<MaestroAlmasComponent>(e);
			GolemComponent* gc = mngr_->getComponent<GolemComponent>(e);
			AcechanteComponent* acc = mngr_->getComponent<AcechanteComponent>(e);
			IconComponent* ic = mngr_->getComponent<IconComponent>(e);
			AngelComponent* anc = mngr_->getComponent<AngelComponent>(e);
			DefensorRealComponent* drc = mngr_->getComponent<DefensorRealComponent>(e);
			EnemyTypeComponent* etc = mngr_->getComponent<EnemyTypeComponent>(e);
			Transform* tr = mngr_->getComponent<Transform>(e);
			FramedImage* fi = mngr_->getComponent<FramedImage>(e);

			if (ic != nullptr && ic->hasIcon()) {
				Transform* iconTr = mngr_->getComponent<Transform>(ic->getIcon());
				iconTr->setPosition(*(tr->getPosition()));
			}

			// golem
			if (gc != nullptr) {
				gc->setTime(game().getDeltaTime() + gc->getElapsed());
				if (gc->getElapsed() >= gc->getReload()) {
					gc->Regenera();
					gc->setTime(0.0f);
				}
			}

			// acechante
			if (acc != nullptr) {
				acc->setTime(game().getDeltaTime() + acc->getElapsed());
				if (acc->getElapsed() >= acc->getReload() - 0.5) {
					mc->setStop(true);
				}
				if (acc->getElapsed() >= acc->getReload()) {
					acc->inRange(enemies);
					acc->setTime(0.0f);
				}
			}

			// route
			if (rc != nullptr) {
				rc->checkdestiny();
				if (mc != nullptr && !mc->getStop()) {
					mc->Move();
				}

			}

			// attack
			if (ac != nullptr) {
				ac->setElapsedTime(ac->getElapsedTime() + game().getDeltaTime());
				if (ac->getElapsedTime() > ac->getReloadTime()) {
					ac->setLoaded(true);
					ac->targetEnemy(towers);

					if (ac->getTarget() != nullptr && (ac->getAttackTowers() || mngr_->getComponent<NexusComponent>(ac->getTarget()))) {
						mc->setStop(true);
						if (!ac->getAttack()) {
							ac->setAttack(true);
							changeAnimation(ac->getAttack(), e);
						}
						
						if (ma != nullptr) {
							ma->CiegaTorre(ac->getTarget());
							ac->setElapsedTime(0.0f);
							ac->setLoaded(false);
						}
						else {
							//std::cout << "atacando";
							ac->doDamageTo(ac->getTarget(), ac->getDamage(), _hdlr_LOW_TOWERS);
							ac->setElapsedTime(0.0f);
							ac->setLoaded(false);
						}
					}
					else {
						mc->setStop(false);
						if (ac->getAttack()) {
							ac->setAttack(false);
							changeAnimation(ac->getAttack(), e);
						}
						
					}
				}
			}

			// angel
			if (anc != nullptr) {
				anc->setElapsed(anc->getElapsed() + game().getDeltaTime());
				if (anc->getElapsed() > 1.0f) {
					for (const auto& enemy : enemies) {
						IconComponent* icOther = mngr_->getComponent<IconComponent>(enemy);
						if (anc->getDistance(mngr_->getComponent<Transform>(enemy)->getPosition()) < anc->getRange() && enemy != e) {
							if (icOther == nullptr)	icOther = mngr_->addComponent<IconComponent>(enemy, _HEALED);//Agregarselo si no lo tiene
							if (icOther->getIconType() == _HEALED) {
								if (!icOther->hasIcon()) {//Crearlo si no lo tiene
									Entity* icon = mngr_->addEntity(_grp_ICONS);
									mngr_->addComponent<RenderComponent>(icon, hpIcon);
									Transform* tr = mngr_->addComponent<Transform>(icon);
									Transform* targetTR = mngr_->getComponent<Transform>(enemy);
									tr->setPosition(*(targetTR->getPosition()));
									tr->setScale(*(targetTR->getScale()) / 4);

									icOther->setHasIcon(true);
									icOther->setIcon(icon);
								}
							}
							mngr_->getComponent<HealthComponent>(enemy)->addHealth(mngr_->getComponent<HealthComponent>(enemy)->getBaseHealth() / 100.0f);
							anc->setElapsed(0);
						}
						else {
							if (icOther != nullptr && icOther->hasIcon() && icOther->getIconType() == _ANGEL) {//Eliminarlo si no se encuentra en la distancia
								icOther->setHasIcon(false);
								mngr_->setAlive(icOther->getIcon(), false);
							}
						}
					}
				}
			}

		}
	}
}
			
void EnemySystem::addField(Vector2D pos) {
	Entity* field = mngr_->addEntity(_grp_AREAOFATTACK);
	Transform* fieldTR = mngr_->addComponent<Transform>(field);
	mngr_->addComponent<RenderComponent>(field, shield);
	mngr_->addComponent<FramedImage>(field, 7, 1, 626, 352, 0, 5, 6);
	mngr_->addComponent<LimitedTime>(field, 5);
	fieldTR->setScale({ 640, 330 });
	fieldTR->setPosition(pos + Vector2D(-240, -20));
	SDL_Rect fieldRect = fieldTR->getRect();
	Message m;
	m.id = _m_ADD_RECT;
	m.rect_data.id = _FIELD;
	m.rect_data.entity = field;
	mngr_->send(m);
}

void EnemySystem::changeAnimation(bool isAttacking, Entity* e) {
	FramedImage* fi = mngr_->getComponent<FramedImage>(e);
	enmId enemy_type = mngr_->getComponent<EnemyTypeComponent>(e)->GetEnemyType();
	RenderComponent* rc = mngr_->getComponent<RenderComponent>(e);
	switch (enemy_type)
	{
	case _enm_MALMAS:
		if (isAttacking) {
			rc->setTexture(gameTextures::maestro_attack);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		else
		{
			rc->setTexture(gameTextures::maestro);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		break;
	case _enm_AELECTRICO:
		if (isAttacking) {

		}
		else
		{

		}
		break;
	case _enm_MALDITO:
		if (isAttacking) {

		}
		else
		{

		}
		break;
	case _enm_GOLEM:
		if (isAttacking) {

		}
		else
		{

		}
		break;
	case _enm_DALADO:
		if (isAttacking) {
			rc->setTexture(gameTextures::demonioAlado_attack);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		else
		{
			rc->setTexture(gameTextures::demonioAlado);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		break;
	case _enm_GOBLIN:
		if (isAttacking) {

		}
		else
		{

		}
		break;
	case _enm_ELFO:
		if (isAttacking) {
			rc->setTexture(gameTextures::elfo_attack);
			fi->setFrames(6, 1, 0, 8, 5);
		}
		else
		{
			rc->setTexture(gameTextures::elfo);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		break;
	case _enm_MMUERTE:
		if (isAttacking) {

		}
		else
		{

		}
		break;
	case _enm_ANGEL:
		if (isAttacking) {

		}
		else
		{

		}
		break;
	case _enm_DINFERNAL:
		if (isAttacking) {

		}
		else
		{

		}
		break;
	case _enm_DREAL:
		if (isAttacking) {
			rc->setTexture(gameTextures::defensor_attack);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		else
		{
			rc->setTexture(gameTextures::defensor);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		break;
	case _enm_CMALDITO:
		if (isAttacking) {

		}
		else
		{

		}
		break;
	case _enm_PRINCIPITO:
		if (isAttacking) {
			rc->setTexture(gameTextures::principito_attack);
			fi->setFrames(10, 1, 0, 8, 9);
		}
		else
		{
			rc->setTexture(gameTextures::principito);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		break;
	case _enm_MONJE:
		if (isAttacking) {

		}
		else
		{

		}
		break;
	case _enm_MUERTE:
		if (isAttacking) {
			rc->setTexture(gameTextures::muerte_attack);
			fi->setFrames(6, 1, 0, 8, 5);
		}
		else
		{
			rc->setTexture(gameTextures::muerte);
			fi->setFrames(1, 1, 0, 0, 1);
		}
		break;
	default:
		break;
	}
}
	
void EnemySystem::generateMalditos(Vector2D pos, int destiny, vector<Vector2D> route) {
	auto& random = sdlutils().rand();
	for (int i = 0; i < 10; i++) {
		int x = random.nextInt(-10, 11);
		int y = random.nextInt(-10, 11);

		Vector2D malditoPos = pos + Vector2D(x, y);

		Entity* maldito = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
		Transform* tr = mngr_->addComponent<Transform>(maldito);//transform
		MovementComponent* mc = mngr_->addComponent<MovementComponent>(maldito);

		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(maldito, gameTextures::maldito);
		mngr_->addComponent<HealthComponent>(maldito, 60);
		Vector2D v = { tr->getWidth() / 1.0f, tr->getHeight() / 3.0f };
		for (auto& e : route) {
			e = e - v;
		}

		RouteComponent* rc = mngr_->addComponent<RouteComponent>(maldito, route);
		rc->setDestiny(destiny);
		tr->setPosition(malditoPos);
		mngr_->addComponent<AttackComponent>(maldito, 10, 1, 20, false);
		mngr_->addComponent<FramedImage>(maldito, 8, 1, 64, 64, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(maldito, _enm_MALDITO);

		mngr_->setHandler(_hdlr_ENEMIES, maldito);
	}
	
}