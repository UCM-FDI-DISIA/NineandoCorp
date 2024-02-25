#include "TowerSystem.h"


TowerSystem::TowerSystem() :timer_(), active_(true) {
}

TowerSystem::~TowerSystem() {
	towers.clear();
	//enemies.clear();
}

void TowerSystem::initSystem() {
	active_ = true;
}

void TowerSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	}
}


void TowerSystem::update() {
	const auto& bullets = mngr_->getEntities(_grp_BULLETS);
	

	for (auto& t : towers) {
		if(!mngr_->isAlive(t)){ eliminateDestroyedTowers(t); }//Eliminamos la torre de los arrays si esta muerta
		else {
			AttackComponent* ac = mngr_->getComponent<AttackComponent>(t);
			if (ac != nullptr) {
				ac->setElapsedTime(timer_.currTime() / 1000);
				if (ac->getElapsedTime() > ac->getTimeToShoot()) {
					ac->setLoaded(true);
					ac->targetEnemy(mngr_->getHandler(_hdlr_ENEMIES));
					//std::cout << "Elapsed: " << timer_.currTime() << "\n";
					//std::cout << "TTS: " << ac->getTimeToShoot() << "\n";
					if (ac->getTarget() != nullptr) {
						shootBullet(ac->getTarget(), ac->getDamage());
						ac->setTimeToShoot(ac->getTimeToShoot() + ac->getReloadTime());
						ac->setLoaded(false);
					}
				}
			}
			BulletTower* bt = mngr_->getComponent<BulletTower>(t);
			if (bt != nullptr && bt->isMaxLevel()) {
				bt->setElapsedTime(timer_.currTime() / 1000);
				if (bt->getElapsedTime() > bt->getTimeToShoot()) {
					bt->targetSecondEnemy(mngr_->getHandler(_hdlr_ENEMIES));
					if (bt->getTarget() != nullptr) { shootBullet(bt->getTarget(), bt->getDamage()); }
				}
			}
			EnhancerTower* et = mngr_->getComponent<EnhancerTower>(t);
			if (et != nullptr) {
				for (size_t i = 0; i < towers.size(); i++)
				{
					if (true) {//enRango
						AttackComponent* ac = mngr_->getComponent<AttackComponent>(towers[i]);
						if (ac != nullptr) {ac->setDamage(ac->getBaseDamage() * (1 + et->getDamageIncreasePercentage()));}
						HealthComponent* h = mngr_->getComponent<HealthComponent>(towers[i]);
						if (h != nullptr) { h->setMaxHealth(h->getBaseHealth() + et->getTowersHPboost()); }
					}
				}
			}

		}	
	}

	for (auto& b : bullets) {
		Transform* t = mngr_->getComponent<Transform>(b);
		BulletComponent* bc = mngr_->getComponent<BulletComponent>(b);

		t->translate();
		if (!mngr_->isAlive(bc->getTarget())) {//Si ha muerto por el camino
			bc->onTravelEnds();
		}
		else{ //Si choca con el enemigo
			if (((*(t->getPosition()) - *(mngr_->getComponent<Transform>(bc->getTarget())->getPosition())).magnitude() <= 5.0f)) {
				bc->doDamageTo(mngr_->getComponent<HealthComponent>(bc->getTarget()));
				bc->onTravelEnds();
			}
		}
	}
}

void TowerSystem::eliminateDestroyedTowers(Entity* t) {
	bool found = false;
	int i = 0;
	/*while (i < lowTowers.size() && !found) {
		if (t == lowTowers[i]) {
			found = true;
			lowTowers[i] = lowTowers[lowTowers.size()];
			lowTowers.pop_back();
		}
		i++;
	}
	found = false;
	i = 0;*/
	while (i < towers.size() && !found) {
		if (t == towers[i]) {
			found = true;
			towers[i] = towers[towers.size()];
			towers.pop_back();
		}
		i++;
	}
}

void TowerSystem::shootBullet(Entity* target, float damage) {
	Entity* bullet = mngr_->addEntity(_grp_BULLETS);
	Transform* t = mngr_->addComponent<Transform>(bullet);
	mngr_->addComponent<BulletComponent>(bullet, t, target, damage);
	mngr_->addComponent<RenderComponent>(bullet, square);
}

void TowerSystem::addTower(TowerType type, Vector2D pos, Height height) {
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	mngr_->addComponent<Transform>(t)->setPosition(pos);
	mngr_->addComponent<RenderComponent>(t, towerTexture);
	float health = 100.0f;
	if (height == LOW) { 
		mngr_->addComponent<HealthComponent>(t, health); 
		//lowTowers.push_back(t);
		mngr_->setHandler(_hdlr_LOW_TOWERS, t);
	}
	switch (type)
	{
	case FENIX:
		break;
	case BULLET:
		break;
	case WALL:
		break;
	case ENHANCER://Pasar rango, porcentaje incremento de ataque y vida extra
		break;
	case DIEGO:
		break;
	case SLIME:
		break;
	case SHIELD:
		break;
	default:
		break;
	}
	towers.push_back(t);
}

void TowerSystem::onRoundStart() {
	
}

void TowerSystem::onRoundOver() {
	
}