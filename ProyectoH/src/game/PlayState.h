#pragma once
#include "GameState.h"

class PlayState : public GameState
{
public:
	PlayState();
	~PlayState();

	void handleInput() override;
	void update() override;
};

