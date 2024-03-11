#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../components/MovementComponent.h"
#include "../components/FramedImage.h"
#include "../components/FramedImage.h"
#include "../components/RenderComponent.h"
#include "../utils/NetMap.h"


class RenderSystem : public System {
public:
	static constexpr sysId_type id = _sys_RENDER;
	// Constructor
	RenderSystem(NetMap* net = nullptr);
	virtual ~RenderSystem();
	// Reaccionar a los mensajes recibidos (llamando a mÈtodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.dddd
	void initSystem() override;
	// - Dibujar asteroides, balas y caza (sÛlo si el juego no estÅEparado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego estÅEparado, etc (como en
	// la pr·ctica 1)
	void update() override;
private:
	
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_.
	void onRoundStart();
	void onGameStart();
	void onGameOver(Uint8 winner);
	// Displays pause message
	void onPause();
	// Hides pause message
	void onResume();

	uint8_t winner_; // 0 - None, 1 - Asteroid, 2- Fighter

	SDL_Rect offset = build_sdlrect(0,0,0,0);
	NetMap* net;

	//limites de la camara
	int limtop = 200;
	int limbot = -1200;
	int limleft = 1000;
	int limright = -1000;

	// Textures
	Texture* textures[gameTextures::gmTxtrSize];
	Texture* cursorTexture;
	Texture* cursorTexture2;
	// Doing a texture array so we do not need to access sdlutils' map every time
};
