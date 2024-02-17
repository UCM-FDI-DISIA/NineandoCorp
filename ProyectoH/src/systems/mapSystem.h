#pragma once
#include "../ecs/System.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Types.hpp>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/RenderComponent.h"

#include <memory>
#include <vector>
#include <array>
#include <map>
#include <string>
#include <limits>
#include <iostream>
#include <cmath>

 

class mapSystem : public System {
private:
	uint8_t winner_;
	tmx::Vector2f m_chunkSize = tmx::Vector2f(64.f, 64.f);
	tmx::Vector2u m_MapTileSize;
	tmx::FloatRect m_globalBounds;
	
public:
	static constexpr sysId_type id = _sys_MAP;

	mapSystem(std::string filename);
	virtual ~mapSystem();
	virtual void receive(const Message& m);
	void initSystem() override;
	void update() override;

	void loadMap(std::string filename);
	void loadTile(const tmx::Map& map, const tmx::TileLayer& layer);
};