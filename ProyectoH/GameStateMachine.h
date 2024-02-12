#pragma once
#include "GameState.h"


class GameStateMachine
{
private:
	// Estado Actual 
	GameState* current_state;

	// Diferentes Estados del Juego
	GameState* running_state;
	GameState* pausedmenu_state;
	GameState* mainmanu_state;
	GameState* gameover_state;
	GameState* default_state;
public:
	enum State {
		RUNNING, PAUSEDMENU, MAINMENU, GAMEOVER, DEFAULT
	};
	
	inline void setState(State s) {};
private:
};

