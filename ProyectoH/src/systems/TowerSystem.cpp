#include "TowerSystem.h"
#include "..//ecs/ecs.h"
#include "..//components/SlimeBullet.h"


TowerSystem::TowerSystem() : active_(true) {
}

TowerSystem::~TowerSystem() {
	towers.clear();
}

void TowerSystem::initSystem() {
	active_ = true;

	//addTower(twrId::_twr_BULLET, { (float)sdlutils().width() / 1.9f, 500.f }, LOW);
	//addTower(twrId::_twr_BULLET, { (float)sdlutils().width() / 2.2f, 500.f }, LOW);
	addTower(twrId::_twr_BULLET, { (float)sdlutils().width() / 1.9f, 550.f }, LOW);
	//addTower(twrId::_twr_DIEGO, { (float)sdlutils().width() / 1.9f, 600.f }, LOW);
	addTower(twrId::_twr_BULLET, { (float)sdlutils().width() / 2.3f, 600.f }, LOW);
	addTower(twrId::_twr_SLIME, { (float)sdlutils().width() / 2.3f, 630.f }, LOW);
	addTower(twrId::_twr_BULLET, { (float)sdlutils().width() / 1.8f, 600.f }, LOW);
	//addTower(twrId::_twr_BULLET, { (float)sdlutils().width() / 1.7f, 550.f }, LOW);
	//addTower(twrId::_twr_POWER, { (float)sdlutils().width() / 2.2f, 540.f }, LOW);
}

void TowerSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	case _m_TOWER_TO_ATTACK://Mandado por el enemySystem al atacar una torre
		onAttackTower(m.tower_to_attack.e, m.tower_to_attack.damage);
	}
}

/// <summary>
/// Ataca a torre
/// </summary>
/// <param name="e">Torre atacada</param>
/// <param name="dmg">Dano que debe recibir la torre</param>
void TowerSystem::onAttackTower(Entity* e, int dmg) {
	if (e != nullptr && mngr_->isAlive(e)) {
		HealthComponent* h = mngr_->getComponent<HealthComponent>(e);
		if (h->getHealth() - dmg <= 0) {
			mngr_->deleteHandler(_hdlr_LOW_TOWERS, e); eliminateDestroyedTowers(e);
		}
		h->subtractHealth(dmg);
	}
}
//Realiza las funcionalidades de las torres, accediendo a los atributos de los componentes y realizando la mecanica de cada torre
void TowerSystem::update() {
	const auto& bullets = mngr_->getEntities(_grp_BULLETS);
	const float DIEGO_OFFSET = sdlutils().floatConst().at("DiegoSniperOffset");
	
	for (auto& t : towers) {

			Transform* TR = mngr_->getComponent<Transform>(t);

			EnhancerTower* et = mngr_->getComponent<EnhancerTower>(t);
			if (et != nullptr) {
				int lvl = mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel();
				mngr_->getComponent<FramedImage>(t)->setCurrentFrame(lvl);
				Vector2D myPos = mngr_->getComponent<Transform>(t)->getPosition();
				//std::cout << et->getRange() << std::endl;
				for (size_t i = 0; i < towers.size(); i++)//miramos las torres de alarededor para potenciarlas
				{
					Vector2D towerPos = mngr_->getComponent<Transform>(towers[i])->getPosition();
					float distance = sqrt(pow(towerPos.getX() - myPos.getX(), 2) + pow(towerPos.getY() - myPos.getY(), 2));//distancia a la torre
					if (distance <= et->getRange() && towers[i] != t) {//enRango
						//std::cout << "Potenciada: " << i << std::endl;
						DiegoSniperTower* ac = mngr_->getComponent<DiegoSniperTower>(towers[i]);
						if (ac != nullptr) {
							ac->setDamage(ac->getBaseDamage() * (1 + et->getDamageIncreasePercentage()));
						}//incrementamos daño
						HealthComponent* h = mngr_->getComponent<HealthComponent>(towers[i]);
						if (h != nullptr) { h->setMaxHealth(h->getBaseHealth() + et->getTowersHPboost()); }//incrementamos vida
					}
				}
			}
			//Cada cierto tiempo targetea a un enemigo y le dispara, cambiando su imagen en funci�n de la direcci�n del disparo
			BulletTower* bt = mngr_->getComponent<BulletTower>(t);					
			if (bt != nullptr) {
				Vector2D offset{ DIEGO_OFFSET, DIEGO_OFFSET };//Offset para el punto de spawn de la bala
				int valFrame = 0;//Valor del frame que se ha de escoger del spritesheet para renderizar la torre en la direccion correcta
				bt->setElapsedTime(bt->getElapsedTime()+game().getDeltaTime());
				if (bt->getElapsedTime() > 0.5) {
					
					bt->targetEnemy(mngr_->getHandler(_hdlr_ENEMIES));
					bt->setElapsedTime(0);
					if (bt->getTarget() != nullptr ) {			 				
						//Se coge el vector de la torre al objetivo, y en funcion de su direccion en los dos ejes se escoje el frame para la torre y 
						//el punto desde el que sale la bala, que debe ser el canon de la torre. Para eso se usa el offset
						Vector2D dir = *(mngr_->getComponent<Transform>(bt->getTarget())->getPosition()) - *(TR->getPosition());
						if (dir.getX() >= 0 && dir.getY() >= 0) { valFrame = 4; offset.setX(DIEGO_OFFSET * 2.5); }
						else if (dir.getX() >= 0 && dir.getY() < 0) { valFrame = 12; offset.setY(0); offset.setX(DIEGO_OFFSET * 2.5); }
						else if (dir.getX() < 0 && dir.getY() >= 0) { offset.setX(0); }
						else if (dir.getX() < 0 && dir.getY() < 0) { valFrame = 8; offset.setX(0); offset.setY(0); }
						//mngr_->getComponent<FramedImage>(t)->setCurrentFrame(valFrame + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						Vector2D spawn = { TR->getPosition()->getX() + offset.getX(),	TR->getPosition()->getY() + offset.getY() };//Punto de spawn de la bala con el offset
						shootBullet(bt->getTarget(), t, bt->getDamage(), sdlutils().floatConst().at("BalasVelocidad"), spawn, bulletTexture, { 35, 35 }, _twr_BULLET);//Dispara la bala
					}
					if (bt->isMaxLevel()) {//Mejora maxima de la torre de balas: targetear a un segundo enemigo. Funciona igual que el primer targeteo
						bt->targetSecondEnemy(mngr_->getHandler(_hdlr_ENEMIES));
						if (bt->getSecondTarget() != nullptr) {;

							Vector2D dir = *(mngr_->getComponent<Transform>(bt->getSecondTarget())->getPosition()) - *(TR->getPosition());
							if (dir.getX() >= 0 && dir.getY() >= 0) { valFrame = 4; offset.setX(DIEGO_OFFSET * 2.5); }
							else if (dir.getX() >= 0 && dir.getY() < 0) { valFrame = 12; offset.setY(0); offset.setX(DIEGO_OFFSET * 2.5); }
							else if (dir.getX() < 0 && dir.getY() >= 0) { offset.setX(0); }
							else if (dir.getX() < 0 && dir.getY() < 0) { valFrame = 8; offset.setX(0); offset.setY(0); }
							shootBullet(bt->getSecondTarget(), t, bt->getDamage(), sdlutils().floatConst().at("BalasVelocidad"), TR->getPosition(), bulletTexture, { 35, 35 }, _twr_BULLET);

							mngr_->getComponent<FramedImage>(t)->setCurrentFrame(valFrame + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
							Vector2D spawn = { TR->getPosition()->getX() + offset.getX(),	TR->getPosition()->getY() + offset.getY() };//Punto de spawn de la bala con el offset
		
						}
					}
					
				}

			}
			
			//Cada cierto tiempo manda un mensaje con info del escudo para el nexo y la explosion si esta al nivel maximo
			CrystalTower* ct = mngr_->getComponent<CrystalTower>(t);
			if (ct != nullptr) {
				ct->setElapsedTime(ct->getElapsedTime()+game().getDeltaTime());
				if (ct->getElapsedTime() > ct->getTimeToShield()) {
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
			//
			// 
			SlimeTowerComponent* st = mngr_->getComponent<SlimeTowerComponent>(t);
			if (st != nullptr) {
				st->setElapsedTime(st->getElapsedTime() + game().getDeltaTime());//Lo pasa a segundos
				if (st->getElapsedTime() > st->getTimeToShoot()) {
					st->targetEnemy(mngr_->getHandler(_hdlr_ENEMIES));
					if (st->getTarget() != nullptr) {
						Vector2D offset{ DIEGO_OFFSET, DIEGO_OFFSET };
						int valFrame = 0;
						Vector2D dir = *(mngr_->getComponent<Transform>(st->getTarget())->getPosition()) - *(TR->getPosition());
						if (dir.getX() >= 0 && dir.getY() >= 0) { valFrame = 4; offset.setX(DIEGO_OFFSET * 3.5); }
						else if (dir.getX() >= 0 && dir.getY() < 0) { valFrame = 12; offset.setY(0); offset.setX(DIEGO_OFFSET * 3.5); }
						else if (dir.getX() < 0 && dir.getY() >= 0) { offset.setX(0); }
						else if (dir.getX() < 0 && dir.getY() < 0) { valFrame = 8; offset.setX(0); offset.setY(0); }
						mngr_->getComponent<FramedImage>(t)->setCurrentFrame(valFrame + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						RenderComponent* rc = mngr_->getComponent<RenderComponent>(t);
						Vector2D spawn = { TR->getPosition()->getX() + offset.getX(),	TR->getPosition()->getY() + offset.getY() };
						Entity* bullet = shootBullet(st->getTarget(), t, st->getDamage(), sdlutils().floatConst().at("SlimeVelocidad"), spawn, slimeBulletTexture, { 25, 25 }, _twr_SLIME);
						mngr_->addComponent<SlimeBullet>(bullet, st->getDuration(), st->getSpeedDecrease(), st->getDPS());
						st->setElapsedTime(0);
					}
				}
			}

			//Cada cierto tiempo dispara al enemigo que tiene mas vida que esta en rango, 
			//con el dano de critico anadido. Falta que haga el critico en funcion de una probabilida
			DiegoSniperTower* ds = mngr_->getComponent<DiegoSniperTower>(t);
			if (ds != nullptr) {
				ds->setElapsedTime(ds->getElapsedTime()+game().getDeltaTime());//Lo pasa a segundos
				if (ds->getElapsedTime() > ds->getTimeToShoot()) {//si esta cargada busca enemigo con mas vida
					float health = 0;
					Entity* target = nullptr;
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
						Vector2D offset { DIEGO_OFFSET, DIEGO_OFFSET };
						int valFrame = 0;
						Vector2D dir = *(mngr_->getComponent<Transform>(target)->getPosition()) - *(TR->getPosition());
						if (dir.getX() >= 0 && dir.getY() >= 0) { valFrame = 4; offset.setX(DIEGO_OFFSET * 3.5); }
						else if (dir.getX() >= 0 && dir.getY() < 0) { valFrame = 12; offset.setY(0); offset.setX(DIEGO_OFFSET * 3.5);}
						else if (dir.getX() < 0 && dir.getY() >= 0){ offset.setX(0); }
						else if (dir.getX() < 0 && dir.getY() < 0) { valFrame = 8; offset.setX(0); offset.setY(0);}
						mngr_->getComponent<FramedImage>(t)->setCurrentFrame(valFrame + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						RenderComponent* rc = mngr_->getComponent<RenderComponent>(t);
						Vector2D spawn = { TR->getPosition()->getX() + offset.getX(),	TR->getPosition()->getY() + offset.getY()};
						
						shootBullet(target, t, ds->getDamage() * ds->getCritDamage(), sdlutils().floatConst().at("DiegoSniperVelocidad"), spawn, sniperBulletTexture, {25, 20}, _twr_DIEGO);
						
					}
					ds->setElapsedTime(0);
				}
				if (!mngr_->isAlive(t)) { eliminateDestroyedTowers(t); };
			}		
	}
	//Mueve y dirige las balas, y destruye las balas si su objetivo muere o si choca con el objetivo, causandole dano
	for (auto& b : bullets) {
		Transform* t = mngr_->getComponent<Transform>(b);
		BulletComponent* bc = mngr_->getComponent<BulletComponent>(b);	
		SlimeBullet* sb = mngr_->getComponent<SlimeBullet>(b);
		FramedImage* fi = mngr_->getComponent<FramedImage>(bc->getTarget());
		Vector2D targetPos = *(mngr_->getComponent<Transform>(bc->getTarget())->getPosition());
		if (fi != nullptr) {
			Vector2D offset = { (float)fi->getSrcRect().w / 4, (float)fi->getSrcRect().h / 4 };//Se dirige hacia el centro del rect
			targetPos = targetPos + offset;
		}
		Vector2D myPos = *(t->getPosition());
		
		if (!mngr_->isAlive(bc->getTarget())) {//Si ha muerto por el camino
			bc->onTravelEnds();
		}	
		else if(((targetPos - myPos).magnitude() <= 5.0f)) { //Si choca con el enemigo
			if (sb != nullptr) {
				Entity* area = mngr_->addEntity(_grp_SLIMEAREA);
				Transform* tr = mngr_->addComponent<Transform>(area);
				tr->setPosition(t->getPosition());
				tr->setScale({ 200, 200 });
				mngr_->addComponent<RenderComponent>(area, slimeArea);
				mngr_->addComponent<FramedImage>(area, 9, 1, 500, 400, 0, 5, 8);
			}
			bc->doDamageTo(bc->getTarget(), bc->getDamage());
			bc->onTravelEnds();
		}
		else {
			bc->setDir();
			t->translate();
		}
	}
}

void TowerSystem::eliminateDestroyedTowers(Entity* t) {//elimina del array las torres muertas
	towers.erase(find(towers.begin(), towers.end(), t));
}

/// <summary>
/// Spawnea una bala con una posicion, una direccion, un dano y una velocidad
/// </summary>
/// <param name="target">Entidad objetivo de la bala</param>
/// <param name="src">Entidad origen de la bala</param>
/// <param name="damage">Dano</param>
/// <param name="speed">Velocidad</param>
/// <param name="spawnPos">Posicion de spawn, que deberia ser la de la posicion del canon de la torre</param>
Entity* TowerSystem::shootBullet(Entity* target, Entity* src ,float damage, float speed, Vector2D spawnPos, gameTextures texture, Vector2D bulletScale, twrId id) {
	Entity* bullet = mngr_->addEntity(_grp_BULLETS);//crea bala
	Transform* t = mngr_->addComponent<Transform>(bullet);//transform
	t->setPosition(spawnPos);
	t->setScale(bulletScale);
	mngr_->addComponent<BulletComponent>(bullet, t, target, src, damage, speed);//bullet component
	mngr_->addComponent<RenderComponent>(bullet, texture);//habra que hacer switch
	return bullet;
}
/// <summary>
/// Debe spawnear una entidad con un fireComponent que tenga un rect y se detecte la colision con enemigos en un collision system
/// </summary>
/// <param name="shootingTime">Tiempo en el que esta disparando fuego la torre de fenix</param>
/// <param name="damage">Dano por segundo causado por la torre de fenix</param>
void TowerSystem::shootFire(float shootingTime, int damage, Vector2D spawnPos) {
	Entity* fire = mngr_->addEntity(_grp_BULLETS);
	Transform* t = mngr_->addComponent<Transform>(fire);
	RenderComponent* r = mngr_->addComponent<RenderComponent>(fire, square);
	Message m;
	m.rect_data.rect = fire;
	m.rect_data.id = _FENIX;
	mngr_->send(m);
}
/// <summary>
/// Anade una torre al sistema, con un tipo, una posicion y una elevacion. A cada torre le anade un render component, un 
/// framed image, un transform, su componente especifico, un health component y un upgrade tower component, con sus atributos correspondientes sacados de un json.
/// Las torres se meten en los handlers en funcion de su elevacion
/// </summary>
/// <param name="type">Tipo de la torre que definira sus mecanicas y su aspecto</param>
/// <param name="pos">Posicion en la que se coloca la torre</param>
/// <param name="height">Elevacion de la torre; puede ser alta o baja</param>
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
	else mngr_->setHandler(_hdlr_HIGH_TOWERS, t);
	switch (type)
	{
	case _twr_FENIX://Dano, Enfriamiento, TiempoDisparo, Rango
		mngr_->addComponent<PhoenixTower>(t, sdlutils().floatConst().at("FenixDano"), sdlutils().floatConst().at("FenixEnfriamiento"), sdlutils().floatConst().at("FenixTiempoDisparo"), sdlutils().floatConst().at("FenixRango"));
		mngr_->addComponent<RenderComponent>(t, phoenixTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("FenixColumns"), sdlutils().intConst().at("FenixRows"), sdlutils().intConst().at("FenixWidth"), sdlutils().intConst().at("FenixHeight"), 0, 0);
		break;
	case _twr_BULLET://Pasar rango, recarga, da?o y si dispara
		mngr_->addComponent<BulletTower>(t, sdlutils().floatConst().at("BalasRango"), sdlutils().floatConst().at("BalasRecarga"), sdlutils().intConst().at("BalasDano"));
		mngr_->addComponent<RenderComponent>(t, bulletTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("BalasColumns"), sdlutils().intConst().at("BalasRows"), sdlutils().intConst().at("BalasWidth"), sdlutils().intConst().at("BalasHeight"), 0, 0);
		//mngr_->getComponent<UpgradeTowerComponent>(t)->LevelUp();
		//mngr_->getComponent<UpgradeTowerComponent>(t)->LevelUp();
		//mngr_->getComponent<UpgradeTowerComponent>(t)->LevelUp();
		//mngr_->getComponent<UpgradeTowerComponent>(t)->LevelUp();

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
	case _twr_DIEGO://Rango, Probabilidad de critico, Dano por critico, Tiempo de recarga y Dano
		mngr_->addComponent<DiegoSniperTower>(t, sdlutils().floatConst().at("DiegoSniperRango"), sdlutils().floatConst().at("DiegoSniperCritProb1"), sdlutils().floatConst().at("DiegoSniperCritDano1"), sdlutils().floatConst().at("DiegoSniperRecarga"), sdlutils().intConst().at("DiegoSniperDano"));
		mngr_->addComponent<RenderComponent>(t, sniperTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("DiegoSniperColumns"), sdlutils().intConst().at("DiegoSniperRows"), sdlutils().intConst().at("DiegoSniperWidth"), sdlutils().intConst().at("DiegoSniperHeight"), 0, 0);
		break;
	case _twr_SLIME:
		mngr_->addComponent<SlimeTowerComponent>(t, sdlutils().intConst().at("SlimeRango"), sdlutils().floatConst().at("SlimeTiempoSlime"), sdlutils().floatConst().at("SlimeRalentizacion"), sdlutils().intConst().at("SlimeDPS"), sdlutils().intConst().at("SlimeRecarga") ,sdlutils().intConst().at("SlimeDano"));
		mngr_->addComponent<RenderComponent>(t, slimeTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("SlimeColumns"), sdlutils().intConst().at("SlimeRows"), sdlutils().intConst().at("SlimeWidth"), sdlutils().intConst().at("SlimeHeight"), 0, 0);

		break;
	case _twr_CRISTAL://Escudo, Tiempo de recarga y dano por explosion
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
