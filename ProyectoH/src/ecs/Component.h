#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ecs.h"

#ifdef Version_1_0
class Component 
#else
struct Component 
#endif
{
protected:
	Entity* ent_;
	Manager* mngr_;
public: 
	Component() {}  
	virtual ~Component() {}
	inline void setContext(Entity* ent, Manager* mngr) {
		ent_ = ent;
		mngr_ = mngr;
	}
	virtual void initComponent() { }
	virtual void update() { }
	virtual void render() { }
	virtual void handleInput() { }
};
#endif