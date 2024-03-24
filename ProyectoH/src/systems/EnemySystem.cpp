#include "EnemySystem.h"
#include "..//components/MovementComponent.h"
#include "..//components/RouteComponent.h"
#include "..//components/HealthComponent.h"
#include "..//components/generateEnemies.h"
#include "../ecs/Manager.h"

EnemySystem::EnemySystem() {

}
EnemySystem::~EnemySystem() {

}


void EnemySystem::initSystem() {
	active_ = true;
	


}
void  EnemySystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		netmap = m.start_game_data.netmap;
		level = m.start_game_data.level;
		numSpawns = sdlutils().numSpawns().at("nivel" + to_string(level));
		onRoundStart(numSpawns, level);
		onWaveStart(level);

		break;
	case _m_START_GAME:
		onWaveStart();
		
		
		
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		wave++;
		break;
	case _m_RESET_SPEED:
		for (const auto& enemy : mngr_->getHandler(_hdlr_ENEMIES))
		{
			MovementComponent* mc = mngr_->getComponent<MovementComponent>(enemy);
			if (mc != nullptr) { mc->activateSlow(m.reset_speed.speed, false); }
		}
		break;
	case _m_ENTITY_TO_ATTACK:
		if (m.entity_to_attack.e != nullptr && mngr_->isAlive(m.entity_to_attack.e)) {
			 HealthComponent* h = mngr_->getComponent<HealthComponent>(m.entity_to_attack.e);
			 if (h->subtractHealth(m.entity_to_attack.damage)) { 
				 mngr_->deleteHandler(_hdlr_ENEMIES, m.entity_to_attack.e); 
				 if(mngr_->hasComponent<AttackComponent>(m.entity_to_attack.src))mngr_->getComponent<AttackComponent>(m.entity_to_attack.src)->setTarget(nullptr);
			 };
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
	}
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
void EnemySystem::update() {
	//Genero los enemigos segun el tiempo especificado en el json
	for (auto& s : spawnsVector) {
		auto spawn = mngr_->getComponent<generateEnemies>(s);
		if (!spawn->getSpawnGroup()->typeEnemy.empty() && spawn->getElapsedTime() >= spawn->getSpawnGroup()->timeSpawn) {
			spawn->generateEnemy();
			spawn->next_Enemy();
			spawn->setElapsedTime(0.0);
		}
		else {
			spawn->setElapsedTime(spawn->getElapsedTime() + game().getDeltaTime());
		}
	}
	
	const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);
	const auto& towers = mngr_->getHandler(_hdlr_LOW_TOWERS);
	for (auto& e : enemies) {
		//std::cout << enemies.size();
		RouteComponent* rc = mngr_->getComponent<RouteComponent>(e);
		MovementComponent* mc = mngr_->getComponent<MovementComponent>(e);
		AttackComponent* ac = mngr_->getComponent<AttackComponent>(e);
		bool para = false;
		if (rc != nullptr) {
			rc->checkdestiny();
			if (mc != nullptr && !mc->getStop()) {
				mc->Move();
			}

		}
		if (ac != nullptr) {
			ac->setElapsedTime(ac->getElapsedTime() + game().getDeltaTime());
			if (ac->getElapsedTime() > ac->getReloadTime()) {
				ac->setLoaded(true);
				ac->targetEnemy(towers);
				
				if (ac->getTarget() != nullptr) {
					mc->setStop(true);
					
					std::cout << "atacando";
					ac->doDamageTo(ac->getTarget(), ac->getDamage());
					ac->setElapsedTime(0.0f);
					ac->setLoaded(false);
				}
				else{
					mc->setStop(false);
					
					}
				}
			}
		}
	}
