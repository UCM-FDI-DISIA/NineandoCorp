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
	std::vector<Vector2D> typesResolutions;
	bool isPlayState;
public:
	static constexpr sysId_type id = _sys_ENEMYBOOK;
	ConfigSystem(bool isPlayState): isPlayState(isPlayState) {}
	virtual ~ConfigSystem();

	void initSystem() override;
	void update() override {};
	void receive(const Message& m) override;
	};

