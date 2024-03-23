#pragma once
#include "..//ecs/Manager.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "..//utils/NetMap.h"
#include "..//ecs/Component.h"
#include <vector>
class RouteComponent :public Component
{
public:
	const float epsilon = 2.5;
	static const cmpId id = cmpId::_ROUTE;
	RouteComponent(std::vector<Vector2D> route) :transform_(nullptr), renderComponent_(nullptr), route_(route), destiny_(0){};
	void initComponent();
	void update();
	void checkdestiny();
	void changevelocity(Vector2D destino);
private:
	int destiny_;
	std::vector<Vector2D> route_;
	Transform* transform_;
	RenderComponent* renderComponent_;
};

