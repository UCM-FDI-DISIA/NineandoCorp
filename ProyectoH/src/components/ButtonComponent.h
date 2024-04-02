#pragma once
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"

enum ButtonTypes {
	//Others
	pruebaButton, 
	exit_button,
	//MainMenu
	selector_main, enemies_main, pause_main,
	//Level Selector
	start_game, back_selector,

	//Upgrades main menu
	upgrade_nexus, 
	upgrade_crystal_main,
	upgrade_slime_main, upgrade_bullet_main, 
	upgrade_sniper_main, upgrade_fenix_main,
	upgrade_clay_main, upgrade_enhancer_main,

	// ----- HUD -----//
	crystal_drag,
	slime_drag,
	sniper_drag,
	clay_drag,
	bullet_drag,
	fenix_drag,
	enhancer_drag,



	none
};

class ButtonComponent : public Component
{
	
public:
	static const cmpId id = cmpId::_BUTTON;

	ButtonComponent( ButtonTypes id) : id_(id), tr_(nullptr) {}
	~ButtonComponent() {}

	void initComponent() override;
	
	/// <param name="mousePos">posicion del puntero</param>
	/// <returns>id_ del boton en caso de que se haya pulsado encima del boton </returns>
	ButtonTypes isPressed(Vector2D mousePos);

	/// <summary>
	/// Comprueba si el puntero se situa encima del boton
	/// </summary>
	/// <param name="mousePos">Posicion del cursor</param>
	/// <returns></returns>
	bool hover(Vector2D mousePos);

	/// <summary>
	/// Establece la textura del hover
	/// </summary>
	/// <param name="h"> Textura del hover</param>
	inline void setHover(gameTextures h) { hoverTexture_ = h; }

	/// <summary>
	/// Establece la textura base del boton
	/// </summary>
	/// <param name="t"> Textura base del boton </param>
	inline void setTexture(gameTextures t) { texture_ = t; }
	
	/// <returns> Textura del boton</returns>
	inline gameTextures getTexture() { return texture_; }

	/// <returns> Textura del hover</returns>
	inline gameTextures getHover() { return hoverTexture_; }

	/// <summary>
	/// Activa y desactiva el boton
	/// </summary>
	/// <param name="b">booleano si activo o no</param>
	inline void setActive(bool b) { isActive_ = b; }

	/// <returns>Si el boton está activo o no</returns>
	inline bool isActive() { return isActive_; }
 
private:
	//Transform del boton
	Transform* tr_;
	//Id del boton
	ButtonTypes id_;
	//Textura predefinida del boton
	gameTextures texture_;
	//Textura del hover del boton
	gameTextures hoverTexture_;
	//Atributo que define si el boton es interactuable o no
	bool isActive_ = true;
};

