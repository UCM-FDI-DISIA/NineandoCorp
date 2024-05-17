#pragma once
#include "../ecs/System.h"
#include "../utils/Vector2D.h"
#include "../components/ButtonComponent.h"
#include "../components/SliderComponent.h"
#include <vector>

class ButtonSystem : public System
{
public: 
	static constexpr sysId_type id = _sys_BUTTON;
	hdlrId_type hdlr_but_id;

	ButtonSystem(hdlrId_type but_id);
	virtual ~ButtonSystem();
	void receive(const Message& m) override;
	void initSystem() override;
	void update() override; 


	void manageButtons();
	void managePauseButtons();
	void manageKeys();
	/// <summary>
	/// Crea un boton como entidad y lo a�ade al manager con grpId = _grp_HUD_FOREGROUND y hdlrId = button_id
	/// </summary>
	/// <param name="pos">posicion del boton</param>
	/// <param name="scale">escala del boton</param>
	/// <param name="tex">textura base del boton</param>
	/// <param name="hov">textura del hover</param>
	/// <param name="type">tipo del boton</param>
	Entity* addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type, int level = 0,int width = 0, int height= 0, Message m = Message());

	/// <summary>
	/// Crea una imagen como entidad y lo a�ade al manager 
	/// </summary>
	/// <param name="pos">posicion de la imagen</param>
	/// <param name="scale">escala de la imagen</param>
	/// <param name="rot">rotacion de la imagen</param>
	/// <param name="t">textura de la imagen</param>
	/// <param name="grpId">id del grupo con el que se a�ade la entidad al manager</param>
	Entity* addImage(const Vector2D& pos, const Vector2D& scale, const double rot, gameTextures t, grpId_type grpId);
	
	
	/// <summary>
	/// A�ade una entitdad de tipo texto al manager
	/// </summary>
	/// <returns> La propia entidad </returns>
	Entity* addText(const string& txt, const SDL_Color& color, const Vector2D& pos, const Vector2D& scale, grpId gId = _grp_TEXTS);



	void changeButtonsIdHandler(hdlrId_type id) { hdlr_but_id = id; };

	Entity* addSlider(const Vector2D& pos, const Vector2D& scale, gameTextures tex, grpId_type grpId, SliderTypes slTy);

	/// <summary>
	/// Devuelve las monedas H acumuladas en la partida
	/// </summary>
	/// <returns>Las monedas H</returns>
	int getHMoney() { return HMoney_; };

	/// <summary>
	/// Devuelve las monedas doradas acumuladas en la partida
	/// </summary>
	/// <returns>Las monedas doradas</returns>
	int getMoney() { return money_; }

	void setCanstartWave(bool canstartwave) { canStartWave = canstartwave; }

	void generateUpgradeImages();

	void generateNexusImage(int level, int health);

	void generateNexusText(int level);

	void updateNexusImage(int level, int health);
private:
	/// <summary>
	/// Añade el dinero correspondiente a la torre vendida
	/// </summary>
	/// <param name="twr"></param>
	void sellTower(Entity* twr);
	/// <summary>
	/// Llama a las funciones correspondientes dependiendo del tipo del boton cuando este es pulsado
	/// </summary>
	/// <param name="type">tipo del boton</param>
	/// <param name="en">entidad correspondiente del boton</param>
	void callFunction(ButtonTypes type, Entity* en);

	/// <summary>
	/// Crea el texto con las monedas H
	/// </summary>
	void generateHMoneyText();

	void generateUpgradeMoneyTexts();

	/// <summary>
	/// Desactiva todos los botones de la escena
	/// </summary>
	void pauseAllButtons();

	void enableAllButton(bool b, grpId bType);

	/// <summary>
	/// Mensaje de carga de estado de selector de niveles
	/// </summary>
	void loadLevelSelector();

	/// <summary>
	/// Mensaje para la pausa
	/// </summary>
	void Pause(bool onPause);

	/// <summary>
	/// Mensaje para la pausa
	/// </summary>
	void Acelerate(float _acel);

	/// <summary>
	/// Mensaje para la pausa
	/// </summary>
	void Warning(string text, ButtonTypes butTyp);

	/// <summary>
	/// Mensaje de carga enemyBook para ver los enemigos encontrados
	/// </summary>
	void EnemyBook();


	/// <summary>
	/// Te devuelve al menu principal
	/// </summary>
	void backToMainMenu();

	/// <summary>
	/// Te carga PlayState
	/// </summary>
	void startGame(Entity* en);

	/// <summary>
	/// Envia mensaje para arrastrar 
	/// </summary>
	void dragTower(twrId tower);

	/// <summary>
	/// M�todo encargado de enviar el mensaje de mejorar una torre
	/// con x Id pasado por par�metro 
	/// </summary>
	void upgradeTower(twrId t, string idPrecioJSON, Entity* bC);

	/// <summary>
	/// Actualiza la textura con el texto de las monedas a las monedas actuales
	/// </summary>
	void updateText(int money, const Vector2D& font_size);


	/// <summary>
	/// Funcion que realiza el mensaje START_GAME
	/// </summary>
	void OnStartGame();

	/// <summary>
	/// Envia mensaje para salirse del menu de mejora
	/// </summary>
	void exitUpMenu();

	void startWave();

	void showTempText(string txt, const SDL_Color& color, const Vector2D& pos, const Vector2D& scale, int time);

	void Config();


	void stopConfig( Entity* bC);
	void setUpgradeTex(Entity* bC);
	bool canStartWave = true;
	bool mActive;
	bool resolutionActive;
	int numAcelButs; // cuantos botones hay para acelerar el tiempo
	int cauntAcelButs; // contador 
	int money_;
	int HMoney_;
	int costs[_twr_SIZE];
	int const towerLevelMax = 5;
	bool isPlayState;
	Entity* moneyText_;
	SDL_Point	mouse;
	SDL_bool 	mouse_follow = SDL_FALSE;
	SDL_Point 	mouse_offset;

	//Texto del coste de las torres
	Entity* bulletMoneyText_;
	Entity* cristalMoneyText_;
	Entity* slimeMoneyText_;
	Entity* diegoMoneyText_;
	Entity* enhancerMoneyText_;
	Entity* fenixMoneyText_;
	Entity* dirtMoneyText_;

	//Texto del nivel de la torre
	Entity* bulletLvlText_;
	Entity* cristalLvlText_;
	Entity* slimeLvlText_;
	Entity* diegoLvlText_;
	Entity* enhancerLvlText_;
	Entity* fenixLvlText_;
	Entity* dirtLvlText_;

	//Imagenes de las torres
	Entity* bulletImage_;
	Entity* cristalImage_;
	Entity* slimeImage_;
	Entity* diegoImage_;
	Entity* enhancerImage_;
	Entity* fenixImage_;
	Entity* dirtImage_;
	
	//Textos e imagendes del nexo
	Entity* nexusImage_;
	Entity* nexusLvl_;
	Entity* nexushealth_;
	Entity* nexusLifebar_;
	Entity* nexusLifebarBg_;
	Entity* nexusPriceText_;

	//Tamaño de texto de las monedas "in-game"
	Vector2D font_size_coin_HUD;
	//Tamaño de texto de las monedas H del nexo
	Vector2D font_size_Hcoin_nexus;
	//Separacion entre la imagen de la torre y el borde derecho de la pantalla
	float twr_img_separation;
	//Separacion entre el dinero y el borde derecho de la pantalla
	float info_separation = 45.0f;
	//Tamaño de las imagenes de las torres
	Vector2D towerImagesSize;
	//Separacion del texto de nivel
	const float lvl_separation = 220.0f;
	//Tamaño de fuente para los textos de nivel y coste
	const Vector2D font_size = { 12.0f, 30.0f };

	void throwUpgradeAnim(const Vector2D& pos); 

	int intAt(basic_string<char> s) { return sdlutils().intConst().at(s); }
	float floatAt(basic_string<char> s) { return sdlutils().floatConst().at(s); }

};




