#include "CrystalTower.h"

CrystalTower::CrystalTower(int shieldVal, float timeToShield, int explosionDmg, float range): 
	shieldVal_(shieldVal), timeToShield_(timeToShield),explosionDmg_(explosionDmg), elapsedTime_(timeToShield), range_(range){}
