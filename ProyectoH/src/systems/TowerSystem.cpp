#include "TowerSystem.h"
#include "..//ecs/ecs.h"
#include "..//components/SlimeBullet.h"
#include "..//components/ShieldComponent.h"
#include "..//components/TowerStates.h"
#include "../components/InteractiveTower.h"


TowerSystem::TowerSystem() : mActive(true) {
}

TowerSystem::~TowerSystem() {
	towers.clear();
}

void TowerSystem::initSystem() {
	mActive = true;
}

void TowerSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_WAVE_START:
		cameraOffset_ = m.start_game_data.cameraOffset;
		break;
	case _m_ENTITY_TO_ATTACK://Mandado por el enemySystem al atacar una torre
		if(m.entity_to_attack.targetId == _hdlr_LOW_TOWERS)onAttackTower(m.entity_to_attack.e, m.entity_to_attack.damage);
		break;
	case _m_ADD_TOWER:
		addTower(m.add_tower_data.towerId, m.add_tower_data.pos, m.add_tower_data.height);
		break;
	case _m_TOWER_CLICKED:
		addTowerToInteract(m.tower_clicked_data.tower);
		break;
	case _m_PAUSE:
		mActive = !mActive;
		break;
	default:
		break;
	}
}

void TowerSystem::clearShieldsArea(Entity* e) {
	CrystalTower* eh = mngr_->getComponent<CrystalTower>(e);
	if (eh != nullptr) {
		Vector2D myPos = mngr_->getComponent<Transform>(e)->getPosition();
		for (auto& tower : towers)
		{
			Vector2D towerPos = mngr_->getComponent<Transform>(tower)->getPosition();
			float distance = sqrt(pow(towerPos.getX() - myPos.getX(), 2) + pow(towerPos.getY() - myPos.getY(), 2));//distancia a la torre
			if (distance < eh->getRange()) {//En rango
				ShieldComponent* s = mngr_->getComponent<ShieldComponent>(tower);
				s->setShield(0.0);
				if(s->getImg() != NULL)mngr_->setAlive(s->getImg(), false);
			}
		}
	}
}

void TowerSystem::createShieldExplosion(Vector2D pos) {
	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.idGrp = _grp_TOWERS_AND_ENEMIES;
	m.anim_create.animSpeed = 20;
	m.anim_create.iterationsToDelete = 1;
	m.anim_create.pos = pos;
	m.anim_create.frameInit = 0;
	m.anim_create.frameEnd = 70;
	m.anim_create.cols = 10;
	m.anim_create.rows = 8;
	m.anim_create.scale = { 500, 500 };
	m.anim_create.width = 100;
	m.anim_create.height = 100;
	m.anim_create.tex = gameTextures::shieldExp;
	mngr_->send(m);
}

void TowerSystem::createBulletExplosion(Vector2D pos) {
	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.idGrp = _grp_TOWERS_AND_ENEMIES;
	m.anim_create.animSpeed = 8;
	m.anim_create.iterationsToDelete = 1;
	m.anim_create.pos = pos;
	m.anim_create.frameInit = 0;
	m.anim_create.frameEnd = 7;
	m.anim_create.cols = 4;
	m.anim_create.rows = 2;
	m.anim_create.scale = { 80, 80 };
	m.anim_create.width = 167;
	m.anim_create.height = 180;
	m.anim_create.tex = gameTextures::bulletExplosion;
	mngr_->send(m);
}


void TowerSystem::onAttackTower(Entity* e, int dmg) {
	if (e != nullptr && mngr_->isAlive(e)) {
		HealthComponent* h = mngr_->getComponent<HealthComponent>(e);
		ShieldComponent* s = mngr_->getComponent<ShieldComponent>(e);
		
		
		if (s->getShield() <= 0 && h->getHealth() - dmg <= 0) {		
			eliminateDestroyedTowers(e);
			//std::cout << "Torre eliminada-TorresTotales: " << towers.size() << std::endl;
			mngr_->deleteHandler(_hdlr_LOW_TOWERS, e);
			clearShieldsArea(e);
			h->subtractHealth(dmg);		 
		}
		else {
			if(s->getShield() > 0 && s->getShield() - dmg <= 0 ){ 
				
				Transform* t = mngr_->getComponent<Transform>(e);				
				if(t != nullptr){ createShieldExplosion(*(t->getPosition())); }
				if(s->getImg() != NULL)mngr_->setAlive(s->getImg(), false);
			}
			s->subtractShield((float)dmg);
		}	
	}
}
//Realiza las funcionalidades de las torres, accediendo a los atributos de los componentes y realizando la mecanica de cada torre
void TowerSystem::update() {
	if (mActive) {

		const auto& bullets = mngr_->getEntities(_grp_BULLETS);

		float health = 0;
		Entity* targetMostHP = nullptr;
		for (const auto& enemy : mngr_->getHandler(_hdlr_ENEMIES))
		{

			if (mngr_->isAlive(enemy)) {
				HealthComponent* h = mngr_->getComponent<HealthComponent>(enemy);
				if (h != nullptr) {//se guarda la referencia al enemigo con mas vida
					if (h->getHealth() > health) {
						targetMostHP = enemy;
						health = h->getHealth();
					}
				}
			}
		}

		if (towersToInteract.size() > 0) {
			auto tower = getFrontTower();
			Message m;
			m.id = _m_SHOW_UPGRADE_TOWER_MENU;
			auto upgrdCmp = mngr_->getComponent<UpgradeTowerComponent>(tower);
			m.show_upgrade_twr_menu_data.cLevel = upgrdCmp->getLevel();
			m.show_upgrade_twr_menu_data.tId = upgrdCmp->id_;
			m.show_upgrade_twr_menu_data.pos = mngr_->getComponent<Transform>(tower)->getPosition();
			mngr_->send(m);

			towersToInteract.clear();
		}


		// Updates de torre interactiva / comprueba si se ha clicado la torre
		for (auto& t : towers) {
			auto iTwr = mngr_->getComponent<InteractiveTower>(t);
			if (iTwr != nullptr) {
				iTwr->update();
			}
		}


		for (auto& t : towers) {
			Transform* TR = mngr_->getComponent<Transform>(t);
			TowerStates* tw = mngr_->getComponent<TowerStates>(t);

			if (tw->getCegado()) {//si esta cegada
				tw->setElapsed(tw->getElapsed() + game().getDeltaTime());
				IconComponent* ic = mngr_->getComponent<IconComponent>(t);
				if (ic == nullptr)	ic = mngr_->addComponent<IconComponent>(t, _BLINDED);//Agregarselo si no lo tiene
				if (ic->getIconType() == _BLINDED) {
					if (!ic->hasIcon()) {//Crearlo si no lo tiene
						Entity* icon = mngr_->addEntity(_grp_ICONS);
						mngr_->addComponent<RenderComponent>(icon, blindedIcon);
						Transform* tr = mngr_->addComponent<Transform>(icon);
						Transform* targetTR = mngr_->getComponent<Transform>(t);
						tr->setPosition(*(targetTR->getPosition()));
						tr->setScale(*(targetTR->getScale()) / 4);

						ic->setHasIcon(true);
						ic->setIcon(icon);
					}
				}
				if (tw->getElapsed() > tw->getCegado()) {
					if (ic != nullptr && ic->hasIcon() && ic->getIconType() == _BLINDED) {//Eliminarlo si no se encuentra en la distancia
						ic->setHasIcon(false);
						mngr_->setAlive(ic->getIcon(), false);
					}
					tw->setCegado(false, 0.0);
					tw->setElapsed(0.0);
				}
			}
			else {
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
						IconComponent* ic = mngr_->getComponent<IconComponent>(towers[i]);
						if (distance <= et->getRange() && towers[i] != t) {//enRango
							//std::cout << "Potenciada: " << i << std::endl;						
							if (ic == nullptr)	ic = mngr_->addComponent<IconComponent>(towers[i], _POWERUP);//Agregarselo si no lo tiene
							if (ic->getIconType() == _POWERUP) {
								if (!ic->hasIcon()) {//Crearlo si no lo tiene
									Entity* icon = mngr_->addEntity(_grp_ICONS);
									mngr_->addComponent<RenderComponent>(icon, powerIcon);
									Transform* tr = mngr_->addComponent<Transform>(icon);
									Transform* targetTR = mngr_->getComponent<Transform>(towers[i]);
									tr->setPosition(*(targetTR->getPosition()));
									tr->setScale(*(targetTR->getScale()) / 4);

									ic->setHasIcon(true);
									ic->setIcon(icon);
								}
							}
							DiegoSniperTower* ac = mngr_->getComponent<DiegoSniperTower>(towers[i]);
							if (ac != nullptr) {
								ac->setDamage(ac->getBaseDamage() * (1 + et->getDamageIncreasePercentage()));
							}//incrementamos daño
							HealthComponent* h = mngr_->getComponent<HealthComponent>(towers[i]);
							if (h != nullptr) { h->setMaxHealth(h->getBaseHealth() + et->getTowersHPboost()); }//incrementamos vida
						}
						else if (ic != nullptr && ic->hasIcon() && ic->getIconType() == _POWERUP) {//Eliminarlo si no se encuentra en la distancia
							ic->setHasIcon(false);
							mngr_->setAlive(ic->getIcon(), false);
						}					
					}
				}
				//Cada cierto tiempo targetea a un enemigo y le dispara, cambiando su imagen en funci�n de la direcci�n del disparo
				BulletTower* bt = mngr_->getComponent<BulletTower>(t);
				if (bt != nullptr) {
					Vector2D offset{ floatAt("DiegoSniperOffset"),  floatAt("DiegoSniperOffset") };//Offset para el punto de spawn de la bala
					int valFrame = 0;//Valor del frame que se ha de escoger del spritesheet para renderizar la torre en la direccion correcta
					bt->setElapsedTime(bt->getElapsedTime() + game().getDeltaTime());
					if (bt->getElapsedTime() > 0.5) {

						bt->targetEnemy(mngr_->getHandler(_hdlr_ENEMIES));
						bt->setElapsedTime(0);
						if (bt->getTarget() != nullptr) {
							//Se coge el vector de la torre al objetivo, y en funcion de su direccion en los dos ejes se escoje el frame para la torre y 
							//el punto desde el que sale la bala, que debe ser el canon de la torre. Para eso se usa el offset
							Vector2D dir = *(mngr_->getComponent<Transform>(bt->getTarget())->getPosition()) - *(TR->getPosition());
							if (dir.getX() >= 0 && dir.getY() >= 0) { valFrame = 4; offset.setX(floatAt("DiegoSniperOffset") * 2.5); }
							else if (dir.getX() >= 0 && dir.getY() < 0) { valFrame = 12; offset.setY(0); offset.setX(floatAt("DiegoSniperOffset") * 2.5); }
							else if (dir.getX() < 0 && dir.getY() >= 0) { offset.setX(0); }
							else if (dir.getX() < 0 && dir.getY() < 0) { valFrame = 8; offset.setX(0); offset.setY(0); }
							mngr_->getComponent<FramedImage>(t)->setCurrentFrame(valFrame + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
							Vector2D spawn = { TR->getPosition()->getX() + offset.getX(),	TR->getPosition()->getY() + offset.getY() };//Punto de spawn de la bala con el offset
							shootBullet(bt->getTarget(), t, bt->getDamage(), floatAt("BalasVelocidad"), spawn, bulletTexture, { 35, 35 }, _twr_BULLET);//Dispara la bala
							createBulletExplosion(spawn + Vector2D(-10, -20));
						}
						if (bt->isMaxLevel()) {//Mejora maxima de la torre de balas: targetear a un segundo enemigo. Funciona igual que el primer targeteo
							bt->targetSecondEnemy(mngr_->getHandler(_hdlr_ENEMIES));
							if (bt->getSecondTarget() != nullptr) {
								;

								Vector2D dir = *(mngr_->getComponent<Transform>(bt->getSecondTarget())->getPosition()) - *(TR->getPosition());
								if (dir.getX() >= 0 && dir.getY() >= 0) { valFrame = 4; offset.setX(floatAt("DiegoSniperOffset") * 2.5); }
								else if (dir.getX() >= 0 && dir.getY() < 0) { valFrame = 12; offset.setY(0); offset.setX(floatAt("DiegoSniperOffset") * 2.5); }
								else if (dir.getX() < 0 && dir.getY() >= 0) { offset.setX(0); }
								else if (dir.getX() < 0 && dir.getY() < 0) { valFrame = 8; offset.setX(0); offset.setY(0); }
								shootBullet(bt->getSecondTarget(), t, bt->getDamage(), floatAt("BalasVelocidad"), TR->getPosition(), bulletTexture, { 35, 35 }, _twr_BULLET);
								createBulletExplosion(TR->getPosition());
								//mngr_->getComponent<FramedImage>(t)->setCurrentFrame(valFrame + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());


							}
						}

					}
				}

				//Cada cierto tiempo manda un mensaje con info del escudo para el nexo y la explosion si esta al nivel maximo
				CrystalTower* ct = mngr_->getComponent<CrystalTower>(t);
				if (ct != nullptr) {
					ct->setElapsedTime(ct->getElapsedTime() + game().getDeltaTime());
					if (ct->getElapsedTime() > ct->getTimeToShield()) {
						Vector2D myPos = TR->getPosition();
						for (auto& tower : towers)
						{
							Vector2D towerPos = mngr_->getComponent<Transform>(tower)->getPosition();
							float distance = sqrt(pow(towerPos.getX() - myPos.getX(), 2) + pow(towerPos.getY() - myPos.getY(), 2));//distancia a la torre
							if (distance < ct->getRange()) {//En rango
								ShieldComponent* s = mngr_->getComponent<ShieldComponent>(tower);
								if (s->getShield() <= 0) {
									s->setImg(addShield(*(mngr_->getComponent<Transform>(tower)->getPosition()) + Vector2D(20, 0)));//añade el escudo visible y lo asigna al shieldComponent
								}
								s->setMaxShield((float)ct->getShieldVal());
								s->setShield((float)s->getMaxShield());//Regenera escudos
							}
						}
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
							Vector2D offset{ floatAt("DiegoSniperOffset"),  floatAt("DiegoSniperOffset") };
							int valFrame = 0;
							Vector2D dir = *(mngr_->getComponent<Transform>(st->getTarget())->getPosition()) - *(TR->getPosition());
							if (dir.getX() >= 0 && dir.getY() >= 0) { valFrame = 4; offset.setX(floatAt("DiegoSniperOffset") * 3.5); }
							else if (dir.getX() >= 0 && dir.getY() < 0) { valFrame = 12; offset.setY(0); offset.setX(floatAt("DiegoSniperOffset") * 3.5); }
							else if (dir.getX() < 0 && dir.getY() >= 0) { offset.setX(0); }
							else if (dir.getX() < 0 && dir.getY() < 0) { valFrame = 8; offset.setX(0); offset.setY(0); }
							mngr_->getComponent<FramedImage>(t)->setCurrentFrame(valFrame + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
							RenderComponent* rc = mngr_->getComponent<RenderComponent>(t);
							Vector2D spawn = { TR->getPosition()->getX() + offset.getX(),	TR->getPosition()->getY() + offset.getY() };
							Entity* bullet = shootBullet(st->getTarget(), t, st->getDamage(), floatAt("SlimeVelocidad"), spawn, slimeBulletTexture, { 25, 25 }, _twr_SLIME);
							mngr_->addComponent<SlimeBullet>(bullet, st->getDuration(), st->getSpeedDecrease(), st->getDPS());
							st->setElapsedTime(0);
						}
					}
				}

				//Cada cierto tiempo dispara al enemigo que tiene mas vida que esta en rango, 
				//con el dano de critico anadido. Falta que haga el critico en funcion de una probabilida
				DiegoSniperTower* ds = mngr_->getComponent<DiegoSniperTower>(t);
				if (ds != nullptr) {
					ds->setElapsedTime(ds->getElapsedTime() + game().getDeltaTime());//Lo pasa a segundos
					if (ds->getElapsedTime() > ds->getTimeToShoot()) {//si esta cargada busca enemigo con mas vida								
						if (targetMostHP != nullptr) {//Dispara con el critico
							Vector2D offset{ floatAt("DiegoSniperOffset"),  floatAt("DiegoSniperOffset") };
							int valFrame = 0;
							Vector2D dir = *(mngr_->getComponent<Transform>(targetMostHP)->getPosition()) - *(TR->getPosition());
							if (dir.getX() >= 0 && dir.getY() >= 0) { valFrame = 4; offset.setX(floatAt("DiegoSniperOffset") * 3.5); }
							else if (dir.getX() >= 0 && dir.getY() < 0) { valFrame = 12; offset.setY(0); offset.setX(floatAt("DiegoSniperOffset") * 3.5); }
							else if (dir.getX() < 0 && dir.getY() >= 0) { offset.setX(0); }
							else if (dir.getX() < 0 && dir.getY() < 0) { valFrame = 8; offset.setX(0); offset.setY(0); }
							mngr_->getComponent<FramedImage>(t)->setCurrentFrame(valFrame + mngr_->getComponent<UpgradeTowerComponent>(t)->getLevel());
							RenderComponent* rc = mngr_->getComponent<RenderComponent>(t);
							Vector2D spawn = { TR->getPosition()->getX() + offset.getX(),	TR->getPosition()->getY() + offset.getY() };

							shootBullet(targetMostHP, t, ds->getDamage() * ds->getCritDamage(), floatAt("DiegoSniperVelocidad"), spawn, sniperBulletTexture, { 25, 20 }, _twr_DIEGO);
							createBulletExplosion(spawn + Vector2D(-10, -20));
						}
						ds->setElapsedTime(0);
					}
					if (!mngr_->isAlive(t)) { eliminateDestroyedTowers(t); };
				}

				PhoenixTower* pt = mngr_->getComponent<PhoenixTower>(t);
				if (pt != nullptr) {
					Vector2D spawn(TR->getPosition()->getX() - floatAt("FenixOffsetX"), TR->getPosition()->getY() - floatAt("FenixOffsetY"));
					pt->setElapsedTime(pt->getElapsedTime() + game().getDeltaTime());
					pt->targetEnemy(mngr_->getHandler(_hdlr_ENEMIES));
					Vector2D offset(0, 0);
					if (pt->getTarget() != nullptr) {
						Vector2D targetPos = *(mngr_->getComponent<Transform>(pt->getTarget())->getPosition());
						Vector2D dir = targetPos - spawn;
						dir = dir.normalize();

						if (dir.getY() < -0.5 && dir.getX() >= -1 && dir.getX() <= 1) { pt->setRotation(90.0f); }//Rotar el fuego en funcion de la posicion relativa del target
						else if (dir.getX() > 0.5 && dir.getY() <= 1 && dir.getY() >= -1) { pt->setRotation(180.0f); }
						else if (dir.getX() < -0.5 && dir.getY() >= -1 && dir.getY() <= 1) { pt->setRotation(0.0f); }
						else if (dir.getY() > 0.5 && dir.getX() >= -1 && dir.getX() <= 1) { pt->setRotation(270.0f); }
						if (pt->getFire() != nullptr) {
							Transform* fTR = mngr_->getComponent<Transform>(pt->getFire());
							fTR->setRotation(pt->getRotation());
						}
					}
					if (pt->getRotation() == 90.0f)offset = Vector2D(0.0f, 0.0f);//Ajuste del rect en funcion del angulo
					else if (pt->getRotation() == 180.0f) offset = Vector2D(65.0f, 60.0f);
					else if (pt->getRotation() == 0.0f)offset = Vector2D(-80.0f, 50.0f);
					else if (pt->getRotation() == 270.0f) offset = Vector2D(-15.0f, 90.0f);
					if (pt->getFire() != nullptr) {
						Transform* fTR = mngr_->getComponent<Transform>(pt->getFire());
						fTR->setPosition(Vector2D(spawn.getX() + offset.getX(), spawn.getY() + offset.getY()));
					}
					//std::cout << pt->getRotation() << "\n";
					if (pt->getElapsedTime() > pt->getCoolingTime() && !pt->isShooting()) {

						pt->setFire(shootFire(Vector2D(spawn.getX() + offset.getX(), spawn.getY() + offset.getY()), pt->getRotation(), pt->getDamage(), t));
						pt->setIsShooting(true);
						pt->setElapsedTime(0);
					}
					if (pt->isShooting() && pt->getElapsedTime() > pt->getShootingTime()) {
						if (pt->getFire() != nullptr)pt->removeFire();
						pt->setIsShooting(false);
						pt->setElapsedTime(0);
					}
				}
			}
		}
		//Mueve y dirige las balas, y destruye las balas si su objetivo muere o si choca con el objetivo, causandole dano
		for (auto& b : bullets) {
			Transform* t = mngr_->getComponent<Transform>(b);
			BulletComponent* bc = mngr_->getComponent<BulletComponent>(b);
			SlimeBullet* sb = mngr_->getComponent<SlimeBullet>(b);
			FramedImage* fi = mngr_->getComponent<FramedImage>(bc->getTarget());
			Transform* targetTR = mngr_->getComponent<Transform>(bc->getTarget());
			Vector2D targetPos = *(targetTR->getPosition());
			if (fi != nullptr) {
				Vector2D offset = { (float)fi->getSrcRect().w / 4, (float)fi->getSrcRect().h / 4 };//Se dirige hacia el centro del rect
				targetPos = targetPos + offset;
			}
			Vector2D myPos = *(t->getPosition());

			if (!mngr_->isAlive(bc->getTarget())) {//Si ha muerto por el camino
				bc->onTravelEnds();
			}
			else if (((targetPos - myPos).magnitude() <= 5.0f)) { //Si choca con el enemigo
				if (sb != nullptr) {
					Entity* area = mngr_->addEntity(_grp_AREAOFATTACK);
					Transform* tr = mngr_->addComponent<Transform>(area);
					Vector2D scale = { 250, 200 };
					tr->setScale(scale);
					Vector2D pos = { t->getPosition()->getX() - scale.getX() / 2, t->getPosition()->getY() - scale.getY() / 4 };
					tr->setPosition(pos);
					mngr_->addComponent<RenderComponent>(area, slimeArea);
					mngr_->addComponent<FramedImage>(area, 9, 1, 500, 400, 0, 4, 8);
					mngr_->addComponent<SlimeBullet>(area, sb->getDuration(), sb->getSpeedDecrease(), sb->getDPS());
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
}

void TowerSystem::eliminateDestroyedTowers(Entity* t) {//elimina del array las torres muertas
	towers.erase(find(towers.begin(), towers.end(), t));
}


Entity* TowerSystem::shootBullet(Entity* target, Entity* src ,float damage, float speed, Vector2D spawnPos, gameTextures texture, Vector2D bulletScale, twrId id) {
	Entity* bullet = mngr_->addEntity(_grp_BULLETS);//crea bala
	Transform* t = mngr_->addComponent<Transform>(bullet);//transform
	t->setPosition(spawnPos);
	t->setScale(bulletScale);
	mngr_->addComponent<BulletComponent>(bullet, t, target, src, damage, speed);//bullet component
	mngr_->addComponent<RenderComponent>(bullet, texture);//habra que hacer switch
	return bullet;
}

Entity* TowerSystem::shootFire(Vector2D spawnPos, float rot, float dmg, Entity* src) {
	Entity* fire = mngr_->addEntity(_grp_AREAOFATTACK);
	Transform* t = mngr_->addComponent<Transform>(fire);
	t->setPosition(spawnPos);
	t->setRotation(rot);
	mngr_->addComponent<RenderComponent>(fire, fireTexture);
	mngr_->addComponent<FramedImage>(fire, intAt("FireFrames"), 1, intAt("FireWidth"), intAt("FireHeight"), 0, intAt("FireFrames"), intAt("FireFrames"));
	mngr_->addComponent<FireComponent>(fire, dmg, rot, src);
	Message m;
	m.id = _m_ADD_RECT;
	m.rect_data.entity = fire;
	m.rect_data.id = _FENIX;
	mngr_->send(m);

	return fire;
}

Entity* TowerSystem::addShield(Vector2D pos) {
	auto ent = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	auto t = mngr_->addComponent<Transform>(ent);
	t->setScale({320, 165});
	t->setPosition(pos + Vector2D(-120, -10));
	mngr_->addComponent<RenderComponent>(ent, shield);
	mngr_->addComponent<FramedImage>(ent, 7, 1, 626, 352, 0, 5, 6);
	return ent;
}



void TowerSystem::addTower(twrId type,const Vector2D& pos, Height height) {
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);//Se a?ade al mngr
	Transform* tr = mngr_->addComponent<Transform>(t);//transform
	mngr_->addComponent<ShieldComponent>(t, 0);
	tr->setPosition(pos);
	mngr_->addComponent<TowerStates>(t);
	mngr_->addComponent<UpgradeTowerComponent>(t, type, 4);
	mngr_->addComponent<InteractiveTower>(t, cameraOffset_);
	float health = 100.0f;
	if (height == LOW) {
		mngr_->addComponent<HealthComponent>(t, health);
		mngr_->setHandler(_hdlr_LOW_TOWERS, t);
	}
	else mngr_->setHandler(_hdlr_HIGH_TOWERS, t);
	switch (type)
	{
	case _twr_FENIX://Dano, Enfriamiento, TiempoDisparo, Rango
		tr->setScale({ floatAt("FenixScaleX"), floatAt("FenixScaleY")});
 		mngr_->addComponent<PhoenixTower>(t, floatAt("FenixDano"), floatAt("FenixEnfriamiento"), floatAt("FenixTiempoDisparo"), floatAt("FenixRango"));
		mngr_->addComponent<RenderComponent>(t, phoenixTowerTexture);
		mngr_->addComponent<FramedImage>(t, intAt("FenixColumns"), intAt("FenixRows"), intAt("FenixWidth"), intAt("FenixHeight"), 3, 0);

		break;
	case _twr_BULLET://Pasar rango, recarga, da?o y si dispara
		tr->setScale({ floatAt("BulletScaleX"), floatAt("BulletScaleY") });
		mngr_->addComponent<BulletTower>(t, floatAt("BalasRango"), floatAt("BalasRecarga"), intAt("BalasDano"));
		mngr_->addComponent<RenderComponent>(t, bulletTowerTexture);
		mngr_->addComponent<FramedImage>(t, intAt("BalasColumns"), intAt("BalasRows"), intAt("BalasWidth"), intAt("BalasHeight"), 0, 0);
		break;
	case _twr_CLAY:
		tr->setScale({ floatAt("ClayScaleX"), floatAt("ClayScaleY") });
		mngr_->addComponent<DirtTower>(t);
		mngr_->addComponent<RenderComponent>(t, clayTowerTexture);
		mngr_->addComponent<FramedImage>(t, intAt("ArcillaColumns"), intAt("ArcillaRows"), intAt("ArcillaWidth"), intAt("ArcillaHeight"), 0, 0);
		break;
	case _twr_POWER://Pasar rango, porcentaje incremento de ataque y vida extra
		tr->setScale({ floatAt("PotenciadorScaleX"), floatAt("PotenciadorScaleY") });
		mngr_->addComponent<EnhancerTower>(t, floatAt("PotenciadoraRango"), floatAt("PotenciadoraAumentoDano"), floatAt("PotenciadoraAumentoVida"));
		mngr_->addComponent<RenderComponent>(t, boosterTowerTexture);
		mngr_->addComponent<FramedImage>(t, intAt("PotenciadoraColumns"), intAt("PotenciadoraRows"), intAt("PotenciadoraWidth"), intAt("PotenciadoraHeight"), 0, 0);
		break;
	case _twr_DIEGO://Rango, Probabilidad de critico, Dano por critico, Tiempo de recarga y Dano
		tr->setScale({ floatAt("SniperScaleX"), floatAt("SniperScaleY") });
		mngr_->addComponent<DiegoSniperTower>(t, floatAt("DiegoSniperRango"), floatAt("DiegoSniperCritProb1"), floatAt("DiegoSniperCritDano1"), floatAt("DiegoSniperRecarga"), intAt("DiegoSniperDano"));
		mngr_->addComponent<RenderComponent>(t, sniperTowerTexture);
		mngr_->addComponent<FramedImage>(t, intAt("DiegoSniperColumns"), intAt("DiegoSniperRows"), intAt("DiegoSniperWidth"), intAt("DiegoSniperHeight"), 0, 0);
		break;
	case _twr_SLIME:
		tr->setScale({ floatAt("SlimeScaleX"), floatAt("SlimeScaleY") });
		mngr_->addComponent<SlimeTowerComponent>(t, intAt("SlimeRango"), floatAt("SlimeTiempoSlime"), floatAt("SlimeRalentizacion"), intAt("SlimeDPS"), intAt("SlimeRecarga") ,intAt("SlimeDano"));
		mngr_->addComponent<RenderComponent>(t, slimeTowerTexture);
		mngr_->addComponent<FramedImage>(t, intAt("SlimeColumns"), intAt("SlimeRows"), intAt("SlimeWidth"), intAt("SlimeHeight"), 0, 0);

		break;
	case _twr_CRISTAL://Escudo, Tiempo de recarga y dano por explosion
		tr->setScale({ floatAt("CristalScaleX"), floatAt("CristalScaleY") });
		mngr_->addComponent<CrystalTower>(t, intAt("CristalEscudo"), floatAt("CristalRecarga"), intAt("CristalExplosion"), floatAt("CristalRango"));
		mngr_->addComponent<RenderComponent>(t, cristalTowerTexture);
		mngr_->addComponent<FramedImage>(t, intAt("CristalColumns"), intAt("CristalRows"), intAt("CristalWidth"), intAt("CristalHeight"), 0, 0);
		
		break;
	default:
		break;
	}
	towers.emplace_back(t);
	//std::cout << "Torre añadida: " << type << " TorresTotales: " << towers.size() << std::endl;
}
