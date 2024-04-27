#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"

class EnemyStates : public Component
{
public:
	static const cmpId id = cmpId::_ENEMYSTATES;
	EnemyStates() :acelerado_(false), tiempoAcelerado_(0.0f), isHealing_(false) {};
	void setAcelerado(bool a, float t) { 
		acelerado_ = a; tiempoAcelerado_ = t; 
	};

	bool isHealing() { return isHealing_; }
	void setIsHealing(bool b) { isHealing_ = b; }

private:
	bool acelerado_;
	float tiempoAcelerado_;
	bool isHealing_;
};

