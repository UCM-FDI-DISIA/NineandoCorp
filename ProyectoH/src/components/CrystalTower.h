#pragma once
#include "..//ecs/Component.h"

class CrystalTower : public Component
{
public:
	static const cmpId id = cmpId::_ATTACK;
	CrystalTower(int shieldVal, float timeToShield, int explosionDmg);
	void levelUp(int level);

	int getShieldVal() { return shieldVal_; }
	float getTimeToShield() { return timeToShield_; }
	float getElapsedTime() { return elapsedTime_; }
	int getExplosionDmg() { return explosionDmg_; }

	void setShieldVal(int val) { shieldVal_ = val; }
	void setTimeToShield(float time) {  timeToShield_ = time; }
	void setExplosionDmg(int dmg) {  explosionDmg_ = dmg; }
	void setElapsedTime(float time) { elapsedTime_ = time; }

private:
	int shieldVal_;
	float timeToShield_;
	float elapsedTime_ = 0.0f;
	int explosionDmg_;
	bool isMaxLevel_ = false;
};

