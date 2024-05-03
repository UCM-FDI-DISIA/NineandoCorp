#include "GameOverState.h"
#include "../systems/GameOverSystem.h" 
#include "../systems/RenderSystem.h" 
#include "../systems/ButtonSystem.h" 

GameOverState::GameOverState(int rounds, int enemies, int coinsH ,int currentLvl, bool winner) : GameState(_gmStt_LEVELSELECTOR) {
	mngr_->addSystem<RenderSystem>();
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_GAMEOVER);
	mngr_->addSystem<GameOverSystem>();

	Message m;
	m.id = _m_OVER_GAME;
	m.over_game.winner = winner; // false, ha perdido. true, ha ganado
	m.over_game.currentLvl = currentLvl;
	m.over_game.coinsH = coinsH;
	m.over_game.rounds = rounds;
	m.over_game.enemies = enemies;
	mngr_->send(m);

	// MUSICA
	sdlutils().musics().at("Soundtrack").haltMusic();
}

GameOverState::~GameOverState() {
	delete mngr_;
}
