#pragma once
#include "../ecs/System.h"
#include "..//sdlutils/VirtualTimer.h"
#include "../game/Game.h"
#include "../components/NexusComponent.h"
#include <vector>

class MainControlSystem : public System
{
public:
	static constexpr sysId_type id = _sys_MAINCONTROL;

	MainControlSystem();
	~MainControlSystem() {};

	void initSystem() override;
	void receive(const Message& m) override;
	void update();

protected:
	bool active_;
	int numDoradasActuales;
	int numDoradasIniciales;
	int numDoradasPorSegundo;
	int currentLevel = 0;
	float tiempoEntreOleadas;
	double elapsedTime_;
	VirtualTimer timer_;
	Entity* nexo;

	// Niveles de nexo y torres
	int turrentLevels_ [_twr_SIZE];	// Nexo última torre

	void onRoundOver();
	void OnStartGame();
	void subtractCoins(int num);

	void initializeNexus(gameTextures texture, int life, Vector2D pos);

	void upgradeTower(twrId id);
	
	inline void resetButtons() {
		for (auto b : mngr_->getHandler(_hdlr_BUTTON)) {
			mngr_->getComponent<ButtonComponent>(b)->setActive(true);
		}
	}
};

