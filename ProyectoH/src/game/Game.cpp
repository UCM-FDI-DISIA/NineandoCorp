#include "Game.h"

// Destructor
Game::~Game() {
	delete gameStateMachine;
}
// Executes the game
void Game::run() {
	
	save.loadFile();
	pushState<MainMenuState>();

	Uint64 currentTime = SDL_GetPerformanceCounter();
	Uint64 startTime = 0;
	delay = 1.0f;
	// Ocultar el cursor predeterminado de SDL
	SDL_ShowCursor(SDL_DISABLE);
	while (!exit) {
		ih().refresh();	//Restarts inputs
		// Calculate Delta Time
		startTime = currentTime;
		currentTime = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTime - startTime)/ ((double)SDL_GetPerformanceFrequency()/ delay));

		// cleon: cuidado, falta el delta
		gameStateMachine->update();

		// Allows to exit if the window is closed in any moment
		if (ih().closeWindowEvent() || ih().isKeyDown(SDLK_ESCAPE)) {
			exit = true;
		}
	}
}
