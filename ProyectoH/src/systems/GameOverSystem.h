#pragma once
#include "../ecs/System.h"

class GameOverSystem : public System
{
public:
	static constexpr sysId_type id = _sys_GAMEOVER;
	GameOverSystem();
	virtual ~GameOverSystem(); 
	void initSystem() override;
};

