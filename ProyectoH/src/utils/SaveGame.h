#pragma once
#include <vector>
#include <string>
#include "../ecs/ecs.h"
class SaveGame
{	
private:
	int HCoins_;
	int levelsUnlocked_;

	int turretsLevel_[_twr_SIZE];


	bool enemiesBook_[_enm_SIZE];

public:
	SaveGame() :levelsUnlocked_(8), HCoins_(0) { std::fill_n(enemiesBook_, _enm_SIZE, true); std::fill_n(turretsLevel_, _twr_SIZE, 0); };

	int getHCoins() { return HCoins_; };
	void setHCoins(int h) { HCoins_ = h; };

	int getLevelsUnlocked() { return levelsUnlocked_; };
	void setLevelsUnlocked(int l) { levelsUnlocked_ = l; };

	int* getTurretsLevels() { return turretsLevel_; };

	bool* getEnemiesBook() { return enemiesBook_; };

	void saveFile();
	void loadFile();
	void checkEnemies(bool* enemies);
};

