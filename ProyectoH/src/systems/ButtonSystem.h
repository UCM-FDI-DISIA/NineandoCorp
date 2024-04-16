#pragma once
#include "../ecs/System.h"
#include "../components/ButtonComponent.h"
#include <vector>

class ButtonSystem : public System
{
public: 
	static constexpr sysId_type id = _sys_BUTTON;
	const hdlrId_type hdlr_but_id;

	ButtonSystem(hdlrId_type but_id);
	virtual ~ButtonSystem();
	void receive(const Message& m) override;
	void initSystem() override;
	void update() override; 


	void manageButtons();
	void managePauseButtons();
	/// <summary>
	/// Crea un boton como entidad y lo a�ade al manager con grpId = _grp_HUD_FOREGROUND y hdlrId = button_id
	/// </summary>
	/// <param name="pos">posicion del boton</param>
	/// <param name="scale">escala del boton</param>
	/// <param name="tex">textura base del boton</param>
	/// <param name="hov">textura del hover</param>
	/// <param name="type">tipo del boton</param>
	Entity* addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type, int level = 0, Message m = Message());

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
	Entity* addText(const string& txt, const SDL_Color& color, const Vector2D& pos, const Vector2D& scale);

	/// <summary>
	/// Devuelve las monedas H acumuladas en la partida
	/// </summary>
	/// <returns>Las monedas H</returns>
	int getHMoney() { return HMoney_; };
private:
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
	void upgradeTower(twrId t, string idPrecioJSON);

	/// <summary>
	/// Actualiza la textura con el texto de las monedas a las monedas actuales
	/// </summary>
	void updateText();

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

	bool mActive;
	int money_;
	int HMoney_;
	int costs[_twr_SIZE];
	Entity* moneyText_;
};




