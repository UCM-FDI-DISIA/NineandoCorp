#pragma once

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Types.hpp>
#include "../ecs/Entity.h"

#include <memory>
#include <vector>
#include <array>
#include <map>
#include <string>
#include <limits>
#include <iostream>
#include <cmath>
class MapLayer{
public:
	MapLayer(const tmx::Map& map, std::size_t idx) {
		const auto& layers = map.getLayers();
		if (map.getOrientation() == tmx::Orientation::Isometric &&
			idx < layers.size() && layers[idx]->getType() == tmx::Layer::Type::Tile) {
			const auto tileSize = map.getTileSize();
			m_chunkSize.x = std::floor(m_chunkSize.x / tileSize.x) * tileSize.x;
			m_chunkSize.y = std::floor(m_chunkSize.y / tileSize.y) * tileSize.y;
			m_MapTileSize.x = map.getTileSize().x;
			m_MapTileSize.y = map.getTileSize().y;
			const auto& layer = layers[idx]->getLayerAs<tmx::TileLayer>();

			createChunks(map, layer);

			auto mapSize = map.getBounds();
			m_globalBounds.width = mapSize.width;
			m_globalBounds.height = mapSize.height;
		}
	}
	~MapLayer() = default;
	
	

	void createChunks(const tmx::Map& map, const tmx::TileLayer& layer) {
		
		const auto& tileSets = map.getTilesets();
		const auto& layerIDs = layer.getTiles();

		for (auto i = tileSets.rbegin(); i != tileSets.rend(); ++i)
		{
			for (auto tile : layerIDs)
			{
				if (tile.ID == 2) {
					tyleMap.push_back(new Entity(tileId::_idPRADERA));
				}
				else if(tile.ID == 4)
					tyleMap.push_back(new Entity(tileId::_idMONTANA));
				else if (tile.ID == 133)
					tyleMap.push_back(new Entity(tileId::_idCAMINOS));
				else if (tile.ID == 85) {
					tyleMap.push_back(new Entity(tileId::_idLAGOS));
				}
				else if (tile.ID > 80 && tile.ID < 101)
					tyleMap.push_back(new Entity(tileId::_idBORDELAGOS));
				
			}
		}
		
	}
private:
	tmx::Vector2f m_chunkSize = tmx::Vector2f(64.f, 64.f);
	tmx::Vector2u m_MapTileSize;
	tmx::FloatRect m_globalBounds;

	std::vector<Entity*> tyleMap;
};

