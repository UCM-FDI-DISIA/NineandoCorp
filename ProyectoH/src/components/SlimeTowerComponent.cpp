#include "SlimeTowerComponent.h"

SlimeTowerComponent::SlimeTowerComponent(float range, float slimeDuration, float speedDecreasePer, float slimeDPS, float reloadTime)
	: AttackComponent::AttackComponent(range, reloadTime, slimeDPS, true), slimeDuration_(slimeDuration), speedDecreasePer_(speedDecreasePer){}


float SlimeTowerComponent::getSpeedDecrease() const { return speedDecreasePer_; }

float SlimeTowerComponent::getDuration() const { return slimeDuration_; }

void SlimeTowerComponent::setSlimeDuration(float duration) { slimeDuration_ = duration; }

void SlimeTowerComponent::setSpeedDecrease(float percentage) { speedDecreasePer_ = percentage; }