#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/RenderComponent.h"
#include "../components/Transform.h"
#include "../components/ButtonComponent.h"
class EnemyBookSystem : public System
{
private:
	bool* Vistos;

	//vector textura enemigo
	vector<gameTextures> Texturas{
		gameTextures::maestro_icon,
		gameTextures::acechante_icon,
		gameTextures::maldito_icon,
		gameTextures::golem_icon,
		gameTextures::demonioAlado_icon,
		gameTextures::goblin_icon,
		gameTextures::elfo_icon,
		gameTextures::mensajero_icon,
		gameTextures::angel_icon,
		gameTextures::demonioInfernal_icon,
		gameTextures::defensor_icon,
		gameTextures::CMaldito_icon,
		gameTextures::principito_icon,
		gameTextures::monje_icon,
		gameTextures::muerte_icon
	};
	vector<gameTextures> TexturasSilueta{
		gameTextures::maestro_de_almas_silueta,
		gameTextures::acechante_electrico_silueta,
		gameTextures::caballero_maldito_silueta,
		gameTextures::demonio_alado_silueta,
		gameTextures::golem_silueta,
		gameTextures::goblin_silueta,
		gameTextures::elfo_silueta,
		gameTextures::mensajero_silueta,
		gameTextures::angel_silueta,
		gameTextures::demonio_infernal_silueta,
		gameTextures::defensor_real_silueta,
		gameTextures::caballero_maldito_silueta,
		gameTextures::boss2_silueta,
		gameTextures::boss3_silueta,
		gameTextures::muerte_silueta,
		
	};
	//vector de textos
	vector<Entity*> texto;

	//Background position and scale
	Vector2D bPos, bSize;

	//Tamaño de la fuente del texto del cuerpo
	Vector2D font_size_body;
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
	
	std::vector<std::string> getDescription(basic_string<char> s) {
		return sdlutils().descriptions().at(s);
	}
public:
	static constexpr sysId_type id = _sys_ENEMYBOOK;
	virtual ~EnemyBookSystem();

	void initSystem() override;
	void EnemyPopUp(int i);
	void EnemyPopUpABILITY(int i);
	void receive(const Message& m) override;
	
};

