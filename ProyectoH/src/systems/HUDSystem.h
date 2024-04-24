#pragma once
#include "../ecs/System.h"
#include "../components/ButtonComponent.h"
#include "ButtonSystem.h"
#include "../components/DragAndDrop.h"
#include "../components/LockComponent.h"
class HUDSystem : public System
{
public:

	static constexpr sysId_type id = _sys_HUD;

	HUDSystem();
	virtual ~HUDSystem();
	void receive(const Message& m) override;
	void initSystem() override;

	void update() override;

	bool isOnSelector(const Vector2D& pos) const {
		return pos.getY() + cameraOffset_->y < sdlutils().height() - twrSel_.selectorHeight;
	}
	/// <summary>
	/// Devuelve si el punto clicado esta encima del menu de mejora de la torre o no
	/// </summary>
	/// <param name="mPos">Clicked position</param>
	/// <returns>True si esta dentro, false si esta fuera</returns>
	bool isOnUpMenu(const Vector2D& mPos) const;

private: 
	struct UpgradeMenu{
		Entity* background;
		Entity* upgradeButton;
		Entity* twrName;
		Entity* twrLvl;
		Entity* exitButton;
		Entity* cost;
		Entity* lvlText;
		Entity* hpText;
		Entity* damageText;
		Entity* reloadText;
		Entity* sellButton;
		Entity* range;
		Entity* upCost;
		Entity* coinImg;
		Entity* frame;
		UpgradeMenu() :
			background(nullptr), //
			upgradeButton(nullptr), //
			twrName(nullptr), // 
			twrLvl(nullptr), // 
			exitButton(nullptr), //
			lvlText(nullptr), //
			sellButton(nullptr), //
			hpText(nullptr), //
			damageText(nullptr), //
			reloadText(nullptr), //
			cost(nullptr), //
			range(nullptr), //
			upCost(nullptr), //
			frame(nullptr), //
			coinImg(nullptr)
		{}

		~UpgradeMenu() {}
	};

	 struct TowerButton {

		Vector2D initialPos;
		Entity* button;
		Entity* img;
		Entity* coinImg;
		Entity* moneyTxt;

		TowerButton() : 
			initialPos(Vector2D()),
			button(nullptr), //
			coinImg(nullptr), //
			moneyTxt(nullptr), //
			img(nullptr) {
		}

		TowerButton(Entity* but, Entity* im, const Vector2D& pos, Entity* coin, Entity* money) : 
			initialPos(pos), //
			button(but), //
			coinImg(coin), //
			moneyTxt(money), // 
			img(im) {
		}
	};

	struct TowerSelector {
		std::vector<TowerButton> buttons;
		Entity* background;
		Entity* roundButton;
		int selectorHeight = 200;
		TowerSelector() :
			buttons(), //
			background(nullptr), //
			roundButton(nullptr) {}		
	};

	Entity* pauseButton;
	Entity* acelerateButton;

	inline string getTowerName(twrId tId) {
		string name = "";
		switch (tId)
		{ 
		case _twr_BULLET:
			name = "BULLET TOWER";
			break;
		case _twr_CLAY:
			name = "CLAY TOWER";
			break;
		case _twr_SLIME:
			name = "SLIME TOWER";
			break;
		case _twr_FENIX:
			name = "PHOENIX TOWER";
			break;
		case _twr_DIEGO:
			name = "SNIPER TOWER";
			break;
		case _twr_POWER:
			name = "ENHANCER TOWER";
			break;
		case _twr_CRISTAL:
			name = "CRYSTAL TOWER";
			break;
		default:
			break;
		}
		return name;
	}


	UpgradeMenu upM_;
	TowerSelector twrSel_;

	void exitUpgradeMenu();

	void showSelector(bool active);

	bool mActive;

	void NewAcelerationButton(float acel);

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

	void updateTowerInfo();

	// Espacio designado para los botones de compra de las torres
	float buttonsSpace_length_; 
	float infoSpace_length_;

	bool upMenuIsOn;
	bool canStartWave = false;

	//ofset de la camara al renderizar
	SDL_Rect* cameraOffset_;

	Entity* tower_;
	
};

