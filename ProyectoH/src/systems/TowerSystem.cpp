#include "TowerSystem.h"


TowerSystem::TowerSystem() : active_(true) {
}

TowerSystem::~TowerSystem() {
	towers.clear();
}

void TowerSystem::initSystem() {
	active_ = true;

	addTower(twrId::_twr_BULLET, { (float)sdlutils().width() / 2.f, 600.f }, LOW);
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

void TowerSystem::onRoundStart() {

}

void TowerSystem::onRoundOver() {

}

/// <summary>
/// Ataca a torre
/// </summary>
/// <param name="e">Torre atacada</param>
/// <param name="dmg">Dano que debe recibir la torre</param>
void TowerSystem::onAttackTower(Entity* e, int dmg) {

	if (mngr_->isAlive(e)) {//Si dos enemigos atacan a la vez puede morir antes del segundo ataque entonces se debe comprobar
		HealthComponent* h = mngr_->getComponent<HealthComponent>(e);
		if (h->getHealth() - dmg <= 0) {
			mngr_->deleteHandler(_hdlr_LOW_TOWERS, e); eliminateDestroyedTowers(e);//Elimina la torre del handler y del array del system
		}
		h->subtractHealth(dmg);
	}
}

//Realiza las funcionalidades de las torres, accediendo a los atributos de los componentes y realizando la mecanica de cada torre
void TowerSystem::update() {
	const auto& bullets = mngr_->getEntities(_grp_BULLETS);
		
	for (auto& t : towers) {

			Transform* TR = mngr_->getComponent<Transform>(t);
			BulletTower* bt = mngr_->getComponent<BulletTower>(t);
			
			//Cada cierto tiempo targetea a un enemigo y le dispara, cambiando su imagen en funci�n de la direcci�n del disparo
			if (bt != nullptr) {
				bt->setElapsedTime(bt->getElapsedTime()+game().getDeltaTime());
				if (bt->getElapsedTime() > bt->getTimeToShoot()) {
					bt->targetEnemy(mngr_->getHandler(_hdlr_ENEMIES));
					bt->setElapsedTime(0);
					if (bt->getTarget() != nullptr) {
						Vector2D dir = *(mngr_->getComponent<Transform>(bt->getTarget())->getPosition()) - *(TR->getPosition());
						if (dir.getX() >= 0 && dir.getY() >= 0) mngr_->getComponent<FramedImage>(t)->setCurrentFrame(4 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() >= 0 && dir.getY() < 0) mngr_->getComponent<FramedImage>(t)->setCurrentFrame(12 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() < 0 && dir.getY() >= 0)mngr_->getComponent<FramedImage>(t)->setCurrentFrame(0 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						else if (dir.getX() < 0 && dir.getY() < 0)mngr_->getComponent<FramedImage>(t)->setCurrentFrame(8 + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
						shootBullet(bt->getTarget(), t, bt->getDamage(), sdlutils().floatConst().at("BalasVelocidad"), TR->getPosition());
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
			//Potencia las torres que esten en rango de esta
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
						if (ac != nullptr) {ac->setDamage(ac->getBaseDamage() * (1 + et->getDamageIncreasePercentage()));}//incrementamos da�o
						HealthComponent* h = mngr_->getComponent<HealthComponent>(towers[i]);
						if (h != nullptr) { h->setMaxHealth(h->getBaseHealth() + et->getTowersHPboost()); }//incrementamos vida
					}
				}
			}

			//Cada cierto tiempo manda un mensaje con info del escudo para el nexo y la explosion si esta al nivel maximo
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

			//Cada cierto tiempo dispara al enemigo que tiene mas vida que esta en rango, 
			//con el dano de critico anadido. Falta que haga el critico en funcion de una probabilidad
			DiegoSniperTower* ds = mngr_->getComponent<DiegoSniperTower>(t);
			if (ds != nullptr) {
				ds->setElapsedTime(ds->getElapsedTime()+game().getDeltaTime());//Lo pasa a segundos
				if (ds->getElapsedTime() > ds->getTimeToShoot()) {//si esta cargada busca enemigo con mas vida
					float health = 0;
					Entity* target = nullptr;
					//std::cout << mngr_->getHandler(_hdlr_ENEMIES).size();
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
						Vector2D spawn = { TR->getPosition()->getX(),	TR->getPosition()->getY() + sdlutils().floatConst().at("DiegoSniperOffset") };
						
						shootBullet(target, t, ds->getDamage() * ds->getCritDamage(), sdlutils().floatConst().at("DiegoSniperVelocidad"), spawn);
						
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
	//Mueve y dirige las balas, y destruye las balas si su objetivo muere o si choca con el objetivo, causandole dano
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
void TowerSystem::shootBullet(Entity* target, Entity* src ,float damage, float speed, Vector2D spawnPos) {
	Entity* bullet = mngr_->addEntity(_grp_BULLETS);//crea bala
	Transform* t = mngr_->addComponent<Transform>(bullet);//transform
	t->setPosition(spawnPos);
	t->setScale({ 40.0f, 40.0f });
	Vector2D dir = *(mngr_->getComponent<Transform>(target)->getPosition()) - *(t->getPosition());
	Vector2D norm = { 1, 0 };
	float angle = atan2(dir.getY(), dir.getX());
	t->addRotation(angle);
	mngr_->addComponent<BulletComponent>(bullet, t, target, src, damage, speed);//bullet component
	mngr_->addComponent<RenderComponent>(bullet, bulletTexture);//habra que hacer switch
}
/// <summary>
/// Debe spawnear una entidad con un fireComponent que tenga un rect y se detecte la colision con enemigos en un collision system
/// </summary>
/// <param name="shootingTime">Tiempo en el que esta disparando fuego la torre de fenix</param>
/// <param name="damage">Dano por segundo causado por la torre de fenix</param>
void TowerSystem::shootFire(float shootingTime, int damage) {

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
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);//Se anade al mngr
	Transform* tr = mngr_->addComponent<Transform>(t);//transform
	tr->setPosition(pos);
	tr->setScale({ 100.0f, 150.0f });
	mngr_->addComponent<UpgradeTowerComponent>(t, type, 4);
	float health = 100.0f;
	mngr_->addComponent<HealthComponent>(t, health);
	if (height == LOW) {	
		mngr_->setHandler(_hdlr_LOW_TOWERS, t);
	}else mngr_->setHandler(_hdlr_HIGH_TOWERS, t);
	switch (type)
	{
	case _twr_FENIX://Dano, Enfriamiento, TiempoDisparo, Rango
		mngr_->addComponent<PhoenixTower>(t, sdlutils().floatConst().at("FenixDano"), sdlutils().floatConst().at("FenixEnfriamiento"), sdlutils().floatConst().at("FenixTiempoDisparo"), sdlutils().floatConst().at("FenixRango"));
		mngr_->addComponent<RenderComponent>(t, phoenixTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("FenixColumns"), sdlutils().intConst().at("FenixRows"), sdlutils().intConst().at("FenixWidth"), sdlutils().intConst().at("FenixHeight"), 0, 0);
		break;
	case _twr_BULLET://Pasar rango, recarga, dano y si dispara
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
	case _twr_DIEGO://Rango, Probabilidad de critico, Dano por critico, Tiempo de recarga y Dano
		mngr_->addComponent<DiegoSniperTower>(t, sdlutils().floatConst().at("DiegoSniperRango"), sdlutils().floatConst().at("DiegoSniperCritProb1"), sdlutils().floatConst().at("DiegoSniperCritDano1"), sdlutils().floatConst().at("DiegoSniperRecarga"), sdlutils().intConst().at("DiegoSniperDano"));
		mngr_->addComponent<RenderComponent>(t, sniperTowerTexture);
		mngr_->addComponent<FramedImage>(t, sdlutils().intConst().at("DiegoSniperColumns"), sdlutils().intConst().at("DiegoSniperRows"), sdlutils().intConst().at("DiegoSniperWidth"), sdlutils().intConst().at("DiegoSniperHeight"), 0, 0);
		break;
	case _twr_SLIME:
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

