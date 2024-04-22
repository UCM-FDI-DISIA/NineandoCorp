#include "EnemyBookSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"


EnemyBookSystem::~EnemyBookSystem()
{
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_ENEMYBOOK)) {
		mngr_->setAlive(en, false);
	}
	mngr_->refresh();
	mngr_->deleteAllHandlers(_hdlr_BUTTON_ENEMYBOOK);
}
void EnemyBookSystem::initSystem() {
	Vistos = game().getSaveGame()->getEnemiesBook();
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	//BACKGROUND
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = { 1000.0f , 600.0f };
	bS->addImage(pAux, sAux, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	//boton cerrar
	pAux = pAux + Vector2D(430.0f, -230.0f);
	sAux = { 70.0f, 70.0f };
	bS->addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

	// Calcular la posición inicial del contenido
	float contentPosX = 400.f; // Posición inicial x del contenido
	float contentPosY = 350.f; // Posición y del contenido
	float contentPosYaux = 300.f; // Posición y del contenido aux
	float contentWidth = 100.f; // Ancho del contenido
	float contentHeight = 100.f; // Alto del contenido


	// Añadir imágenes de enemigos
	float spacingX = 120.f; // Espacio horizontal entre las imágenes de enemigos
	int t = 0;

	auto text = gameTextures::large_box;
	for (size_t i = 0; i < _enm_SIZE; i++) {
		// Calcular la posición de la imagen del enemigo
		Vector2D pAux = { contentPosX + t * spacingX, contentPosY };
		Vector2D sAux = { contentWidth, contentHeight };
		Vector2D sAuxbox = { contentWidth + 15, contentHeight + 15 };
		Message m;
		m.id = _m_ENEMY_BOOKPOPUP;
		m.start_enemy_book_but.n = i;
		if (Vistos[i] == true)
		{
			text = Texturas[i];
			bS->addImage(pAux, sAuxbox, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
			bS->addButton(pAux, sAux, text, text, ButtonTypes::enemybook,0,0,0,m);

		}
		else {
			text = gameTextures::large_box;
			bS->addImage(pAux, sAuxbox, 0.0, text, _grp_HUD_FOREGROUND);
		}

		t++;
		if (t % 5 == 0 && t != 0)
		{
			contentPosY += contentPosYaux / 2;
			t = 0;
		}
	}
}
void  EnemyBookSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _m_ENEMY_BOOKPOPUP:
		EnemyPopUp(m.start_enemy_book_but.n);
		break;

		default:
		break;
	}
}
void EnemyBookSystem::EnemyPopUp(int i) {
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	//BACKGROUND
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = { 500.0f , 300.0f };
	bS->addImage(pAux, sAux, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	//BOTON CERRAR
	pAux = pAux + Vector2D(200, -100.0f);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

	string habilidad = "";
	string vel = "";
	string vida = "";
	string tipo = "";
	string atq = "";
	string nombre = "";
	string rango = "";
	string Tiempo = "";
	switch (i)
	{
		case 0:
			nombre = "Maestro de Almas";
			vida = std::to_string(sdlutils().intConst().at("MaestroVida"));
			atq = std::to_string(sdlutils().intConst().at("MaestroAtaque"));
			vel = std::to_string(sdlutils().intConst().at("MaestroVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Maestrotiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 1:
			nombre = "Acechante Electrico";
			vida = std::to_string(sdlutils().intConst().at("AcechanteVida"));
			atq = std::to_string(sdlutils().intConst().at("AcechanteAtaque"));
			vel = std::to_string(sdlutils().intConst().at("AcechanteVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Acechantetiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 2:
			nombre = "Maldito";
			vida = std::to_string(sdlutils().intConst().at("MalditoVida"));
			atq = std::to_string(sdlutils().intConst().at("MalditoAtaque"));
			vel = std::to_string(sdlutils().intConst().at("MalditoVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Malditotiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 3:
			nombre = "Golem";
			vida = std::to_string(sdlutils().intConst().at("GolemVida"));
			atq = std::to_string(sdlutils().intConst().at("GolemAtaque"));
			vel = std::to_string(sdlutils().intConst().at("GolemVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Golemtiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			
			break;
		case 4:
			nombre = "Demonio Alado";
			vida = std::to_string(sdlutils().intConst().at("DemonioAladoVida"));
			atq = std::to_string(sdlutils().intConst().at("DemonioAladoAtaque"));
			vel = std::to_string(sdlutils().intConst().at("DemonioAladoVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("DemonioAladotiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 5:
			nombre = "Goblin";
			vida = std::to_string(sdlutils().intConst().at("GoblinVida"));
			atq = std::to_string(sdlutils().intConst().at("GoblinAtaque"));
			vel = std::to_string(sdlutils().intConst().at("GoblinVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Goblintiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 6:
			nombre = "Elfo";
			vida = std::to_string(sdlutils().intConst().at("ElfoVida"));
			atq = std::to_string(sdlutils().intConst().at("ElfoAtaque"));
			vel = std::to_string(sdlutils().intConst().at("ElfoVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Elfotiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 7:
			nombre = "Mensajero de la Muerte";
			vida = std::to_string(sdlutils().intConst().at("MensajeroVida"));
			atq = std::to_string(sdlutils().intConst().at("MensajeroAtaque"));
			vel = std::to_string(sdlutils().intConst().at("MensajeroVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Mensajerotiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 8:
			nombre = "Angel";
			vida = std::to_string(sdlutils().intConst().at("AngelVida"));
			atq = std::to_string(sdlutils().intConst().at("AngelAtaque"));
			vel = std::to_string(sdlutils().intConst().at("AngelVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Angeltiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 9:
			nombre = "Demonio Infernal";
			vida = std::to_string(sdlutils().intConst().at("DemonioInfernalVida"));
			atq = std::to_string(sdlutils().intConst().at("DemonioInfernalAtaque"));
			vel = std::to_string(sdlutils().intConst().at("DemonioInfernalVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("DemonioInfernaltiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 10:
			nombre = "Defensor";
			vida = std::to_string(sdlutils().intConst().at("DefensorVida"));
			atq = std::to_string(sdlutils().intConst().at("DefensorAtaque"));
			vel = std::to_string(sdlutils().intConst().at("DefensorVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Defensortiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 11:
			nombre = "C.Maldito";
			vida = std::to_string(sdlutils().intConst().at("CMalditoVida"));
			atq = std::to_string(sdlutils().intConst().at("CMalditoAtaque"));
			vel = std::to_string(sdlutils().intConst().at("CMalditoVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("CMalditotiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 12:
			nombre = "Principito";
			vida = std::to_string(sdlutils().intConst().at("PrincipitoVida"));
			atq = std::to_string(sdlutils().intConst().at("PrincipitoAtaque"));
			vel = std::to_string(sdlutils().intConst().at("PrincipitoVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Principitotiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 13:
			nombre = "Monje";
			vida = std::to_string(sdlutils().intConst().at("MonjeVida"));
			atq = std::to_string(sdlutils().intConst().at("MonjeAtaque"));
			vel = std::to_string(sdlutils().intConst().at("MonjeVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Monjetiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		case 14:
			nombre = "Muerte";
			vida = std::to_string(sdlutils().intConst().at("MuerteVida"));
			atq = std::to_string(sdlutils().intConst().at("MuerteAtaque"));
			vel = std::to_string(sdlutils().intConst().at("MuerteVelocidad"));
			Tiempo = std::to_string(sdlutils().intConst().at("Muertetiempo"));
			//tipo = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//rango = std::to_string(sdlutils().intConst().at("MalditoVida"));
			//habilidad = std::to_string(sdlutils().intConst().at("MalditoVida"));
			break;
		default:
		break;
	}
	//AÑADIR IMG ENEMIGO
	pAux = Vector2D{500,470};
	sAux = Vector2D{ 100,100 };
	bS->addImage(pAux, sAux + Vector2D{50,50}, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	bS->addImage(pAux, sAux,0.0,Texturas[i], _grp_HUD_FOREGROUND);
	//AÑADIR NOMBRE
	pAux = Vector2D{ 700,420 };
	sAux = Vector2D{ 210,70};
	SDL_Color NombreColor = { 255, 255, 255, 255 };
	bS->addText(nombre, NombreColor, pAux, sAux);
	//AÑADIR ATAQUE
	pAux = Vector2D{ 650,470 };
	sAux = Vector2D{ 90,30 };
	bS->addText("Ataque: " + atq, NombreColor, pAux, sAux);
	//AÑADIR VIDA
	pAux = Vector2D{ 800,470 };
	bS->addText("Vida: " +vida, NombreColor, pAux, sAux);
	//AÑADIR VELOCIDAD
	pAux = Vector2D{ 650,510 };
	bS->addText("Velocidad: " +vel, NombreColor, pAux, sAux);
	//AÑADIR TIEMPO ATAQUE
	sAux = Vector2D{ 100,34 };
	pAux = Vector2D{ 800,510};
	bS->addText("Vel.Ataque: " +Tiempo, NombreColor, pAux, sAux);

	//AÑADIR RANGO
	//pAux = Vector2D{ 700,420 };
	//bS->addText(, NombreColor, pAux, sAux);
	//AÑADIR HABILIDAD
	//pAux = Vector2D{ 700,420 };
	//bS->addText(nombre, NombreColor, pAux, sAux);

}