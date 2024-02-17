#pragma once
#include "../ecs/Component.h"


class UpgradeTowerComponent : public Component
{
public:

	UpgradeTowerComponent(twrId id, int maxLevel) : id_(id), maxLevel_(maxLevel), currentLevel_(0) {};
	~UpgradeTowerComponent() {};

	void LevelUp();
	int getLevel() { return currentLevel_; }
	int getMaxLevel() { return maxLevel_; }


protected:
	twrId id_;
	int maxLevel_;
	int currentLevel_;
};

