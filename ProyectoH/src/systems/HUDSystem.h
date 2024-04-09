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

	bool isOnSelector(const Vector2D& pos) {
		return pos.getY() + cameraOffset_->y < sdlutils().height() - twrSel_.selectorHeight;
	}

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

	struct TowerSelector {
		std::vector<Entity*> buttons;
		std::vector<Entity*> imgs;
		Entity* background;
		Entity* roundButton;
		int selectorHeight = 200;
		TowerSelector() :
			buttons(), //
			imgs(), //
			background(nullptr), //
			roundButton(nullptr) {}		
	};

	UpgradeMenu upM_;
	TowerSelector twrSel_;

	void exitUpgradeMenu();

	void showSelector(bool active);

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

	bool canStartWave = false;

	// Posiciones de los iconos de las torres
	std::vector<Vector2D> initial_pos;
	//ofset de la camara al renderizar
	SDL_Rect* cameraOffset_;
};

