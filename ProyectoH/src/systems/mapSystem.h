#pragma once
#include "../ecs/System.h"
#include <iostream>
#include <fstream>
#include "../json/JSON.h"
#include "../sdlutils/SDLUtils.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <SDL.h>
#include <fstream>   
#include "../systems/IsometricLayer.h"

 

class mapSystem : public System {
private:
	static sysId_type id;
	uint8_t winner_;

	std::vector<MapLayer> m_layers;
	
public:
	mapSystem(std::string filename);
	virtual ~mapSystem();
	virtual void receive(const Message& m);
	void initSystem() override;
	void update() override;

	void loadMap(std::string filename);
	void loadTile(int id);
};