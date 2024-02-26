#include "PlayState.h"
#include "../game/Game.h"


PlayState::PlayState() : GameState(_gmStt_PLAY) {
	// Sistemas requeridos para que funcione el juego

	//mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");
	//Entity* t = new Entity(_grp_TOWERS);
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	mngr_->addComponent<AttackComponent>(t, 1000.0f, 2.0f, 30, true);
	mngr_->addComponent<RenderComponent>(t, towerTexture);
	Transform * tr = mngr_->addComponent<Transform>(t);
	mngr_->addSystem<TowerSystem>();
	tr->setPosition({ 10,10 });
	mngr_->addSystem<RenderSystem>();

	Entity* e = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	mngr_->addComponent<RenderComponent>(e, towerTexture);
	mngr_->setHandler(_hdlr_ENEMIES, e);
	Transform* tr2 = mngr_->addComponent<Transform>(e);
	HealthComponent* h = mngr_->addComponent<HealthComponent>(e, 100.0f);
	
	tr2->setPosition({ 100,100 });
}

void PlayState::update() {
	GameState::update();
}