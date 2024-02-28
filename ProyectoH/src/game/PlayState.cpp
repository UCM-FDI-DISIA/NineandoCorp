#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() : GameState(_gmStt_PLAY) {
	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");
	TowerSystem* ts = mngr_->addSystem<TowerSystem>();
	ts->addTower(_twr_BULLET, { 550.0f,550.0f }, LOW);

	Entity* e2 = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	Transform* t = mngr_->addComponent<Transform>(e2);
	t->setPosition({ 500,500 });
	t->setVelocity({20,-20});
	mngr_->addComponent<HealthComponent>(e2, 10.0f);
	//mngr_->addComponent<MovementComponent>(e2);
	//std::vector<Vector2D> routes;
	//routes.push_back({ 600, 600 });
	//mngr_->addComponent<RouteComponent>(e2, routes);
	mngr_->addComponent<RenderComponent>(e2, square);
	mngr_->setHandler(_hdlr_ENEMIES, e2);

	Entity* e3 = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
	Transform* t2 = mngr_->addComponent<Transform>(e3);
	t2->setPosition({ 600,600 });
	t2->setVelocity({ 20,-20 });
	mngr_->addComponent<HealthComponent>(e3, 10.0f);
	//mngr_->addComponent<MovementComponent>(e3);
	//mngr_->addComponent<RouteComponent>(e2, routes);
	mngr_->addComponent<RenderComponent>(e3, square);
	mngr_->setHandler(_hdlr_ENEMIES, e3);

	//mngr_->addSystem<EnemySystem>();
}

void PlayState::update() {
	GameState::update();
	//mngr_->getComponent<MovementComponent>(*(mngr_->getHandler(_hdlr_ENEMIES).begin()))->update();
}