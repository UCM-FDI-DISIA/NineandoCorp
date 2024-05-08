#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"
#include "ButtonSystem.h" 

class TowerInfoSystem : public System
{
public:
	static constexpr sysId_type id = _sys_INFO;
	TowerInfoSystem(twrId tId) : 
	tower_id(tId)
	{}
	TowerInfoSystem() : tower_id() {}
	virtual ~TowerInfoSystem();

	void initSystem() override;
	void receive(const Message& m) override;

private: 

	twrId tower_id;
	ButtonSystem* bs_;

	//Background position and scale
	Vector2D bPos, bSize;

	//Tamaño de la fuente del texto del cuerpo
	Vector2D font_size_body;
	//Tamaño de la fuente del texto de los subtitulos
	Vector2D font_size_subtitle;
	//Tamaño de la fuente del texto de titulo
	Vector2D font_size_title;
	//Posicion inicial en el eje y de las stats
	float stats_initial_pos_y;
	//Separacion del cuerpo respecto el titulo
	float body_separation;
	//Separacion entre lineas
	float between_line_offset;
	//Separacion entre la descripcion general y las mejoras de estadisticas
	float stats_separation;
	//Separacion del borde derecho
	float right_separation;
	//Color del texto del cuerpo
	SDL_Color body_c;
	//Color del testo de titulo y subtitulo
	SDL_Color title_c;


	/// <summary>
	/// Crea el texto del nombre de la torre
	/// </summary>
	void setTowerName(); 
	/// <summary>
	/// Crea los textos correspondientes a la descripcion general de la torre y sus estadisticas base
	/// </summary>
	void setGeneralDesc(); 
	/// <summary>
	/// Crea los textos de las estadisticas que se mejoran en cada nivel
	/// </summary>
	void setUpStats();
	/// <summary>
	/// Devuelve el string correspondiente del mapa de strings "descriptions"
	/// </summary>
	/// <param name="s">valor del parametro en el mapa de strings</param>
	/// <returns>String de la descripcion</returns>
	std::vector<std::string> getDescription(basic_string<char> s) {
		return sdlutils().descriptions().at(s);
	}
};

