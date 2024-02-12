#include "Game.h"

void Game::start() {
	bool exit = false;
	auto& ihdlr = ih();
	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();
		ihdlr.refresh();
		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}
		current_state->update();
		Uint32 frameTime = sdlutils().currRealTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}