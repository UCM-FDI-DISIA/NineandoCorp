#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	void handleInput() override;
};

