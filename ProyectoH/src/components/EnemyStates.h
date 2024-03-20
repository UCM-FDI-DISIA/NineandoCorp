#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
class EnemyStates : public Component
{
public:
	static const cmpId id = cmpId::_ENEMYSTATES;
	EnemyStates() :acelerado_(false), tiempoAcelerado_(0.0f){};
	void setAcelerado(bool a, float t) { 
		acelerado_ = a; tiempoAcelerado_ = t; 
	};

private:
	bool acelerado_;
	float tiempoAcelerado_;
};

