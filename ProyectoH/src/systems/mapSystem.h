#pragma once
#include "../ecs/System.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Types.hpp>
#include <tmxlite/Tileset.hpp>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/RenderComponent.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../game/Game.h"


#include <memory>
#include <vector>
#include <array>
#include <map>
#include <string>
#include <limits>
#include <iostream>
#include <cmath>
#include "../utils/NetMap.h"

class mapSystem : public System {
private:
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_.
	void onGameStart();

	uint8_t winner_;
	tmx::Vector2f m_chunkSize = tmx::Vector2f(64.f, 64.f);
	tmx::Vector2u m_MapTileSize;
	tmx::FloatRect m_globalBounds;
	NetMap* net;
	Vector2D tileSize_;
	std::string filename;
	
public:
	static constexpr sysId_type id = _sys_MAP;

	mapSystem(std::string filename);
	virtual ~mapSystem();
	virtual void receive(const Message& m);
	void initSystem() override;
	void update() override;

	void loadMap(std::string filename);
	void loadTile(const tmx::Map& map, const tmx::TileLayer& layer);
	Vector2D getTileSize() const { return tileSize_; }

	NetMap* getMalla() { return net; };
};