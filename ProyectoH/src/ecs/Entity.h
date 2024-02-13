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
	inline void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->update();
	}
	inline void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->render();
	}
	inline void handleInput() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->handleInput();
	}
};


#endif // !ENTITY_H_