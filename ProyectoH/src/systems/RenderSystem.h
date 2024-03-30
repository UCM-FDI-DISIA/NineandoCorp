#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../components/MovementComponent.h"
#include "../components/FramedImage.h"
#include "../components/FramedImage.h"
#include "../components/RenderComponent.h"
#include "../components/ParticleLifeTime.h"
#include "../utils/NetMap.h"


class RenderSystem : public System {
public:
	static constexpr sysId_type id = _sys_RENDER;
	// Constructor
	RenderSystem();
	virtual ~RenderSystem();

	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;

	// - Dibujar enemigos, torres, tiles, interfaces y texto.
	void update() override;
private:
	void onPause();
	void onResume();
	void onGameOver(Uint8 winner);

	rectId getRectId(Entity* e);

	uint8_t winner_; // 0 - None, 1 - Enemigos, 2- Jugador

	//Rect con el offset de la camara
	SDL_Rect* offset = new SDL_Rect();

	//Limites de la camara
	int limtop = 200;
	int limbot = -1200;
	int limleft = 1000;
	int limright = -1000;

	// Textures
	Texture* textures[gameTextures::gmTxtrSize];
	Texture* cursorTexture;
	Texture* cursorTexture2;
};
