#pragma once
#include "..//ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"

class MainMenuSystem : public System
{
public:
	static constexpr sysId_type id = _sys_MAINMENU;
	MainMenuSystem();
	virtual ~MainMenuSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override ;

private: 
	/// <summary>
	/// Crea un boton como entidad y lo añade al manager con grpId = _grp_HUD_FOREGROUND y hdlrId = _hdlr_BUTTON
	/// </summary>
	/// <param name="pos">posicion del boton</param>
	/// <param name="scale">escala del boton</param>
	/// <param name="tex">textura base del boton</param>
	/// <param name="hov">textura del hover</param>
	/// <param name="type">tipo del boton</param>
	void addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type);

	/// <summary>
	/// Crea una imagen como entidad y lo añade al manager 
	/// </summary>
	/// <param name="pos">posicion de la imagen</param>
	/// <param name="scale">escala de la imagen</param>
	/// <param name="rot">rotacion de la imagen</param>
	/// <param name="t">textura de la imagen</param>
	/// <param name="grpId">id del grupo con el que se añade la entidad al manager</param>
	void addImage(const Vector2D& pos, const Vector2D & scale, const double rot, gameTextures t, grpId_type grpId);

	/// <summary>
	/// Crea un texto a partir de una textura como entidad y lo añade al manager
	/// </summary>
	/// <param name="pos">posicion del texto</param>
	/// <param name="scale">escala del texto</param>
	/// <param name="rot">rotacion del texto</param>
	/// <param name="grpId">id del grupo con el que se añade la entidad al manager</param>
	void addText(const Vector2D& pos, const Vector2D& scale, const double rot, grpId_type grpId);

	/// <summary>
	/// Llama a las funciones correspondientes dependiendo del tipo del boton cuando este es pulsado
	/// </summary>
	/// <param name="type">tipo del boton</param>
	/// <param name="en">entidad correspondiente del boton</param>
	void callFunction(ButtonTypes type, ButtonComponent* en);

	/// <summary>
	/// Mensaje de carga de estado de selector de niveles
	/// </summary>
	void loadLevelSelector();

	/// <summary>
	/// Desactiva todos los botones de la escena
	/// </summary>
	void pauseAllButtons();

	/// <summary>
	/// Envia mensaje para subir de nivel el nexo
	/// </summary>
	void upgradeNexus();
};

