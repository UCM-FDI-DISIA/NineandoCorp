#include "GameOverState.h"
#include "../systems/GameOverSystem.h" 
#include "../systems/RenderSystem.h" 
#include "../systems/ButtonSystem.h" 

GameOverState::GameOverState(int currentLvl, bool winner) : GameState(_gmStt_LEVELSELECTOR) {
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_GAMEOVER);
	mngr_->addSystem<GameOverSystem>();
}

GameOverState::~GameOverState() {

}
