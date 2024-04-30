#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"

class PauseSystem : public System
{

public:
	static constexpr sysId_type id = _sys_PAUSE;
	PauseSystem();
	virtual ~PauseSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override;

private:
	Entity* background;
	Entity* resume;
	Entity* backToMenu;
	Entity* settings;
	Entity* exitGame;
	Entity* resumeIcon;

	void WarningPanel(string text, ButtonTypes butTyp);
	void SetActivePauseButons(bool mActive);
	void addText(const Vector2D& pos, const Vector2D& scale, const double rot, grpId_type grpId);
};

