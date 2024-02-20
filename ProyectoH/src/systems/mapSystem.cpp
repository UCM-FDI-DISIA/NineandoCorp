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
	int i = 1300 / 2;
	int j = 0;
	float sep = 1.34;
	const auto tileSize = map.getTileSize();
	for (auto tile : layerIDs)
	{
		Entity* entityTile = nullptr;
		Vector2D tilePosition(((layer.getOffset().x + i - j)/ sep ),
			((layer.getOffset().y + (i + j) / 2)) / sep);
		if (tile.ID == 2) {
			entityTile = mngr_->addEntity(_grp_TILES_L1);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::hillTexture);
		}
		else if (tile.ID == 4) {
			entityTile = mngr_->addEntity(_grp_TILES_L3);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::mountainTexture);
		}
		else if (tile.ID == 133) {
			entityTile = mngr_->addEntity(_grp_TILES_L1);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::roadTexture);
		}
		else if (tile.ID == 81) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture1);
		}
		else if (tile.ID == 82) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture2);
		}
		else if (tile.ID == 83) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture3);
		}
		else if (tile.ID == 84) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture4);
		}
		else if (tile.ID == 85) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture5);
		}
		else if (tile.ID == 87) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture6);
		}
		else if (tile.ID == 88) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture7);
		}
		else if (tile.ID == 89) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture8);
		}
		else if (tile.ID == 90) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture9);
		}
		else if (tile.ID == 98) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture10);
		}
		else if (tile.ID == 99) {
			entityTile = mngr_->addEntity(_grp_TILES_L2);
			mngr_->addComponent<RenderComponent>(entityTile, gameTextures::lakeTexture11);
		}
		if (entityTile) 
			mngr_->addComponent<Transform>(entityTile)->setPosition(tilePosition);
		
		i += m_chunkSize.x;
		if (i >= (layer.getSize().x * m_chunkSize.x) + 650) {
			i = 1300 / 2;
			j += m_chunkSize.y;
		}
	}
}

