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
	int oleadaActual;
	int numOleadas;
	float tiempoEntreOleadas;
	double elapsedTime_;
	VirtualTimer timer_;
	Entity* nexo;

	// Niveles de nexo y torres
	vector<int> levels_;

	void onRoundOver();
	void onRoundStart();
	void subtractCoins(int num);
	
	inline void resetButtons() {
		for (auto b : mngr_->getHandler(_hdlr_BUTTON)) {
			mngr_->getComponent<ButtonComponent>(b)->setActive(true);
		}
	}
};

