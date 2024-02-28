#pragma once
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "..//ecs/Component.h"
#include <vector>
class RouteComponent :public Component
{
public:
	RouteComponent(std::vector<Vector2D> route	) :transform_(nullptr), route_(route),destiny_(1){};
	void initComponent();
	void update();
	void checkdestiny();
	void changevelocity(Vector2D destino);
private:
	int destiny_;
	std::vector<Vector2D> route_;
	Transform* transform_;
};

