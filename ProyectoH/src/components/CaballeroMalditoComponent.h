#pragma once
#include "../ecs/Component.h"

class CaballeroMalditoComponent: public Component
{
public:
	static const cmpId id = cmpId::_ANGEL;
	CaballeroMalditoComponent() {};
	void generateMalditos(Vector2D pos, int destiny, vector<Vector2D> route);
};

