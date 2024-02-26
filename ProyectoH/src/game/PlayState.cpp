#include "PlayState.h"
#include "../game/Game.h"
#include "..//components/Transform.h"
#include "..//components/RouteComponent.h"
#include "..//components/MovementComponent.h"
#include<vector>

PlayState::PlayState() : GameState(_gmStt_PLAY) {
	// Sistemas requeridos para que funcione el juego
	mngr_->setHandler(_hdlr_ENEMIES, enemy);

	mngr_->addSystem<RenderSystem>();
	
	
	Vector2D a = { 300,200 };
	Vector2D b = { 700,300 };
	Vector2D c = { 400,500 };

	vector<Vector2D>v = { a,b,c };
	mngr_->addComponent<Transform>(enemy);
	mngr_->addComponent<RouteComponent>(enemy,v);
	mngr_->addComponent<MovementComponent>(enemy);
	mngr_->addComponent<RenderComponent>(enemy,square);
	mngr_->addSystem<EnemySystem>();
}

void PlayState::handleInput() {
	
}

void PlayState::update() {
	GameState::update();

}