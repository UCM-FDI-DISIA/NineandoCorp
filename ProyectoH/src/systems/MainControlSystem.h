#pragma once
#include "../ecs/System.h"
#include "../game/Game.h"
#include "../components/NexusComponent.h"
#include "../utils/SaveGame.h"
#include <vector>

class MainControlSystem : public System
{
public:
	static constexpr sysId_type id = _sys_MAINCONTROL;

	MainControlSystem(int currentLevel);
	~MainControlSystem() {};

	void initSystem() override;
	void receive(const Message& m) override;
	void update();

protected:
	bool nexusIsAlive_;
	int numDoradasActuales;
	int numDoradasIniciales;
	int numDoradasPorSegundo;
	int currentLevel;
	float tiempoEntreOleadas;
	double elapsedTime_;
	VirtualTimer timer_;
	Entity* nexo;
	SaveGame* saveGame;

	// Niveles de nexo y torres
	int* turrentLevels_;	// Nexo última torre

	void onRoundOver();
	void OnStartGame();
	void subtractCoins(int num);

	void upgradeTower(twrId id);
	
	inline void resetButtons() {
		for (auto b : mngr_->getHandler(_hdlr_BUTTON)) {
			mngr_->getComponent<ButtonComponent>(b)->setActive(true);
		}
	}
};

