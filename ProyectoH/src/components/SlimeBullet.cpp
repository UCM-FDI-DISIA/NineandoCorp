#include "SlimeBullet.h"

SlimeBullet::SlimeBullet(float slimeDuration, float speedDecreasePer, float slimeDPS) : slimeDuration_(slimeDuration), speedDecreasePer_(speedDecreasePer), slimeDPS_(slimeDPS) {}

float SlimeBullet::getSpeedDecrease() const { return speedDecreasePer_; }

float SlimeBullet::getDuration() const { return slimeDuration_; }