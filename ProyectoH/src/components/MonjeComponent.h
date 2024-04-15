
#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
class MonjeComponent : public Component
{
public:
	static const cmpId id = cmpId::_MONJE;
	MonjeComponent(float reloadTime, float ultiTime):reloadTime_(reloadTime),ultiTime_(ultiTime), devuelve(false), elapsedTime_(0.0f), elapsedTime2_(0.0f) {};

	void setReloadTime(float time) { reloadTime_ = time; };
	void setElapsedTime(float elapsed) { elapsedTime_ = elapsed; };
	void setElapsedTime2(float elapsed2) { elapsedTime2_ = elapsed2; };
	void setDevuelve(bool t) { devuelve = t; }

	float getReloadTime()const { return reloadTime_; }
	float getUltiTime()const { return ultiTime_; }
	float getElapsedTime()const { return elapsedTime_; }
	float getElapsedTime2()const { return elapsedTime2_; }
	bool getDevuelve()const { return devuelve; }

private:
	float reloadTime_;
	float ultiTime_;
	float elapsedTime_;
	float elapsedTime2_;

	bool devuelve;
};
