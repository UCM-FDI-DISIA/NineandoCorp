#ifndef GAME_H_
#define GAME_H_
#include "../sdlutils/SDLUtils.h"

#include "GameStateMachine.h"

#include "../sdlutils/InputHandler.h"
#include "../utils/Singleton.h"

#include "../gameStates/PlayState.h"
#include "../gameStates/LevelSelectorState.h"
#include "../gameStates/EnemyBookState.h"
#include "../gameStates/PauseState.h"
#include "../gameStates/MainMenuState.h"
#include "../gameStates/WaveState.h"
constexpr int WIN_WIDTH = 1200;
constexpr int WIN_HEIGHT = 900;
#include "../systems/RenderSystem.h"

#include <SDL.h>
#include <SDL_image.h>

class Game : public Singleton<Game> {
	friend Singleton<Game>;
private:
	bool exit;
	double deltaTime;
	GameStateMachine* gameStateMachine;

	// Constructor
	Game() : exit(false), deltaTime(0), gameStateMachine(new GameStateMachine()) {
		SDLUtils::init("Proyect H", WIN_WIDTH, WIN_HEIGHT, "resources/config/towerDefenseResources.json", "resources/config/config.json");
		auto& sdl = *SDLUtils::instance();

		//show the cursor
		sdl.showCursor();
	}

public:

	// Destructor
	~Game();
	// Executes the game
	void run();
	// Returns game time between updates
	inline double getDeltaTime() const { return deltaTime; }

	// Launches a new GameState on top of the current one
	template <typename T, typename ...Ts>
	inline void pushState(Ts&& ...args) {
		gameStateMachine->pushState(new T(std::forward<Ts>(args)...));

	}
	// Quits the current GameState
	inline void popState() {
		gameStateMachine->popState();
	}

	// Quits current GameStates and launches a new one
	template <typename T, typename ...Ts>
	inline void changeState(Ts&& ...args) {
		gameStateMachine->changeState(new T(std::forward<Ts>(args)...));
	}

	inline void exitGame() {
		exit = true;
	}

	inline GameState* currentState() {return gameStateMachine->currentState(); }
};

// Returns reference to game instance
inline Game& game() { return *Game::instance(); }
#endif

