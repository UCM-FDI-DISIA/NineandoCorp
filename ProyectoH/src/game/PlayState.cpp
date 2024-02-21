#include "PlayState.h"
#include "../game/Game.h"
#include "..//components/Transform.h"
#include "..//components/RouteComponent.h"
#include "..//components/MovementComponent.h"
#include<vector>

PlayState::PlayState() : GameState(_gmStt_PLAY) {
	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<RenderSystem>();
	
	
	Vector2D a = { 300,200 };
	Vector2D b = { 700,300 };
	Vector2D c = { 400,500 };

	vector<Vector2D>v = { a,b,c };
	mngr_->addComponent<Transform>(enemy);
	mngr_->addComponent<RouteComponent>(enemy,v);
	mngr_->addComponent<MovementComponent>(enemy);
	mngr_->addComponent<RenderComponent>(enemy,square);
	RouteComponent* rc = mngr_->getComponent<RouteComponent>(enemy);
	MovementComponent* mc = mngr_->getComponent<MovementComponent>(enemy);
	rc->checkdestiny();
	mc->Move();
	//mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivelPrueba.tmx");
}

void PlayState::handleInput() {
	
}

void PlayState::update() {
	GameState::update();
	MovementComponent* mc = mngr_->getComponent<MovementComponent>(enemy);
	RouteComponent* rc = mngr_->getComponent<RouteComponent>(enemy);
	rc->checkdestiny();
	mc->Move();
	rc->checkdestiny();
	cout << *(mngr_->getComponent<Transform>(enemy)->getPosition());
}