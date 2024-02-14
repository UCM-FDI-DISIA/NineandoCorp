#pragma once
#include "../ecs/System.h"
#include <iostream>
#include <fstream>
#include "../json/JSON.h"
#include "../sdlutils/SDLUtils.h"
#include <SDL.h>
#include <fstream>   
 

class mapSystem : public System {
private:
	static sysId_type id;
	uint8_t winner_;
public:
	mapSystem();
	virtual ~mapSystem();
	virtual void receive(const Message& m);
	void initSystem() override;
	void update() override;

	template<typename T>
	using sdl_resource_table = std::unordered_map<std::string, T>;
	void loadMap(std::string filename);
	void loadTile(int id);
};