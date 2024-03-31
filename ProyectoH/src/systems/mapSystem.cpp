#include "mapSystem.h"

mapSystem::mapSystem(std::string filename): filename(filename), winner_(0){
	net = new NetMap(32);
}

mapSystem::~mapSystem() {
}

void mapSystem::initSystem(){
	Message m;
	m.id = _m_ROUND_START;
	m.start_game_data.netmap = net;
	m.start_game_data.level = level;
	mngr_->send(m, true);
}

void mapSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
			level++;
			break;
	case _m_PAUSE:
		onPause();
		break;
	case _m_OFFSET_CONTEXT:
		net->setOffset(m.offset_context.offset);
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

	const auto tileSize = map.getTileSize();
	tileSize_ = {(float)tileSize.x, (float)tileSize.y};

	const auto& layers = map.getLayers();
	for (std::size_t i = 0; i < layers.size(); ++i) {
		if (map.getOrientation() == tmx::Orientation::Isometric && layers[i]->getType() == tmx::Layer::Type::Tile) {
			tileSize_ = map.getTileSize();
			m_chunkSize.x = std::floor(m_chunkSize.x / tileSize_.x) * tileSize_.x;
			m_chunkSize.y = std::floor(m_chunkSize.y / tileSize_.y) * tileSize_.y;
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

/// <summary> hola </summary>
/// <param name='map'>mapa con los tiles</param>
/// <param name='layer'>las capas</param>
/// <returns> Lo que devuelve</returns>
void mapSystem::loadTile(const tmx::Map& map, const tmx::TileLayer& layer){
	const auto& tileSets = map.getTilesets();
	const auto& layerIDs = layer.getTiles();
	int i = (WIN_WIDTH + 200)/ 2;
	int j = 0;
	float sep = 1.34;
	int n = 0;
	int col = 0, fil = 0;
	for (auto tile : layerIDs)
	{
		n++;
		if (tile.ID != 0) {
			Entity* entityTile = nullptr;
			Vector2D tilePosition(((layer.getOffset().x + i - j) / sep),
				((layer.getOffset().y + (i + j) / 2)) / sep);

			if (tile.ID == 2 || tile.ID == 133) {

				entityTile = mngr_->addEntity(_grp_TILES_L1);
				Cell* c = new Cell();
				c->position = { tilePosition.getX() + 48, tilePosition.getY() + 24 };
				c->isFree = true;
				c->id = TILE_LOW;
				net->setCell(fil - 1, col - 1 , c);
			}
			else if (tile.ID > 80 && tile.ID < 100) {
				entityTile = mngr_->addEntity(_grp_TILES_L2);
				Cell* c = new Cell();
				c->position = { tilePosition.getX() + 48, tilePosition.getY() + 24 };
				c->isFree = false;
				c->id = TILE_LAKE;
				net->setCell(fil - 1, col - 1, c);
			}
			else {
				entityTile = mngr_->addEntity(_grp_TILES_L3);
				Cell* c = new Cell();
				c->position = { tilePosition.getX() + 48, tilePosition.getY() + 24};
				c->isFree = true;
				c->id = TILE_HIGH;
				net->setCell(fil, col, c);
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
		fil++;
		if (fil == 32) {
			fil = 0;
			col++;
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

	loadMap(filename + std::to_string(level) + ".tmx");
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
