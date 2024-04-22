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

	//vector textura enemigo
	vector<gameTextures> Texturas{
		gameTextures::maestro_icon,
		gameTextures::acechante_icon,
		gameTextures::maldito_icon,
		gameTextures::golem_icon,
		gameTextures::demonioAlado_icon,
		gameTextures::goblin_icon,
		gameTextures::elfo_icon,
		gameTextures::mensajero_icon,
		gameTextures::angel_icon,
		gameTextures::demonioInfernal_icon,
		gameTextures::defensor_icon,
		gameTextures::CMaldito_icon,
		gameTextures::principito_icon,
		gameTextures::monje_icon,
		gameTextures::muerte_icon
	};
	
public:
	static constexpr sysId_type id = _sys_ENEMYBOOK;
	virtual ~EnemyBookSystem();

	void initSystem() override;
	void EnemyPopUp(int i);
	void receive(const Message& m) override;
	
};

