#pragma once
#include "../ecs/System.h"
#include "../ecs/ecs.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/PhoenixTower.h"
#include <SDL.h>

class CollisionSystem : public System {
public:
	static constexpr sysId_type id = _sys_COLLISION;
	CollisionSystem();
	~CollisionSystem();

	void initSystem()override;
	void update()override;
	void receive(const Message& m)override;
	void onRoundOver() {};
	void onRoundStart() {};
	void addRect(Entity* rect, const rectId id);

protected:
	std::vector<Entity*> fenixRects_;//Puedo acceder a su Rect obteniendo el transform
	std::vector<Entity*> slimeRects_;
	std::vector<Entity*> enemyRects_;
};