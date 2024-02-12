#include "GameStateMachine.h"

inline void GameStateMachine::setState(State s) {
	GameState* new_state = nullptr;
	switch (s) {
	case RUNNING:
		new_state = running_state;
		break;
	case PAUSEDMENU:
		new_state = pausedmenu_state;
		break;
	case MAINMENU:
		new_state = mainmanu_state;
		break;
	case GAMEOVER:
		new_state = gameover_state;
		break;
	case DEFAULT:
		new_state = default_state;
		break;
	default:
		break;
	}
	current_state->leave();
	current_state = new_state;
	current_state->enter();
}