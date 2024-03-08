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

enum tileId { lake, low, high };

class mapSystem : public System {
private:
	struct casilla{
		Vector2D position;
		bool isFree;
		tileId id;
	};
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_.
	void onRoundStart();
	void onGameStart();
	void onGameOver(Uint8 winner);
	// Displays pause message
	void onPause();
	// Hides pause message
	void onResume();

	uint8_t winner_;
	tmx::Vector2f m_chunkSize = tmx::Vector2f(64.f, 64.f);
	tmx::Vector2u m_MapTileSize;
	tmx::FloatRect m_globalBounds;
	vector<vector<casilla>> malla;

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
};