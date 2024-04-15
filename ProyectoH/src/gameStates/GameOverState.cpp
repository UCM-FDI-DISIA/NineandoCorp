#include "GameOverState.h"
#include "../systems/GameOverSystem.h" 
#include "../systems/RenderSystem.h" 

GameOverState::GameOverState(int coinsH, bool* enemiesSaw, int currentLvl, bool winner) : GameState(_gmStt_LEVELSELECTOR) {
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<GameOverSystem>();
}

GameOverState::~GameOverState() {

}
