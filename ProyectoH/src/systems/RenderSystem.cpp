#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

struct cmpIsometricY {
	cmpIsometricY(Manager* mngr_) { this->mngr_ = mngr_; }
	bool operator ()(Entity* e1, Entity* e2) {
		if (mngr_->getComponent<Transform>(e1)->getY() < mngr_->getComponent<Transform>(e2)->getY())
			return true;
		return false;
	}
	Manager* mngr_;
};

// Constructorss
RenderSystem::RenderSystem() : winner_(0)
{
	*offset = build_sdlrect(0, 0, 0, 0);

	//Towers
	textures[square] = &sdlutils().images().at("square");
	textures[tileSet] = &sdlutils().images().at("map");
	textures[play] = &sdlutils().images().at("play");
	textures[play_hover] = &sdlutils().images().at("play_hover");
	textures[bulletTowerTexture] = &sdlutils().images().at("bullet_tower");
	textures[cristalTowerTexture] = &sdlutils().images().at("cristal_tower");
	textures[phoenixTowerTexture] = &sdlutils().images().at("phoenix_tower");
	textures[slimeTowerTexture] = &sdlutils().images().at("slime_tower");
	textures[boosterTowerTexture] = &sdlutils().images().at("booster_tower");
	textures[sniperTowerTexture] = &sdlutils().images().at("sniper_tower");
	textures[clayTowerTexture] = &sdlutils().images().at("clay_tower");
	textures[bulletTexture] = &sdlutils().images().at("canon_bullet");
	textures[sniperBulletTexture] = &sdlutils().images().at("sniper_bullet");
	textures[slimeBulletTexture] = &sdlutils().images().at("slime_bullet");
	textures[nexusTexture] = &sdlutils().images().at("nexus_tower");

	textures[box] = &sdlutils().images().at("box"); 
	textures[box_hover] = &sdlutils().images().at("box_hover");
	textures[none_box] = &sdlutils().images().at("none_box");
	textures[none_box_hover] = &sdlutils().images().at("none_box_hover");
	textures[large_box] = &sdlutils().images().at("large_box");
	textures[close] = &sdlutils().images().at("close");
	textures[close_hover] = &sdlutils().images().at("close_hover");
	textures[enemies_button] = &sdlutils().images().at("enemies");
	textures[enemies_button_hover] = &sdlutils().images().at("enemies_hover");
	textures[menu_background] = &sdlutils().images().at("menu_background");
	textures[upgrade] = &sdlutils().images().at("upgrade");
	textures[upgrade_hover] = &sdlutils().images().at("upgrade_hover");
	textures[logo] = &sdlutils().images().at("logo");

	textures[crystal_tower_image] = &sdlutils().images().at("cristal_tower_image");
	textures[bullet_tower_image] = &sdlutils().images().at("bullet_tower_image");
	textures[slime_tower_image] = &sdlutils().images().at("slime_tower_image");
	textures[sniper_tower_image] = &sdlutils().images().at("sniper_tower_image");
	textures[phoenix_tower_image] = &sdlutils().images().at("phoenix_tower_image");
	textures[clay_tower_image] = &sdlutils().images().at("dirt_tower_image");
	textures[power_tower_image] = &sdlutils().images().at("power_tower_image");
	textures[nexus_level_3_image] = &sdlutils().images().at("nexus_level_3_image");
	textures[nexus_level_text] = &sdlutils().msgs().at("nexus_level_text");


	textures[fireTexture] = &sdlutils().images().at("fireball");
	textures[slimeArea] = &sdlutils().images().at("slime_area");
	textures[shield] = &sdlutils().images().at("shield");


	//HUD
	cursorTexture = &sdlutils().images().at("cursor");
	cursorTexture2 = &sdlutils().images().at("cursorpress");
	textures[box] = &sdlutils().images().at("box");
	textures[box_hover] = &sdlutils().images().at("box_hover");
	textures[large_box] = &sdlutils().images().at("large_box");
	textures[close] = &sdlutils().images().at("close");
	textures[close_hover] = &sdlutils().images().at("close_hover");
	textures[enemies_button] = &sdlutils().images().at("enemies");
	textures[enemies_button_hover] = &sdlutils().images().at("enemies_hover");
	textures[menu_background] = &sdlutils().images().at("menu_background");
	textures[upgrade] = &sdlutils().images().at("upgrade");
	textures[upgrade_hover] = &sdlutils().images().at("upgrade_hover");
	textures[logo] = &sdlutils().images().at("logo");
	textures[play] = &sdlutils().images().at("play");
	textures[play_hover] = &sdlutils().images().at("play_hover");
	textures[nexus_level_3_image] = &sdlutils().images().at("nexus_level_3_image");
	textures[nexus_level_text] = &sdlutils().msgs().at("nexus_level_text");

	//Explosions
	textures[shieldExp] = &sdlutils().images().at("shieldExp");
	textures[bulletExplosion] = &sdlutils().images().at("bulletExp");

	//Miscelanious
	textures[square] = &sdlutils().images().at("square");
	textures[tileSet] = &sdlutils().images().at("map");



}


RenderSystem::~RenderSystem() {
}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void RenderSystem::receive(const Message& m) {
	switch (m.id) {
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
	Message m;
	m.id = _m_OFFSET_CONTEXT;
	m.offset_context.offset = offset;
	mngr_->send(m, true);
}

//Renderiza cada entity por grupos
void RenderSystem::update() {
	sdlutils().clearRenderer();

	//Este control tiene que estar en el main control sistem
	////Control de camara
	if (ih().isKeyDown(SDLK_UP) && offset->y < limtop) {
		offset->y += 50;
	}
	else if (ih().isKeyDown(SDLK_LEFT) && offset->x < limleft) {
		offset->x += 50;
	}
	else if (ih().isKeyDown(SDLK_RIGHT) && offset->x > limright) {
		offset->x -= 50;
	}
	else if (ih().isKeyDown(SDLK_DOWN) && offset->y > limbot) {
		offset->y -= 50;
	}
	//tmp->update();

	//LAYER 1 TILEMAP
	const auto& tilesl1 = mngr_->getEntities(_grp_TILES_L1);
	for (auto& t : tilesl1) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect = mngr_->getComponent<FramedImage>(t)->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		textures[textureId]->render(srcRect, trRect);
	}

	//LAYER 2 TILEMAP
	const auto& tilesl2 = mngr_->getEntities(_grp_TILES_L2);
	for (auto& t : tilesl2) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect = mngr_->getComponent<FramedImage>(t)->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		textures[textureId]->render(srcRect, trRect);
	}

	//LAYER 3 TILEMAP
	const auto& tilesl3 = mngr_->getEntities(_grp_TILES_L3);
	for (auto& t : tilesl3) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect = mngr_->getComponent<FramedImage>(t)->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		textures[textureId]->render(srcRect, trRect);
	}

	

	//Este grupo tiene que estar ordenado de arriba a abajo de la pantalla segun su transform (posicion y)
	// NO CAMBIAR LECHES
	//TOWERS AND ENEMIES
	auto& towers = mngr_->getEntities(_grp_TOWERS_AND_ENEMIES);
	sort(towers.begin(), towers.end(), cmpIsometricY(mngr_));
	for (auto& t : towers) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect;
		FramedImage* fi = mngr_->getComponent<FramedImage>(t);
		if (fi != nullptr) { srcRect = fi->getSrcRect(); fi->updateCurrentFrame(); }
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		if (fi != nullptr)textures[textureId]->render(srcRect, trRect, tr->getRotation());
		else textures[textureId]->render(trRect, tr->getRotation());
	}

	//AREA OF ATTACK (SLIME AND FENIX)
	const auto& areas = mngr_->getEntities(_grp_AREAOFATTACK);
	for (auto& area : areas)
	{
		Transform* tr = mngr_->getComponent<Transform>(area);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(area)->getTexture();
		FramedImage* img = mngr_->getComponent<FramedImage>(area);
		SDL_Rect srcRect = img->getSrcRect();
		img->updateCurrentFrame();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		//SDL_RenderFillRect(sdlutils().renderer(), &trRect); //Debug para ver la hitbox
		textures[textureId]->render(srcRect, trRect, tr->getRotation());
	}
	

	// BULLETS
	const auto& buls = mngr_->getEntities(_grp_BULLETS);
	for (auto& b : buls) {
		Transform* tr = mngr_->getComponent<Transform>(b);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(b)->getTexture();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		textures[textureId]->render(trRect, tr->getRotation());
	}

	//ICONS
	const auto& icons = mngr_->getEntities(_grp_ICONS);
	for (auto& i : icons) {
		Transform* tr = mngr_->getComponent<Transform>(i);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(i)->getTexture();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
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
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		textures[textureId]->render(trRect, tr->getRotation());
	}

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

	SDL_Rect cursorRect = { x-10, y-4, 41, 64 };

	if (pointerdown)
	{
		cursorTexture2->render(cursorRect);
	}
	else {
		cursorTexture->render(cursorRect);
	}

	sdlutils().presentRenderer();
}


// Para gestionar los mensajes correspondientes y actualizar los atributos
// winner_ y state_.
// Displays pause message
void RenderSystem::onPause() {
}
// Hides pause message
void RenderSystem::onResume() {
}