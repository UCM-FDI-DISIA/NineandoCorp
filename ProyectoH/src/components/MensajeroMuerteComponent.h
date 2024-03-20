#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
class MensajeroMuerteComponent : public Component
{
public:
	static const cmpId id = cmpId::_MENSAJEROMUERTE;
	MensajeroMuerteComponent() :fantasma_(true) {};
	void changeGroup();
private:
	bool fantasma_;
};

