#include "TowerSystem.h"


TowerSystem::TowerSystem() : active_(true) {
}

TowerSystem::~TowerSystem() {
	towers.clear();
}

void TowerSystem::initSystem() {
	active_ = true;

	addTower(twrId::_twr_BULLET, { (float)sdlutils().width() / 2.f, 600.f }, LOW);
	addTower(twrId::_twr_DIEGO, { (float)sdlutils().width() / 1.5f, 600.f }, LOW);
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
		//std::cout << towers.size() << std::endl;
		//if(!mngr_->isAlive(t)){ eliminateDestroyedTowers(t); }//Eliminamos la torre de los arrays si esta muerta
		//else {
			Transform* TR = mngr_->getComponent<Transform>(t);
			BulletTower* bt = mngr_->getComponent<BulletTower>(t);
					
			if (bt != nullptr) {
				bt->setElapsedTime(bt->getElapsedTime()+game().getDeltaTime());
				//std::cout << bt->getElapsedTime() << "\n";
				//std::cout << bt->getReloadTime() << "\n";
				if (bt->getElapsedTime() > bt->getReloadTime()) {
					
					bt->targetEnemy(mngr_->getHandler(_hdlr_ENEMIES));
					bt->setElapsedTime(0);
					//bt->targetSecondEnemy(mngr_->getHandler(_hdlr_ENEMIES));
					if (bt->getTarget() != nullptr ) {
						Vector2D dir = *(mngr_->getComponent<Transform>(bt->getTarget())->getPosition()) - *(TR->getPosition());
						if (dir.getX() >= 0 && dir.getY() >= 0) mngr_->getComponent<FramedImage>(t)->setCurrentFrame(4 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() >= 0 && dir.getY() < 0) mngr_->getComponent<FramedImage>(t)->setCurrentFrame(12 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() < 0 && dir.getY() >= 0)mngr_->getComponent<FramedImage>(t)->setCurrentFrame(0 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() < 0 && dir.getY() < 0)mngr_->getComponent<FramedImage>(t)->setCurrentFrame(8 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						shootBullet(bt->getTarget(), t, bt->getDamage(), BULLET_SPEED, TR->getPosition(), bulletTexture, { 35, 35 });
						//bt->setTimeToShoot(bt->getTimeToShoot() + bt->getReloadTime());
						
						//std::cout << dir.getX() << " " << dir.getY() << "\n";
					}
					/*if (bt->getSecondTarget() != nullptr) {
						Vector2D dir = *(mngr_->getComponent<Transform>(bt->getSecondTarget())->getPosition()) - *(TR->getPosition());
						if (dir.getX() >= 0 && dir.getY() >= 0) mngr_->getComponent<FramedImage>(t)->setCurrentFrame(4 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() >= 0 && dir.getY() < 0) mngr_->getComponent<FramedImage>(t)->setCurrentFrame(12 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() < 0 && dir.getY() >= 0)mngr_->getComponent<FramedImage>(t)->setCurrentFrame(0 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() < 0 && dir.getY() < 0)mngr_->getComponent<FramedImage>(t)->setCurrentFrame(8+mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						shootBullet(bt->getSecondTarget(), bt->getDamage(), BULLET_SPEED, TR->getPosition());	
						bt->setTimeToShoot(bt->getTimeToShoot() + bt->getReloadTime());
						std::cout << dir.getX() << " " << dir.getY() << "\n";
					}*/
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
				ct->setElapsedTime(ct->getElapsedTime()+game().getDeltaTime());
				if (ct->getElapsedTime() > ct->getTimeToShield()*1000) {
					Message m;
					m.id = _m_SHIELD_NEXUS;
					m.shield_data.shield = ct->getShieldVal();
					if (ct->isMaxLevel()) {
						m.shield_data.explodes = true;
						m.shield_data.explosionDmg = ct->getExplosionDmg();
					}
					mngr_->send(m);
					ct->setElapsedTime(0);
				}
			}

			DiegoSniperTower* ds = mngr_->getComponent<DiegoSniperTower>(t);
			if (ds != nullptr) {
				ds->setElapsedTime(ds->getElapsedTime()+game().getDeltaTime());//Lo pasa a segundos
				if (ds->getElapsedTime() > ds->getTimeToShoot()) {//si esta cargada busca enemigo con mas vida
					float health = 0;
					Entity* target = nullptr;
					std::cout << mngr_->getHandler(_hdlr_ENEMIES).size();
					for (const auto& enemy : mngr_->getHandler(_hdlr_ENEMIES))
					{	
						
						if (mngr_->isAlive(enemy)) {
							HealthComponent* h = mngr_->getComponent<HealthComponent>(enemy);
							if (h != nullptr) {//se guarda la referencia al enemigo con mas vida
								if (h->getHealth() > health) {
									target = enemy;
									health = h->getHealth();
								}		
							}
						}					
					}
					if (target != nullptr) {//Dispara con el critico
						//std::cout << "shot";
						Vector2D dir = *(mngr_->getComponent<Transform>(target)->getPosition()) - *(TR->getPosition());
						if (dir.getX() >= 0 && dir.getY() >= 0) mngr_->getComponent<FramedImage>(t)->setCurrentFrame(4 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() >= 0 && dir.getY() < 0) mngr_->getComponent<FramedImage>(t)->setCurrentFrame(12 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() < 0 && dir.getY() >= 0)mngr_->getComponent<FramedImage>(t)->setCurrentFrame(0 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() < 0 && dir.getY() < 0)mngr_->getComponent<FramedImage>(t)->setCurrentFrame(8 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						RenderComponent* rc = mngr_->getComponent<RenderComponent>(t);
						Vector2D spawn = { TR->getPosition()->getX(),	TR->getPosition()->getY() + DIEGO_OFFSET};
						
						shootBullet(target, t, ds->getDamage() * ds->getCritDamage(), DIEGO_SPEED, spawn, sniperBulletTexture, {25, 20});
						
					}
					ds->setElapsedTime(0);
				}
				if (!mngr_->isAlive(t)) { eliminateDestroyedTowers(t); };
			}
			//Esto no hay que hacerlo en el update, si no en el LevelUp
			/*if (et == nullptr) {
				int lvl = mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel();
				if (lvl == 4)lvl--;
				mngr_->getComponent<FramedImage>(t)->setCurrentFrame(lvl);
			}*/
		//}		
	}

	for (auto& b : bullets) {
		Transform* t = mngr_->getComponent<Transform>(b);
		BulletComponent* bc = mngr_->getComponent<BulletComponent>(b);	
		if (!mngr_->isAlive(bc->getTarget())) {//Si ha muerto por el camino
			bc->onTravelEnds();
		}
		else if(((*(t->getPosition()) - *(mngr_->getComponent<Transform>(bc->getTarget())->getPosition())).magnitude() <= 5.0f)) {
			bc->doDamageTo(bc->getTarget(), bc->getDamage());
			bc->onTravelEnds();
		}
		else {
			bc->setDir();
			t->translate();
		}
	}
}

void TowerSystem::eliminateDestroyedTowers(Entity* t) {//elimina delk array las torres muertas
	bool found = false;
	int i = 0;
	
	while (i < towers.size() && !found) {
		if (t == towers[i]) {
			found = true;
			if (towers.size() > 1) { towers[i] = towers.back(); }
			towers.pop_back();
		}
		i++;
	}
}

void TowerSystem::shootBullet(Entity* target, Entity* src ,float damage, float speed, Vector2D spawnPos, gameTextures texture, Vector2D bulletScale) {
	Entity* bullet = mngr_->addEntity(_grp_BULLETS);//crea bala
	Transform* t = mngr_->addComponent<Transform>(bullet);//transform
	t->setPosition(spawnPos);
	t->setScale(bulletScale);
	mngr_->addComponent<BulletComponent>(bullet, t, target, src, damage, speed);//bullet component
	mngr_->addComponent<RenderComponent>(bullet, texture);//habra que hacer switch
}

void TowerSystem::shootFire(float shootingTime, int damage) {

}

void TowerSystem::addTower(twrId type, Vector2D pos, Height height) {
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);//Se a?ade al mngr
	Transform* tr = mngr_->addComponent<Transform>(t);//transform
	tr->setPosition(pos);
	tr->setScale({ 100.0f, 150.0f });
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
		mngr_->addComponent<PhoenixTower>(t, sdlutils().floatConst().at("FenixDano"), sdlutils().floatConst().at("FenixEnfriamiento"), sdlutils().floatConst().at("FenixTiempoDisparo"), sdlutils().floatConst().at("FenixRango"));
		mngr_->addComponent<RenderComponent>(t, phoenixTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("FenixColumns"), sdlutils().intConst().at("FenixRows"), sdlutils().intConst().at("FenixWidth"), sdlutils().intConst().at("FenixHeight"), 0, 0);
		break;
	case _twr_BULLET://Pasar rango, recarga, da?o y si dispara
		mngr_->addComponent<BulletTower>(t, sdlutils().floatConst().at("BalasRango"), sdlutils().floatConst().at("BalasRecarga"), sdlutils().intConst().at("BalasDano"));
		mngr_->addComponent<RenderComponent>(t, bulletTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("BalasColumns"), sdlutils().intConst().at("BalasRows"), sdlutils().intConst().at("BalasWidth"), sdlutils().intConst().at("BalasHeight"), 0, 0);

		break;
	case _twr_DIRT:
		mngr_->addComponent<DirtTower>(t);
		mngr_->addComponent<RenderComponent>(t, clayTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("ArcillaColumns"), sdlutils().intConst().at("ArcillaRows"), sdlutils().intConst().at("ArcillaWidth"), sdlutils().intConst().at("ArcillaHeight"), 0, 0);
		break;
	case _twr_POWER://Pasar rango, porcentaje incremento de ataque y vida extra
		mngr_->addComponent<EnhancerTower>(t, sdlutils().floatConst().at("PotenciadoraRango"), sdlutils().floatConst().at("PotenciadoraAumentoDano"), sdlutils().floatConst().at("PotenciadoraAumentoVida"));
		mngr_->addComponent<RenderComponent>(t, boosterTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("PotenciadoraColumns"), sdlutils().intConst().at("PotenciadoraRows"), sdlutils().intConst().at("PotenciadoraWidth"), sdlutils().intConst().at("PotenciadoraHeight"), 0, 0);
		break;
	case _twr_DIEGO:
		mngr_->addComponent<DiegoSniperTower>(t, sdlutils().floatConst().at("DiegoSniperRango"), sdlutils().floatConst().at("DiegoSniperCritProb1"), sdlutils().floatConst().at("DiegoSniperCritDano1"), sdlutils().floatConst().at("DiegoSniperRecarga"), sdlutils().intConst().at("DiegoSniperDano"));
		mngr_->addComponent<RenderComponent>(t, sniperTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("DiegoSniperColumns"), sdlutils().intConst().at("DiegoSniperRows"), sdlutils().intConst().at("DiegoSniperWidth"), sdlutils().intConst().at("DiegoSniperHeight"), 0, 0);
		break;
	case _twr_SLIME:
		mngr_->addComponent<RenderComponent>(t, slimeTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("SlimeColumns"), sdlutils().intConst().at("SlimeRows"), sdlutils().intConst().at("SlimeWidth"), sdlutils().intConst().at("SlimeHeight"), 0, 0);

		break;
	case _twr_CRISTAL:
		mngr_->addComponent<CrystalTower>(t, sdlutils().intConst().at("CristalEscudo"), sdlutils().floatConst().at("CristalRecarga"), sdlutils().intConst().at("CristalExplosion"));
		mngr_->addComponent<RenderComponent>(t, cristalTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("CristalColumns"), sdlutils().intConst().at("CristalRows"), sdlutils().intConst().at("CristalWidth"), sdlutils().intConst().at("CristalHeight"), 0, 0);
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
	/*std::list<Entity*> towers = mngr_->getHandler(_hdlr_LOW_TOWERS);
	std::list<Entity*>::iterator findIter = std::find(towers.begin(), towers.end(), e);*/
	if (mngr_->isAlive(e)) {
		HealthComponent* h = mngr_->getComponent<HealthComponent>(e);
		if (h->getHealth() - dmg <= 0) {
			mngr_->deleteHandler(_hdlr_LOW_TOWERS, e); eliminateDestroyedTowers(e);
		}
		h->subtractHealth(dmg);
	}
}