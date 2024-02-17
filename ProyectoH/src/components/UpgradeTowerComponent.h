#pragma once
#include "../ecs/Component.h"
#include "..//..//resources/config/tower_upgrade_info.json"
#include "../json/JSON.h"
#include <fstream>

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

