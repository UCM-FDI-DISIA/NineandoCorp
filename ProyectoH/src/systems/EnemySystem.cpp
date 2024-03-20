#include "EnemySystem.h"
#include "..//components/MovementComponent.h"
#include "..//components/RouteComponent.h"
#include "..//components/HealthComponent.h"
#include "..//components/MaestroAlmasComponent.h"
#include "..//components/GolemComponent.h"
#include "../ecs/Manager.h"

EnemySystem::EnemySystem() {

}
EnemySystem::~EnemySystem() {

}


void EnemySystem::initSystem() {
	active_ = true;

	addEnemy(_enm_ANGEL, { 700,500 });
}
void  EnemySystem::receive(const Message& m) {
	switch (m.id) {
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
				if (mngr_->hasComponent<AttackComponent>(m.entity_to_attack.src))mngr_->getComponent<AttackComponent>(m.entity_to_attack.src)->setTarget(nullptr);
			};
		}
		break;

	case _m_START_GAME:
		onRoundStart();
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
	}
}
void EnemySystem::onRoundStart() {
	const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);

	for (auto& t : enemies) {
		enemiesTransforms.push_back(mngr_->getComponent<Transform>(t));
	}
}

void EnemySystem::onRoundOver() {
	enemiesTransforms.clear();
}
void EnemySystem::update() {
	const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);
	const auto& towers = mngr_->getHandler(_hdlr_LOW_TOWERS);
	for (auto& e : enemies) {
		//std::cout << enemies.size();
		RouteComponent* rc = mngr_->getComponent<RouteComponent>(e);
		MovementComponent* mc = mngr_->getComponent<MovementComponent>(e);
		AttackComponent* ac = mngr_->getComponent<AttackComponent>(e);
		MaestroAlmasComponent* ma = mngr_->getComponent<MaestroAlmasComponent>(e);
		GolemComponent* gc= mngr_->getComponent<GolemComponent>(e);
		bool para = false;

		if (gc != nullptr) {
			gc->setTime(game().getDeltaTime()+gc->getElapsed());
			if (gc->getElapsed() >= gc->getReload()) {
				gc->Regenera();
				gc->setTime(0.0f);
			}
		}

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
					if (ma != nullptr) {
						ma->CiegaTorre(ac->getTarget());
						ac->setElapsedTime(0.0f);
						ac->setLoaded(false);
					}
					else {
						std::cout << "atacando";
						ac->doDamageTo(ac->getTarget(), ac->getDamage());
						ac->setElapsedTime(0.0f);
						ac->setLoaded(false);
					}
				}
				else{
					mc->setStop(false);
					
					}
				}
			}
		}
	
	}
void EnemySystem::addEnemy(enmId type, Vector2D pos) {
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);

	Transform* tr = mngr_->addComponent<Transform>(t);//transform
	tr->setPosition(pos);

	MovementComponent* mc = mngr_->addComponent<MovementComponent>(t);

	std::vector<Vector2D> route;
	route.push_back({ (float)sdlutils().width() / 2.f, 300.f });
	route.push_back({ (float)sdlutils().width() / 2.f, 600.f });
	route.push_back({ 300, 600.f });

	switch (type) {
	case _enm_MALMAS:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_AELECTRICO:
		tr->setSpeed(70.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_MALDITO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_GOLEM:
		tr->setSpeed(20.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_DALADO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_GOBLIN:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_ELFO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_MMUERTE:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_ANGEL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<GolemComponent>(t);
		mngr_->addComponent<AttackComponent>(t, 100, 2, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_DINFERNAL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_DREAL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_CMALDITO:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_PRINCIPITO:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_MONJE:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_MUERTE:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
			

	}
	mngr_->setHandler(_hdlr_ENEMIES, t);

			
}
