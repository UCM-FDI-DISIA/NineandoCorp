#pragma once
#include "../ecs/System.h"
#include "../ecs/ecs.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/PhoenixTower.h"
#include <SDL.h>

class CollisionSystem : public System {
private:
	
public:
	static constexpr sysId_type id = _sys_COLLISION;
	CollisionSystem();
	~CollisionSystem();

	void initSystem()override;
	void update()override;
	void receive(const Message& m)override;
	void addRect(Entity* rect, const rectId id);
	void removeRect(Entity* rect, const rectId id);

protected:
	std::vector<Entity*> fenixRects_;//Puedo acceder a su Rect obteniendo el transform
	std::vector<Entity*> slimeRects_;
	std::vector<Entity*> meteoriteRects_;
	std::vector<Entity*> thunderRects_;
	std::vector<Entity*> enemyRects_;
	std::vector<Entity*> earthquakeRects_;
	std::vector<Entity*> tornadoRects_;
	std::vector<Entity*> tsunamiRects_;

	bool mActive;
};