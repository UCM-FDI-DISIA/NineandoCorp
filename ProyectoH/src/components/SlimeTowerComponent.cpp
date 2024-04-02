#include "SlimeTowerComponent.h"

SlimeTowerComponent::SlimeTowerComponent(float range, float slimeDuration, float speedDecreasePer, float slimeDPS, float reloadTime, float damage)
	: AttackComponent::AttackComponent(range, reloadTime, damage, true), slimeDuration_(slimeDuration), speedDecreasePer_(speedDecreasePer), slimeDPS_(slimeDPS) {}


float SlimeTowerComponent::getSpeedDecrease() const { return speedDecreasePer_; }

float SlimeTowerComponent::getDuration() const { return slimeDuration_; }

float SlimeTowerComponent::getDPS() const { return slimeDPS_; }

void SlimeTowerComponent::setDPS(float dps) { slimeDPS_ = dps; }

void SlimeTowerComponent::setSlimeDuration(float duration) { slimeDuration_ = duration; }

void SlimeTowerComponent::setSpeedDecrease(float percentage) { speedDecreasePer_ = percentage; }