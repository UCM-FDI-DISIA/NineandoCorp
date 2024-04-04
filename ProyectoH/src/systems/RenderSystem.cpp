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
	mActive = true;
	//Camera offset
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
	textures[nexusTexture] = &sdlutils().images().at("nexus_tower");	// Quitar creo
	textures[box] = &sdlutils().images().at("box");
	textures[box_hover] = &sdlutils().images().at("box_hover");
	textures[none_box] = &sdlutils().images().at("none_box");
	textures[none_box_hover] = &sdlutils().images().at("none_box_hover");
	textures[large_box] = &sdlutils().images().at("large_box");
	textures[pause_button] = &sdlutils().images().at("pause_button");
	textures[pause_button_hover] = &sdlutils().images().at("pause_button_hover");
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
	textures[nexus_level_3_image] = &sdlutils().images().at("nexus_level_3_image");		// Quitar creo
	textures[nexus_level_text] = &sdlutils().msgs().at("nexus_level_text");
	textures[fireTexture] = &sdlutils().images().at("fireball");
	textures[slimeArea] = &sdlutils().images().at("slime_area");
	textures[shield] = &sdlutils().images().at("shield");

	//Nexus
	textures[nexusLvl1] = &sdlutils().images().at("nexusLvl1");
	textures[nexusLvl2] = &sdlutils().images().at("nexusLvl2");
	textures[nexusLvl3] = &sdlutils().images().at("nexusLvl3");
	textures[nexusLvl4] = &sdlutils().images().at("nexusLvl4");

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
	textures[hpIcon] = &sdlutils().images().at("hp_icon");
	textures[powerIcon] = &sdlutils().images().at("powerup_icon");
	textures[lightningIcon] = &sdlutils().images().at("lightning_icon");
	textures[blindedIcon] = &sdlutils().images().at("blinded_icon");
	textures[slimeArea] = &sdlutils().images().at("slime_area");
	textures[fireTexture] = &sdlutils().images().at("fireball");


	//Explosions
	textures[shieldExp] = &sdlutils().images().at("shieldExp");
	textures[bulletExplosion] = &sdlutils().images().at("bulletExp");
	//Miscelanious
	textures[square] = &sdlutils().images().at("square");
	textures[tileSet] = &sdlutils().images().at("map");

	//Enemies
	textures[goblin] = &sdlutils().images().at("goblin");
	textures[maldito] = &sdlutils().images().at("maldito");
	textures[elfo] = &sdlutils().images().at("elfo");
	textures[golem] = &sdlutils().images().at("golem");
	textures[angel] = &sdlutils().images().at("angel");
	textures[maestro] = &sdlutils().images().at("maestro");
	textures[acechante] = &sdlutils().images().at("acechante");
	textures[defensor] = &sdlutils().images().at("defensor");
	textures[demonioAlado] = &sdlutils().images().at("demonioAlado");
	textures[demonioInfernal] = &sdlutils().images().at("demonioInfernal");
	textures[mensajero] = &sdlutils().images().at("mensajero");
	textures[CMaldito] = &sdlutils().images().at("maldito");
	textures[principito] = &sdlutils().images().at("principito");
	textures[monje] = &sdlutils().images().at("monje");
	textures[muerte] = &sdlutils().images().at("muerte");
	//Enemies Icons
	textures[goblin_icon] = &sdlutils().images().at("goblin_icon");
	textures[maldito_icon] = &sdlutils().images().at("maldito_icon");
	textures[elfo_icon] = &sdlutils().images().at("elfo_icon");
	textures[golem_icon] = &sdlutils().images().at("golem_icon");
	textures[angel_icon] = &sdlutils().images().at("angel_icon");
	textures[maestro_icon] = &sdlutils().images().at("malmas_icon");
	textures[acechante_icon] = &sdlutils().images().at("acechante_icon");
	textures[defensor_icon] = &sdlutils().images().at("defensor_icon");
	textures[demonioAlado_icon] = &sdlutils().images().at("demonioalado_icon");
	textures[demonioInfernal_icon] = &sdlutils().images().at("demonioinfernal_icon");
	textures[mensajero_icon] = &sdlutils().images().at("mensajero_icon");
	textures[CMaldito_icon] = &sdlutils().images().at("maldito_icon");
	textures[principito_icon] = &sdlutils().images().at("principito_icon");
	textures[monje_icon] = &sdlutils().images().at("monje_icon");
	textures[muerte_icon] = &sdlutils().images().at("muerte_icon");

	//fenomenos
	textures[thunder] = &sdlutils().images().at("thunder");
	textures[meteorites] = &sdlutils().images().at("meteorites");
	textures[earthquake] = &sdlutils().images().at("earthquake");
	textures[tornado] = &sdlutils().images().at("tornado");

}


RenderSystem::~RenderSystem() {
}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void RenderSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_PAUSE:
		mActive = !m.start_pause.onPause;
		break;
	default:
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
	if(mActive) {

		sdlutils().clearRenderer();

		//Este control tiene que estar en el main control sistem
		////Control de camara
		if (ih().isKeyDown(SDLK_UP)) {
			k_up = true;
		}
		else if (ih().isKeyUp(SDLK_UP)) {
			k_up = false;
		}
		if (ih().isKeyDown(SDLK_LEFT)) {
			k_left = true;
		}
		else if (ih().isKeyUp(SDLK_LEFT)) {
			k_left = false;
		}
		if (ih().isKeyDown(SDLK_RIGHT)) {
			k_right = true;
		}
		else if (ih().isKeyUp(SDLK_RIGHT)) {
			k_right = false;
		}
		if (ih().isKeyDown(SDLK_DOWN)) {
			k_down = true;
		}
		else if (ih().isKeyUp(SDLK_DOWN)) {
			k_down = false;
		}

		if (k_up && offset->y < limtop) {
			cameraY_ += VelCam * game().getDeltaTime();
			offset->y = cameraY_;
		}
		if (k_left && offset->x < limleft) {
			cameraX_ += VelCam * game().getDeltaTime();
			offset->x = cameraX_;
		}
		if (k_right && offset->x > limright) {
			cameraX_ -= VelCam * game().getDeltaTime();
			offset->x = cameraX_;
		}
		if (k_down && offset->y > limbot) {
			cameraY_ -= VelCam * game().getDeltaTime();
			offset->y = cameraY_;
		}
	}


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
		textures[textureId]->render(srcRect, trRect, tr->getRotation());
	}

	auto& naturalEffects = mngr_->getEntities(_grp_NATURALS_EFFECTS);
	sort(naturalEffects.begin(), naturalEffects.end(), cmpIsometricY(mngr_));
	for (auto& t : naturalEffects) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect;
		FramedImage* fi = mngr_->getComponent<FramedImage>(t);
		fi->updateCurrentFrame();
		if (fi != nullptr)srcRect = fi->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		SDL_RendererFlip flip = mngr_->getComponent<RenderComponent>(t)->getFlip();
		if (fi != nullptr)textures[textureId]->render(srcRect, trRect, tr->getRotation(), nullptr, flip);
		else textures[textureId]->render(trRect, tr->getRotation());
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
		fi->updateCurrentFrame();
		if (fi != nullptr)srcRect = fi->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		SDL_RendererFlip flip = mngr_->getComponent<RenderComponent>(t)->getFlip();
		if (fi != nullptr)textures[textureId]->render(srcRect, trRect, tr->getRotation(), nullptr,flip);
		else textures[textureId]->render(trRect, tr->getRotation());
	}



	//AREA OF ATTACK (SLIME AND FENIX)
	for (auto& area : mngr_->getEntities(_grp_AREAOFATTACK))
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
		auto fI = mngr_->getComponent<FramedImage>(h);
		Transform* tr = mngr_->getComponent<Transform>(h);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(h)->getTexture();

		if (fI != nullptr) {
			SDL_Rect srcRect = fI->getSrcRect();
			textures[textureId]->render(srcRect, tr->getRect(), tr->getRotation());
		}
		else {
			textures[textureId]->render(tr->getRect(), tr->getRotation());
		}
	}

	//Texts HUD
	const auto& texts = mngr_->getEntities(_grp_TEXTS);
	for (auto& t : texts) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		mngr_->getComponent<TextComponent>(t)->getTexture()->render(tr->getRect(), tr->getRotation());
	}

	//DRAG AND DROP
	const auto& dnd = mngr_->getEntities(_grp_HUD_DRAG_AND_DROP);
	for (auto& e : dnd) {
		Transform* tr = mngr_->getComponent<Transform>(e);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(e)->getTexture();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		Vector2D pos = tr->getPosition();
		Vector2D scale = tr->getScale();
		auto fI = mngr_->getComponent<FramedImage>(e);
		auto dnd = mngr_->getComponent<DragAndDrop>(e);
		if (fI != nullptr) { 
			if (dnd != nullptr) {
				//Dibuja un rectangulo debajo de la torre
				if (dnd->isDragged()) {
					SDL_Renderer* renderer = textures[textureId]->getRenderer();
					SDL_Point center = { (pos.getX() + (scale.getX() / 2) - 8) + offset->x, (pos.getY() + (3 * scale.getY() / 4)) + offset->y };
					
					//Seleccion de color si se puede poner la torre o no
					SDL_Color color;
					if (dnd->canDrop())
						color = { 0, 255,0 , 100 }; //verde 
					else color = { 255, 0, 0, 100 }; //rojo 

					// Ajuste de posicion y escala del rectangulo
					auto mapSys = mngr_->getSystem<mapSystem>();
					int w = 98;
					auto h = tanf(M_PI / 6) * (w / 2) + 20;
					if (dnd->getTowerId() == _twr_CRISTAL) center.y += 17;
					drawDiamond(renderer, center, w, h, color);
				}

			}
			SDL_Rect srcRect = fI->getSrcRect();
			textures[textureId]->render(srcRect, trRect,  tr->getRotation());
		}
		else {
			textures[textureId]->render(tr->getRect(), tr->getRotation());
		}
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
void RenderSystem::onGameOver(Uint8 winner) {
}

void RenderSystem::drawDiamond(SDL_Renderer* renderer, const SDL_Point& center, int width, int height, const SDL_Color& fillColor)
{
	SDL_Point top = { center.x, center.y - height / 2 };
	SDL_Point right = { center.x + width / 2, center.y };
	SDL_Point bottom = { center.x, center.y + height / 2 };
	SDL_Point left = { center.x - width / 2, center.y };

	SDL_Point diamondVertices[] = { top, right, bottom, left };
	int rW, rH;
	SDL_GetRendererOutputSize(renderer, &rW, &rH);

	// Establecer el modo de mezcla para permitir la transparencia
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Rellenar el rombo con el color de relleno con transparencia
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	renderFillPolygon(renderer, rW, rH, diamondVertices , 4, fillColor);

}

void RenderSystem::renderFillPolygon(SDL_Renderer* renderer, int width, int height, const SDL_Point vertices[], int numVertices, const SDL_Color& color) {
	// Crear un array de límites verticales
	std::vector<int> minY(width + 1, INT_MAX);
	std::vector<int> maxY(width + 1, INT_MIN);

	// Encontrar los límites verticales para cada columna
	for (int i = 0; i < numVertices; ++i) {
		int j = (i + 1) % numVertices;
		int dx = abs(vertices[j].x - vertices[i].x);
		int dy = abs(vertices[j].y - vertices[i].y);
		int steps = std::max(dx, dy);

		float xIncrement = static_cast<float>(vertices[j].x - vertices[i].x) / steps;
		float yIncrement = static_cast<float>(vertices[j].y - vertices[i].y) / steps;

		float x = vertices[i].x;
		float y = vertices[i].y;

		for (int k = 0; k <= steps; ++k) {
			int ix = static_cast<int>(x + 0.5);

			if (ix >= 0 && ix < sdlutils().width()) {
				minY[ix] = std::min(minY[ix], static_cast<int>(y));
				maxY[ix] = std::max(maxY[ix], static_cast<int>(y));
			}
			x += xIncrement;
			y += yIncrement;
		}

		for (int x = 0; x < width; ++x) {
			if (minY[x] <= maxY[x]) {
				//SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
				SDL_RenderDrawLine(renderer, x, minY[x], x, maxY[x]);
			}
		}
	}
}

