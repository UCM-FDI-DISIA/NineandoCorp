#include "TowerInfoSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

TowerInfoSystem::~TowerInfoSystem()
{
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_INFO)) {
		mngr_->setAlive(en, false);
	}
	mngr_->refresh();
	mngr_->deleteAllHandlers(_hdlr_BUTTON_INFO);
}

void TowerInfoSystem::initSystem()
{
	auto bS = mngr_->getSystem<ButtonSystem>();
	bS->addImage({ 300.0f, 300.0f },
		{ 200.0f, 200.0f },
		0, gameTextures::box, grpId::_grp_HUD_BACKGROUND);
}

void TowerInfoSystem::receive(const Message& m)
{
}
