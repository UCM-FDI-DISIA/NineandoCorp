#pragma once
#include "..//ecs/Component.h"

class ParticleLifeTime : public Component
{
public:
	static const cmpId id = cmpId::_P_TIME;

	ParticleLifeTime(int iterations) : iters_(iterations){}
	int getIters() { return iters_; }
private:
	int iters_;
};


