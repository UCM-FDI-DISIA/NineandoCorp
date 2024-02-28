#pragma once
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"

enum ButtonTypes {
	//Others
	pruebaButton, 
	//MainMenu
	selector_main, 
	//Level Selector
	start_game, back_selector,
	//Tower_menu
	glass_menu,
	slime_menu,
	bullet_menu,
	sniper_menu,
	fenix_menu,
	clay_menu,
	enhancer_menu,

	//Upgrades main menu
	upgrade_nexus, 
	upgrade_glass_main,
	upgrade_slime_main, upgrade_bullet_main, 
	upgrade_sniper_main, upgrade_fenix_main,
	upgrade_clay_main, upgrade_enhancer_main,

	// ----- HUD -----//
	


	none
};

class ButtonComponent : public Component
{
	
public:
	static const cmpId id = cmpId::_BUTTON;

	ButtonComponent( ButtonTypes id) : id_(id), tr_(nullptr) {}
	~ButtonComponent() {}

	void initComponent() override;

	ButtonTypes isPressed(Vector2D mousePos);
	bool hover(Vector2D mousePos);

	inline void setHover(gameTextures h) { hoverTexture = h; }
	inline void setTexture(gameTextures t) { texture = t; }

	inline gameTextures getTexture() { return texture; }
	inline gameTextures getHover() { return hoverTexture; }

	inline void setActive(bool b) { isActive_ = b; }
	inline bool isActive() { return isActive_; }
 
private:
	Transform* tr_;
	ButtonTypes id_;
	gameTextures texture;
	gameTextures hoverTexture;
	bool isActive_ = true;
};

