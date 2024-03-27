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

	vector<vector<Cell*>> net;        //Malla
	SDL_Rect* offset =new SDL_Rect(); // Este offset es el mismo que el del render system

public:
	NetMap(int size);

	/// <summary>
	/// Referencia de la casilla siendo la casilla superior la esquina superior izquierda del cuadrado
	/// </summary>
	/// <param name="fila">Fila en la que se encuenta la casilla</param>
	/// <param name="columna">Columna en la que se ancuentra la casilla</param>
	/// <returns>Devuelve el puntero de la casilla</returns>
	Cell* getCell(int fila, int columna) const { return net[fila][columna]; };

	/// <summary>
	/// Establece la celda
	/// </summary>
	/// <param name="fila">La fila de la malla</param>
	/// <param name="columna">La columna de la malla</param>
	/// <param name="c">La celda nueva</param>
	void setCell(int fila, int columna, Cell* c) { net[fila][columna] = c; };

	/// <summary>
	/// Establece la referencia al offset
	/// </summary>
	/// <param name="rect"></param>
	void setOffset(SDL_Rect* rect) { offset = rect; };

	/// <summary>
	/// Busca la celda correspondiente segun una posicion dada en pantalla
	/// </summary>
	/// <param name="targetPosition">Posicion objetivo</param>
	/// <returns>Puntero de la celda mas proxima</returns>
	Cell* searchCell(const Vector2D &targetPosition) const;
};

