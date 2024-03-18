#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"

class MaestroAlmasComponent: public Component
{
public:
	static const cmpId id = cmpId::_MAESTROALMAS;
	MaestroAlmasComponent(float r) :ceguera_(true){  };
	void CiegaTorre(Entity* t);
private:
	float ceguera_;
};

