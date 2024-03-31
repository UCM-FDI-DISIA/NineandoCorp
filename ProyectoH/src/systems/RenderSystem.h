#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../components/MovementComponent.h"
#include "../components/FramedImage.h"
#include "../components/FramedImage.h"
#include "../components/TextComponent.h"
#include "../components/RenderComponent.h"
#include "../utils/NetMap.h"
#include "../include/SDL.h"


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
	

	/// <summary>
	/// Define un rombo en base a su centro, ancho y alto y lo renderiza
	/// </summary>
	
	void drawDiamond(SDL_Renderer* renderer, const SDL_Point& top, 
					int width, int height, const SDL_Color& borderColor,	
					const SDL_Color& fillColor);
private:
	void onPause();
	void onResume();
	void onGameOver(Uint8 winner);

	
	/// <param name="renderer"></param>
	/// <param name="top"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="borderColor"></param>
	/// <param name="fillColor"></param>
	void resetTexture(gameTextures texId);

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
