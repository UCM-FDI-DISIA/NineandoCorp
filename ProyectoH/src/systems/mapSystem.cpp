#include "mapSystem.h"

mapSystem::mapSystem(std::string filename): filename(filename), winner_(0){
    
}

mapSystem::~mapSystem() {
}

void mapSystem::initSystem(){
	loadMap(filename);
}

void mapSystem::receive(const Message& m) {

}

void mapSystem::update(){}

void mapSystem::loadMap(std::string filename) {

    tmx::Map map;
    map.load(filename);

	const auto& layers = map.getLayers();
	for (std::size_t i = 0; i < layers.size(); ++i) {
		if (map.getOrientation() == tmx::Orientation::Isometric && layers[i]->getType() == tmx::Layer::Type::Tile) {
			const auto tileSize = map.getTileSize();
			m_chunkSize.x = std::floor(m_chunkSize.x / tileSize.x) * tileSize.x;
			m_chunkSize.y = std::floor(m_chunkSize.y / tileSize.y) * tileSize.y;
			m_MapTileSize.x = map.getTileSize().x;
			m_MapTileSize.y = map.getTileSize().y;
			const auto& layer = layers[i]->getLayerAs<tmx::TileLayer>();

			loadTile(map, layer);

			auto mapSize = map.getBounds();
			m_globalBounds.width = mapSize.width;
			m_globalBounds.height = mapSize.height;
		}
	}

	
}
void mapSystem::loadTile(const tmx::Map& map, const tmx::TileLayer& layer){
	const auto& tileSets = map.getTilesets();
	const auto& layerIDs = layer.getTiles();
	int i = (WIN_WIDTH + 200)/ 2;
	int j = 0;
	float sep = 1.34;
	int n = 0;
	for (auto tile : layerIDs)
	{
		n++;
		if (tile.ID != 0) {
			Entity* entityTile = nullptr;
			Vector2D tilePosition(((layer.getOffset().x + i - j) / sep),
				((layer.getOffset().y + (i + j) / 2)) / sep);

			if (tile.ID == 2 || tile.ID == 133) {

				entityTile = mngr_->addEntity(_grp_TILES_L1);
			}
			else if (tile.ID > 80 && tile.ID < 100) {
				entityTile = mngr_->addEntity(_grp_TILES_L2);
			}
			else {
				entityTile = mngr_->addEntity(_grp_TILES_L3);
			}
			mngr_->addComponent<FramedImage>(entityTile, 10, 16, m_chunkSize.x, m_chunkSize.y, tile.ID -1);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::tileSet);
			if (entityTile) {
				const auto transform = mngr_->addComponent<Transform>(entityTile);
				transform->setPosition(tilePosition);
				/*transform->setWidth(32);
				transform->setHeight(32);*/
			}
		}
		
			
			
		
		i += m_chunkSize.x;
		if (i >= (layer.getSize().x * (m_chunkSize.x)) + (WIN_WIDTH + 200) / 2) {
			i = (WIN_WIDTH + 200) / 2;
			j += m_chunkSize.y;
		}
	}
}

