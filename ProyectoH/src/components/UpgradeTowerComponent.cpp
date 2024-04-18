#include "UpgradeTowerComponent.h"
#include "../ecs/Manager.h"
#include "../components/BulletTower.h"
#include "..//components/EnhancerTower.h"
#include "..//components/CrystalTower.h"
#include "..//components/RenderComponent.h"
#include "..//components/DiegoSniperTower.h"
#include "..//components/PhoenixTower.h"
#include "..//components/DirtTower.h"
#include "..//components/SlimeTowerComponent.h"
#include "../components/TowerComponent.h"

using namespace std;

UpgradeTowerComponent::UpgradeTowerComponent(twrId id, int maxLevel, int upCost,int initCost) : 
	id_(id), //
	maxLevel_(maxLevel), //
	currentLevel_(1), //
	acumCost_(initCost), //
	upgradeCost_(upCost) {
}

void UpgradeTowerComponent::levelUp() {
	

	auto fi = mngr_->getComponent<FramedImage>(ent_);
	if (currentLevel_ < maxLevel_) {

		Message m;
		m.id = _m_ADD_MONEY;
		m.money_data.money = -upgradeCost_;
		std::cout << "COSTE DE MEJORA: " << upgradeCost_ << std::endl;
		mngr_->send(m);
		//Suma al contador de dinero acumulado el coste de la mejora actual
		acumCost_ += upgradeCost_;
		//Aumenta un 75% el dinero que cuesta 
		upgradeCost_ += upgradeCost_ * 0.75;

		mngr_->getComponent<TowerComponent>(ent_)->increaseSellMoney();

		fi->setCurrentFrame(fi->getCurrentFrame() + 1);
		auto tr = mngr_->getComponent<Transform>(ent_);
		//Vector de ajuste debido al desplazamiento causado por el spritesheet
		Vector2D adjustOffset = Vector2D(3.0f * currentLevel_, 0);

		tr->setPosition(*tr->getPosition() - adjustOffset);
		currentLevel_++;

		if (currentLevel_ == 0) { currentLevel_ = 1; }

		auto bt = mngr_->getComponent<BulletTower>(ent_);
		auto ct = mngr_->getComponent<CrystalTower>(ent_);
		auto st = mngr_->getComponent<SlimeTowerComponent>(ent_);
		auto ds = mngr_->getComponent<DiegoSniperTower>(ent_);
		auto ft = mngr_->getComponent<PhoenixTower>(ent_);
		auto pt = mngr_->getComponent<EnhancerTower>(ent_);
		auto dt = mngr_->getComponent<DirtTower>(ent_);
		auto h = mngr_->getComponent<HealthComponent>(ent_);

		h->setMaxHealth(h->getMaxHealth() + sdlutils().intConst().at("UpgradeLife"));
		h->resetHealth();

		switch (id_) {
		case _twr_BULLET:
			switch (currentLevel_) {
			case 2:
				bt->setDamage(sdlutils().intConst().at("BalasDano1"));
				break;
			case 3:
				bt->setDamage(sdlutils().intConst().at("BalasDano2"));
				break;
			case 4:
				bt->setDamage(sdlutils().intConst().at("BalasDano3"));
				break;
			default:
				break;
			}
			break;
		case _twr_CRISTAL:
			ct->setShieldVal(ct->getShieldVal() + sdlutils().floatConst().at("CristalEscudo1"));
			break;
		case _twr_SLIME:

			switch (currentLevel_) {
			case 2:
				st->setTimeToShoot(st->getTimeToShoot() - sdlutils().floatConst().at("SlimeRecargaUpdate"));
				break;
			case 3:
				st->setSpeedDecrease(sdlutils().floatConst().at("SlimeRalentizacion"));
				break;
			case 4:
				st->setSlimeDuration(st->getDuration() - sdlutils().floatConst().at("SlimeTiempoSlime"));
				break;
			default:
				break;
			}
			break;
		case _twr_DIEGO:

			switch (currentLevel_) {
			case 2:
				ds->setDamage(sdlutils().intConst().at("DiegoSniperDano1"));
				ds->setCritDamage(sdlutils().floatConst().at("DiegoSniperCritDano1"));
				ds->setCritProb(sdlutils().floatConst().at("DiegoSniperCritProb1"));
				break;
			case 3:
				ds->setTimeToShoot(ds->getTimeToShoot() - sdlutils().floatConst().at("DiegoSniperRecargaUpdate1"));
				break;
			case 4:
				ds->setCritProb(sdlutils().floatConst().at("DiegoSniperCritProb2"));
				ds->setTimeToShoot(ds->getTimeToShoot() - sdlutils().floatConst().at("DiegoSniperRecargaUpdate1"));
				break;
			default:
				break;
			}
			break;
		case _twr_FENIX:

			switch (currentLevel_) {
			case 2:
				ft->setDamage(sdlutils().floatConst().at("FenixDPS1"));
				ft->setCooling(sdlutils().floatConst().at("FenixEnfriamiento1"));
				break;
			case 3:
				ft->setDamage(sdlutils().floatConst().at("FenixDPS2"));
				ft->setCooling(sdlutils().floatConst().at("FenixEnfriamiento2"));
				break;
			case 4:
				ft->setCooling(sdlutils().floatConst().at("FenixEnfriamientoCero"));
				//Falta anadir la opcion de aumentar el rango del fuego
				break;
			default:
				break;
			}
			break;
		case _twr_CLAY:

			h->setMaxHealth(sdlutils().floatConst().at("ArcillaVida" + to_string((int)currentLevel_ - 1)));
			h->resetHealth();
			break;
		case _twr_POWER:

			switch (currentLevel_) {
			case 2:
				pt->setDamageIncreasePercentage(sdlutils().floatConst().at("PotenciadoraDano1"));
				pt->setTowersHPboost(sdlutils().floatConst().at("PotenciadoraAumentoVida"));
				break;
			case 3:
				pt->setDamageIncreasePercentage(sdlutils().floatConst().at("PotenciadoraDano2"));
				break;
			case 4:
				pt->setDamageIncreasePercentage(sdlutils().floatConst().at("PotenciadoraDano3"));
				pt->setTowersHPboost(sdlutils().floatConst().at("PotenciadoraVida2"));
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}