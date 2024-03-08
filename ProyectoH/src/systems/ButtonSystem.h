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
private:

	void manageButtons();
	/// <summary>
	/// Crea un boton como entidad y lo añade al manager con grpId = _grp_HUD_FOREGROUND y hdlrId = button_id
	/// </summary>
	/// <param name="pos">posicion del boton</param>
	/// <param name="scale">escala del boton</param>
	/// <param name="tex">textura base del boton</param>
	/// <param name="hov">textura del hover</param>
	/// <param name="type">tipo del boton</param>
	Entity* addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type);

	/// <summary>
	/// Crea una imagen como entidad y lo añade al manager 
	/// </summary>
	/// <param name="pos">posicion de la imagen</param>
	/// <param name="scale">escala de la imagen</param>
	/// <param name="rot">rotacion de la imagen</param>
	/// <param name="t">textura de la imagen</param>
	/// <param name="grpId">id del grupo con el que se añade la entidad al manager</param>
	void addImage(const Vector2D& pos, const Vector2D& scale, const double rot, gameTextures t, grpId_type grpId);

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


};




