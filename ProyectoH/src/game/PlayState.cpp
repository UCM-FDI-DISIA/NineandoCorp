#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {
	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");
	TowerSystem* ts = mngr_->addSystem<TowerSystem>();
	ts->addTower(BULLET, { 0,0 }, LOW);

	Entity* e2 = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	Transform* t = mngr_->addComponent<Transform>(e2);
	t->setPosition({ 100,100 });
	t->setVelocity({20,-20});
	mngr_->addComponent<HealthComponent>(e2, 10.0f);
	mngr_->addComponent<MovementComponent>(e2);
	mngr_->addComponent<RenderComponent>(e2, square);
	mngr_->setHandler(_hdlr_ENEMIES, e2);


}

void PlayState::update() {
	GameState::update();
	mngr_->getComponent<MovementComponent>(*(mngr_->getHandler(_hdlr_ENEMIES).begin()))->update();
}