#include "TowerInfoSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

TowerInfoSystem::~TowerInfoSystem()
{
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_INFO)) {
		mngr_->setAlive(en, false);
	}
	mngr_->refresh();
	mngr_->deleteAllHandlers(_hdlr_BUTTON_INFO);
}

void TowerInfoSystem::initSystem()
{

	#pragma region INITIALITATIONS

	bs_ = mngr_->getSystem<ButtonSystem>();

	bPos = Vector2D((float)sdlutils().width() / 2, (float)sdlutils().height() / 2);

	bSize = Vector2D(sdlutils().width() / 1.5f, sdlutils().height() / 1.5f);

	font_size_body = { 10.0f, 24.0f };

	font_size_title = { 30.0f, 70.0f };

	font_size_subtitle = { 13.0f, 30.0f };

	body_separation = 130.0f;

	between_line_offset = font_size_body.getY() + 10.0f;

	body_c = { 180,180,180,255 };

	title_c = { 255,255,255,255 };

	right_separation = 50.0f;

	stats_separation = 60.0f;

	twr_img_pos = { bPos.getX() + bSize.getX() / 4, bPos.getY() + bSize.getY() / 4 };

	twr_img_size = Vector2D(80.5f, 112.0f ) * 2;

#pragma endregion


	#pragma region SINGLE ELEMENTS
	/**
	*   -- BACKGROUND
	*/
	bs_->addImage(bPos, bSize, 180, gameTextures::large_box, grpId::_grp_HUD_FOREGROUND);

	/**
	*	-- EXIT BUTTON
	*/
	Vector2D eSize = Vector2D(70.0f, 70.0f);
	Vector2D ePos = Vector2D(bPos.getX() + bSize.getX() / 2 - eSize.getX(), bPos.getY() - bSize.getY() / 2 + eSize.getY());
	bs_->addButton(ePos, eSize, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

#pragma endregion
	

	#pragma region TITLE


	/**
	*	-- TOWER NAME
	*/
	setTowerName();


#pragma endregion


	#pragma region BODY

	/**
	*	-- GENERAL DESCRIPTION
	*/
	setGeneralDesc();

	/**
	*	-- UPGRADE STATS
	*/
	setUpStats();

	/**
	*	-- TOWER IMAGE
	*/
	setTowerImg();

#pragma endregion

}

void TowerInfoSystem::receive(const Message& m)
{
}

void TowerInfoSystem::setTowerName(){

	std::basic_string name = "";
	switch (tower_id)
	{
	case _twr_BULLET:
		name = "BULLET TOWER";
		break;
	case _twr_CLAY:
		name = "CLAY TOWER";
		break;
	case _twr_SLIME:
		name = "SLIME TOWER";
		break;
	case _twr_FENIX:
		name = "PHOENIX TOWER";
		break;
	case _twr_DIEGO:
		name = "SNIPER TOWER";
		break;
	case _twr_POWER:
		name = "ENHANCER TOWER";
		break;
	case _twr_CRISTAL:
		name = "CRYSTAL TOWER";
		break;
	default:
		break;
	}
	Vector2D namePos = Vector2D(bPos.getX() - name.size() / 2, bPos.getY() - (bSize.getY() / 2) + font_size_title.getY() + 20);
	Vector2D nameScale = {font_size_title.getX() * name.size(), font_size_title.getY()};
	bs_->addText(name, title_c,
		namePos,
		nameScale
	);
}

void TowerInfoSystem::setGeneralDesc()
{
	
	std::vector<std::string> g_des;
	switch (tower_id)
	{
	case _twr_BULLET:
		g_des = getDescription("bullet_des_general");
		break;
	case _twr_CLAY:
		g_des = getDescription("clay_des_general");
		break;
	case _twr_SLIME:
		g_des = getDescription("slime_des_general");
		break;
	case _twr_FENIX:
		g_des = getDescription("fenix_des_general");
		break;
	case _twr_DIEGO:
		g_des = getDescription("sniper_des_general");
		break;
	case _twr_POWER:
		g_des = getDescription("power_des_general");
		break;
	case _twr_CRISTAL:
		g_des = getDescription("cristal_des_general");
		break;
	default:
		break;
	}
	
	Vector2D auxPos = { 0, body_separation + (bPos.getY() - bSize.getY() / 2) + font_size_body.getY()};
	for (int i = 0; i < g_des.size(); ++i) {
		Vector2D namePos = Vector2D(bPos.getX() - bSize.getX() / 2 + g_des[i].size() * font_size_body.getX() / 2 + right_separation , between_line_offset * i) + auxPos;
		Vector2D nameScale = { font_size_body.getX() * g_des[i].size(), font_size_body.getY()};
		bs_->addText(g_des[i], body_c,
			namePos,
			nameScale
		);

		if (i == g_des.size() - 1) {
			stats_initial_pos_y = namePos.getY() + stats_separation;
		}
	}
}

void TowerInfoSystem::setUpStats() {

	string prefix = "";
	switch (tower_id)
	{
	case _twr_BULLET:
		prefix = "bullet";
		break;
	case _twr_CLAY:
		prefix = "clay";		
		break;
	case _twr_SLIME:
		prefix = "slime";		
		break;
	case _twr_FENIX:
		prefix = "fenix";		
		break;
	case _twr_DIEGO:
		prefix = "sniper";		
		break;
	case _twr_POWER:
		prefix = "power";		
		break;
	case _twr_CRISTAL:
		prefix = "cristal";		
		break;
	default:
		break;
	}

	float aux_pos_y = stats_initial_pos_y;

	/**
	*	-- LEVEL 2
	*/
	auto des_2 = getDescription(prefix + "_des_2");

	// Texto del nivel
	basic_string subtitle_2 = "LEVEL 2:";
	bs_->addText(subtitle_2, title_c, 
		{ bPos.getX() - bSize.getX() / 2 + subtitle_2.size() * font_size_subtitle.getX() / 2 + right_separation, aux_pos_y }, 
		{subtitle_2.size() * font_size_subtitle.getX(), font_size_subtitle.getY()});
	aux_pos_y += between_line_offset;

	for (int i = 0; i < des_2.size(); ++i) {
		Vector2D namePos = Vector2D(bPos.getX() - bSize.getX() / 2 + des_2[i].size() * font_size_body.getX() / 2 + right_separation, aux_pos_y);
		Vector2D nameScale = { font_size_body.getX() * des_2[i].size(), font_size_body.getY() };
		bs_->addText(des_2[i], body_c,
			namePos,
			nameScale
		);
		aux_pos_y += between_line_offset;
	}

	/**
	*	-- LEVEL 3
	*/
	auto des_3 = getDescription(prefix + "_des_3");
	basic_string subtitle_3 = "LEVEL 3:";
	bs_->addText(subtitle_3, title_c,
		{ bPos.getX() - bSize.getX() / 2 + subtitle_3.size() * font_size_subtitle.getX() / 2 + right_separation, aux_pos_y },
		{ subtitle_3.size() * font_size_subtitle.getX(), font_size_subtitle.getY() });
	aux_pos_y += between_line_offset;

	for (int i = 0; i < des_3.size(); ++i) {
		Vector2D namePos = Vector2D(bPos.getX() - bSize.getX() / 2 + des_3[i].size() * font_size_body.getX() / 2 + right_separation, aux_pos_y);
		Vector2D nameScale = { font_size_body.getX() * des_3[i].size(), font_size_body.getY() };
		bs_->addText(des_3[i], body_c,
			namePos,
			nameScale
		);
		aux_pos_y += between_line_offset;
	}
	/**
	*	-- LEVEL 4
	*/
	auto des_4 = getDescription(prefix + "_des_4");
	basic_string subtitle_4 = "LEVEL 4:";
	bs_->addText(subtitle_4, title_c,
		{ bPos.getX() - bSize.getX() / 2 + subtitle_4.size() * font_size_subtitle.getX() / 2 + right_separation, aux_pos_y },
		{ subtitle_4.size() * font_size_subtitle.getX(), font_size_subtitle.getY() });
	aux_pos_y += between_line_offset;

	for (int i = 0; i < des_4.size(); ++i) {
		Vector2D namePos = Vector2D(bPos.getX() - bSize.getX() / 2 + des_4[i].size() * font_size_body.getX() / 2 + right_separation, aux_pos_y);
		Vector2D nameScale = { font_size_body.getX() * des_4[i].size(), font_size_body.getY() };
		bs_->addText(des_4[i], body_c,
			namePos,
			nameScale
		);
		aux_pos_y += between_line_offset;
	}

}

void TowerInfoSystem::setTowerImg()
{
	gameTextures tex;
	switch (tower_id)
	{
	case _twr_BULLET:
		tex = gameTextures::bullet_tower_image;
		break;
	case _twr_CLAY:
		tex = gameTextures::clay_tower_image;
		break;
	case _twr_SLIME:
		tex = gameTextures::slime_tower_image;
		break;
	case _twr_FENIX:
		tex = gameTextures::phoenix_tower_image;
		break;
	case _twr_DIEGO:
		tex = gameTextures::sniper_tower_image;
		break;
	case _twr_POWER:
		tex = gameTextures::power_tower_image;
		break;
	case _twr_CRISTAL:
		tex = gameTextures::crystal_tower_image;
		break;
	default:
		break;
	}
	bs_->addImage(twr_img_pos - twr_img_size / 4 - Vector2D(0, 70.0f), twr_img_size, 0, tex, _grp_HUD_FOREGROUND);
}

