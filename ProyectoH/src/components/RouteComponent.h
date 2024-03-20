#pragma once
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "..//utils/NetMap.h"
#include "..//ecs/Component.h"
#include <vector>
class RouteComponent :public Component
{
public:
	const float epsilon = 2.5;
	static const cmpId id = cmpId::_ROUTE;
	RouteComponent(std::vector<Vector2D> route, NetMap* map) :transform_(nullptr), route_(route), destiny_(0), netmap(map){};
	void initComponent();
	void update();
	void checkdestiny();
	void changevelocity(Vector2D destino);
private:
	int destiny_;
	std::vector<Vector2D> route_;
	std::vector<Vector2D> route_translate;
	Transform* transform_;
	NetMap* netmap;
};

