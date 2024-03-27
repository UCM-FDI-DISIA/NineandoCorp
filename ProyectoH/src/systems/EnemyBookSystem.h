#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"
class EnemyBookSystem : public System
{
public:
	static constexpr sysId_type id = _sys_ENEMYBOOK;
	EnemyBookSystem();
	virtual ~EnemyBookSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override;
};

