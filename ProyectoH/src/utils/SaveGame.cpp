#include "SaveGame.h"
#include <iostream>
#include <string>
#include <fstream>  
#include <filesystem>

SaveGame::SaveGame() : levelsUnlocked_(1), HCoins_(1000) {
	std::fill_n(enemiesBook_, _enm_SIZE, false); 
	//std::fill_n(enemiesBook_, _twr_SIZE, 4); //Sustituir esto por lo de abajo para tener todas las torretas desbloqueadas
	for (int i = 0; i < _twr_SIZE; i++) {
		if (i == _twr_CLAY || i == _twr_BULLET || i == _twr_NEXUS)
			turretsLevel_[i] = 1;
		else
			turretsLevel_[i] = 0;
	}
}

void SaveGame::loadFile() {
	std::ifstream fs("saves/save.sav", std::ios::in | std::ios::binary); 
	if (!fs) {
		cout << "No se ha podido abrir el archivo de guardado.";
	}
	else{
		fs.read(reinterpret_cast<char*>(&HCoins_), sizeof HCoins_);
		fs.read(reinterpret_cast<char*>(&levelsUnlocked_), sizeof levelsUnlocked_);
		for (int i = 0; i < _twr_SIZE; i++)
			fs.read(reinterpret_cast<char*>(&turretsLevel_[i]), sizeof turretsLevel_[i]);
		for (int i = 0; i < _enm_SIZE; i++)
			fs.read(reinterpret_cast<char*>(&enemiesBook_[i]), sizeof enemiesBook_[i]);
		fs.close();

		if (!fs.good())
			cout << "Ha ocurrido un error al leer el archivo de guardado.";
	}
}

namespace fs = std::filesystem;
void SaveGame::saveFile() {

	if (!fs::is_directory("saves") || !fs::exists("saves")) { // Check if src folder exists
		fs::create_directory("saves"); // create src folder
	}

	std::ofstream fs("saves/save.sav", std::ios::out | std::ios::binary);
	if (!fs) {
		cout << "No se ha podido abrir el archivo de guardado.";
	}
	else {
		fs.write(reinterpret_cast<const char*>(&HCoins_), sizeof HCoins_);
		fs.write(reinterpret_cast<const char*>(&levelsUnlocked_), sizeof levelsUnlocked_);
		for(int i = 0; i < _twr_SIZE; i++)
			fs.write(reinterpret_cast<const char*>(&turretsLevel_[i]), sizeof turretsLevel_[i]);
		for (int i = 0; i < _enm_SIZE; i++)
			fs.write(reinterpret_cast<const char*>(&enemiesBook_[i]), sizeof enemiesBook_[i]);
		fs.close();

		if (!fs.good())
			cout << "Ha ocurrido un error al escribir en el archivo de guardado.";
	}
}

void SaveGame::checkEnemies(bool* enemies) {
	for (int i = 0; i < _enm_SIZE; i++) {
		if (enemies[i])
			enemiesBook_[i] = true;
	}
}