#include "CollisionSystem.h"
#include "..//components/SlimeBullet.h"
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
	}
}

void CollisionSystem::removeRect(Entity* rect, rectId id) {
	switch (id) {
	case _FENIX:
		fenixRects_.erase(find(fenixRects_.begin(), fenixRects_.end(), rect));
		break;
	case _SLIME:
		slimeRects_.erase(find(slimeRects_.begin(), slimeRects_.end(), rect));
		break;
	case _ENEMY:
		enemyRects_.erase(find(enemyRects_.begin(), enemyRects_.end(), rect));
		break;
	}
	mngr_->setAlive(rect, false);
}

void CollisionSystem::update() {
	const float timeInterval = 0.25f;
	const auto& slimes = mngr_->getEntities(_grp_AREAOFATTACK);
	const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);
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
				}
			}				
		}
	}	
}

