#pragma once
#include "Vector2D.h"
#include <vector>
#include "../sdlutils/SDLUtils.h"

using namespace std;

enum tileId { TILE_LAKE, TILE_LOW, TILE_HIGH, TILE_NONE };

struct Cell {
	Vector2D position;
	bool isFree;
	tileId id = TILE_NONE;
};

class NetMap
{
private:

	vector<vector<Cell*>> net;
	SDL_Rect offset = build_sdlrect(0, 0, 0, 0);

public:
	NetMap(int size);
	/// <summary>
	/// Referencia de la casilla siendo la casilla superior la esquina superior izquierda del cuadrado
	/// </summary>
	/// <param name="fila">Fila en la que se encuenta la casilla</param>
	/// <param name="columna">Columna en la que se ancuentra la casilla</param>
	/// <returns>Devuelve el puntero de la casilla</returns>
	Cell* getCell(int fila, int columna) const { return net[fila][columna]; };

	void setCell(int fila, int columna, Cell* c) { net[fila][columna] = c; };

	void setOffset(SDL_Rect& rect) { offset.x = rect.x; offset.y = offset.y; };

	Cell* searchCell(float x, float y) const;
};

