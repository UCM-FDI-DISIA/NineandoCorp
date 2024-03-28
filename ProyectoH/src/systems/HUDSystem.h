#pragma once
#include "../ecs/System.h"
#include "../components/ButtonComponent.h"
#include "ButtonSystem.h"
#include "../components/DragAndDrop.h"

class HUDSystem : public System
{
public:

	static constexpr sysId_type id = _sys_HUD;

	HUDSystem();
	virtual ~HUDSystem();
	void receive(const Message& m) override;
	void initSystem() override;

	void update() override;

	void resetTowerIcon(twrId tId);
private: 
	int intAt(basic_string<char> s) { return sdlutils().intConst().at(s); }
	
	/// <summary>
	/// Arrastra el icono de la torre correspondiente dependiendo de la posicion del cursor
	/// </summary>
	/// <param name=""></param>
	void dragTowerIcon(Entity* e); 

	// Espacio designado para los botones de compra de las torres
	float buttonsSpace_length_; 
	float infoSpace_length_;


	// Para la interaccion con el HUD, no tocar de momento
	std::vector<Entity*> towers_imgs;
	std::vector<Vector2D> initial_pos;
	std::vector<Vector2D> intial_scale;
	//std::vector<std::pair<Entity*, Entity*>> tower_selector_; 
};

