#include "mapSystem.h"

mapSystem::mapSystem(){}

mapSystem::~mapSystem() {
}

void mapSystem::initSystem(){
    SDLUtils::init("Map", 800, 600, "resources/config/nivelPrueba.json");
}

void mapSystem::receive(const Message& m) {

}

void mapSystem::update(){}
void mapSystem::loadMap( std::string filename){
    std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));
    if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
        throw "Something went wrong while load/parsing '" + filename + "'";
    }
    JSONObject root = jValueRoot->AsObject();
    JSONValue* jValue = nullptr;

    jValue = root["layers"];
    if (jValue != nullptr) {
        if (jValue->IsArray()) {
            sdl_resource_table<size_t> layers;
            layers.emplace(jValue->AsArray().size());
            for (auto& v : jValue->AsArray()) {
                if (v->IsObject()) {
                    JSONObject vObj = v->AsObject();
                    JSONArray data = vObj["data"]->AsArray();
                    std::string name = vObj["name"]->AsString();

                    std::cout << "Loading font with id: " << name << std::endl;


                    for (size_t i = 0; i < data.size(); i++)
                    {
                        int id = data[i]->AsNumber();
                        loadTile(id);
                    }

                    layers.emplace(name, data);
                }
                else {
                    throw "'layers' array in '" + filename
                        + "' includes and invalid value";
                }
            }
        }
        else {
            throw "'layers' is not an array in '" + filename + "'";
        }
    }
}
void mapSystem::loadTile(int id){}

