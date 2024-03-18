#include "CrystalTower.h"

CrystalTower::CrystalTower(int shieldVal, float timeToShield, int explosionDmg): 
	shieldVal_(shieldVal), timeToShield_(timeToShield),explosionDmg_(explosionDmg), elapsedTime_(timeToShield){}

void CrystalTower::levelUp(int level) {
	switch (level) {
	case 1:
		setShieldVal(getShieldVal()+ sdlutils().floatConst().at("CristalEscudo1"));
		break;
	case 2:
		setShieldVal(getShieldVal() + sdlutils().floatConst().at("CristalEscudo1"));
		break;
	case 3:
		setShieldVal(getShieldVal() + sdlutils().floatConst().at("CristalEscudo1"));
		break;
	case 4:
		isMaxLevel_ = true;
		break;
	default:
		break;
	}
}