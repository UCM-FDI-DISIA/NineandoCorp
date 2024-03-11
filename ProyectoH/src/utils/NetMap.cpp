#include "NetMap.h"


NetMap::NetMap(int size) {
	*offset = build_sdlrect(0, 0, 0, 0);
	for (int i = 0; i < size; i++) {
		net.push_back(vector<Cell*>(size));
	}
};

Cell* NetMap::searchCell(float x, float y) const {
	int i = 0, j = 0;

	bool exit = false;
	while (!exit) {
		if (i == 31 || j == 31) {
			return net[30][30];
		}
		if (net[i][j]->position.getX() + offset->x > x)
			i++;
		else if (net[i][j]->position.getY() + offset->y < y)
			j++;
		else
			exit = true;;
	}
	return net[i][j];
}