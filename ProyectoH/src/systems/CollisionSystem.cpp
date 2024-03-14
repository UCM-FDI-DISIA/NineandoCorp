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
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	case _m_ADD_RECT:
		addRect(m.rect_data.rect, m.rect_data.id);
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

void CollisionSystem::update() {
	const float timeInterval = 1.0f;
	const auto& slimes = mngr_->getEntities(_grp_AREAOFATTACK);
	const auto& enemies = mngr_->getHandler(_hdlr_ENEMIES);
	for (const auto& er : enemies) {
		SDL_Rect enemy = mngr_->getComponent<Transform>(er)->getRect();
		/*for (const auto& fr : fenixRects_) {
			SDL_Rect fenix = mngr_->getComponent<Transform>(fr)->getRect();
			SDL_bool col = SDL_HasIntersection(&fenix, &enemy);
			float dps = mngr_->getComponent<PhoenixTower>(fr)->getDamage();

			if (col) {
				Message m;
				m.id = _m_ENTITY_TO_ATTACK;
				m.entity_to_attack.e = er;
				m.entity_to_attack.src = fr;
				m.entity_to_attack.damage = dps;
				mngr_->send(m);
			}
		}	*/

		for (const auto& sr : slimes) {
			
			SlimeBullet* sb = mngr_->getComponent<SlimeBullet>(sr);	
			if (sb != nullptr) {
				sb->setElapsedTime(sb->getElapsedTime() + game().getDeltaTime());
				if (sb->getElapsedTime() > timeInterval) {
					SDL_Rect slime = mngr_->getComponent<Transform>(sr)->getRect();
					if (SDL_HasIntersection(&slime, &enemy)) {
						Message m;
						m.id = _m_ENTITY_TO_ATTACK;
						m.entity_to_attack.e = er;
						m.entity_to_attack.src = sr;
						m.entity_to_attack.damage = sb->getDPS();
						mngr_->send(m);
					}
				}
				sb->setElapsedDuration(sb->getElapsedDuration() + game().getDeltaTime());
				if (sb->getElapsedDuration() > sb->getDuration()) { mngr_->setAlive(sr, false); }
			}				
		}
	}	
}

