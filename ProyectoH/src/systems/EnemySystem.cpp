#include "EnemySystem.h"
#include "..//components/MovementComponent.h"
#include "..//components/MonjeComponent.h"
#include "..//components/RouteComponent.h"
#include "..//components/HealthComponent.h"
#include "..//components/generateEnemies.h"
#include "../ecs/Manager.h"
#include "..//components/AcechanteComponent.h"
#include "../components/MaestroAlmasComponent.h"
#include "../components/MensajeroMuerteComponent.h"
#include "../components/PrincipitoComponent.h"
#include "../components/CaballeroMalditoComponent.h"
#include "../components/AngelComponent.h"
#include "../components/IconComponent.h"
#include "../components/GolemComponent.h"
#include "../components/LimitedTime.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/EnemyBookSystem.h"


EnemySystem::EnemySystem() :mActive(true), generateEnemies_(false), stopGenerate(false), wave(1), level(1) {

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
		mActive = !m.start_pause.onPause;
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
			auto mj = mngr_->getComponent<MonjeComponent>(m.entity_to_attack.e);
			if (mj != nullptr && mj->getDevuelve()) {
				Message a;
				a.id = _m_ENTITY_TO_ATTACK;
				a.entity_to_attack.e = m.entity_to_attack.src;
				a.entity_to_attack.damage = m.entity_to_attack.damage;
				a.entity_to_attack.targetId = m.entity_to_attack.srcId;
				a.entity_to_attack.src = m.entity_to_attack.e;
				a.entity_to_attack.srcId = _hdlr_ENEMIES;
				mngr_->send(a);
			}
			else {
				HealthComponent* h = mngr_->getComponent<HealthComponent>(m.entity_to_attack.e);
				if (h->getHealth() - m.entity_to_attack.damage <= 0) {
					auto enemytype = mngr_->getComponent<EnemyTypeComponent>(m.entity_to_attack.e);
					Message m1;
					m1.id = _m_ENEMY_DIED;
					m1.return_entity.ent = m.entity_to_attack.e;
					mngr_->send(m1);
				}
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
						mngr_->getComponent<CaballeroMalditoComponent>(mal)->generateMalditos(*(mngr_->getComponent<Transform>(mal)->getPosition()), rc->getDestiny(), rc->getRoute());
					}
					AddMoney(enemytype->GetEnemyType(), level);
					if (mngr_->hasComponent<AttackComponent>(m.entity_to_attack.src))mngr_->getComponent<AttackComponent>(m.entity_to_attack.src)->setTarget(nullptr);

				};
			}
		}
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

void EnemySystem::AddMoney(enmId type, int level) {
	int money = 0;
	int Hmoney = 0;
	switch (type)
	{
	case _enm_MALMAS:
		money = sdlutils().intConst().at("MALMASmoney");
		break;
	case _enm_AELECTRICO:
		money = sdlutils().intConst().at("AELECTRICOmoney");
		break;
	case _enm_DREAL:
		money = sdlutils().intConst().at("DREALmoney");
		break;
	case _enm_ELFO:
		money = sdlutils().intConst().at("ELFOmoney");
		break;
	case _enm_MALDITO:
		money = sdlutils().intConst().at("MALDITOmoney");
		break;
	case _enm_GOLEM:
		money = sdlutils().intConst().at("GOLEMmoney");
		break;
	case _enm_DALADO:
		money = sdlutils().intConst().at("DALADOmoney");
		break;
	case _enm_GOBLIN:
		money = sdlutils().intConst().at("GOBLINmoney");
		break;
	case _enm_MMUERTE:
		money = sdlutils().intConst().at("MMUERTEmoney");
		break;
	case _enm_ANGEL:
		money = sdlutils().intConst().at("ANGELmoney");
		break;
	case _enm_DINFERNAL:
		money = sdlutils().intConst().at("DINFERNALmoney");
		break;
	case _enm_CMALDITO:
		money = sdlutils().intConst().at("CMALDITOmoney");
		break;
	case _enm_PRINCIPITO:
		money = sdlutils().intConst().at("PRINCIPITOmoney");
		break;
	case _enm_MONJE:
		money = sdlutils().intConst().at("MONJEmoney");
		break;
	case _enm_MUERTE:
		money = sdlutils().intConst().at("MUERTEmoney");
		break;
	default:
		break;
	}

	switch (level)
	{
	case 1:
	case 2:
		Hmoney = sdlutils().intConst().at("Hmoney1");
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		Hmoney = sdlutils().intConst().at("Hmoney2");
		break;
	case 7:
	case 8:
		Hmoney = sdlutils().intConst().at("Hmoney3");
		break;
	default:
		break;
	}
	Message m1;
	m1.id = _m_ADD_MONEY;
	m1.money_data.money = money;
	mngr_->send(m1);
	Message m2;
	m2.id = _m_ADD_MONEY_H;
	m2.money_data.money = Hmoney;
	mngr_->send(m2);
}

void EnemySystem::update()
{
	if (mActive) {
		const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);
		const auto& genemies = mngr_->getHandler(_hdlr_GHOST_ENEMIES);
		const auto& towers = mngr_->getHandler(_hdlr_LOW_TOWERS);
		if (generateEnemies_) {
			if (enemies.empty() && stopGenerate && genemies.empty()) {
				if (wave > sdlutils().waves().at("nivel" + std::to_string(level))) {
					Message m;
					m.id = _m_ROUND_OVER;
					m.money_data.money = mngr_->getSystem<ButtonSystem>()->getHMoney();
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
						stopGenerate = false;
					}
					else if (spawn->totalEnemies() != 0 && spawn->getNumEnemies() >= spawn->totalEnemies())
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
			PrincipitoComponent* pc = mngr_->getComponent<PrincipitoComponent>(e);
			MensajeroMuerteComponent* mm = mngr_->getComponent<MensajeroMuerteComponent>(e);
			MonjeComponent* mj = mngr_->getComponent<MonjeComponent>(e);
			Transform* tr = mngr_->getComponent<Transform>(e);
			FramedImage* fi = mngr_->getComponent<FramedImage>(e);

			if (ic != nullptr) {
				for (int i = 0; i < ic->getIcons().size(); i++) {
					icon enemyIcon = ic->getIcons()[i];
					Transform* iconTr = mngr_->getComponent<Transform>(enemyIcon.ent_);
					iconTr->setPosition(*(tr->getPosition()) + Vector2D(intAt("IconOffset") * i, 0));
				}
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
					ac->targetFromGroup(towers);

					if (ac->getTarget() != nullptr && (ac->getAttackTowers() || mngr_->getComponent<NexusComponent>(ac->getTarget()) || mngr_->getComponent<DirtTower>(ac->getTarget()))) {
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
							if (pc != nullptr) {
								pc->setAttackSpeed();
								std::cout << ac->getReloadTime()<<"\n";
							}
						}
					}
					else {
						mc->setStop(false);

						if (pc != nullptr) {
							pc->ResetVelocity();
						}

						if (ac->getAttack()) {
							ac->setAttack(false);
							changeAnimation(ac->getAttack(), e);
						}
						

						if (mm != nullptr) {
							if (!mm->Detect(towers)) {
								std::cout << "invisible\n";
								mm->changeGroup(_hdlr_GHOST_ENEMIES);
							}
						}

					}
				}
			}

			// monje
			if (mj != nullptr) {
				mj->setElapsedTime(mj->getElapsedTime() + game().getDeltaTime());
				if (mj->getElapsedTime() >= mj->getReloadTime()) {
					mj->setDevuelve(true);
					std::cout << "devuelve\n";
					mj->setElapsedTime(0.0f);
				}
				if (mj->getDevuelve()) {
					mc->setStop(true);
					mj->setElapsedTime2(mj->getElapsedTime2() + game().getDeltaTime());
					if (mj->getElapsedTime2() >= mj->getUltiTime()) {
						mj->setDevuelve(false);
						std::cout << "no devuelve\n";
						mc->setStop(false);
						mj->setElapsedTime2(0.0f);
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
							if (!icOther->hasIcon(_HEALED)) {//Crearlo si no lo tiene
								icOther->addIcon(_HEALED);
							}
							
							mngr_->getComponent<HealthComponent>(enemy)->addHealth(mngr_->getComponent<HealthComponent>(enemy)->getBaseHealth() / 100.0f);
							anc->setElapsed(0);
						}
						else {
							if (icOther != nullptr && icOther->hasIcon(_HEALED)) {//Eliminarlo si no se encuentra en la distancia
								icOther->removeIcon(_HEALED);
							}
						}
					}
				}
			}

		}
		for (auto e : genemies) {
			RouteComponent* rc2 = mngr_->getComponent<RouteComponent>(e);
			MovementComponent* mc2 = mngr_->getComponent<MovementComponent>(e);
			AttackComponent* ac2 = mngr_->getComponent<AttackComponent>(e);
			bool para = false;
			IconComponent* ic2 = mngr_->getComponent<IconComponent>(e);
			MensajeroMuerteComponent* mm2 = mngr_->getComponent<MensajeroMuerteComponent>(e);
			Transform* tr2 = mngr_->getComponent<Transform>(e);

			if (ic2 != nullptr) {
				for (int i = 0; i < ic2->getIcons().size(); i++) {
					icon enemyIcon = ic2->getIcons()[i];
					Transform* iconTr = mngr_->getComponent<Transform>(enemyIcon.ent_);
					iconTr->setPosition(*(tr2->getPosition()) + Vector2D(intAt("IconOffset") * i,0));
				}		
			}

			// route
			if (rc2 != nullptr) {
				rc2->checkdestiny();
				if (mc2 != nullptr && !mc2->getStop()) {
					mc2->Move();
				}

			}

			//attack
			if (mm2 != nullptr) {
				
				if (mm2->Detect(towers)) {
					std::cout << "visible\n";
					mm2->changeGroup(_hdlr_ENEMIES);
				}
			
			}
		}
	}
}
			
void EnemySystem::addField(Vector2D pos) {
	Entity* field = mngr_->addEntity(_grp_AREAOFATTACK);
	Transform* fieldTR = mngr_->addComponent<Transform>(field);
	mngr_->addComponent<RenderComponent>(field, force_field);
	mngr_->addComponent<FramedImage>(field, 1, 1, 147, 130, 1, 1, 1);
	mngr_->addComponent<LimitedTime>(field, 5);
	fieldTR->setScale({ 300, 300 });
	fieldTR->setPosition(pos + Vector2D(-80, -80));
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
			rc->setTexture(gameTextures::acechante_attack);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		else
		{
			rc->setTexture(gameTextures::acechante);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		break;
	case _enm_MALDITO:
		if (isAttacking) {
			rc->setTexture(gameTextures::maldito_attack);
			fi->setFrames(7, 1, 0, 8, 6);
		}
		else
		{
			rc->setTexture(gameTextures::maldito);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		break;
	case _enm_GOLEM:
		if (isAttacking) {
			// este funciona distinto
			/*rc->setTexture(gameTextures::golem);
			fi->setFrames(8, 1, 0, 8, 7);*/
		}
		else
		{
			rc->setTexture(gameTextures::golem);
			fi->setFrames(10, 10, 40, 10, 46);
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
			rc->setTexture(gameTextures::goblin_attack);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		else
		{
			rc->setTexture(gameTextures::goblin);
			fi->setFrames(8, 1, 0, 8, 7);
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
			rc->setTexture(gameTextures::mensajero);
			fi->setFrames(8, 16, 16, 8, 23);
		}
		else
		{
			rc->setTexture(gameTextures::mensajero);
			fi->setFrames(8, 8, 8, 8, 15);
		}
		break;
	case _enm_ANGEL:
		if (isAttacking) {
			rc->setTexture(gameTextures::angel);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		else
		{
			rc->setTexture(gameTextures::angel);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		break;
	case _enm_DINFERNAL:
		if (isAttacking) {
			rc->setTexture(gameTextures::demonioInfernal);
			fi->setFrames(6, 2, 6, 8, 11);
		}
		else
		{
			rc->setTexture(gameTextures::demonioInfernal);
			fi->setFrames(8, 4, 16, 4, 19);
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
			rc->setTexture(gameTextures::maldito_attack);
			fi->setFrames(7, 1, 0, 8, 6);
		}
		else
		{
			rc->setTexture(gameTextures::maldito);
			fi->setFrames(8, 1, 0, 8, 7);
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
			rc->setTexture(gameTextures::monje_attack);
			fi->setFrames(8, 1, 0, 8, 7);
		}
		else
		{
			rc->setTexture(gameTextures::defensor_attack);
			fi->setFrames(8, 1, 0, 8, 7);
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
