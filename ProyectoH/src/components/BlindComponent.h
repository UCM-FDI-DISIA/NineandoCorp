#pragma once
#include "..//ecs/Component.h"

class BlindComponent : public Component
{
public:
	BlindComponent(bool blinded, float timer);
	void setBlind(bool blind);
	void setBlindTime(float time);
	float getBlindTime() { return blindTime_; };

private:
	bool blinded_;
	float blindTime_;
};