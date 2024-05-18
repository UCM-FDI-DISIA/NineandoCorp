#include "CaballeroMalditoComponent.h"
#include "../ecs/Manager.h"
#include "RenderComponent.h"
#include "RouteComponent.h"
#include "MovementComponent.h"
#include "AttackComponent.h"
#include "EnemyTypeComponent.h"
#include "FramedImage.h"

void CaballeroMalditoComponent::generateMalditos(Vector2D pos, int destiny, vector<Vector2D> route) {
	auto& random = sdlutils().rand();
	vector<Vector2D> routeAux = route;


	for (int i = 0; i < 10; i++) {
		int x = random.nextInt(-40, 41);
		int y = random.nextInt(-40, 41);

		Vector2D malditoPos = pos + Vector2D(x, y);

		Entity* maldito = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);
		Transform* tr = mngr_->addComponent<Transform>(maldito);//transform
		MovementComponent* mc = mngr_->addComponent<MovementComponent>(maldito);

		tr->setSpeed(40.0f);

		mngr_->addComponent<RenderComponent>(maldito, gameTextures::maldito);
		mngr_->addComponent<HealthComponent>(maldito, 60);

		
		RouteComponent* rc = mngr_->addComponent<RouteComponent>(maldito, routeAux);
		rc->setDestiny(destiny);
		tr->setPosition(malditoPos);
		rc->changevelocity(routeAux[destiny]);
		

		mngr_->addComponent<AttackComponent>(maldito, 100, 1, 20, false);
		mngr_->addComponent<FramedImage>(maldito, 8, 1, 64, 64, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(maldito, _enm_MALDITO);

		mngr_->setHandler(_hdlr_ENEMIES, maldito);

	}
}