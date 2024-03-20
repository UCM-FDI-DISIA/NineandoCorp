#pragma once
#include "../ecs/System.h"
#include "../components/ButtonComponent.h"

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
	/// <summary>
	/// Crea un boton como entidad y lo a�ade al manager con grpId = _grp_HUD_FOREGROUND y hdlrId = button_id
	/// </summary>
	/// <param name="pos">posicion del boton</param>
	/// <param name="scale">escala del boton</param>
	/// <param name="tex">textura base del boton</param>
	/// <param name="hov">textura del hover</param>
	/// <param name="type">tipo del boton</param>
	Entity* addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type);

	/// <summary>
	/// Crea una imagen como entidad y lo a�ade al manager 
	/// </summary>
	/// <param name="pos">posicion de la imagen</param>
	/// <param name="scale">escala de la imagen</param>
	/// <param name="rot">rotacion de la imagen</param>
	/// <param name="t">textura de la imagen</param>
	/// <param name="grpId">id del grupo con el que se a�ade la entidad al manager</param>
	Entity* addImage(const Vector2D& pos, const Vector2D& scale, const double rot, gameTextures t, grpId_type grpId);
private:
	/// <summary>
	/// Llama a las funciones correspondientes dependiendo del tipo del boton cuando este es pulsado
	/// </summary>
	/// <param name="type">tipo del boton</param>
	/// <param name="en">entidad correspondiente del boton</param>
	void callFunction(ButtonTypes type, Entity* en);

	/// <summary>
	/// Desactiva todos los botones de la escena
	/// </summary>
	void pauseAllButtons();

	/// <summary>
	/// Mensaje de carga de estado de selector de niveles
	/// </summary>
	void loadLevelSelector();

	/// <summary>
	/// Mensaje de carga enemyBook para ver los enemigos encontrados
	/// </summary>
	void Pause();

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
	void startGame();
	/// <summary>
	/// Envia mensaje para arrastrar 
	/// </summary>
	void dragTower(twrId tower);

	/// <summary>
	/// M�todo encargado de enviar el mensaje de mejorar una torre
	/// con x Id pasado por par�metro
	/// </summary>
	void upgradeTower(twrId t);

	/// <summary>
	/// Llamada al m�todo de mejora del Nexo
	/// </summary>
	void upgradeNexusMain();

	/// <summary>
	/// Llamada al m�todo de mejora de la Torre de Cristal
	/// </summary>
	void upgradeCrystalMain();

	/// <summary>
	/// Llamada al m�todo de mejora de la Torre de Slime
	/// </summary>
	void upgradeSlimeMain();

	/// <summary>
	/// Llamada al m�todo de mejora de la Torre Bullet
	/// </summary>
	void upgradeBulletMain();

	/// <summary>
	/// Llamada al m�todo de mejora de la Torre Sniper
	/// </summary>
	void upgradeSniperMain();

	/// <summary>
	/// Llamada al m�todo de mejora de la Torre Fenix
	/// </summary>
	void upgradeFenixMain();

	/// <summary>
	/// Llamada al m�todo de mejora de la Torre de Arcilla
	/// </summary>
	void upgradeClayMain();

	/// <summary>
	/// Llamada al m�todo de mejora de la Torre de Mejora
	/// </summary>
	void upgradeEnhancerMain();



};



