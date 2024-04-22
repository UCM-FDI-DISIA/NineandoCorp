#pragma once
#include "../ecs/Component.h"


class UpgradeTowerComponent : public Component
{
public:
	static const cmpId id = cmpId::_UPGRADETOWER;

	UpgradeTowerComponent(int upCost) : id_(), maxLevel_(1), currentLevel_(1), upgradeCost_(upCost) {}
	UpgradeTowerComponent(twrId id, int maxLevel, int upCost, int initialCost);
	void initComponent() override;
	~UpgradeTowerComponent() {};

	void levelUp();
	int getLevel() const { return currentLevel_; }
	int getMaxLevel() const { return maxLevel_; }
	twrId id_;
	bool isMaxLeveled() const { return currentLevel_ == maxLevel_; }

	inline int getUpgradeCost() const { return upgradeCost_; }
	inline int getAcumCost() const { return acumCost_; }
private:
	int maxLevel_;
	int currentLevel_;
	//cuanto cuesta la mejora actual
	int upgradeCost_;
	int acumCost_;
	//JSONValue* upgradeInfo_;
};

