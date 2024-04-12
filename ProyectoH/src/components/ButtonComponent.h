#pragma once
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"

enum ButtonTypes {
	//Others
	pruebaButton, 
	exit_button,
	//MainMenu
	selector_main, enemies_main, pause_main, resume_main,
	//Level Selector
	level_selected, back_selector, play_wave,

	//Upgrades main menu
	upgrade_nexus, 
	upgrade_crystal_main,
	upgrade_slime_main, upgrade_bullet_main, 
	upgrade_sniper_main, upgrade_fenix_main,
	upgrade_clay_main, upgrade_enhancer_main,
	//Enemybook
	enemybook,

	// ----- HUD -----//
	crystal_drag,
	slime_drag,
	sniper_drag,
	clay_drag,
	bullet_drag,
	fenix_drag,
	enhancer_drag,

	// --- UPGRADE IN-GAME --- //
	upgrade_tower,
	exit_up_menu,

	// --- SELL --- //
	sell_tower,

	none
};
 
class ButtonComponent : public Component
{
	
public:
	static const cmpId id = cmpId::_BUTTON;

	ButtonComponent() : id_(), tr_(nullptr), hoverTexture_(), texture_(), msg_(Message()) {}
	ButtonComponent( ButtonTypes id, Message msg = Message()) : id_(id), tr_(nullptr), hoverTexture_(), texture_(), msg_(msg) {}
	~ButtonComponent() {}

	void initComponent() override;
	
	/// <param name="mousePos">posicion del puntero</param>
	/// <returns>id_ del boton en caso de que se haya pulsado encima del boton </returns>
	ButtonTypes isPressed(const Vector2D& mousePos);

	/// <summary>
	/// Comprueba si el puntero se situa encima del boton
	/// </summary>
	/// <param name="mousePos">Posicion del cursor</param>
	/// <returns></returns>
	bool hover(const Vector2D& mousePos);

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
 

	inline Message getMessage() { return msg_; }

	inline void setLevel(int currentLevel) { level = currentLevel; };

	inline int getLevel() const { return level; };
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
	//Mensaje del boton
	Message msg_;
	int level = 1;
};

