#include "WaveSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

WaveSystem::WaveSystem()
{
	mActive = true;
}
WaveSystem::~WaveSystem()
{
	
}

void WaveSystem::initSystem()
{
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();


	//play button
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = { 350, 110 };
	bS->addButton(pAux, sAux, gameTextures::play, gameTextures::play_hover, ButtonTypes::play_wave);
	
}

void WaveSystem::receive(const Message& m)
{
}

void WaveSystem::update() {
}




