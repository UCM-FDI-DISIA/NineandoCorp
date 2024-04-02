#include "generateEnemies.h"

void generateEnemies::initComponent() {

}
/// <summary>
/// generación de enemigos donde asigno cada etiqueta a su id
/// </summary>
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
/// <summary>
/// creación de la etiqueta del grupo
/// </summary>
void generateEnemies::addGroupEnemies(){
	std::string id = "nivel" + std::to_string(level) + "oleada" + std::to_string(wave) + "grupo" + std::to_string(grp);
	auto spawneo = &sdlutils().spawns().at(id);
	spawnGroup = spawneo;
}
/// <summary>
/// Hacemos una corrección de la ruta para colocar el sprite en el medio del camino
/// </summary>
/// <param name="tr">transform del enemigo</param>
/// <param name="route"></param>
/// <param name="divHeight"></param>
/// <param name="divWidth"></param>
void generateEnemies::RoutesCorrection(Transform* tr, std::vector<Vector2D>& route, float divHeight, float divWidth) {
	Vector2D v = { tr->getWidth() / divWidth, tr->getHeight() / divHeight };
	for (auto& e : route) {
		e = e - v;
	}
}
/// <summary>
/// añadimos el enemigo con sus componentes correspondientes
/// </summary>
/// <param name="type">tipo de enemigo</param>
/// <param name="route">ruta a seguir</param>
void generateEnemies::addEnemy(enmId type, std::vector<Vector2D> route) {
	Entity* t = mngr_->addEntity(_grp_TOWERS_AND_ENEMIES);

	Transform* tr = mngr_->addComponent<Transform>(t);//transform

	//tr->setScale({ tr->getWidth() / 1.5f, tr->getHeight() / 1.5f});
	

	MovementComponent* mc = mngr_->addComponent<MovementComponent>(t);


	switch (type) {
	case _enm_MALMAS:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, maestro);
		mngr_->addComponent<HealthComponent>(t, 150);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 1.0, 20, true);
		mngr_->addComponent<FramedImage>(t, 1, 1, 250, 250, 0, 8, 7);
		break;
	case _enm_AELECTRICO:
		tr->setSpeed(70.0f);
		mngr_->addComponent<RenderComponent>(t, acechante);
		mngr_->addComponent<HealthComponent>(t, 150);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 10, 1, 35, false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 162, 162, 0, 8, 7);
		break;
	case _enm_MALDITO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, maldito);
		mngr_->addComponent<HealthComponent>(t, 60);
		RoutesCorrection(tr, route, 1.0f, 3.0f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 10, 1, 20, false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 64, 64, 0, 8, 7);
		break;
	case _enm_GOLEM:
		tr->setSpeed(20.0f);
		mngr_->addComponent<RenderComponent>(t, golem);
		mngr_->addComponent<HealthComponent>(t, 1000);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 10, 3, 100, false);
		mngr_->addComponent<FramedImage>(t, 10, 10, 100, 100, 40, 10, 46);
		break;
	case _enm_DALADO:
		tr->setSpeed(40.0f);
		mngr_->addComponent<RenderComponent>(t, demonioAlado);
		mngr_->addComponent<HealthComponent>(t, 25);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 1, 5, true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 150, 150, 0, 8, 7);
		break;
	case _enm_GOBLIN:
		tr->setSpeed(60.0f);
		mngr_->addComponent<RenderComponent>(t, goblin);
		mngr_->addComponent<HealthComponent>(t, 20);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 10, 1, 15, false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 150, 150, 0, 8, 7);
		break;
	case _enm_ELFO:
		tr->setSpeed(20.0f);
		mngr_->addComponent<RenderComponent>(t, elfo);
		mngr_->addComponent<HealthComponent>(t, 60);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 1, 10, true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 100, 100, 0, 8, 7);
		break;
	case _enm_MMUERTE:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, mensajero);
		mngr_->addComponent<HealthComponent>(t, 300);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 10, 1, 20, false);
		mngr_->addComponent<FramedImage>(t, 8, 8, 140, 93, 8, 8, 15);
		break;
	case _enm_ANGEL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, angel);
		mngr_->addComponent<HealthComponent>(t, 400);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 2, 2, true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 122, 117, 0, 8, 7);
		break;
	case _enm_DINFERNAL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, demonioInfernal);
		mngr_->addComponent<HealthComponent>(t, 750);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 2, 20, true);
		mngr_->addComponent<FramedImage>(t, 8, 4, 64, 64, 16, 4, 19);
		break;
	case _enm_DREAL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, defensor);
		mngr_->addComponent<HealthComponent>(t, 200);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 1, 10, true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 231, 190, 0, 8, 7);
		break;
	case _enm_CMALDITO:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, CMaldito);
		mngr_->addComponent<HealthComponent>(t, 1000);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 10, 3, 150, false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 64, 64, 0, 8, 7);
		break;
	case _enm_PRINCIPITO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, principito);
		mngr_->addComponent<HealthComponent>(t, 2500);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 0.25, 10, true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 128, 128, 0, 8, 7);
		break;
	case _enm_MONJE:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, monje);
		mngr_->addComponent<HealthComponent>(t, 5000);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 1, 75, false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 150, 150, 0, 8, 7);
		break;
	case _enm_MUERTE:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, muerte);
		mngr_->addComponent<HealthComponent>(t, 10000);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, 100, 1, 75, true);
		mngr_->addComponent<FramedImage>(t, 1, 1, 100, 100, 0, 0, 1);
		break;


	}
	mngr_->setHandler(_hdlr_ENEMIES, t);


}
