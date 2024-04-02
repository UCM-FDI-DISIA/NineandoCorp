#include "Manager.h"

Manager::Manager() :
	hdlrs_(), entsByGroup_() {
	sys_.fill(nullptr);
	for (auto& groupEntities : entsByGroup_) {
		groupEntities.reserve(100);
	}
}
Manager::~Manager() {
	for (auto& ents : entsByGroup_) {
		for (auto e : ents)
			delete e;
	}
	for (auto& system : sys_) {
		delete system;
		system = nullptr;
	}
}

Entity* Manager::addEntity(grpId_type gId) {
	Entity* e = new Entity(gId);
	setAlive(e, true);
	entsByGroup_[gId].push_back(e);
	return e;
}

void Manager::refresh() {
	for (grpId_type gId = 0; gId < maxGroupId; gId++) {
		auto& grpEnts = entsByGroup_[gId];
		grpEnts.erase(
			std::remove_if(grpEnts.begin(), grpEnts.end(),
				[](Entity* e) {
					if (e->alive_) {
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

std::vector<Entity*>& Manager::getEntities(grpId_type gId) {
	return entsByGroup_[gId];
}

void Manager::update() {
	for (auto& syst : sys_) {
		if (syst != nullptr) syst->update();
	}
}

void Manager::addToGroupList(grpId_type gId, Entity* e) {
	entsByGroup_[gId].push_back(e);
}