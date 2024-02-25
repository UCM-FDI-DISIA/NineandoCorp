#pragma once
class EnhancerTower
{
public:
	EnhancerTower();
	void levelUp(int level);
	float getTowersHPboost() const;
	float getDamageIncreasePercentage() const;
	void setTowersHPboost(float hp);
	void setDamageIncreasePercentage(float damage);
private:
	float towersHPboost_;
	float damageIncreasePercentage_;
	bool isMaxLevel_ = false;
};

