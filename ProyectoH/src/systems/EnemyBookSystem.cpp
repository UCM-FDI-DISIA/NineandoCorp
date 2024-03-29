#include "EnemyBookSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
EnemyBookSystem::EnemyBookSystem()
{
}
EnemyBookSystem::~EnemyBookSystem()
{
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_ENEMYBOOK)) {
		mngr_->setAlive(en, false);
	}
	mngr_->refresh();
	mngr_->deleteAllHandlers(_hdlr_BUTTON_ENEMYBOOK);
}
void EnemyBookSystem::initSystem() {
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	//BACKGROUND
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = { 1000.0f , 600.0f };
	bS->addImage(pAux, sAux, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	//boton cerrar
	pAux = pAux + Vector2D(430.0f, -230.0f);
	sAux = { 70.0f, 70.0f };
	bS->addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);
}
void EnemyBookSystem::receive(const Message& m)
{
}

void EnemyBookSystem::update() {
}