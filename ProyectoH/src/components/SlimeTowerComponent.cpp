#include "SlimeTowerComponent.h"

SlimeTowerComponent::SlimeTowerComponent(float range, float slimeDuration, float speedDecreasePer, float slimeDPS, float reloadTime, float damage)
	: AttackComponent::AttackComponent(range, reloadTime, damage, false), isMaxLevel_(false), slimeDuration_(slimeDuration), speedDecreasePer_(speedDecreasePer), slimeDPS_(slimeDPS) {}


float SlimeTowerComponent::getSpeedDecrease() const { return speedDecreasePer_; }

float SlimeTowerComponent::getDuration() const { return slimeDuration_; }

float SlimeTowerComponent::getDPS() const { return slimeDPS_; }

void SlimeTowerComponent::setDPS(float dps) { slimeDPS_ = dps; }

void SlimeTowerComponent::setSlimeDuration(float duration) { slimeDuration_ = duration; }

void SlimeTowerComponent::setSpeedDecrease(float percentage) { speedDecreasePer_ = percentage; }

void SlimeTowerComponent::levelUp(int level) {
	switch (level) {
		case 1:
			setTimeToShoot(getTimeToShoot()-sdlutils().floatConst().at("SlimeRecargaUpdate"));
			break;
		case 2:
			setSpeedDecrease(sdlutils().floatConst().at("SlimeRalentizacion"));
			break;
		case 3:
			setSlimeDuration(getDuration() - sdlutils().floatConst().at("SlimeTiempoSlime"));
			break;
		case 4:
			isMaxLevel_ = true;
			break;
		default:
			break;
	}
}