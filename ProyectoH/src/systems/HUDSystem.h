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

private: 
	struct UpgradeMenu{
		Entity* background;
		Entity* upgradeButton;
		Entity* twrDescription;
		Entity* twrLvl;
		Entity* exitButton;
		Entity* cost;
		UpgradeMenu() :
			background(nullptr), //
			upgradeButton(nullptr), //
			twrDescription(nullptr), // 
			twrLvl(nullptr), // 
			exitButton(nullptr), //
			cost(nullptr)
		{}

		~UpgradeMenu() {}
	};
	UpgradeMenu upM_;

	void exitUpgradeMenu();

	void changeText(TextComponent* tC, string newTxt);

	bool mActive;

	void showUpgradeMenu(Entity* twr, const Vector2D& pos);

	int intAt(basic_string<char> s) { return sdlutils().intConst().at(s); }
	float floatAt(basic_string<char> s) { return sdlutils().floatConst().at(s); }
	Cell* getCellFromTile(const Vector2D& pos);
	Vector2D resetScale(twrId tId);
	/// <summary>
	/// Arrastra el icono de la torre correspondiente dependiendo de la posicion del cursor
	/// </summary>
	/// <param name=""></param>
	void dragTowerIcon(Entity* e); 

	void enableAllButtons(bool t);

	// Espacio designado para los botones de compra de las torres
	float buttonsSpace_length_; 
	float infoSpace_length_;
	//boton de empezar la oleada
	Entity* play = nullptr;
	bool canStartWave = false;

	// Para la interaccion con el HUD, no tocar de momento
	std::vector<Entity*> towers_imgs;
	std::vector<Vector2D> initial_pos;
	std::vector<Vector2D> intial_scale;
	//std::vector<std::pair<Entity*, Entity*>> tower_selector_; 
};

