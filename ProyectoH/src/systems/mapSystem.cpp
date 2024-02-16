#include "mapSystem.h"

mapSystem::mapSystem(std::string filename){
    loadMap(filename);
}

mapSystem::~mapSystem() {
}

void mapSystem::initSystem(){
    
}

void mapSystem::receive(const Message& m) {

}

void mapSystem::update(){}
void mapSystem::loadMap(std::string filename) {

    tmx::Map map;
    map.load(filename);

    const auto& layers = map.getLayers();
    for (std::size_t i = 0; i < layers.size(); ++i) {
        if (layers[i]->getType() == tmx::Layer::Type::Tile) {
            m_layers.push_back(MapLayer(map, i));
        }
    }

}
void mapSystem::loadTile(int id){

}

