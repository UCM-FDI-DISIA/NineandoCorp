#include "EnemyBookSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
// Definir el tamaño de la barra de desplazamiento
const float SCROLLBAR_WIDTH = 600.f;
const float SCROLLBAR_HEIGHT = 20.f;

EnemyBookSystem::EnemyBookSystem()
{
}
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
    //vector enemigos para ver si han sido avistados
	vector<bool> Vistos(15);
	for (int i = 0; i < Vistos.size(); ++i) {
		//si se han matado a un enemigo, se comprueba si ese enemigo esta a false y si es asi se cambia a true
	}
	//vector textura enemigo
	vector<gameTextures> Texturas(15);

	// Calcular la posición inicial del contenido
	float contentPosX = 350.f; // Posición inicial x del contenido
	float contentPosY = 300.f; // Posición y del contenido
	float contentPosYaux = 300.f; // Posición y del contenido aux
	float contentWidth = 50.f; // Ancho del contenido
	float contentHeight = 50.f; // Alto del contenido

	// Añadir imágenes de enemigos
	int enemies = 15;
	float spacingX = 120.f; // Espacio horizontal entre las imágenes de enemigos
	int t = 0;
	 auto text = gameTextures::large_box;
	for (size_t i = 0; i < enemies; i++) {
		// Calcular la posición de la imagen del enemigo
		Vector2D pAux = { contentPosX + t * spacingX, contentPosY };
		Vector2D sAux = { contentWidth, contentHeight };
		if (Vistos[i] == true)
		{
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
}

void EnemyBookSystem::update() {
}