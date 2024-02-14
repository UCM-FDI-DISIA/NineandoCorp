#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	~MainMenuState();

	void handleInput() override;
};

