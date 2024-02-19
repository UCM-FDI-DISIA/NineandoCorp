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
	int i = 0;
	int j = 0;
	for (auto tile : layerIDs)
	{

		if (tile.ID == 2) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L1);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::hillTexture);
			
		}
		else if (tile.ID == 4) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L3);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::mountainTexture);
		}
		else if (tile.ID == 133) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L1);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::roadTexture);
		}
		else if (tile.ID == 81) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture1);
		}
		else if (tile.ID == 82) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture2);
		}
		else if (tile.ID == 83) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture3);
		}
		else if (tile.ID == 84) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture4);
		}
		else if (tile.ID == 85) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture5);
		}
		else if (tile.ID == 87) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture6);
		}
		else if (tile.ID == 88) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture7);
		}
		else if (tile.ID == 89) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture8);
		}
		else if (tile.ID == 90) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture9);
		}
		else if (tile.ID == 98) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture10);
		}
		else if (tile.ID == 99) {
			Entity* tile = mngr_->addEntity(_grp_TILES_L2);
			Vector2D tilePosition((layer.getOffset().x + i - j),
				(layer.getOffset().y + (i + j) / 2));
			mngr_->addComponent<Transform>(tile)->setPosition(tilePosition);
			mngr_->addComponent<RenderComponent>(tile, gameTextures::lakeTexture11);
		}
		i += m_MapTileSize.x;
		if (i % 2048 == 0)
		{
			i = 0;
			j += m_MapTileSize.x;
		}
	}
}

