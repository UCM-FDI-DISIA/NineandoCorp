#include "generateEnemies.h"

void generateEnemies::initComponent() {

}
void generateEnemies::generateEnemy() {
	if (nextEnemy >= spawnGroup->typeEnemy.size()) {
		return;
	}
	std::string enemyType = spawnGroup->typeEnemy[nextEnemy];
	if (enemyType == "goblin")
		type = _enm_GOBLIN;
	else if (enemyType == "elfos")
		type = _enm_ELFO;
	else if (enemyType == "maldito")
		type = _enm_MALDITO;
	else if (enemyType == "golem")
		type = _enm_GOLEM;
	else if (enemyType == "demonioAlado")
		type = _enm_DALADO;
	else if (enemyType == "demonioInfernal")
		type = _enm_DINFERNAL;
	else if (enemyType == "maestro")
		type = _enm_MALMAS;
	else if (enemyType == "acechante")
		type = _enm_AELECTRICO;
	else if (enemyType == "angel")
		type = _enm_ANGEL;
	else if (enemyType == "defensor")
		type = _enm_DREAL;
	else if (enemyType == "mensajero")
		type = _enm_MMUERTE;
	else if (enemyType == "caballeroMaldito")
		type = _enm_CMALDITO;
	else if (enemyType == "principito")
		type = _enm_PRINCIPITO;
	else if (enemyType == "monje")
		type = _enm_MONJE;
	else if (enemyType == "muerte")
		type = _enm_MUERTE;
	
	
	addEnemy(type, route);
	

}
void generateEnemies::addGroupEnemies(){
	std::string id = "nivel" + std::to_string(level) + "oleada" + std::to_string(wave) + "grupo" + std::to_string(grp);
	auto spawneo = &sdlutils().spawns().at(id);
	spawnGroup = spawneo;
}
void generateEnemies::addEnemy(enmId type, std::vector<Vector2D> route) {
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);

	Transform* tr = mngr_->addComponent<Transform>(t);//transform
	tr->setPosition(route[0]);

	MovementComponent* mc = mngr_->addComponent<MovementComponent>(t);


	switch (type) {
	case _enm_MALMAS:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, maestro);
		mngr_->addComponent<HealthComponent>(t, 150);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 1.0, 0, true);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_AELECTRICO:
		tr->setSpeed(70.0f);
		mngr_->addComponent<RenderComponent>(t, acechante);
		mngr_->addComponent<HealthComponent>(t, 150);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 0, 1, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_MALDITO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_GOLEM:
		tr->setSpeed(20.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_DALADO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_GOBLIN:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_ELFO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_MMUERTE:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_ANGEL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_DINFERNAL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_DREAL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_CMALDITO:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_PRINCIPITO:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_MONJE:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;
	case _enm_MUERTE:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, square);
		mngr_->addComponent<HealthComponent>(t, 50000);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 20, false);
		mngr_->addComponent<FramedImage>(t, 1, 1, 122, 117, 0, 0, 1);
		break;


	}
	mngr_->setHandler(_hdlr_ENEMIES, t);


}
