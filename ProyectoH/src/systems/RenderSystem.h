#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../components/MovementComponent.h"
#include "../components/FramedImage.h"
#include "../components/FramedImage.h"
#include "../components/RenderComponent.h"


// Correspondant text to each state
enum stateText {
	startText, pauseText, winText, loseText, sttTxtSize 
};

class RenderSystem : public System {
public:
	static constexpr sysId_type id = _sys_RENDER;
	// Constructor
	RenderSystem();
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
	
	// Creates an Entity with correspondant text texture and transform
	void addText(stateText stt);
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

	//limites de la camara
	int limtop = 1000;
	int limbot = -1000;
	int limleft = 1000;
	int limright = -1000;

	// Texts
	stateText currStTxt;
	Texture* textTextures[stateText::sttTxtSize];
	Transform* textTr[stateText::sttTxtSize];

	// Textures
	Texture* textures[gameTextures::gmTxtrSize];
	Texture* cursorTexture;
	Texture* cursorTexture2;
	// Doing a texture array so we do not need to access sdlutils' map every time
};
