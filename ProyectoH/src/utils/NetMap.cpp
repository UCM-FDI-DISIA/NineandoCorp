#include "NetMap.h"
#include <math.h>


NetMap::NetMap(int size) {
	*offset = build_sdlrect(0, 0, 0, 0);
	for (int i = 0; i < size; i++) {
		net.push_back(vector<Cell*>(size));
	}
};

Cell* NetMap::searchCell(Vector2D &targetPosition) const {
	int i = 0, j = 0;
	Vector2D offsetPosition = Vector2D(offset->x, offset->y); 

	bool exit = false;
	while (!exit) {
		if (i == 31)
			return net[j][30];
		if(j == 31) 
			return net[30][i];

		Vector2D aux = (net[j][i]->position + offsetPosition) - targetPosition;
		if (abs(aux.magnitude()) < 32)
			exit = true;
		else if (aux.getY() > 0) {
			return net[j][i];
		}
		else if (aux.getX() > 0) {
				i++;
		}
		else {
				j++;
		}
	}
	return net[j][i];
}