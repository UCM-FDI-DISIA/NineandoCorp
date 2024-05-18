#ifndef GAME_H_
#define GAME_H_
#include "../sdlutils/SDLUtils.h"

#include "GameStateMachine.h"

#include "../sdlutils/InputHandler.h"
#include "../utils/Singleton.h"
#include "../utils/SaveGame.h"

#include "../gameStates/PlayState.h"
#include "../gameStates/LevelSelectorState.h"
#include "../gameStates/EnemyBookState.h"
#include "../gameStates/PauseState.h"
#include "../gameStates/MainMenuState.h"
#include "../gameStates/GameOverState.h"
#include "../gameStates/ConfigState.h"
#include "../gameStates/TowerInfoState.h"
constexpr int WIN_WIDTH = 1280;
constexpr int WIN_HEIGHT = 1024;
#include "../systems/RenderSystem.h"

#include <SDL.h>
#include <SDL_image.h>

class Game : public Singleton<Game> {
	friend Singleton<Game>;
private:
	struct Config
	{
		float soundGeneral_ = 50.0f;
		float soundMusic_ = 50.0f;
		float soundEffects_ = 50.0f;
		float newMinGeneral_ = 100;
		float newMaxGeneral_ = 150;
		float newMinMusic_ = 100;
		float newMaxMusic_ = 150;
		float newMinEffects_ = 100;
		float newMaxEffects_ = 150;
		bool fullScreen = false;
		int up = 'w';
		int down = 's';
		int right = 'd';
		int left = 'a';
	};
	bool exit;
	double deltaTime;
	float delay;
	GameStateMachine* gameStateMachine;
	SaveGame save = SaveGame();
	Config config_;
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

	inline SaveGame* getSaveGame() { return &save; };

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

	float CalculoVolumenEfectos() {
		float vol = config_.soundGeneral_ * config_.soundEffects_;
		return (vol * 128) / 10000;
	}

	float CalculoVolumenMusica() {
		float vol = config_.soundMusic_ * config_.soundGeneral_;
		return (vol * 128) / 10000;
	}

	void SetDelay(float _delay) { delay = _delay; };

	float GetDelay() { return delay; };

	inline GameState* currentState() const {return gameStateMachine->currentState(); }

	inline bool getFullScreen() const { return config_.fullScreen; }
	inline void setFullScreen()  { config_.fullScreen = !config_.fullScreen; }
	inline float getSoundGeneral() const { return config_.soundGeneral_; };
	inline void setSoundGeneral(float newVolume) {  config_.soundGeneral_ = newVolume; };
	inline float getSoundMusic() const { return config_.soundMusic_; };
	inline void setSoundMusic(float newVolume) { config_.soundMusic_ = newVolume; };
	inline float getSoundEffect() const { return config_.soundEffects_; };
	inline void setSoundEffect(float newVolume) { config_.soundEffects_ = newVolume; };
	inline float getNewMinGeneral() const { return config_.newMinGeneral_; };
	inline void setNewMinGeneral(float newMin_) { config_.newMinGeneral_ = newMin_; };
	inline float getNewMaxGeneral() const { return config_.newMaxGeneral_; };
	inline void setNewMaxGeneral(float newMax_) { config_.newMaxGeneral_ = newMax_; };
	inline float getNewMinMusic() const { return config_.newMinMusic_; };
	inline void setNewMinMusic(float newMin_) { config_.newMinMusic_ = newMin_; };
	inline float getNewMaxMusic() const { return config_.newMaxMusic_; };
	inline void setNewMaxMusic(float newMax_) { config_.newMaxMusic_ = newMax_; };
	inline float getNewMinEffects() const { return config_.newMinEffects_; };
	inline void setNewMinEffects(float newMin_) { config_.newMinEffects_ = newMin_; };
	inline float getNewMaxEffects() const { return config_.newMaxEffects_; };
	inline void setNewMaxEffects(float newMax_) { config_.newMaxEffects_ = newMax_; };
	inline int getUp() { return config_.up; };
	inline int getDown() { return config_.down; };
	inline int getRight() { return config_.right; };
	inline int getLeft() { return config_.left; };
	inline void setUp(int tecla) { config_.up = tecla; };
	inline void setDown(int tecla) { config_.down = tecla; };
	inline void setRight(int tecla) { config_.right = tecla; };
	inline void setLeft(int tecla) { config_.left = tecla; };
};


// Returns reference to game instance
inline Game& game() { return *Game::instance(); }
#endif

