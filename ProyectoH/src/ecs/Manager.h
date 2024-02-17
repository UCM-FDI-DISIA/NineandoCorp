#pragma once
#include <vector>
#include <array>
#include "ecs.h"
#include "System.h"
#include "Entity.h"


class Manager {
private:
	std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;
	std::array<Entity*, maxHdlrId> hdlrs_;
	std::array<System*, maxSystemId> sys_; 
	std::vector<Message> msgs_;
	std::vector<Message> aux_msgs_;

public:
	Manager();
	virtual ~Manager();
	Entity* addEntity(grpId_type gId = _grp_GENERAL);
	void refresh();
	void update();
	/*void render();
	void handleInput();*/
	inline void setHandler(hdlrId_type hId, Entity* e) {
		hdlrs_[hId] = e;
	}
	inline Entity* getHandler(hdlrId_type hId) {
		return hdlrs_[hId];
	}

	// Components
	template<typename T, typename ...Ts>
	inline T* addComponent(Entity* e, Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);
		constexpr cmpId_type cId = T::id;
		removeComponent<T>(e);
		e->currCmps_.push_back(c);
		e->cmps_[cId] = c;
		c->setContext(e, this);
		c->initComponent();
		return c;
	}
	template<typename T>
	inline void removeComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		if (e->cmps_[cId] != nullptr) {
			auto iter = std::find(e->currCmps_.begin(),
									e->currCmps_.end(),
									e->cmps_[cId]);
			e->currCmps_.erase(iter);
			delete e->cmps_[cId];
			e->cmps_[cId] = nullptr;
		}
	}
	template<typename T>
	inline bool hasComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return e->cmps_[cId] != nullptr;
	}
	template<typename T>
	inline T* getComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return static_cast<T*>(e->cmps_[cId]);
	}
	// Entities
	inline void setAlive(Entity* e, bool alive) {
		e->alive_ = alive;
	}
	inline bool isAlive(Entity* e) {
		return e->alive_;
	}
	inline grpId_type groupId(Entity* e) {
		return e->gId_;
	}
	// Systems
	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&... args) {
		constexpr sysId_type sId = T::id;
		removeSystem<T>();
		System* s = new T(std::forward<Ts>(args)...);
		s->setContext(this);
		s->initSystem();
		sys_[sId] = s;
		return static_cast<T*>(s);
	}

	template<typename T>
	inline T* getSystem() {
		constexpr sysId_type sId = T::id;
		return static_cast<T*>(sys_[sId]);
	}

	template<typename T>
	inline void removeSystem() {
		constexpr sysId_type sId = T::id;
		if (sys_[sId] != nullptr) {
			delete sys_[sId];
			sys_[sId] = nullptr;
		}
	}

	inline void send(const Message& m, bool delay = false) {
		if (!delay) {
			for (System* s : sys_) {
				if (s != nullptr)
					s->receive(m);
			}
		}
		else {
			msgs_.emplace_back(m);
		}
	}
	
	inline void flushMessages() {
		std::swap(msgs_, aux_msgs_);
		for (auto& m : aux_msgs_) {
			for (System* s : sys_) {
				if (s != nullptr)
					s->receive(m);
			}
		}
		aux_msgs_.clear();
	}

	const std::vector<Entity*>& getEntities(grpId_type gId = _grp_GENERAL);
	void addToGroupList(grpId_type gId, Entity* e);
};

