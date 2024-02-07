#include "Manager.h"

Manager::Manager() :
	hdlrs_(), entsByGroup_() {
#ifndef Version_1_0
	sys_.fill(nullptr);
#endif
	for (auto& groupEntities : entsByGroup_) {
		groupEntities.reserve(100);
	}
}
Manager::~Manager() {
	for (auto& ents : entsByGroup_) {
		for (auto e : ents)
			delete e;
	}
#ifdef Version_2_0
	for (auto& system : sys_) {
		delete system;
		system = nullptr;
	}
#endif
}

Entity* Manager::addEntity(grpId_type gId) {
#ifdef Version_1_0
	Entity* e = new Entity();
	e->setAlive(true);
	e->setContext(this);
#else
	Entity* e = new Entity(gId);
	setAlive(e, true);
#endif
	entsByGroup_[gId].push_back(e);
	return e;
}

void Manager::refresh() {
	for (grpId_type gId = 0; gId < maxGroupId; gId++) {
		auto& grpEnts = entsByGroup_[gId];
		grpEnts.erase(
			std::remove_if(grpEnts.begin(), grpEnts.end(),
				[](Entity* e) {
#ifdef Version_1_0
					if (e->isAlive()) {
#else
					if (e->alive_) {
#endif
						return false;
					}
					else {
						delete e;
						return true;
					}
				}),
			grpEnts.end());
	}
}

const std::vector<Entity*>& Manager::getEntities(grpId_type gId) {
	return entsByGroup_[gId];
}

void Manager::update() {
	for (auto& ents : entsByGroup_) {
		auto n = ents.size();
		for (auto i = 0u; i < n; i++)
			ents[i]->update();
	}
#ifdef Version_2_0
	for (auto& syst : sys_) {
		if (syst != nullptr) syst->update();
	}
#endif
}
void Manager::render() {
	for (auto& ents : entsByGroup_) {
		auto n = ents.size();
		for (auto i = 0u; i < n; i++)
			ents[i]->render();
	}
}
void Manager::handleInput() {
	for (auto& ents : entsByGroup_) {
		auto n = ents.size();
		for (auto i = 0u; i < n; i++)
			ents[i]->handleInput();
	}
}

void Manager::addToGroupList(grpId_type gId, Entity* e) {
	entsByGroup_[gId].push_back(e);
}