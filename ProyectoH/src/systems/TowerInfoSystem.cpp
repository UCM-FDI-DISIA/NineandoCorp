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
	//Button System
	auto bS = mngr_->getSystem<ButtonSystem>();

	/**
	*   -- BACKGROUND
	*/
	Vector2D bPos = Vector2D((float)sdlutils().width() / 2, (float)sdlutils().height() / 2);
	Vector2D bSize = Vector2D(sdlutils().width() / 1.5f, sdlutils().height() / 1.5f);
	bS->addImage(bPos, bSize, 180, gameTextures::large_box, grpId::_grp_HUD_FOREGROUND);

	/**
	*	-- EXIT BUTTON
	*/
	Vector2D eSize = Vector2D(70.0f, 70.0f);
	Vector2D ePos = Vector2D(bPos.getX() + bSize.getX() / 2 - eSize.getX() , bPos.getY() - bSize.getY() / 2 + eSize.getY() );
	bS->addButton(ePos, eSize, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

}

void TowerInfoSystem::receive(const Message& m)
{
}
