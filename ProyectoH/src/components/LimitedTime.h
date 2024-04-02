#pragma once
#include "../ecs/Component.h"
#include "../ecs/Manager.h"

class LimitedTime : public Component
{
public:
	static const cmpId id = cmpId::_LIMITEDTIME;

	LimitedTime(int time = 0) : liveTime_(time) {}
	~LimitedTime() {
	}
	inline void addTime(int t) { liveTime_ += t; }


	void update() {
		if (sdlutils().virtualTimer().currTime() > currTime_ + liveTime_) {
			mngr_->setAlive(ent_, false);
		}
	}
	inline void initComponent() override {
		currTime_ = sdlutils().virtualTimer().currTime();
	}
private:
	int liveTime_;
	int currTime_;
};

