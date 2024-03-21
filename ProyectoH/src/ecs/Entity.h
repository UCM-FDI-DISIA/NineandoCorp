#pragma once
#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
#include <array>
#include <vector>
#include "Component.h"

class Manager;

class Entity {
private:
	bool alive_;
	std::vector<Component*> currCmps_;
	std::array<Component*, maxComponentId> cmps_;

	friend Manager;
	grpId_type gId_;

public:
	Entity(grpId_type gId) : gId_(gId), cmps_(), alive_() {
		currCmps_.reserve(maxComponentId);
	}
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	virtual ~Entity() {
		for (auto c : currCmps_) {
			delete c;
		}
	}

	inline void changegId(grpId_type gId) {
		gId_ = gId;
	}
	
};


#endif // !ENTITY_H_