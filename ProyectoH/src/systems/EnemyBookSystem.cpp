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

	bool habilidad = false;
	int vel = 0;
	int vida = 0;
	int tipo = 0;
	int atq = 0;
	switch (i)
	{
		case 1:
			//coger datos json
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
		case 14:
			break;
		case 15:
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
	string nombre = "caballero";
	pAux = Vector2D{ 700,420 };
	sAux = Vector2D{ 120,100};
	SDL_Color NombreColor = { 255, 255, 255, 255 };
	bS->addText(nombre,NombreColor,pAux,sAux);
		//bS->addText(std::to_string(sdlutils().intConst().at("BalasPrecio")), moneyColor, { xAux * ((int)_twr_BULLET + 1) - 20 , heightH + 67 }, { bSize.getX() / 2 , 30 });

}