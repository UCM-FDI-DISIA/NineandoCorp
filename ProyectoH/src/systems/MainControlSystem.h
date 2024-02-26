#pragma once
#include "../ecs/System.h"
#include "..//sdlutils/VirtualTimer.h"
#include "../game/Game.h"

class MainControlSystem : public System
{
public:
	static constexpr sysId_type id = _sys_MAINCONTROL;

	MainControlSystem();
	~MainControlSystem() {};

	void initSystem() override {};
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

	void onRoundOver();
	void onRoundStart();
	void subtractCoins(int num);
};

