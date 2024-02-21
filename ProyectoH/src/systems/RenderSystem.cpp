#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

// Constructorss
RenderSystem::RenderSystem() :
	winner_(0)
{
	/*textures[square] = &sdlutils().images().at("square");*/
	textures[hillTexture] = &sdlutils().images().at("map1");
	textures[roadTexture] = &sdlutils().images().at("map133");
	textures[mountainTexture] = &sdlutils().images().at("map3");
	textures[lakeTexture1] = &sdlutils().images().at("map81");
	textures[lakeTexture2] = &sdlutils().images().at("map82");
	textures[lakeTexture3] = &sdlutils().images().at("map83");
	textures[lakeTexture4] = &sdlutils().images().at("map84");
	textures[lakeTexture5] = &sdlutils().images().at("map85");
	textures[lakeTexture6] = &sdlutils().images().at("map87");
	textures[lakeTexture7] = &sdlutils().images().at("map88");
	textures[lakeTexture8] = &sdlutils().images().at("map89");
	textures[lakeTexture9] = &sdlutils().images().at("map90");
	textures[lakeTexture10] = &sdlutils().images().at("map98");
	textures[lakeTexture11] = &sdlutils().images().at("map99");
	textures[towerTexture] = &sdlutils().images().at("Bullet_Tower");
}


RenderSystem::~RenderSystem() {
}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void RenderSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_GAMESTART:
		onGameStart();
		break;
	case _m_GAMEOVER:
		onGameOver(m.winner_data.n);
		break;
	case _m_PAUSE:
		onPause();
		break;
	case _m_RESUME:
		onResume();
		break;
	}
}
// Inicializar el sistema, etc.
void RenderSystem::initSystem() {
}

//Renderiza cada entity por grupos
void RenderSystem::update() {
	sdlutils().clearRenderer();

	if (ih().isKeyDown(SDLK_UP)) {
		offset.setY(offset.getY() + 50);
	}
	else if (ih().isKeyDown(SDLK_LEFT)) {
		offset.setX(offset.getX() + 50);
	}
	else if (ih().isKeyDown(SDLK_RIGHT)) {
		offset.setX(offset.getX() - 50);
	}
	else if (ih().isKeyDown(SDLK_DOWN)) {
		offset.setY(offset.getY() - 50);
	}

	//LAYER 1 TILEMAP
	const auto& tilesl1 = mngr_->getEntities(_grp_TILES_L1);
	for (auto& t : tilesl1) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect rect = tr->getRect();
		rect.x += offset.getX();
		rect.y += offset.getY();
		textures[textureId]->render(rect, tr->getRotation());
	}

	//LAYER 2 TILEMAP
	const auto& tilesl2 = mngr_->getEntities(_grp_TILES_L2);
	for (auto& t : tilesl2) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect rect = tr->getRect();
		rect.x += offset.getX();
		rect.y += offset.getY();
		textures[textureId]->render(rect, tr->getRotation());
	}

	//LAYER 3 TILEMAP
	const auto& tilesl3 = mngr_->getEntities(_grp_TILES_L3);
	for (auto& t : tilesl3) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect rect = tr->getRect();
		rect.x += offset.getX();
		rect.y += offset.getY();
		textures[textureId]->render(rect, tr->getRotation());
	}

	//Este grupo tiene que estar ordenado de arriba a abajo de la pantalla segun su transform (posicion y)
	//TOWERS AND ENEMIES
	const auto& towers = mngr_->getEntities(_grp_TOWERS_AND_ENEMIES);
	for (auto& t : towers) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect rect = tr->getRect();
		rect.x += offset.getX();
		rect.y += offset.getY();
		textures[textureId]->render(rect, tr->getRotation());
	}

	// BULLETS
	const auto& buls = mngr_->getEntities(_grp_BULLETS);
	for (auto& b : buls) {
		Transform* tr = mngr_->getComponent<Transform>(b);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(b)->getTexture();
		SDL_Rect rect = tr->getRect();
		rect.x += offset.getX();
		rect.y += offset.getY();
		textures[textureId]->render(rect, tr->getRotation());
	}
	
	//HUD BACKGROUND
	const auto& hudB = mngr_->getEntities(_grp_HUD_BACKGROUND);
	for (auto& h : hudB) {
		Transform* tr = mngr_->getComponent<Transform>(h);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(h)->getTexture();
		textures[textureId]->render(tr->getRect(), tr->getRotation());
	}

	//HUD FOREGROUND
	const auto& hudF = mngr_->getEntities(_grp_HUD_FOREGROUND);
	for (auto& h : hudF) {
		Transform* tr = mngr_->getComponent<Transform>(h);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(h)->getTexture();
		textures[textureId]->render(tr->getRect(), tr->getRotation());
	}

	//DRAG AND DROP
	const auto& dnd = mngr_->getEntities(_grp_HUD_DRAG_AND_DROP);
	for (auto& e : dnd) {
		Transform* tr = mngr_->getComponent<Transform>(e);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(e)->getTexture();
		textures[textureId]->render(tr->getRect(), tr->getRotation());
	}

	// TEXTS
	/*if (currStTxt != stateText::sttTxtSize) {
		textTextures[currStTxt]->render(textTr[currStTxt]->getRect());
	}*/


	sdlutils().presentRenderer();
}

// Creates an Entity with correspondant text texture and transform
void RenderSystem::addText(stateText stt) {
	int scale = sdlutils().intConst().at("textScale");
	Entity* text = mngr_->addEntity();
	Vector2D size = Vector2D(textTextures[startText]->width(), textTextures[startText]->height()) * scale;
	textTr[stt] = mngr_->addComponent<Transform>(text);
	textTr[stt]->setPosition(
		Vector2D(sdlutils().width() / 2, sdlutils().intConst().at("pressSpaceMessageY"))
		- size / 2);
	textTr[stt]->setScale(size);
}


// Para gestionar los mensajes correspondientes y actualizar los atributos
// winner_ y state_.
void RenderSystem::onRoundStart() {
}
void RenderSystem::onGameStart() {
}
void RenderSystem::onGameOver(Uint8 winner) {
}

// Displays pause message
void RenderSystem::onPause() {
}
// Hides pause message
void RenderSystem::onResume() {
}