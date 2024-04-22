#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"
class EnemyBookSystem : public System
{
private:
	bool* Vistos;
	
public:
	static constexpr sysId_type id = _sys_ENEMYBOOK;
	virtual ~EnemyBookSystem();

	void initSystem() override;
	void EnemyPopUp(int i);
	void receive(const Message& m) override;
};

