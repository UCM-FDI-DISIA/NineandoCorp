#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "../components/ShieldComponent.h"
#include "../game/Game.h"

// Constructorss
RenderSystem::RenderSystem() : winner_(0)
{
	mActive = true;
	isOnUpMenu = false;
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
	textures[column_box] = &sdlutils().images().at("column_box");
	textures[box_hover] = &sdlutils().images().at("box_hover");
	textures[none_box] = &sdlutils().images().at("none_box");
	textures[none_box_hover] = &sdlutils().images().at("none_box_hover");
	textures[large_box] = &sdlutils().images().at("large_box");
	textures[pause_button] = &sdlutils().images().at("pause_button");
	textures[pause_button_hover] = &sdlutils().images().at("pause_button_hover");
	textures[settings] = &sdlutils().images().at("settings");
	textures[settings_hover] = &sdlutils().images().at("settings_hover");
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
	textures[nexusLvl] = &sdlutils().images().at("nexus");	// Borrados nexos anteriores y cambiar este enombre

	//HUD
	cursorTexture = &sdlutils().images().at("cursor");
	cursorTexture2 = &sdlutils().images().at("cursorpress");
	textures[monedaH] = &sdlutils().images().at("H_coin");
	textures[monedaDorada] = &sdlutils().images().at("gold_coin");
	textures[monedaAnimacion] = &sdlutils().images().at("coin_animation");
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
	textures[level1] = &sdlutils().images().at("level1_button");
	textures[level1_hover] = &sdlutils().images().at("level1_hover");
	textures[level2] = &sdlutils().images().at("level2_button");
	textures[level2_hover] = &sdlutils().images().at("level2_hover");
	textures[level3] = &sdlutils().images().at("level3_button");
	textures[level3_hover] = &sdlutils().images().at("level3_hover");
	textures[level4] = &sdlutils().images().at("level4_button");
	textures[level4_hover] = &sdlutils().images().at("level4_hover");
	textures[level5] = &sdlutils().images().at("level5_button");
	textures[level5_hover] = &sdlutils().images().at("level5_hover");
	textures[level6] = &sdlutils().images().at("level6_button");
	textures[level6_hover] = &sdlutils().images().at("level6_hover");
	textures[level7] = &sdlutils().images().at("level7_button");
	textures[level7_hover] = &sdlutils().images().at("level7_hover");
	textures[level8] = &sdlutils().images().at("level8_button");
	textures[level8_hover] = &sdlutils().images().at("level8_hover");
	textures[level1_desactive] = &sdlutils().images().at("level1_desactive");
	textures[level2_desactive] = &sdlutils().images().at("level2_desactive");
	textures[level3_desactive] = &sdlutils().images().at("level3_desactive");
	textures[level4_desactive] = &sdlutils().images().at("level4_desactive");
	textures[level5_desactive] = &sdlutils().images().at("level5_desactive");
	textures[level6_desactive] = &sdlutils().images().at("level6_desactive");
	textures[level7_desactive] = &sdlutils().images().at("level7_desactive");
	textures[level8_desactive] = &sdlutils().images().at("level8_desactive");
	textures[sell] = &sdlutils().images().at("sell");
	textures[sell_hover] = &sdlutils().images().at("sell_hover");
	textures[resume_button] = &sdlutils().images().at("resume_button");
	textures[resume_button_hover] = &sdlutils().images().at("resume_button_hover");
	textures[resume_icon_button] = &sdlutils().images().at("resume_icon_button");
	textures[resume_icon_button_hover] = &sdlutils().images().at("resume_icon_button_hover");
	textures[acelerate_x1] = &sdlutils().images().at("acelerate_x1");
	textures[acelerate_x1_hover] = &sdlutils().images().at("acelerate_x1_hover");
	textures[acelerate_x1_5] = &sdlutils().images().at("acelerate_x1_5");
	textures[acelerate_x1_5_hover] = &sdlutils().images().at("acelerate_x1_5_hover");
	textures[acelerate_x2] = &sdlutils().images().at("acelerate_x2");
	textures[acelerate_x2_hover] = &sdlutils().images().at("acelerate_x2_hover");
	textures[backToMenu_button] = &sdlutils().images().at("backToMenu_button");
	textures[backToMenu_button_hover] = &sdlutils().images().at("backToMenu_button_hover");
	textures[exitGame_button] = &sdlutils().images().at("exitGame_button");
	textures[exitGame_button_hover] = &sdlutils().images().at("exitGame_button_hover");
	textures[white_frame] = &sdlutils().images().at("white_frame");
	textures[button] = &sdlutils().images().at("button");
	textures[button_hover] = &sdlutils().images().at("button_hover");
	textures[check] = &sdlutils().images().at("check_button");
	textures[check_hover] = &sdlutils().images().at("check_button_hover");
	textures[resolution] = &sdlutils().images().at("resolution");
	textures[resolution_hover] = &sdlutils().images().at("resolution_hover");
	textures[resolution1] = &sdlutils().images().at("resolution1");
	textures[resolution1_hover] = &sdlutils().images().at("resolution1_hover");
	textures[resolution2] = &sdlutils().images().at("resolution2");
	textures[resolution2_hover] = &sdlutils().images().at("resolution2_hover");
	textures[resolution3] = &sdlutils().images().at("resolution3");
	textures[resolution3_hover] = &sdlutils().images().at("resolution3_hover");
	textures[life] = &sdlutils().images().at("life");
	textures[life_background] = &sdlutils().images().at("life_background");
	textures[shield_life] = &sdlutils().images().at("shield_life");
	textures[shield_background] = &sdlutils().images().at("shield_background");
	textures[life_enemy] = &sdlutils().images().at("life_enemy");
	textures[life_background_enemy] = &sdlutils().images().at("life_background_enemy");
	textures[buy] = &sdlutils().images().at("buy");
	textures[buy_hover] = &sdlutils().images().at("buy_hover");
	textures[white_arrow] = &sdlutils().images().at("white_arrow");
	textures[info_icon] = &sdlutils().images().at("info_icon");
	textures[return_button] = &sdlutils().images().at("return_button");
	textures[return_button_hover] = &sdlutils().images().at("return_button_hover");

	//Explosions
	textures[shieldExp] = &sdlutils().images().at("shieldExp");
	textures[bulletExplosion] = &sdlutils().images().at("bulletExp");
	textures[enemyDeath] = &sdlutils().images().at("enemy_death");
	textures[impact] = &sdlutils().images().at("bullet_impact");
	textures[blood] = &sdlutils().images().at("blood");
	textures[enemy_spawn] = &sdlutils().images().at("spawn_enemy");
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
	textures[principito] = &sdlutils().images().at("principito_Run");
	textures[monje] = &sdlutils().images().at("monje");
	textures[muerte] = &sdlutils().images().at("muerte");
	textures[elfo_attack] = &sdlutils().images().at("elfo_Attack");
	//textures[angel_attack] = &sdlutils().images().at("angel_Attack");
	textures[maestro_attack] = &sdlutils().images().at("maestro_Attack");
	textures[defensor_attack] = &sdlutils().images().at("defensor_Attack");
	textures[demonioAlado_attack] = &sdlutils().images().at("demonioAlado_Attack");
	//textures[demonioInfernal_attack] = &sdlutils().images().at("demonioInfernal_Attack");
	//textures[mensajero_attack] = &sdlutils().images().at("mensajero_Attack");
	textures[principito_attack] = &sdlutils().images().at("principito_Attack");
	textures[monje_attack] = &sdlutils().images().at("monje_Attack");
	textures[muerte_attack] = &sdlutils().images().at("muerte_Attack");
	textures[acechante_attack] = &sdlutils().images().at("acechante_Attack");
	textures[maldito_attack] = &sdlutils().images().at("maldito_Attack");
	textures[goblin_attack] = &sdlutils().images().at("goblin_Attack");
	textures[force_field] = &sdlutils().images().at("force_field");
	textures[pocion] = &sdlutils().images().at("pocion");


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
	textures[tsunami] = &sdlutils().images().at("tsunami");
	textures[cloud] = &sdlutils().images().at("cloud");
	textures[tsunami_icon] = &sdlutils().images().at("tsunami_icon");
	textures[thunder_icon] = &sdlutils().images().at("storm_icon");
	textures[earthquake_icon] = &sdlutils().images().at("earthquake_icon");
	textures[tornado_icon] = &sdlutils().images().at("tornado_icon");
	textures[meteorite_icon] = &sdlutils().images().at("meteorite_icon");
	textures[rangeCircle] = &sdlutils().images().at("range_circle");

	//texts
	textures[general_text] = &sdlutils().msgs().at("general_text");
	textures[sounds_text] = &sdlutils().msgs().at("sounds_text");
}


RenderSystem::~RenderSystem() {
	delete offset;
	offset = nullptr;
}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void RenderSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_PAUSE:
		mActive = !m.start_pause.onPause;
		break;
	case _m_SHOW_UPGRADE_TOWER_MENU:
		if (mngr_->getSystem<HUDSystem>()->isOnSelector(m.show_upgrade_twr_menu_data.pos + Vector2D(0, 30)))
			isOnUpMenu = true;
		break;
	case _m_EXIT_UP_MENU:
		isOnUpMenu = false;
		break;
	case _m_CHANGE_CONTROLS:
		changeControls();
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

	sdlutils().clearRenderer();

	if(mActive && !isOnUpMenu) {

		//Este control tiene que estar en el main control sistem
		////Control de camara
		if (ih().isKeyDown(SDLK_UP) || ih().isKeyDown(SDLK_w)) {
			k_up = true;
		}
		else if (ih().isKeyUp(SDLK_UP) || ih().isKeyUp(SDLK_w)) {
			k_up = false;
		}
		if (ih().isKeyDown(SDLK_LEFT) || ih().isKeyDown(SDLK_a)) {
			k_left = true;
		}
		else if (ih().isKeyUp(SDLK_LEFT) || ih().isKeyUp(SDLK_a)) {
			k_left = false;
		}
		if (ih().isKeyDown(SDLK_RIGHT) || ih().isKeyDown(SDLK_d)) {
			k_right = true;
		}
		else if (ih().isKeyUp(SDLK_RIGHT) || ih().isKeyUp(SDLK_d)) {
			k_right = false;
		}
		if (ih().isKeyDown(SDLK_DOWN) || ih().isKeyDown(SDLK_s)) {
			k_down = true;
		}
		else if (ih().isKeyUp(SDLK_DOWN) || ih().isKeyUp(SDLK_s)) {
			k_down = false;
		}

		if (k_up && offset->y < limtop) {
			cameraY_ += VelCam * game().getDeltaTime() / game().GetDelay();
			offset->y = cameraY_;
		}
		if (k_left && offset->x < limleft) {
			cameraX_ += VelCam * game().getDeltaTime() / game().GetDelay();
			offset->x = cameraX_;
		}
		if (k_right && offset->x > limright) {
			cameraX_ -= VelCam * game().getDeltaTime() / game().GetDelay();
			offset->x = cameraX_;
		}
		if (k_down && offset->y > limbot) {
			cameraY_ -= VelCam * game().getDeltaTime() / game().GetDelay();
			offset->y = cameraY_;
		}

		SDL_GetMouseState(&mouseX, &mouseY);
		Vector2D centre = { (float)(sdlutils().width() / 2), (float)(sdlutils().height() / 2) };
		Vector2D dirMove = (centre - Vector2D(mouseX, mouseY)).normalize();
		int margin = 30;
		if (mouseX < margin && offset->x < limleft 
			|| (mouseX > sdlutils().width() - margin && offset->x > limright)
			|| (mouseY < margin && offset->y < limtop)
			|| (mouseY > sdlutils().height() - margin && offset->y > limbot)) {
			cameraX_ += VelCam * game().getDeltaTime() * dirMove.getX() / game().GetDelay();
			offset->x = cameraX_;
			cameraY_ += VelCam * game().getDeltaTime() * dirMove.getY() / game().GetDelay();
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

	auto& naturalEffects = mngr_->getEntities(_grp_NATURALS_EFFECTS_LOW);
	sort(naturalEffects.begin(), naturalEffects.end(), cmpIsometricY(mngr_));
	for (auto& t : naturalEffects) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect;
		FramedImage* fi = mngr_->getComponent<FramedImage>(t);
		if (mActive) {
			fi->updateCurrentFrame();
		}
		if (fi != nullptr)srcRect = fi->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		SDL_RendererFlip flip = mngr_->getComponent<RenderComponent>(t)->getFlip();
		if (fi != nullptr)textures[textureId]->render(srcRect, trRect, tr->getRotation(), nullptr, flip);
		else textures[textureId]->render(trRect, tr->getRotation());
	}
	

	//Este grupo tiene que estar ordenado de arriba a abajo de la pantalla segun su transform (posicion y)
	// NO CAMBIAR 
	//TOWERS AND ENEMIES
	auto& towers = mngr_->getEntities(_grp_TOWERS_AND_ENEMIES);
	sort(towers.begin(), towers.end(), cmpIsometricY(mngr_));
	for (auto& t : towers) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect;
		FramedImage* fi = mngr_->getComponent<FramedImage>(t);
		if (mActive) {
			fi->updateCurrentFrame();
		}
		if (fi != nullptr)srcRect = fi->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		SDL_RendererFlip flip = mngr_->getComponent<RenderComponent>(t)->getFlip();
		if (fi != nullptr)textures[textureId]->render(srcRect, trRect, tr->getRotation(), nullptr,flip);
		else textures[textureId]->render(trRect, tr->getRotation());
		drawBarlife(t);
	}

	auto& naturalEffectsHigh = mngr_->getEntities(_grp_NATURALS_EFFECTS_HIGH);
	sort(naturalEffectsHigh.begin(), naturalEffectsHigh.end(), cmpIsometricY(mngr_));
	for (auto& t : naturalEffectsHigh) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(t)->getTexture();
		SDL_Rect srcRect;
		FramedImage* fi = mngr_->getComponent<FramedImage>(t);
		if (mActive) {
			fi->updateCurrentFrame();
		}
		if (fi != nullptr)srcRect = fi->getSrcRect();
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x;
		trRect.y += offset->y;
		SDL_RendererFlip flip = mngr_->getComponent<RenderComponent>(t)->getFlip();
		if (fi != nullptr)textures[textureId]->render(srcRect, trRect, tr->getRotation(), nullptr, flip);
		else textures[textureId]->render(trRect, tr->getRotation());
	}



	//AREA OF ATTACK (SLIME AND FENIX)
	for (auto& area : mngr_->getEntities(_grp_AREAOFATTACK))
	{
		Transform* tr = mngr_->getComponent<Transform>(area);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(area)->getTexture();
		FramedImage* img = mngr_->getComponent<FramedImage>(area);
		SDL_Rect srcRect = img->getSrcRect();
		if (mActive) {
			img->updateCurrentFrame();
		}
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
		if (mngr_->getComponent<RenderComponent>(h)->isActive)
			textures[textureId]->render(tr->getRect(), tr->getRotation());
	}
	//TOWER ICONS	
	const auto& twrIcons = mngr_->getEntities(_grp_TOWER_ICONS);
	for (auto& twr : twrIcons) {
		Transform* tr = mngr_->getComponent<Transform>(twr);
		auto fI = mngr_->getComponent<FramedImage>(twr);
		SDL_Rect trRect = tr->getRect();
		gameTextures textureId = mngr_->getComponent<RenderComponent>(twr)->getTexture();
		if (mngr_->getComponent<RenderComponent>(twr)->isActive) {
			if (fI != nullptr) {
				SDL_Rect srcRect = fI->getSrcRect();
				textures[textureId]->render(srcRect, trRect, tr->getRotation());
			}
		}
	}
	//Background Texts HUD
	const auto& bgTexts = mngr_->getEntities(_grp_BACKGROUND_TEXTS);
	for (auto& t : bgTexts) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		auto tC = mngr_->getComponent<TextComponent>(t);
		if (tC->isActive) tC->getTexture()->render(tr->getRect(), tr->getRotation());
	}
	//HUD FOREGROUND
	const auto& hudF = mngr_->getEntities(_grp_HUD_FOREGROUND);
	for (auto& h : hudF) {
		auto fI = mngr_->getComponent<FramedImage>(h);
		Transform* tr = mngr_->getComponent<Transform>(h);
		gameTextures textureId = mngr_->getComponent<RenderComponent>(h)->getTexture();
		auto lockCmp = mngr_->getComponent<LockComponent>(h);
		auto dnd = mngr_->getComponent<DragAndDrop>(h);
		if (mngr_->getComponent<RenderComponent>(h)->isActive) {
			// Si tiene drag and drop
			if (dnd != nullptr) {
				//Si tiene lockcomponent y esta desbloqueado se renderiza
				if (lockCmp != nullptr && !lockCmp->isLocked()) {
					SDL_Rect srcRect = fI->getSrcRect();
					textures[textureId]->render(srcRect, tr->getRect(), tr->getRotation());
				}
				//Si no tiene lockComponent tambien se renderiza
				else if (lockCmp == nullptr) {
					SDL_Rect srcRect = fI->getSrcRect();
					textures[textureId]->render(srcRect, tr->getRect(), tr->getRotation());
				}
			}
			//Si no tiene drag and drop se renderiza si condiciones
			else if (dnd == nullptr) {
				if (fI != nullptr) {
					SDL_Rect srcRect = fI->getSrcRect();
					textures[textureId]->render(srcRect, tr->getRect(), tr->getRotation());
				}
				else {
					textures[textureId]->render(tr->getRect(), tr->getRotation());
				}
			}
			//Dando por hecho que solo los botones del HUD tienen lockComponent y no tienen drag and drop
			if (lockCmp != nullptr && dnd == nullptr) {
				if (lockCmp->isLocked()) {
					SDL_Renderer* renderer = textures[textureId]->getRenderer();
					Vector2D pos = tr->getPosition();
					Vector2D scale = tr->getScale();
					SDL_Point center = { pos.getX() + (scale.getX() / 2), pos.getY() + (scale.getY() / 2) };
					SDL_Color red = { 255, 0, 0, 100 };
					drawSquare(renderer, center, tr->getWidth(), red);
				}
			}
		}
	}

	//Texts HUD
	const auto& texts = mngr_->getEntities(_grp_TEXTS);
	for (auto& t : texts) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		auto tC = mngr_->getComponent<TextComponent>(t);
		if(tC->isActive) tC->getTexture()->render(tr->getRect(), tr->getRotation());
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

void RenderSystem::changeControls() {

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

void RenderSystem::drawSquare(SDL_Renderer* renderer, const SDL_Point& center, int width, const SDL_Color& color)
{
	SDL_Point topL = { center.x - width / 2, center.y - width / 2 };
	SDL_Point topR = { center.x + width / 2, center.y - width / 2 };
	SDL_Point bottomR = { center.x + width / 2, center.y + width / 2 };
	SDL_Point bottomL = { center.x - width / 2, center.y  + width / 2};

	SDL_Point squareVertices[] = { topL, topR, bottomR, bottomL};
	int rW, rH;
	SDL_GetRendererOutputSize(renderer, &rW, &rH);

	// Establecer el modo de mezcla para permitir la transparencia
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Rellenar el rombo con el color de relleno con transparencia
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	renderFillPolygon(renderer, rW, rH, squareVertices, 4, color);
}

void RenderSystem::drawRectangle(SDL_Renderer* renderer, const SDL_Point& center, int width, int height, const SDL_Color& color)
{
	SDL_Point topL = { center.x - width / 2, center.y - height / 2 };
	SDL_Point topR = { center.x + width / 2, center.y - height / 2 };
	SDL_Point bottomR = { center.x + width / 2, center.y + height / 2 };
	SDL_Point bottomL = { center.x - width / 2, center.y + height / 2 };

	// Dibujar las líneas del rectángulo sin rellenar
	SDL_Point vertices[] = { topL, topR, bottomR, bottomL, topL };

	// Establecer el color de la línea
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// Establecer el modo de mezcla para permitir la transparencia
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Dibujar las líneas del rectángulo con el grosor deseado
	for (int i = 0; i < 4; ++i) {
		SDL_RenderDrawLine(renderer, vertices[i].x, vertices[i].y, vertices[i + 1].x, vertices[i + 1].y);
	}
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
void RenderSystem::drawBarlife(Entity* t) {

	HealthComponent* hc = mngr_->getComponent<HealthComponent>(t);
	if (hc != nullptr && mngr_->isAlive(t)) {
		Transform* tr = mngr_->getComponent<Transform>(t);
		float health = mngr_->getComponent<HealthComponent>(t)->getHealth();
		Vector2D offsetExtra = { 15.0, 40.0 };
		SDL_Rect trRect = tr->getRect();
		trRect.x += offset->x + offsetExtra.getX();
		trRect.y += offset->y + offsetExtra.getY();
		float a = hc->getMaxHealth();
		float b = hc->getHealth();
		float c = b / a;
		SDL_Rect healthbar = SDL_Rect{trRect.x - 10, trRect.y - 50, (int)(112.0f * c), 20};
		SDL_Rect backgroundbar = SDL_Rect{ trRect.x - 15, trRect.y - 53, 120, 26 };

		//render del background
		if (mngr_->hasComponent<UpgradeTowerComponent>(t) || mngr_->hasComponent<NexusComponent>(t)) {
			textures[gameTextures::life_background]->render(backgroundbar);
			textures[gameTextures::life]->render(healthbar);
		}
		else {
			textures[gameTextures::life_background_enemy]->render(backgroundbar);
			textures[gameTextures::life_enemy]->render(healthbar);
		}


		auto s = mngr_->getComponent<ShieldComponent>(t);// barra de escudo
		if (s != nullptr) {
			if (s->getShield() > 0) {
				float a = s->getMaxShield();
				float b = s->getShield();
				float c = b / a;

				SDL_Rect healthbar = SDL_Rect{ trRect.x - 10, trRect.y - 63, (int)(112.0f * c), 20 };
				SDL_Rect backgroundbar = SDL_Rect{ trRect.x - 15, trRect.y - 66, 120, 26 };

				textures[gameTextures::shield_background]->render(backgroundbar);
				textures[gameTextures::shield_life]->render(healthbar);
			}
		}
		
	}
}
