#include "SlimeBullet.h"

SlimeBullet::SlimeBullet(float slimeDuration, float speedDecreasePer, float slimeDPS) 
	: slimeDuration_(slimeDuration), speedDecreasePer_(speedDecreasePer), slimeDPS_(slimeDPS), elapsedTime_(1), elapsedDuration_(0) {}

float SlimeBullet::getSpeedDecrease() const { return speedDecreasePer_; }

float SlimeBullet::getDuration() const { return slimeDuration_; }

float SlimeBullet::getElapsedTime() const { return elapsedTime_; }

void SlimeBullet::setElapsedTime(float time) { elapsedTime_ = time; }

float SlimeBullet::getElapsedDuration() const { return elapsedDuration_; }

void SlimeBullet::setElapsedDuration(float time) { elapsedDuration_ = time; }

float SlimeBullet::getDPS() const { return slimeDPS_; }