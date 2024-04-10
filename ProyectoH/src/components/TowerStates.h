#pragma once
#include "..//ecs/Component.h"
#include "..//ecs/Manager.h"
class TowerStates: public Component
{
public:
	static const cmpId id = cmpId::_TOWERSTATES;
	TowerStates() :cegado_(false), potenciado_(false),srcPotencia_(nullptr), tiempoCegado_(0.0f), elapsed_(0.0) {};
	void setCegado(bool e, float t) {
		cegado_ = e; tiempoCegado_ = t;
	}
	bool getCegado() const { return cegado_; };
	float getElapsed() const { return elapsed_; };
	void setElapsed(float time) { elapsed_ = time; };

	void setPotenciado(bool p) { potenciado_ = p; }
	bool getPotenciado() { return potenciado_; }

	void setPotenciadora(Entity* src) { srcPotencia_ = src; }
	Entity* getSrcPotencia() { return srcPotencia_; }
private:
	bool cegado_;
	bool potenciado_;
	Entity* srcPotencia_;
	float tiempoCegado_;
	float elapsed_;
};

