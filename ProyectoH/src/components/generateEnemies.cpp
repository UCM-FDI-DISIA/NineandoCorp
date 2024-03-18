#include "generateEnemies.h"

void generateEnemies::initComponent() {

}
void generateEnemies::generateEnemy() {

}
void generateEnemies::addGroupEnemies(){
	std::string id = "nivel" + std::to_string(level) + "oleada" + std::to_string(wave) + "grupo" + std::to_string(grp);
	auto spawneo = &sdlutils().spawns().at(id);
	spawnGroup = spawneo;
}
