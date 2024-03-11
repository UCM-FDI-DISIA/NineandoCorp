#include "CollisionSystem.h"

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

	for (const auto& er : enemyRects_) {
		for (const auto& fr : fenixRects_) {
			SDL_Rect fenix = mngr_->getComponent<Transform>(fr)->getRect();
			SDL_Rect enemy = mngr_->getComponent<Transform>(er)->getRect();
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
		}	

		for (const auto& sr : slimeRects_) {
			SDL_Rect fenix = mngr_->getComponent<Transform>(sr)->getRect();
			SDL_Rect enemy = mngr_->getComponent<Transform>(er)->getRect();
			SDL_bool col = SDL_HasIntersection(&fenix, &enemy);

			if (col) {
				Message m;
				m.id = _m_ENTITY_TO_ATTACK;				
			}
		}
	}	
}

