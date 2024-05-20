#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"
class ConfigSystem : public System
{
private:
	void createResolutions(int resolutions_);
	void changeTextControls(std::string name);
	std::vector<Vector2D> typesResolutions;
	bool isPlayState;
	Entity* left;
	Entity* right;
	Entity* up;
	Entity* down;
public:
	static constexpr sysId_type id = _sys_ENEMYBOOK;
	ConfigSystem(bool isPlayState): isPlayState(isPlayState) {}
	virtual ~ConfigSystem();

	void initSystem() override;
	void update() override {};
	void receive(const Message& m) override;
	};

