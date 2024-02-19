#pragma once
#include "../ecs/Component.h"


class UpgradeTowerComponent : public Component
{
public:

	UpgradeTowerComponent(twrId id, int maxLevel);
	~UpgradeTowerComponent() {};

	void LevelUp();
	int getLevel() { return currentLevel_; }
	int getMaxLevel() { return maxLevel_; }

protected:
	twrId id_;
	int maxLevel_;
	int currentLevel_;
	//JSONValue* upgradeInfo_;
};
