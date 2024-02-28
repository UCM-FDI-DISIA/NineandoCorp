#pragma once
#include "..//ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"

class MainMenuSystem : public System
{
public:
	static constexpr sysId_type id = _sys_MAINMENU;
	MainMenuSystem();
	virtual ~MainMenuSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override ;
private: 
	void addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type);
	//void addImage(const Vector2D &pos, Vector2D(scale), double rot, gameTextures t, grpId_type grpId);

	void addImage(const Vector2D& pos, const Vector2D & scale, const double rot, gameTextures t, grpId_type grpId);
	void callFunction(ButtonTypes type, ButtonComponent* en);
	void funcionPrueba(Transform* tr);
	void loadLevelSelector();
	void startLevel();
	void pause();
	void upgradeNexus();
};

