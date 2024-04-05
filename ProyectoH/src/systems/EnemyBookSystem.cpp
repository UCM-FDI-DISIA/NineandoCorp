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
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	//BACKGROUND
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = { 1000.0f , 600.0f };
	bS->addImage(pAux, sAux, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	//boton cerrar
	pAux = pAux + Vector2D(430.0f, -230.0f);
	sAux = { 70.0f, 70.0f };
	bS->addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);
    
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

	// Calcular la posici�n inicial del contenido
	float contentPosX = 350.f; // Posici�n inicial x del contenido
	float contentPosY = 300.f; // Posici�n y del contenido
	float contentPosYaux = 300.f; // Posici�n y del contenido aux
	float contentWidth = 100.f; // Ancho del contenido
	float contentHeight = 100.f; // Alto del contenido

	// A�adir im�genes de enemigos
	int enemies = 15;
	float spacingX = 120.f; // Espacio horizontal entre las im�genes de enemigos
	int t = 0;
	 auto text = gameTextures::large_box;
	for (size_t i = 0; i < enemies; i++) {
		// Calcular la posici�n de la imagen del enemigo
		Vector2D pAux = { contentPosX + t * spacingX, contentPosY };
		Vector2D sAux = { contentWidth, contentHeight };
		Vector2D sAuxbox = { contentWidth + 15, contentHeight + 15 };
		if (Vistos[i] == true)
		{
			bS->addImage(pAux, sAuxbox, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
			text = Texturas[i];
		}
		else {
			text = gameTextures::large_box;
		}
		bS->addImage(pAux, sAux, 0.0,text, _grp_HUD_FOREGROUND);
		t++;
		if (t%5 ==0 && t!= 0)
		{
			contentPosY += contentPosYaux / 2;
			t = 0;
		}
	}
}
void EnemyBookSystem::receive(const Message& m)
{
	EnemigoVisto(m.start_enemy_book.n, Vistos);
}

void EnemyBookSystem::update() {
}
void EnemyBookSystem::EnemigoVisto(int i, std::vector<bool>Vistos) {
	if (i >= 0 && i < Vistos.size()) {
		Vistos[i] = true;
	}
}