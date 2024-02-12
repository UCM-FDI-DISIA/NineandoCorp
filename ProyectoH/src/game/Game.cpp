#include "Game.h"

// Destructor
Game::~Game() {
	delete gameStateMachine;
}

// Executes the game
void Game::run() {
	
	pushState<PlayState>();
	pushState<MainMenuState>();

	Uint64 currentTime = SDL_GetPerformanceCounter();
	Uint64 startTime = 0;
	while (!exit) {
		ih().refresh();	//Restarts inputs

		// Calculate Delta Time
		startTime = currentTime;
		currentTime = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTime - startTime) / (double)SDL_GetPerformanceFrequency());

#ifdef Version_1_0
		gameStateMachine->handleInput();
#endif
		gameStateMachine->update();
#ifdef Version_1_0
		sdlutils().clearRenderer();
		gameStateMachine->render();
		sdlutils().presentRenderer();
#endif

		// Allows to exit if the window is closed in any moment
		if (ih().closeWindowEvent() || ih().isKeyDown(SDLK_ESCAPE)) {
			exit = true;
		}
	}
}
