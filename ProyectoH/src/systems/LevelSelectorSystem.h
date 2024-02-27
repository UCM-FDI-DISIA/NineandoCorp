#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"

class LevelSelectorSystem : public System
{
public:
	static constexpr sysId_type id = _sys_LEVELSELECTOR;
	LevelSelectorSystem();
	virtual ~LevelSelectorSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override; 
	void backToMainMenu(); 
	void startGame();
	void callFunction(ButtonTypes type, ButtonComponent* bC);
private:
	Entity* addButton(Vector2D pos, Vector2D scale, gameTextures tex, gameTextures hov, ButtonTypes type);
	void addImage(Vector2D pos, Vector2D(scale), double rot, gameTextures t);
	Entity* backButtonEntity;
	Entity* playButtonEntity;
};

