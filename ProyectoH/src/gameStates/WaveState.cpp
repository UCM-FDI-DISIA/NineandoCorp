#include "WaveState.h"
#include "../game/Game.h"

WaveState::WaveState() : GameState(_gmStt_WAVE) {

	// Sistemas requeridos para que funcione el juego
	mngr_->addSystem<MainControlSystem>();
	SDL_Rect* offset = mngr_->addSystem<RenderSystem>()->getOffset();
	mngr_->addSystem<mapSystem>("../ProyectoH/resources/tileMap/nivel");
	mngr_->addSystem<ButtonSystem>(_hdlr_BUTTON_WAVE);
	mngr_->addSystem<HUDSystem>();
	mngr_->addSystem<TowerSystem>();
	mngr_->addSystem< WaveSystem>();

	Message m;
	m.id = _m_WAVE_START;
	m.start_game_data.money = 15000;
	m.start_game_data.cameraOffset = offset;
	mngr_->send(m, true);
}

WaveState::~WaveState() {
	
}