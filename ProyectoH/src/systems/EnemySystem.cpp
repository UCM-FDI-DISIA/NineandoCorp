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

	Entity* enemie = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	Transform* tr = mngr_->addComponent<Transform>(enemie);
	tr->setPosition({(float)sdlutils().width()/2.f - 100.f, 300.f});
	tr->setVelocity({ 0, 100 });
	mngr_->addComponent<MovementComponent>(enemie);
	std::vector<Vector2D> route;
	route.push_back({ 30, 27 });
	route.push_back({ 27, 24 });
	route.push_back({ 8, 24 });
	route.push_back({ 8, 15 });
	route.push_back({ 13, 15});
	mngr_->getComponent<generateEnemies>(spawnsVector[0])->addEnemy(_enm_ANGEL, route);

	mngr_->addComponent<RouteComponent>(enemie, route, netmap);
	mngr_->addComponent<AttackComponent>(enemie, 100, 0.25, 20, false);
	mngr_->addComponent<RenderComponent>(enemie, square);
	mngr_->addComponent<HealthComponent>(enemie, 50000);
	mngr_->addComponent<FramedImage>(enemie, 1, 1, 122, 117, 0, 0, 1);
	mngr_->setHandler(_hdlr_ENEMIES, enemie);
}
void  EnemySystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart(m.create_spawns_data.n_grp);
		break;
	case _m_ROUND_OVER:
		onRoundOver();
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
	case _m_NETMAP_SET:
		netmap = m.netmap_set.netmap;
		break;
	}
}
void EnemySystem::onRoundStart(unsigned int n_grp) {
	/*const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);

	for (auto& t : enemies) {
		enemiesTransforms.push_back(mngr_->getComponent<Transform>(t));
	}*/
	for (auto i = 0; i < n_grp; i++)
	{
		auto e = mngr_->addEntity(_grp_SPAWN);
		auto tr = mngr_->addComponent<generateEnemies>(e);
		spawnsVector.push_back(e);
	}
}
void EnemySystem::onWaveStart(unsigned int level, unsigned int wave) {
	for (auto i = 0; i < spawnsVector.size(); i++)
	{
		mngr_->getComponent<generateEnemies>(spawnsVector[i])->setLevel(level);
		mngr_->getComponent<generateEnemies>(spawnsVector[i])->setWave(wave);
		mngr_->getComponent<generateEnemies>(spawnsVector[i])->setGrp(i);
		mngr_->getComponent<generateEnemies>(spawnsVector[i])->addGroupEnemies();

	}
}
void EnemySystem::onRoundOver() {
	/*enemiesTransforms.clear();*/
}
void EnemySystem::update() {
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
