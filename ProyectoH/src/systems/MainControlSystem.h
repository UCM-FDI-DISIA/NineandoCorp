#pragma once
#include "../ecs/System.h"

class MainControlSystem : public System
{
public:
	static constexpr sysId_type id = _sys_MAINCONTROL;

	MainControlSystem(int doradasIniciales);
	/*~MainControlSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update();
	void onRoundOver();
	void onRoundStart();*/

protected:
	bool active_;
	int numDoradasActuales;
	int numDoradasIniciales;
	int numDoradasPorSegundo;
	int oleadaActual;
};

