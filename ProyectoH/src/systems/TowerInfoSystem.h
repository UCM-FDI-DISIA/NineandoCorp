#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"

class TowerInfoSystem : public System
{
public:
	static constexpr sysId_type id = _sys_INFO;
	TowerInfoSystem(twrId tId) : 
	tower_id(tId)
	{}
	TowerInfoSystem() {}
	virtual ~TowerInfoSystem();

	void initSystem() override;
	void receive(const Message& m) override;

private: 
	twrId tower_id;
};

