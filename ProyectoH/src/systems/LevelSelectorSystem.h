#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"

class LevelSelectorSystem : public System
{
public:
	static constexpr sysId_type id = _sys_LEVELSELECTOR;
	LevelSelectorSystem();
	virtual ~LevelSelectorSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override; 

private:
	/// <summary>
	/// Te devuelve al menu principal
	/// </summary>
	void backToMainMenu();
	/// <summary>
	/// Te carga PlayState
	/// </summary>
	void startGame();
	/// <summary>
	/// Llama a las funciones correspondientes dependiendo del tipo del boton cuando este es pulsado
	/// </summary>
	/// <param name="type">tipo del boton</param>
	/// <param name="bC">buttonComponent de la entidad</param>
	void callFunction(ButtonTypes type, ButtonComponent* bC);
	/// <summary>
	/// Añade un boton a la escena
	/// </summary>
	/// <param name="tex">textura base del boton</param>
	/// <param name="hov">textura del hover</param>
	/// <returns>la entidad del boton</returns>
	Entity* addButton(Vector2D pos, Vector2D scale, gameTextures tex, gameTextures hov, ButtonTypes type);
	/// <summary>
	/// Añade una imagen a la escena
	/// </summary>
	void addImage(Vector2D pos, Vector2D(scale), double rot, gameTextures t);

	//Botones de la escena
	Entity* backButtonEntity;
	Entity* playButtonEntity;
};

