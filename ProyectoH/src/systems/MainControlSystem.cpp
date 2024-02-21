#include "MainControlSystem.h"

MainControlSystem::MainControlSystem(int doradasIniciales, int doradasPorSegundo, int numOleadas, float tiempoEntreOleadas) :
	numDoradasIniciales(doradasIniciales), numDoradasPorSegundo(doradasPorSegundo), numOleadas(numOleadas), tiempoEntreOleadas(tiempoEntreOleadas), numDoradasActuales(0), oleadaActual(0), active_(false), elapsedTime_(0) {

}

void MainControlSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	}
}

void MainControlSystem::update() {
	elapsedTime_ += game().getDeltaTime();
	if (elapsedTime_ > 1.0 && active_) {
		numDoradasActuales += numDoradasPorSegundo;
		elapsedTime_ = 0;
	}
}

void MainControlSystem::onRoundStart() {
	active_ = true;
}

void MainControlSystem::onRoundOver() {
	active_ = false;
}

void MainControlSystem::subtractCoins(int num) {
	numDoradasActuales -= num;
}