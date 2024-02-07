#pragma once

#include "ecs.h"
#ifdef Version_2_0
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

#endif
