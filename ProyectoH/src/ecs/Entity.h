#pragma once
#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
#include <array>
#include <vector>
#include "Component.h"

#ifdef Version_1_0
#include "Manager.h"
#elif defined(Version_2_0)
class Manager;
#endif

class Entity {
private:
	bool alive_;
	std::vector<Component*> currCmps_;
	std::array<Component*, maxComponentId> cmps_;

#ifdef Version_1_0
	Manager* mngr_;

#elif defined(Version_2_0)
	friend Manager;
	grpId_type gId_;
#endif

public:

#ifdef Version_1_0
	Entity() : mngr_(nullptr), cmps_(), currCmps_(), alive_() {
		currCmps_.reserve(maxComponentId);
	}
	inline void setContext(Manager* mngr) { mngr_ = mngr; }

#elif defined(Version_2_0)
	Entity(grpId_type gId) : gId_(gId), cmps_(), alive_() {
		currCmps_.reserve(maxComponentId);
	}
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

#endif
	virtual ~Entity() {
		for (auto c : currCmps_) {
			delete c;
		}
	}
#ifdef Version_1_0
	inline bool isAlive() { return alive_; }
	inline void setAlive(bool alive) { alive_ = alive; }
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);
		removeComponent<T>();
		currCmps_.push_back(c);
		cmps_[T::id] = c;
		c->setContext(this, mngr_);
		c->initComponent();
		return c;
	}
	template<typename T>
	inline void removeComponent() {
		if (cmps_[T::id] != nullptr) {
			auto iter = std::find(currCmps_.begin(),
				currCmps_.end(),
				cmps_[T::id]);
			currCmps_.erase(iter);
			delete cmps_[T::id];
			cmps_[T::id] = nullptr;
		}
	}
	template<typename T>
	inline T* getComponent() {
		return static_cast<T*>(cmps_[T::id]);
	}
	template<typename T>
	inline bool hasComponent() {
		return cmps_[T::id] != nullptr;
	}
#endif
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