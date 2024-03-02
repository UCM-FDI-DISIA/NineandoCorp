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
	case _m_TOWER_TO_ATTACK:
		onAttackTower(m.tower_to_attack.e, m.tower_to_attack.damage);
	}
}


void TowerSystem::update() {
	const auto& bullets = mngr_->getEntities(_grp_BULLETS);
	
	
	for (auto& t : towers) {
		if(!mngr_->isAlive(t)){ eliminateDestroyedTowers(t); }//Eliminamos la torre de los arrays si esta muerta
		else {
			Transform* TR = mngr_->getComponent<Transform>(t);
			BulletTower* bt = mngr_->getComponent<BulletTower>(t);
			if (bt != nullptr) {
				int lvl = mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel();
				mngr_->getComponent<FramedImage>(t)->setCurrentFrame(lvl);
			}		
			if (bt != nullptr && bt->isMaxLevel()) {
				bt->setElapsedTime(timer_.currTime());
				if (bt->getElapsedTime() > bt->getTimeToShoot()*1000) {
					bt->targetSecondEnemy(mngr_->getHandler(_hdlr_ENEMIES));
					if (bt->getTarget() != nullptr) { shootBullet(bt->getTarget(), bt->getDamage(), BULLET_SPEED, TR->getPosition());}
					std::cout << "s";
				}
			}
			EnhancerTower* et = mngr_->getComponent<EnhancerTower>(t);
			if (et != nullptr) {
				int lvl = mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel();
				mngr_->getComponent<FramedImage>(t)->setCurrentFrame(lvl);
				Vector2D myPos = mngr_->getComponent<Transform>(t)->getPosition();
				for (size_t i = 0; i < towers.size(); i++)//miramos las torres de alarededor para potenciarlas
				{
					Vector2D towerPos = mngr_->getComponent<Transform>(towers[i])->getPosition();
					float distance = sqrt(pow(towerPos.getX() - myPos.getX(), 2) + pow(towerPos.getY() - myPos.getY(), 2));//distancia a la torre
					if (distance <= et->getRange() && towers[i] != t) {//enRango
						AttackComponent* ac = mngr_->getComponent<AttackComponent>(towers[i]);
						if (ac != nullptr) {ac->setDamage(ac->getBaseDamage() * (1 + et->getDamageIncreasePercentage()));}//incrementamos daño
						HealthComponent* h = mngr_->getComponent<HealthComponent>(towers[i]);
						if (h != nullptr) { h->setMaxHealth(h->getBaseHealth() + et->getTowersHPboost()); }//incrementamos vida
					}
				}
			}

			CrystalTower* ct = mngr_->getComponent<CrystalTower>(t);
			if (ct != nullptr) {
				ct->setElapsedTime(timer_.currTime());
				if (ct->getElapsedTime() > ct->getTimeToShield()*1000) {
					Message m;
					m.id = _m_SHIELD_NEXUS;
					m.shield_data.shield = ct->getShieldVal();
					if (ct->isMaxLevel()) {
						m.shield_data.explodes = true;
						m.shield_data.explosionDmg = ct->getExplosionDmg();
					}
					mngr_->send(m);
					ct->setTimeToShield(ct->getTimeToShield()+ct->getReloadTime());
				}
			}

			DiegoSniperTower* ds = mngr_->getComponent<DiegoSniperTower>(t);
			if (ds != nullptr) {
				ds->setElapsedTime(timer_.currTime());//Lo pasa a segundos
				if (ds->getElapsedTime() > ds->getTimeToShoot()*1000) {//si esta cargada busca enemigo con mas vida
					float health = 0;
					Entity* target = nullptr;
					for (const auto& enemy : mngr_->getHandler(_hdlr_ENEMIES))
					{	
						if (mngr_->isAlive(enemy)) {
							HealthComponent* h = mngr_->getComponent<HealthComponent>(enemy);
							if (h != nullptr && h->getHealth() > health) {//se guarda la referencia al enemigo con mas vida
								target = enemy;
								health = h->getHealth();
							}
						}					
					}
					if (target != nullptr) {//Dispara con el critico
						std::cout << "shot";
						RenderComponent* rc = mngr_->getComponent<RenderComponent>(t);
						Vector2D spawn = { TR->getPosition()->getX(),	TR->getPosition()->getY() + DIEGO_OFFSET};
						shootBullet(target, ds->getDamage() * ds->getCritDamage(), DIEGO_SPEED, spawn);
						ds->setTimeToShoot(ds->getTimeToShoot() + ds->getReloadTime());
					}
				}
			}
		}	
	}

	for (auto& b : bullets) {
		Transform* t = mngr_->getComponent<Transform>(b);
		BulletComponent* bc = mngr_->getComponent<BulletComponent>(b);

		bc->setDir();
		t->translate();
		if (!mngr_->isAlive(bc->getTarget())) {//Si ha muerto por el camino
			bc->onTravelEnds();
		}
		else{ //Si choca con el enemigo
			if (((*(t->getPosition()) - *(mngr_->getComponent<Transform>(bc->getTarget())->getPosition())).magnitude() <= 5.0f)) {
				bc->doDamageTo(bc->getTarget(), bc->getDamage());
				bc->onTravelEnds();
			}
		}
	}
}

void TowerSystem::eliminateDestroyedTowers(Entity* t) {//elimina delk array las torres muertas
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

void TowerSystem::shootBullet(Entity* target, float damage, float speed, Vector2D spawnPos) {
	Entity* bullet = mngr_->addEntity(_grp_BULLETS);//crea bala
	Transform* t = mngr_->addComponent<Transform>(bullet);//transform
	t->setPosition(spawnPos);
	t->setScale({ 40.0f, 40.0f });
	Vector2D dir = *(mngr_->getComponent<Transform>(target)->getPosition()) - *(t->getPosition());
	Vector2D norm = { 1, 0 };
	float angle = atan2(dir.getY(), dir.getX());
	t->addRotation(angle);
	mngr_->addComponent<BulletComponent>(bullet, t, target, damage, speed);//bullet component
	mngr_->addComponent<RenderComponent>(bullet, bulletTexture);//habra que hacer switch
}

void TowerSystem::addTower(twrId type, Vector2D pos, Height height) {
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);//Se añade al mngr
	towers.push_back(t);
	Transform* tr = mngr_->addComponent<Transform>(t);//transform
	tr->setPosition(pos);
	mngr_->addComponent<UpgradeTowerComponent>(t, type, 4);
	float health = 100.0f;
	if (height == LOW) { 
		mngr_->addComponent<HealthComponent>(t, health); 
		//lowTowers.push_back(t);
		mngr_->setHandler(_hdlr_LOW_TOWERS, t);
	}
	switch (type)
	{
	case _twr_FENIX:
		break;
	case _twr_BULLET://Pasar rango, recarga, daño y si dispara
		mngr_->addComponent<BulletTower>(t, 100.0f/*&sdlutils().floatConst().at("BalasRango")*/, 0.5f/*&sdlutils().floatConst().at("BalasRecarga")*/, 5/*&sdlutils().intConst().at("BalasDano")*/);
		mngr_->addComponent<RenderComponent>(t, bulletTowerTexture);
		mngr_->addComponent<FramedImage>(t, 4, 4, 37, 60, 0, 0);
	/*	mngr_->getComponent<UpgradeTowerComponent>(t)->LevelUp();
		mngr_->getComponent<UpgradeTowerComponent>(t)->LevelUp();
		mngr_->getComponent<UpgradeTowerComponent>(t)->LevelUp();
		mngr_->getComponent<UpgradeTowerComponent>(t)->LevelUp();*/

		break;
	case _twr_DIRT:
		break;
	case _twr_POWER://Pasar rango, porcentaje incremento de ataque y vida extra
		mngr_->addComponent<EnhancerTower>(t, 100.0f/*&sdlutils().floatConst().at("PotenciadoraRango")*/, 0.05f/*&sdlutils().floatConst().at("PotenciadoraAumentoDano")*/, 30.0f/*&sdlutils().floatConst().at("PotenciadoraAumentoVida")*/);
		mngr_->addComponent<RenderComponent>(t, boosterTowerTexture);
		mngr_->addComponent<FramedImage>(t, 5, 1, 35, 54, 0, 0);
		break;
	case _twr_DIEGO:
		mngr_->addComponent<DiegoSniperTower>(t, 1000.0f, 0, 1.0f, 3.0f, 50);
		mngr_->addComponent<RenderComponent>(t, sniperTowerTexture);
		mngr_->addComponent<FramedImage>(t, 5, 1, 35, 54, 0, 0);
		break;
	case _twr_SLIME:
		break;
	case _twr_CRISTAL:
		mngr_->addComponent<CrystalTower>(t,20/* &sdlutils().intConst().at("CristalEscudo")*/, 20.0f/*&sdlutils().floatConst().at("CristalRecarga")*/, 0/*&sdlutils().intConst().at("CristalDano")*/);
		mngr_->addComponent<RenderComponent>(t, cristalTowerTexture);
		mngr_->addComponent<FramedImage>(t, 4, 1, 44, 65, 0, 0);
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

void TowerSystem::onAttackTower(Entity* e, int dmg) {
	std::list<Entity*> towers = mngr_->getHandler(_hdlr_LOW_TOWERS);
	std::list<Entity*>::iterator findIter = std::find(towers.begin(), towers.end(), e);
	mngr_->getComponent<HealthComponent>((*findIter))->subtractHealth(dmg);
}