#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

// Constructorss
RenderSystem::RenderSystem() :
	winner_(0),
	fighterTr(nullptr),
	currStTxt(stateText::startText),
	enemyFighterTr(nullptr)
{
	textTextures[startText] = &sdlutils().msgs().at("Start");
	textTextures[pauseText] = &sdlutils().msgs().at("Continue");
	textTextures[winText] = &sdlutils().msgs().at("Win");
	textTextures[loseText] = &sdlutils().msgs().at("Lose");
	
	textTr[startText] = nullptr;
	textTr[pauseText] = nullptr;
	textTr[winText] = nullptr;
	textTr[loseText] = nullptr;

	textures[bulletTexture] = &sdlutils().images().at("Fire");
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
	addText(startText);
	addText(pauseText);
	addText(winText);
	addText(loseText);
}

//Renderiza cada entity por grupos
void RenderSystem::update() {
	sdlutils().clearRenderer();

	//LAYER 1 TILEMAP
	const auto& tilesl1 = mngr_->getEntities(_grp_TILES_L1);
	for (auto& t : tilesl1) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		textures[textureId]->render(tr->getRect(), tr->getRotation());
	}

	//LAYER 2 TILEMAP
	const auto& tilesl2 = mngr_->getEntities(_grp_TILES_L2);
	for (auto& t : tilesl2) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		textures[textureId]->render(tr->getRect(), tr->getRotation());
	}

	//LAYER 3 TILEMAP
	const auto& tilesl3 = mngr_->getEntities(_grp_TILES_L3);
	for (auto& t : tilesl3) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		textures[textureId]->render(tr->getRect(), tr->getRotation());
	}

	//Este grupo tiene que estar ordenado de arriba a abajo de la pantalla segun su transform (posicion y)
	//TOWERS
	const auto& towers = mngr_->getEntities(_grp_TOWERS);
	for (auto& t : towers) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		textures[textureId]->render(tr->getRect(), tr->getRotation());
	}

	//ENEMIES
	const auto& enemies = mngr_->getEntities(_grp_ENEMIES);
	for (auto& t : enemies) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		textures[textureId]->render(tr->getRect(), tr->getRotation());
	}

	// BULLETS
	const auto& buls = mngr_->getEntities(_grp_BULLETS);
	for (auto& b : buls) {
		Transform* tr = mngr_->getComponent<Transform>(b);
		gameTextures texture = mngr_->getComponent<RenderComponent>(b)->getTexture();
		textures[texture]->render(tr->getRect(), tr->getRotation());
	}
	
	//HUD BACKGROUND
	const auto& hud = mngr_->getEntities(_grp_HUD_BACKGROUND);
	for (auto& h : hud) {
		Transform* tr = mngr_->getComponent<Transform>(h);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(h)->getTexture();
		textures[textureId]->render(tr->getRect(), tr->getRotation());
	}

	//HUD FOREGROUND
	const auto& hud = mngr_->getEntities(_grp_HUD_FOREGROUND);
	for (auto& h : hud) {
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
	if (currStTxt != stateText::sttTxtSize) {
		textTextures[currStTxt]->render(textTr[currStTxt]->getRect());
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
	currStTxt = stateText::sttTxtSize;
}
void RenderSystem::onGameStart() {
	currStTxt = stateText::startText;
	update();
}
void RenderSystem::onGameOver(Uint8 winner) {
	winner_ = winner;
	currStTxt = (winner_ == 1) ? stateText::loseText : stateText::winText;
}

// Displays pause message
void RenderSystem::onPause() {
	currStTxt = stateText::pauseText;
	update();
}
// Hides pause message
void RenderSystem::onResume() {
	currStTxt = stateText::sttTxtSize;
}