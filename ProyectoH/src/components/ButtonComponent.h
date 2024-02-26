#pragma once
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"

enum ButtonTypes {

	pruebaButton, backButton, playButtonMenu, upgradeNexus, upgradeGlassTower,
	upgradeSlimeTower, upgradeBulletTower, upgradeSniperTower, upgradeFenixTower,
	upgradeClayTower, upgradeEnhancerTower, none
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
 
private:
	Transform* tr_;
	ButtonTypes id_;
	gameTextures texture;
	gameTextures hoverTexture;
};

