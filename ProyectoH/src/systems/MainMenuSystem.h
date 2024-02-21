#pragma once
#include "..//ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"
<<<<<<< Updated upstream
=======

//#include "../systems/RenderSystem.h"
>>>>>>> Stashed changes

class MainMenuSystem : public System
{
public:
	static constexpr sysId_type id = _sys_MAINMENU;
	MainMenuSystem();
	virtual ~MainMenuSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override ;
};

