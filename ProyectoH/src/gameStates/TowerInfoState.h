#pragma once
#include "../game/GameState.h"

#include "../systems/TowerInfoSystem.h"
#include "../systems/MainMenuSystem.h"
#include "../systems/ButtonSystem.h"
class TowerInfoState : public GameState
{
public:
	TowerInfoState(Manager* mngr, twrId tId);
	virtual ~TowerInfoState();
private:
	twrId tId_;
};

