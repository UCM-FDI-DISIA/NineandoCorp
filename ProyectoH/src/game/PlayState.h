#pragma once
#include "GameState.h"

class PlayState : public GameState
{
public:
	void handleInput() override;
	void update() override;
};

