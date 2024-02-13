#pragma once

#include "ecs.h"
class System {
public:
	virtual ~System() { }
	void setContext(Manager* mngr) {
		mngr_ = mngr;
	}
	virtual void initSystem() { }
	virtual void update() { }
	virtual void receive(const Message& m) { }

protected:
	Manager* mngr_;
};

