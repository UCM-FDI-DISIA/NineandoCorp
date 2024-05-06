#pragma once
#include "..//ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"
#include "../systems/ButtonSystem.h" 

class MainMenuSystem : public System
{
public:
	static constexpr sysId_type id = _sys_MAINMENU;
	MainMenuSystem();
	virtual ~MainMenuSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override ;
	void createNexusImage();
	void updateNexusImage();

	// Niveles de nexo y torres
	int* turrentLevels;	// Nexo última torre

private: 
	bool mActive;


	/// <summary>
	/// Añade el boton de informacion en base a la torre correspondiente
	/// </summary>
	/// /// <param name="bS">: puntero al ButtonSystem</param>
	/// <param name="info_size">: escala del boton</param>
	/// <param name="tId">: id de la torre</param>
	/// <param name="yOffset">: offset del boton en el eje y para posicion de boton</param>
	/// <param name="info_separation">: separacion del borde de la pantalla</param>
	void addInfoButton(ButtonSystem* bS, const Vector2D& info_size, twrId tId, int yOffset, float info_separation);

	/// <summary>
	/// Crea un texto a partir de una textura como entidad y lo añade al manager
	/// </summary>
	/// <param name="pos">posicion del texto</param>
	/// <param name="scale">escala del texto</param>
	/// <param name="rot">rotacion del texto</param>
	/// <param name="grpId">id del grupo con el que se añade la entidad al manager</param>
	void addNexusText();

	int intAt(basic_string<char> s) { return sdlutils().intConst().at(s); }
	float floatAt(basic_string<char> s) { return sdlutils().floatConst().at(s); }
};

