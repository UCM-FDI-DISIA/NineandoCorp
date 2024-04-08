#pragma once
#include "../ecs/Component.h"


class UpgradeTowerComponent : public Component
{
public:
	static const cmpId id = cmpId::_UPGRADETOWER;

	UpgradeTowerComponent() : id_(), maxLevel_(1), currentLevel_(1) {}
	UpgradeTowerComponent(twrId id, int maxLevel);
	~UpgradeTowerComponent() {};

	void levelUp();
	int getLevel() const { return currentLevel_; }
	int getMaxLevel() { return maxLevel_; }
	twrId id_;

protected:
	int maxLevel_;
	int currentLevel_;

	//cuanto cuesta la mejora actual
	int upgradeCost_;
	//JSONValue* upgradeInfo_;
};

