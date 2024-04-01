#include "CollisionSystem.h"
#include "..//components/SlimeBullet.h"
#include "..//components/TowerStates.h"
#include "../game/Game.h"

CollisionSystem::CollisionSystem():fenixRects_(), slimeRects_(), enemyRects_() {

}

CollisionSystem::~CollisionSystem() {
	fenixRects_.clear();
	slimeRects_.clear();
	enemyRects_.clear();
}

void CollisionSystem::initSystem() {

}

void CollisionSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ADD_RECT:
		addRect(m.rect_data.rect, m.rect_data.id);
		break;
	case _m_REMOVE_RECT:
		removeRect(m.rect_data.rect, m.rect_data.id);
	}
}

void CollisionSystem::addRect(Entity* rect, rectId id) {
	switch (id) {
		case _FENIX:
			fenixRects_.push_back(rect);
			break;
		case _SLIME:
			slimeRects_.push_back(rect);
			break;
		case _ENEMY:
			enemyRects_.push_back(rect);
			break;
		case _METEORITE:
			meteoriteRects_.push_back(rect);
			break;
		case _THUNDER:
			thunderRects_.push_back(rect);
			break;
		case _EARTHQUAKE:
			earthquakeRects_.push_back(rect);
			break;
		case _TORNADO:
			tornadoRects_.push_back(rect);
			break;
		default:
			break;
	}
}

void CollisionSystem::removeRect(Entity* rect, rectId id) {
	switch (id) {
	case _FENIX:
		fenixRects_.erase(find(fenixRects_.begin(), fenixRects_.end(), rect));
		mngr_->setAlive(rect, false);
		break;
	case _SLIME:
		slimeRects_.erase(find(slimeRects_.begin(), slimeRects_.end(), rect));
		break;
	case _ENEMY:
		enemyRects_.erase(find(enemyRects_.begin(), enemyRects_.end(), rect));
		break;
	case _THUNDER:
		thunderRects_.erase(find(thunderRects_.begin(), thunderRects_.end(), rect));
		break;
	case _METEORITE:
		meteoriteRects_.erase(find(meteoriteRects_.begin(), meteoriteRects_.end(), rect));
		break;
	case _EARTHQUAKE:
		earthquakeRects_.erase(find(earthquakeRects_.begin(), earthquakeRects_.end(), rect));
		break;
	case _TORNADO:
		tornadoRects_.erase(find(tornadoRects_.begin(), tornadoRects_.end(), rect));
		break;
	}
	
}

void CollisionSystem::update() {
	const float timeInterval = 0.25f;
	const auto& slimes = mngr_->getEntities(_grp_AREAOFATTACK);
	const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);
	const auto& lowTowers = mngr_->getHandler(_hdlr_LOW_TOWERS);
	const auto& highTowers = mngr_->getHandler(_hdlr_HIGH_TOWERS);

	for (const auto& er : enemies) {
		SDL_Rect enemyRect = mngr_->getComponent<Transform>(er)->getRect();
		
		for (const auto& fr : fenixRects_) {
			if (mngr_->isAlive(fr)) {
				
				Transform* fenixTR = mngr_->getComponent<Transform>(fr);
				SDL_Rect fenixRect;
				if(fenixTR!=nullptr) fenixRect = fenixTR->getRect();
				SDL_bool col = SDL_HasIntersection(&fenixRect, &enemyRect);
				FireComponent* fc = mngr_->getComponent<FireComponent>(fr);

				if (fc != nullptr) {
					if (!mngr_->isAlive(fc->getMyTower()))removeRect(fr, _FENIX);
					float dps = fc->getDamage();
					fc->setElapsedTime(fc->getElapsedTime() + game().getDeltaTime());
					if (fc->getElapsedTime() > 1.0f) {
						if (col) {
							Message m;
							m.id = _m_ENTITY_TO_ATTACK;
							m.entity_to_attack.e = er;
							m.entity_to_attack.src = fr;
							m.entity_to_attack.damage = dps;
							mngr_->send(m);
						}
						fc->setElapsedTime(0);
					}
				}
			}
						
		}	

		for (const auto& mt : meteoriteRects_) {//meteoritos-enemigos
			if (mngr_->isAlive(er)) {
				Transform* meteoriteTR = mngr_->getComponent<Transform>(mt);
				SDL_Rect meteoriteRect;
				if (meteoriteTR != nullptr) meteoriteRect = meteoriteTR->getRect();
				if (SDL_HasIntersection(&meteoriteRect, &enemyRect)) {
					Message m;
					m.id = _m_ENTITY_TO_ATTACK;
					m.entity_to_attack.e = er;
					m.entity_to_attack.src = mt;
					m.entity_to_attack.damage = 5;
					mngr_->send(m);
				}
			}
		}

		for (const auto& t : tornadoRects_) {//meteoritos-enemigos
			if (mngr_->isAlive(er)) {
				Transform* tornadoTR = mngr_->getComponent<Transform>(t);
				SDL_Rect tornadoRect;
				if (tornadoTR != nullptr) tornadoRect = tornadoTR->getRect();
				if (SDL_HasIntersection(&tornadoRect, &enemyRect)) {
					Message m;
					m.id = _m_CHANGE_ROUTE;
					m.change_route.enemy = er;
					mngr_->send(m);
				}
			}
		}

		for (const auto& th : thunderRects_) {//rayos-enemigos
			if (mngr_->isAlive(er)) {
				Transform* thunderTR = mngr_->getComponent<Transform>(th);
				SDL_Rect thunderRect;
				bool active = mngr_->hasComponent<Transform>(th);
				if (active) thunderRect = thunderTR->getRect();
				if (active && SDL_HasIntersection(&thunderRect, &enemyRect)) {
					Message m;
					m.id = _m_ENTITY_TO_ATTACK;
					m.entity_to_attack.e = er;
					m.entity_to_attack.src = th;
					m.entity_to_attack.damage = 5;
					mngr_->send(m);
				}
			}	
		}
		//thunderRects_.clear();
		

		for (const auto& eq : earthquakeRects_) {//terremoto-enemigos
			if (mngr_->isAlive(er)) {
				Transform* earthquakeTR = mngr_->getComponent<Transform>(eq);
				SDL_Rect earthquakeRect;
				if (earthquakeTR != nullptr) earthquakeRect = earthquakeTR->getRect();
				if (SDL_HasIntersection(&earthquakeRect, &enemyRect)) {
					Message m;
					m.id = _m_DECREASE_SPEED;
					m.decrease_speed.e = er;
					m.decrease_speed.slowPercentage = 0.7f;
					mngr_->send(m);
				}
			}
			
		}

		for (const auto& sr : slimes) {
			
			SlimeBullet* sb = mngr_->getComponent<SlimeBullet>(sr);	
			if (sb != nullptr) {
				
				sb->setElapsedTime(sb->getElapsedTime() + game().getDeltaTime());
				if (sb->getElapsedTime() > timeInterval) {
					sb->setElapsedTime(0);
					SDL_Rect slime = mngr_->getComponent<Transform>(sr)->getRect();
					if (SDL_HasIntersection(&slime, &enemyRect)) {
						Message m;
						m.id = _m_ENTITY_TO_ATTACK;
						m.entity_to_attack.e = er;
						m.entity_to_attack.src = sr;
						m.entity_to_attack.damage = sb->getDPS() / timeInterval;
						mngr_->send(m);
						Message m1;
						m1.id = _m_DECREASE_SPEED;
						m1.decrease_speed.e = er;
						m1.decrease_speed.slowPercentage = sb->getSpeedDecrease();
						mngr_->send(m1);
					}
				}
				sb->setElapsedDuration(sb->getElapsedDuration() + game().getDeltaTime());
				if (sb->getElapsedDuration() > sb->getDuration()) { 
					Message m;
					m.id = _m_RESET_SPEED;
					m.reset_speed.speed = 0.0f;
					mngr_->send(m);
					mngr_->setAlive(sr, false); 
					//removeRect(sr, _SLIME);
				}
			}				
		}
	}

	for (const auto& t : lowTowers)
	{
		SDL_Rect towerRect = mngr_->getComponent<Transform>(t)->getRect();

		for (const auto& th : thunderRects_) {//rayos-torres
			if (mngr_->isAlive(t)) {
				Transform* thunderTR = mngr_->getComponent<Transform>(th);
				SDL_Rect thunderRect;
				if (thunderTR != nullptr) thunderRect = thunderTR->getRect();
				auto towerState = mngr_->getComponent<TowerStates>(t);
				if (SDL_HasIntersection(&thunderRect, &towerRect)) {
					Message m;
					m.id = _m_TOWER_TO_ATTACK;
					m.tower_to_attack.e = t;
					m.tower_to_attack.damage = 5;
					mngr_->send(m);
					if (towerState != nullptr) {
						towerState->setCegado(true, 5.0f);//Ciega
					}
				}
			}
		}
		for (const auto& mt : meteoriteRects_) {//meteoritos-torres
			if (mngr_->isAlive(t)) {
				Transform* meteoriteTR = mngr_->getComponent<Transform>(mt);
				SDL_Rect meteoriteRect;
				if (meteoriteTR != nullptr) meteoriteRect = meteoriteTR->getRect();
				if (SDL_HasIntersection(&meteoriteRect, &towerRect)) {
					if (mngr_->hasComponent<FireComponent>(t)) {//Potencia si es torre fenix
						auto f = mngr_->getComponent<FireComponent>(t);
						f->setDamage(f->getBaseDamage() + 20.0);
					}
					Message m;
					m.id = _m_TOWER_TO_ATTACK;
					m.tower_to_attack.e = t;
					m.tower_to_attack.damage = 5;
					mngr_->send(m);
					
				}
			}
		}
		for (const auto& eq : earthquakeRects_) {//terremoto-torres
			if (mngr_->isAlive(t)) {
				Transform* earthquakeTR = mngr_->getComponent<Transform>(eq);
				SDL_Rect earthquakeRect;
				if (earthquakeTR != nullptr) earthquakeRect = earthquakeTR->getRect();
				if (SDL_HasIntersection(&earthquakeRect, &towerRect)) {
					Message m;
					m.id = _m_TOWER_TO_ATTACK;
					m.tower_to_attack.e = t;
					m.tower_to_attack.damage = 5;
					mngr_->send(m);
				}
			}
		}

	}

	//if(thunderRects_.size() > 0)thunderRects_.clear();
}

