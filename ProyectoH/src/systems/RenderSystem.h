#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../components/MovementComponent.h"
#include "../components/FramedImage.h"
#include "../components/FramedImage.h"
#include "../components/TextComponent.h"
#include "../components/RenderComponent.h"
#include "../components/ParticleLifeTime.h"
#include "../components/IconComponent.h"
#include "../utils/NetMap.h"
#include "../include/SDL.h"
#include "../sdlutils/SDLUtils.h"
#include "mapSystem.h"


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

	/// <summary>
	/// Dado un array de vertices, se renderiza un poligono relleno de x color
	/// </summary>
	/// <param name="width">renderer width</param>
	/// <param name="height">renderer height</param>
	void renderFillPolygon(SDL_Renderer* renderer, int width, int height, const SDL_Point vertices[],
		int numVertices, const SDL_Color& color);
	
	SDL_Rect* getOffset() { return offset; };

	/// <summary>
	/// Define un rombo en base a su centro, ancho y alto y lo renderiza
	/// </summary>
	void drawDiamond(SDL_Renderer* renderer, const SDL_Point& top, 
					int width, int height, const SDL_Color& fillColor);
private:
	void onPause();
	void onResume();
	void onGameOver(Uint8 winner);

	bool mActive;

	//void onPause();
	//void onResume();
	uint8_t winner_; // 0 - None, 1 - Enemigos, 2- Jugador

	//Rect con el offset de la camara
	SDL_Rect* offset = new SDL_Rect();

	//Auxiliares para la camara
	double cameraX_ = 0;
	double cameraY_ = 0;
	double VelCam = 300;

	//Limites de la camara
	int limtop = 200;
	int limbot = -1200;
	int limleft = 1000;
	int limright = -1000;

	//Booleanos de los controles de la camara
	bool k_up = false;
	bool k_down = false;
	bool k_left = false;
	bool k_right = false;

	// Textures
	Texture* textures[gameTextures::gmTxtrSize];
	Texture* cursorTexture;
	Texture* cursorTexture2;
};
