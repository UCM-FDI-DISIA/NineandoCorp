#pragma once
#include "../game/GameState.h"

class GameOverState : public GameState
{
public:
	GameOverState(int coinsH, bool* enemiesSaw, int currentLvl, bool winner);
	virtual ~GameOverState();
};

