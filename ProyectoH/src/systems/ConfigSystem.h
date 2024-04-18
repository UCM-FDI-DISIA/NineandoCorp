#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"
class ConfigSystem : public System
{
private:
	bool* Vistos = nullptr;
	
public:
	static constexpr sysId_type id = _sys_ENEMYBOOK;
	virtual ~ConfigSystem();

	void initSystem() override;
	void update() override {};
	};

