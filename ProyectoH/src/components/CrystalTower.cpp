#include "CrystalTower.h"

CrystalTower::CrystalTower(int shieldVal, float timeToShield, int explosionDmg): 
	shieldVal_(shieldVal), timeToShield_(timeToShield),explosionDmg_(explosionDmg){}

void CrystalTower::levelUp(int level) {
	switch (level) {
	case 1:
		setShieldVal(getShieldVal()+50);
		break;
	case 2:
		setShieldVal(getShieldVal() + 50);
		break;
	case 3:
		setShieldVal(getShieldVal() + 50);
		break;
	case 4:
		isMaxLevel_ = true;
		break;
	default:
		break;
	}
}