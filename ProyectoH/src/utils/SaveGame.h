#pragma once
#include <vector>
#include <string>
#include "../ecs/ecs.h"
class SaveGame
{	
private:
	int HCoins_ = 0;
	int levelsUnlocked_ = 8;

	int turretsLevel_[_twr_SIZE] = {0};


	bool enemiesBook_[_enm_SIZE] = {true};

public:
	SaveGame() {};

	int getHCoins() { return HCoins_; };
	void setHCoins(int h) { HCoins_ = h; };

	int getLevelsUnlocked() { return levelsUnlocked_; };
	void setLevelsUnlocked(int l) { levelsUnlocked_ = l; };

	int* getTurretsLevels() { return turretsLevel_; };
	//void setTurretsLevels(int* turretsLevel, int turretsLevelSize ) { turretsLevel_ = turretsLevel; }

	bool* getEnemiesBook() { return enemiesBook_; };
	//void setTurretsLevels(int* enemiesBook, int enemiesBookSize) { enemiesBookSize_ = enemiesBookSize; enemiesBook_ = enemiesBook_; }

	void saveFile();
	void loadFile();
};

