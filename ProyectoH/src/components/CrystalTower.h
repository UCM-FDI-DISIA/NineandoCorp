#pragma once
#include "..//ecs/Component.h"

class CrystalTower : public Component
{
public:
	static const cmpId id = cmpId::_CRISTALTOWER;
	CrystalTower(int shieldVal, float timeToShield, int explosionDmg, float range);

	int getShieldVal() const { return shieldVal_; }
	float getTimeToShield() const { return timeToShield_; }
	float getElapsedTime() const { return elapsedTime_; }
	int getExplosionDmg() const { return explosionDmg_; }
	bool isMaxLevel() const { return isMaxLevel_; }
	float getRange() const { return range_; }

	void setShieldVal(int val) { shieldVal_ = val; }
	void setTimeToShield(float time) {  timeToShield_ = time; }
	void setExplosionDmg(int dmg) {  explosionDmg_ = dmg; }
	void setElapsedTime(float time) { elapsedTime_ = time; }

private:
	int shieldVal_;//Valor del escudo; como los puntos de vida
	float timeToShield_;//Tiempo para actualizar el escudo
	float elapsedTime_;
	float range_;
	int explosionDmg_;//Dano del escudo; para la mejora maxima
	bool isMaxLevel_ = false;
};

