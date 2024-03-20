#include "BlindComponent.h"

BlindComponent::BlindComponent(bool blinded, float timer) 
	: 
	blinded_(blinded), blindTime_(timer)
{

}

void BlindComponent::setBlind(bool blind) { blinded_ = blind; }

void BlindComponent::setBlindTime(float time) { blindTime_ = time; }
