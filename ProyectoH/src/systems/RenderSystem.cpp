#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

struct cmpIsometricY {
	cmpIsometricY(Manager* mngr_) { this->mngr_ = mngr_; }
	bool operator ()(Entity* e1, Entity* e2) {
		if (mngr_->getComponent<Transform>(e1)->getY() <= mngr_->getComponent<Transform>(e2)->getY())
			return true;
		return false;
	}
	Manager* mngr_;
};

// Constructorss
RenderSystem::RenderSystem() :
	winner_(0)
{
	textures[square] = &sdlutils().images().at("square");
	textures[tileSet] = &sdlutils().images().at("map");
	textures[play] = &sdlutils().images().at("play");
	textures[playHover] = &sdlutils().images().at("play_hover");
	textures[bulletTowerTexture] = &sdlutils().images().at("Bullet_Tower");
	textures[cristalTowerTexture] = &sdlutils().images().at("cristal_tower");
	textures[phoenixTowerTexture] = &sdlutils().images().at("Phoenix_Tower");
	/*textures[slimeTowerTexture] = &sdlutils().images().at("Slime_Tower");*/
	textures[boosterTowerTexture] = &sdlutils().images().at("booster_tower");
	/*textures[sniperTowerTexture] = &sdlutils().images().at("Sniper_Tower");
	textures[clayTowerTexture] = &sdlutils().images().at("Clay_Tower");*/
	cursorTexture = &sdlutils().images().at("cursor");
	cursorTexture2 = &sdlutils().images().at("cursorpress");
}


RenderSystem::~RenderSystem() {
}

// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void RenderSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_GAMESTART:
		onGameStart();
		break;
	case _m_GAMEOVER:
		//onGameOver(m.winner_data.n);
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

	//Este control tiene que estar en el main control sistem
	////Control de camara
	if (ih().isKeyDown(SDLK_UP) && offset.y < limtop) {
		offset.y += 50;
	}
	else if (ih().isKeyDown(SDLK_LEFT) && offset.x < limleft) {
		offset.x += 50;
	}
	else if (ih().isKeyDown(SDLK_RIGHT) && offset.x > limright) {
		offset.x -= 50;
	}
	else if (ih().isKeyDown(SDLK_DOWN) && offset.y > limbot) {
		offset.y -= 50;
	}
	//tmp->update();

	//LAYER 1 TILEMAP
	const auto& tilesl1 = mngr_->getEntities(_grp_TILES_L1);
	for (auto& t : tilesl1) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect = mngr_->getComponent<FramedImage>(t)->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset.x;
		trRect.y += offset.y;
		textures[textureId]->render(srcRect,trRect);
	}

	//LAYER 2 TILEMAP
	const auto& tilesl2 = mngr_->getEntities(_grp_TILES_L2);
	for (auto& t : tilesl2) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect = mngr_->getComponent<FramedImage>(t)->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset.x;
		trRect.y += offset.y;
		textures[textureId]->render(srcRect, trRect);
	}

	//LAYER 3 TILEMAP
	const auto& tilesl3 = mngr_->getEntities(_grp_TILES_L3);
	for (auto& t : tilesl3) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect = mngr_->getComponent<FramedImage>(t)->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset.x;
		trRect.y += offset.y;
		textures[textureId]->render(srcRect, trRect);
	}

	//Este grupo tiene que estar ordenado de arriba a abajo de la pantalla segun su transform (posicion y)
	// NO CAMBIAR LECHES
	//TOWERS AND ENEMIES
	auto& towers = mngr_->getEntities(_grp_TOWERS_AND_ENEMIES);
	sort(towers.begin(),towers.end(), cmpIsometricY(mngr_));
	for (auto& t : towers) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset.x;
		trRect.y += offset.y;
		textures[textureId]->render(trRect, tr->getRotation());
	}

	// BULLETS
	const auto& buls = mngr_->getEntities(_grp_BULLETS);
	for (auto& b : buls) {
		Transform* tr = mngr_->getComponent<Transform>(b);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(b)->getTexture();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset.x;
		trRect.y += offset.y;
		textures[textureId]->render(trRect, tr->getRotation());
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

	//Renderizar cursor
	int x, y;
	bool pointerdown = false;
	Uint32 mouseState = SDL_GetMouseState(&x, &y);
	if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		pointerdown = true;
	}
	else {
		pointerdown = false;
	}

	SDL_Rect cursorRect = { x, y, 41, 64 };

	if (pointerdown)
	{
		cursorTexture2->render(cursorRect);
	}
	else {
		cursorTexture->render(cursorRect);
	}

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