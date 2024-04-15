#pragma once
#include "../game/GameState.h"

class GameOverState : public GameState
{
public:
	GameOverState(int rounds, int enemies, int coinsH, int currentLvl, bool winner);
	virtual ~GameOverState();
};

