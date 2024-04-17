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
	bool getPotenciado() const { return potenciado_; }

	void setPotenciadora(Entity* src) { srcPotencia_ = src; }
	Entity* getSrcPotencia() const { return srcPotencia_; }

	void setConfundido(bool c, float t) { confundido_ = c; timeConfused_ = t; }
	bool getConfundido() const { return confundido_; }
private:
	bool cegado_;
	bool potenciado_;
	Entity* srcPotencia_;
	float tiempoCegado_;
	float elapsed_;
	bool confundido_;
	float timeConfused_;
};

