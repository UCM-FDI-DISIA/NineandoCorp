#pragma once
#include "../ecs/System.h"
#include "../components/ButtonComponent.h"

class HUDSystem : public System
{
public:

	static constexpr sysId_type id = _sys_HUD;

	HUDSystem();
	virtual ~HUDSystem();
	void receive(const Message& m) override;
	void initSystem() override;
	void update() override;
private: 
	void manageButtons();
	void addButton(const Vector2D& pos, const Vector2D& scale, gameTextures tex, gameTextures hov, ButtonTypes type);
	//void addImage(const Vector2D &pos, Vector2D(scale), double rot, gameTextures t, grpId_type grpId);

	void addImage(const Vector2D& pos, const Vector2D& scale, const double rot, gameTextures t, grpId_type grpId);
	void callFunction(ButtonTypes type, ButtonComponent* en);
	void pause();

	// Espacio designado para los botones de compra de las torres
	float buttonsSpace_length_; 
	float infoSpace_length_;
};

