#pragma once
#include "../ecs/System.h"
#include "../components/ButtonComponent.h"

class HUDSystem : public System
{
public:

	static constexpr sysId_type id = _sys_HUD;

	HUDSystem();
	virtual ~HUDSystem();
	void receive(const Message& m) override;
	void initSystem() override;
	void update() override;
};

