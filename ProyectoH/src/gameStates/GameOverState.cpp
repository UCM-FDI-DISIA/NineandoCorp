#include "GameOverState.h"
#include "../systems/GameOverSystem.h" 
#include "../systems/RenderSystem.h" 
#include "../systems/ButtonSystem.h" 

GameOverState::GameOverState(int currentLvl, bool winner) : GameState(_gmStt_LEVELSELECTOR) {
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_GAMEOVER);
	mngr_->addSystem<GameOverSystem>();

	Message m;
	m.id = _m_OVER_GAME;
	m.over_game.winner = winner; // false, ha perdido. true, ha ganado
	m.over_game.currentLvl = currentLvl;
	mngr_->send(m);
}

GameOverState::~GameOverState() {

}
