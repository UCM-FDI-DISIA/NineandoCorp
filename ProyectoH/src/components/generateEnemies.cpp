#include "generateEnemies.h"
#include "../systems/EnemyBookSystem.h"


void generateEnemies::initComponent() {

}
/// <summary>
/// generación de enemigos donde asigno cada etiqueta a su id
/// </summary>
void generateEnemies::generateEnemy() {
	
	if (nextEnemy == spawnGroup->numEnemies[pos]) {
		pos++;
		nextEnemy = 0;
	}
	std::string enemyType = spawnGroup->typeEnemy[pos];
	
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
	nextEnemy++;

}
/// <summary>
/// creación de la etiqueta del grupo
/// </summary>
void generateEnemies::addGroupEnemies(){
	std::string id = "nivel" + std::to_string(level) + "oleada" + std::to_string(wave) + "grupo" + std::to_string(grp);
	auto spawneo = &sdlutils().spawns().at(id);
	spawnGroup = spawneo;
}

int generateEnemies::totalEnemies() const{
	int total = 0;
	for (auto e : spawnGroup->numEnemies) {
		total += e;
	}
	return total;
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


	Message m;
	m.id = _m_ENEMYSEE;
	m.start_enemy_book.n = type;
	mngr_->send(m);

	MovementComponent* mc = mngr_->addComponent<MovementComponent>(t);

	switch (type) {
	case _enm_MALMAS:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, maestro);
		mngr_->addComponent<HealthComponent>(t, intAt("MaestroVida"));
		mngr_->addComponent<MaestroAlmasComponent>(t, intAt("MaestroHabilidad"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("MaestroRango"), intAt("Maestrotiempo"), intAt("MaestroAtaque"), true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 250, 250, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_MALMAS);

		break;
	case _enm_AELECTRICO:
		tr->setSpeed(70.0f);
		mngr_->addComponent<RenderComponent>(t, acechante);
		mngr_->addComponent<HealthComponent>(t, intAt("AcechanteVida"));
		mngr_->addComponent<AcechanteComponent>(t, floatAt("AcechanteAceleracion"), floatAt("AcechanteRango"), floatAt("AcechanteReload"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("AcechanteRango"), intAt("Acechantetiempo"), intAt("AcechanteAtaque"), false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 162, 162, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_AELECTRICO);
		break;
	case _enm_MALDITO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, maldito);
		mngr_->addComponent<HealthComponent>(t, intAt("MalditoVida"));
		RoutesCorrection(tr, route, 1.0f, 3.0f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("MalditoRango"), intAt("Malditotiempo"), intAt("MalditoAtaque"), false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 64, 64, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_MALDITO);
		break;
	case _enm_GOLEM:
		tr->setSpeed(20.0f);
		mngr_->addComponent<RenderComponent>(t, golem);
		mngr_->addComponent<HealthComponent>(t, intAt("GolemVida"));
		mngr_->addComponent<GolemComponent>(t);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("GolemRango"), intAt("Golemtiempo"), intAt("GolemAtaque"), false);
		mngr_->addComponent<FramedImage>(t, 10, 10, 100, 100, 40, 10, 46);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_GOLEM);
		break;
	case _enm_DALADO:
		tr->setSpeed(40.0f);
		mngr_->addComponent<RenderComponent>(t, demonioAlado);
		mngr_->addComponent<HealthComponent>(t, intAt("DemonioAladoVida"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("DemonioAladoRango"), intAt("DemonioAladotiempo"), intAt("DemonioAladoAtaque"), true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 150, 150, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_DALADO);
		break;
	case _enm_GOBLIN:
		tr->setSpeed(60.0f);
		mngr_->addComponent<RenderComponent>(t, goblin);
		mngr_->addComponent<HealthComponent>(t, intAt("GoblinVida"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("GoblinRango"), intAt("Goblintiempo"), intAt("GoblinAtaque"), false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 150, 150, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_GOBLIN);
		break;
	case _enm_ELFO:
		tr->setSpeed(20.0f);
		mngr_->addComponent<RenderComponent>(t, elfo);
		mngr_->addComponent<HealthComponent>(t, intAt("ElfoVida"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("ElfoRango"), intAt("Elfotiempo"), intAt("ElfoAtaque"), true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 100, 100, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_ELFO);
		break;
	case _enm_MMUERTE:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, mensajero);
		mngr_->addComponent<HealthComponent>(t, intAt("MensajeroVida"));
		RoutesCorrection(tr, route, 1.0f, 3.0f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("MensajeroRango"), intAt("Mensajerotiempo"), intAt("MensajeroAtaque"), true);
		mngr_->addComponent<FramedImage>(t, 8, 8, 140, 93, 8, 8, 15);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_MMUERTE);
		mngr_->addComponent<MensajeroMuerteComponent>(t);
		mngr_->setHandler(_hdlr_GHOST_ENEMIES, t);
		break;
	case _enm_ANGEL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, angel);
		mngr_->addComponent<HealthComponent>(t, intAt("AngelVida"));
		mngr_->addComponent<AngelComponent>(t, 100.0f);
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("AngelRango"), intAt("Angeltiempo"), intAt("AngelAtaque"), true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 122, 117, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_ANGEL);
		break;
	case _enm_DINFERNAL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, demonioInfernal);
		mngr_->addComponent<HealthComponent>(t, intAt("DemonioInfernalVida"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("DemonioInfernalRango"), intAt("DemonioInfernaltiempo"), intAt("DemonioInfernalAtaque"), true);
		mngr_->addComponent<FramedImage>(t, 8, 4, 64, 64, 16, 4, 19);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_DINFERNAL);
		break;
	case _enm_DREAL:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, defensor);
		mngr_->addComponent<HealthComponent>(t, intAt("DefensorVida"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("DefensorRango"), intAt("Defensortiempo"), intAt("DefensorAtaque"), true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 231, 190, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_DREAL);
		break;
	case _enm_CMALDITO:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, CMaldito);
		mngr_->addComponent<HealthComponent>(t, intAt("CMalditoVida"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("CMalditoRango"), intAt("CMalditotiempo"), intAt("CMalditoAtaque"), false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 64, 64, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_CMALDITO);
		mngr_->addComponent<CaballeroMalditoComponent>(t);
		break;
	case _enm_PRINCIPITO:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, principito);
		mngr_->addComponent<HealthComponent>(t, intAt("PrincipitoVida"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("PrincipitoRango"), intAt("Principitotiempo"), intAt("PrincipitoAtaque"), true);
		mngr_->addComponent<FramedImage>(t, 8, 1, 128, 128, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_PRINCIPITO);
		mngr_->addComponent<PrincipitoComponent>(t,3);
		break;
	case _enm_MONJE:
		tr->setSpeed(30.0f);
		mngr_->addComponent<RenderComponent>(t, monje);
		mngr_->addComponent<HealthComponent>(t, intAt("MonjeVida"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("MonjeRango"), intAt("Monjetiempo"), intAt("MonjeAtaque"), false);
		mngr_->addComponent<FramedImage>(t, 8, 1, 150, 150, 0, 8, 7);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_MONJE);
		mngr_->addComponent<MonjeComponent>(t,10.0f,2.5f);
		break;
	case _enm_MUERTE:
		tr->setSpeed(10.0f);
		mngr_->addComponent<RenderComponent>(t, muerte);
		mngr_->addComponent<HealthComponent>(t, intAt("MuerteVida"));
		RoutesCorrection(tr, route, 1.5f, 1.5f);
		tr->setPosition(route[0]);
		mngr_->addComponent<RouteComponent>(t, route);
		mngr_->addComponent<AttackComponent>(t, intAt("MuerteRango"), intAt("Muertetiempo"), intAt("MuerteAtaque"), true);
		mngr_->addComponent<FramedImage>(t, 1, 1, 100, 100, 0, 0, 1);
		mngr_->addComponent<EnemyTypeComponent>(t, _enm_MUERTE);
		break;


	}

	createSpawnAnimation(route[0]);

	if (type != _enm_MMUERTE) {
		mngr_->setHandler(_hdlr_ENEMIES, t);
	}
}

void generateEnemies::createSpawnAnimation(Vector2D pos) {
	Message m;
	m.id = _m_ANIM_CREATE;
	m.anim_create.idGrp = _grp_NATURALS_EFFECTS_HIGH;
	m.anim_create.animSpeed = 15;
	m.anim_create.iterationsToDelete = 1;
	m.anim_create.pos = pos;
	m.anim_create.frameInit = 1;
	m.anim_create.frameEnd = 24;
	m.anim_create.cols = 6;
	m.anim_create.rows = 5;
	m.anim_create.scale = { 100, 100 };
	m.anim_create.width = 273;
	m.anim_create.height = 273;
	m.anim_create.tex = gameTextures::enemy_spawn;
	mngr_->send(m);
}
