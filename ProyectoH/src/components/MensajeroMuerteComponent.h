#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
class MensajeroMuerteComponent : public Component
{
public:
	static const cmpId id = cmpId::_MENSAJEROMUERTE;
	MensajeroMuerteComponent() :fantasma_(true) {};
	void changeGroup(hdlrId_type h);

	void setDetectable(bool d) { fantasma_ = d; }

	bool getDetectable() const { return fantasma_; }

	bool Detect(const std::list<Entity*>& g);

private:
	bool fantasma_;
};



