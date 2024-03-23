#pragma once

#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../ecs/ecs.h"


class MeteorologySystem : public System
{
public:

	static constexpr sysId_type id = _sys_METEOROLOGY;
	MeteorologySystem();
	~MeteorologySystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update();
};
