#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState() {};

	void handleInput() override;
};

