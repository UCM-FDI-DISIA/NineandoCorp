#pragma once
#include <vector>
#include <string>
class SaveGame
{	
private:
	int monedasH_ = 0;
	std::vector<int>* turretsLevel_;
	int levelsDesb;
	std::vector<std::string>* enemiesBook_;

public:
	int getHCoins() { return monedasH_; };
	void setHCoins(int h) { monedasH_ = h; };

	void saveFile();
	void loadFile();
};

