#include "SaveGame.h"
#include <iostream>
#include <cstring>
#include <fstream>

void SaveGame::loadFile() {

}

void SaveGame::saveFile() {
	std::ofstream fs("saves/save.sav", std::ios::out | std::ios::binary | std::ios::app);
	fs.write(reinterpret_cast<const char*>(&monedasH_), sizeof monedasH_);
	fs.close();
}