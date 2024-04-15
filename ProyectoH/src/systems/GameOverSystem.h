#pragma once
#include "../ecs/System.h"

enum GameOverAnim {HEADER_ANIM, ROUNDS_ANIM, ENEMIES_ANIM, COINS_ANIM, BUTTON_ANIM, NONE_ANIM};

class GameOverSystem : public System
{
private:
	bool win; // false, ha perdido. true, ha ganado
	int currentLvl;
	int roundsPassed;
	float startTime = 1;
	float timer = startTime;
	GameOverAnim currentAnim = HEADER_ANIM;
	Entity* header;
	Entity* rounds;
	Entity* enemies;
	Entity* coins;
	float enemiesCont = 0;
	float coinsCont = 0;
	int enemiesDefeated;
	int coinsObtained;

public:
	static constexpr sysId_type id = _sys_GAMEOVER;
	GameOverSystem();
	virtual ~GameOverSystem(); 
	void initSystem() override;
	void receive(const Message& m) override; 
	void update() override;
};

