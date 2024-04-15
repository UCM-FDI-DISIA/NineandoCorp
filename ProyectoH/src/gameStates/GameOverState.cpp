#include "GameOverState.h"
#include "../systems/GameOverSystem.h" 
#include "../systems/RenderSystem.h" 
#include "../systems/ButtonSystem.h" 

GameOverState::GameOverState(int coinsH, bool* enemiesSaw, int currentLvl, bool winner) : GameState(_gmStt_LEVELSELECTOR) {
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<GameOverSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_ENEMYBOOK);
}

GameOverState::~GameOverState() {

}
