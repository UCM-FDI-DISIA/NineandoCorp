#pragma once
#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

class LimitedTime : public Component
{
public:
	static const cmpId id = cmpId::_LIMITEDTIME;

	LimitedTime(double time = 0) : liveTime_(time), currTime_(0){}
	~LimitedTime() {
	}
	inline void addTime(double t) { liveTime_ += t; }

	double getLifeTime() { return liveTime_; }
	double getCurrTime() { return currTime_; }

	void setCurrTime(double time) { currTime_ = time; }
	void update() {
		currTime_ += game().getDeltaTime();
		if (currTime_ > liveTime_) {
			mngr_->setAlive(ent_, false);
			currTime_ = 0;
		}
	}
	inline void initComponent() override {
		//currTime_ = sdlutils().virtualTimer().currTime();
	}
private:
	double liveTime_;
	double currTime_;
};

