#include "mapSystem.h"

mapSystem::mapSystem(std::string filename): filename(filename), winner_(0){
	int size = 1;
	bool incremento = true;
	for (int i = 0; i < 64; i++) {
		malla.push_back(vector<casilla>(size));
		if (incremento)
			size++;
		else
			size--;
	}
}

mapSystem::~mapSystem() {
}

void mapSystem::initSystem(){
	loadMap(filename);
}

void mapSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_GAMESTART:
		onGameStart();
		break;
	case _m_GAMEOVER:
		//onGameOver(m.winner_data.n);
		break;
	case _m_PAUSE:
		onPause();
		break;
	case _m_RESUME:
		onResume();
		break;
	}
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
				malla[j][i].position = tilePosition;
				malla[j][i].isFree = false;
				malla[j][i].id = lake;
			}
			else if (tile.ID > 80 && tile.ID < 100) {
				entityTile = mngr_->addEntity(_grp_TILES_L2);
				malla[j][i].position = tilePosition;
				malla[j][i].isFree = true;
				malla[j][i].id = low;
			}
			else {
				entityTile = mngr_->addEntity(_grp_TILES_L3);
				malla[j][i].position = tilePosition;
				malla[j][i].isFree = true;
				malla[j][i].id = high;
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
// Para gestionar los mensajes correspondientes y actualizar los atributos
// winner_ y state_.
void mapSystem::onRoundStart() {

	loadMap(filename);
}
void mapSystem::onGameStart() {
}
void mapSystem::onGameOver(Uint8 winner) {
}

// Displays pause message
void mapSystem::onPause() {
}
// Hides pause message
void mapSystem::onResume() {
}
