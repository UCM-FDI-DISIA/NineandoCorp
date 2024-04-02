#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"
class EnemyBookSystem : public System
{
private:
	
public:
	std::vector<bool> Vistos;
	static constexpr sysId_type id = _sys_ENEMYBOOK;
	EnemyBookSystem() : Vistos(15, false) {};
	virtual ~EnemyBookSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override;
	void EnemigoVisto(int i, std::vector<bool>Vistos);
};

