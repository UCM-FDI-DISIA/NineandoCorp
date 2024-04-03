#pragma once
#ifndef ECS_H_
#define ECS_H_

#include "../checkML.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/NetMap.h"
#include <vector>


class Entity;
class Manager;


using uint8_t = unsigned char;

enum Height { HIGH = 0, LOW, PATH, BOTH};

using cmpId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM = 0,
	_RENDER,
	_FRAMEDIMAGE,
	_ATTACK,
	_HEALTH,
	_BULLET,
	_MOVEMENT,
	_BUTTON,
	_ROUTE,
	_UPGRADETOWER,
	_POWERTOWER,
	_CRISTALTOWER,
	_DIEGOTOWER,
	_NEXUS,
	_PHOENIXTOWER,
	_DIRTTOWER,
	_DRAG_AND_DROP,
	_SLIMETOWER,
	_SLIMEBULLET,
	_GENERATENEMIES,
	_SHIELD,
	_TOWERSTATES,
	_ENEMYSTATES,
	_MAESTROALMAS,
	_P_TIME,
	_GOLEM,
	_ACECHANTE,
	_FIRE,
	_MENSAJEROMUERTE,
	_TEXT,
	_ANGEL,
	_ICON,
	_LIMITEDTIME,
	_INTERACTIVE_TOWER,
	_ENEMYTYPE,


	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

using hdlrId_type = int;
enum hdlrId : hdlrId_type { 
	_hdlr_DRAG_AND_DROP,
	_hdlr_SUBMENU,
	_hdlr_LOW_TOWERS,
	_hdlr_HIGH_TOWERS,
	_hdlr_ENEMIES,
	_hdlr_SPAWNS,
	//botones de las escenas
	_hdlr_BUTTON,
	_hdlr_BUTTON_MAIN,
	_hdlr_BUTTON_PAUSE,
	_hdlr_BUTTON_LVLSEL,
	_hdlr_BUTTON_ENEMYBOOK,
	_hdlr_BUTTON_PLAY,
	_hdlr_PARTICLES,
	_hdlr_ICONS,
	
	// do not remove this
	_LAST_HDLR_ID };
constexpr hdlrId_type maxHdlrId = _LAST_HDLR_ID;

using grpId_type = int;
enum grpId : grpId_type {
	_grp_GENERAL,
	_grp_TILES_L1,
	_grp_TILES_L2,
	_grp_TILES_L3,
	_grp_TOWERS_AND_ENEMIES,
	_grp_BULLETS,
	_grp_HUD_BACKGROUND,
	_grp_HUD_FOREGROUND,
	_grp_TEXTS,
	_grp_HUD_DRAG_AND_DROP,
	_grp_AREAOFATTACK,
	_grp_SPAWN,
	_grp_NATURALS_EFFECTS,
	_grp_ICONS,
	
	// do not remove this
	_LAST_GRP_ID
};
constexpr grpId_type maxGroupId = _LAST_GRP_ID;

using gmSttId_type = uint8_t;
enum gmSttId : gmSttId_type {
	_gmStt_PLAY,
	_gmStt_PAUSE,
	_gmStt_GAMEOVER,
	_gmStt_MAINMENU,
	_gmStt_LEVELSELECTOR,
	_gmStt_ENEMYBOOK,

	// do not remove this
	_LAST_GMSTT_ID
};
constexpr gmSttId_type maxGameStateId = _LAST_GMSTT_ID;

using sysId_type = uint8_t;
enum sysId : sysId_type {
	_sys_GAMECNTRL = 0,
	_sys_COLLISIONS,
	_sys_RENDER,
	_sys_MAP,
	_sys_TOWERS,
	_sys_HUD,
	_sys_MAINMENU,
	_sys_MAINCONTROL,
	_sys_ENEMIES,
	_sys_LEVELSELECTOR,
	_sys_ENEMYBOOK,
	_sys_PAUSE,
	_sys_BUTTON,
	_sys_COLLISION,
	_sys_PARTICLES,
	_sys_METEOROLOGY,

	// do not remove this
	_LAST_SYS_ID
};

constexpr sysId_type maxSystemId = _LAST_SYS_ID;

using rectId_type = uint8_t;
enum rectId : rectId_type {
	_FENIX,
	_SLIME,
	_ENEMY,
	_METEORITE,
	_THUNDER,
	_EARTHQUAKE,
	_TORNADO,

	_LAST_RECT_ID
};

constexpr rectId_type lastRectId = _LAST_RECT_ID;

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_ROUND_START, //
	_m_ROUND_OVER,
	_m_SHOOT,
	_m_TOWERS_TO_ATTACK,
	_m_ENTITY_TO_ATTACK,
	_m_ATTACK_NEXUS,
	_m_TOWER_TO_ATTACK,
	_m_TOWER_TO_BLIND,
	_m_PAUSE,
	_m_RESUME,
	_m_START_GAME,
	_m_OVER_GAME,
	_m_LEVEL_SELECTOR,
	_m_ENEMY_BOOK,
	_m_UPGRADE_TOWER,
	_m_BACK_TO_MAINMENU,
	_m_TEXT_MESSAGE,
	_m_DRAG,
	_m_LEVELS_INFO,
	_m_ADD_TOWER,
	_m_OFFSET_CONTEXT,
	_m_ADD_RECT,
	_m_DECREASE_SPEED,
	_m_RESET_SPEED,
	_m_NETMAP_SET,
	_m_REMOVE_RECT,
	_m_ADD_MONEY,
	_m_LEVEL_SELECTED,
	_m_ANIM_CREATE,
	_m_RETURN_ENTITY,
	_m_ABLEBUTTONS,
	_m_CHANGE_ROUTE,
	_m_ADD_TEXT,
	_m_ENEMYSEE,
	_m_SHOW_UPGRADE_TOWER_MENU,
	_m_TOWER_CLICKED
};

using twrId_type = uint8_t;
enum twrId : twrId_type {
	_twr_BULLET,
	_twr_CRISTAL,
	_twr_SLIME,
	_twr_DIEGO,
	_twr_FENIX,
	_twr_CLAY,
	_twr_POWER,
	_twr_NEXUS,
	_twr_SIZE
};
using enmId_type = uint8_t;
enum enmId : enmId_type {
	_enm_MALMAS,
	_enm_AELECTRICO,
	_enm_MALDITO,
	_enm_GOLEM,
	_enm_DALADO,
	_enm_GOBLIN,
	_enm_ELFO,
	_enm_MMUERTE,
	_enm_ANGEL,
	_enm_DINFERNAL,
	_enm_DREAL,
	_enm_CMALDITO,
	_enm_PRINCIPITO,
	_enm_MONJE,
	_enm_MUERTE,

};

// Correspondant texture to each type of entity
enum gameTextures {
	//map
	tileSet,
	//UI
	play, play_hover, box, box_hover, large_box, none_box, none_box_hover, pause_button, pause_button_hover,
	close, close_hover, enemies_button, enemies_button_hover,
	menu_background, upgrade, upgrade_hover, logo,
	crystal_tower_image, bullet_tower_image, slime_tower_image,
	sniper_tower_image, phoenix_tower_image, clay_tower_image,
	power_tower_image, nexus_level_3_image,
	// towers
	square, bulletTowerTexture, cristalTowerTexture, phoenixTowerTexture,
	slimeTowerTexture, boosterTowerTexture, sniperTowerTexture, clayTowerTexture, nexusTexture, fireTexture,
	// nexus
	nexusLvl1, nexusLvl2, nexusLvl3, nexusLvl4,

	//enemies
	goblin, maldito, elfo, golem, angel, maestro, acechante, defensor, demonioAlado,
	demonioInfernal, mensajero, CMaldito, principito, monje, muerte,
	//enemies icons
	goblin_icon, maldito_icon, elfo_icon, golem_icon, angel_icon, maestro_icon, acechante_icon, defensor_icon,
	demonioAlado_icon, demonioInfernal_icon, mensajero_icon, CMaldito_icon, principito_icon, monje_icon, muerte_icon,
	//texts
	nexus_level_text,

	//others
    meteorites, earthquake,tornado,thunder,
	bulletTexture, sniperBulletTexture, slimeBulletTexture, slimeArea, shield, hpIcon, blindedIcon, lightningIcon, powerIcon,

	//explosions
	shieldExp, bulletExplosion,


	gmTxtrSize
};

enum iconId {
	_BLINDED, _PARALIZED, _HEALED, _POWERUP
};

inline Uint16 sdlnet_hton(Uint16 v) {
	Uint16 nv;
	SDLNet_Write16(v, &nv);
	return nv;
}
inline Uint16 sdlnet_ntoh(Uint16 nv) {
	return SDLNet_Read16(&nv);
}
inline Uint32 sdlnet_hton(Uint32 v) {
	Uint32 nv;
	SDLNet_Write32(v, &nv);
	return nv;
}
inline Uint32 sdlnet_ntoh(Uint32 nv) {
	return SDLNet_Read32(&nv);
}

inline Uint8* _serialize_(Uint32& v, Uint8* buf) {
	*reinterpret_cast<Uint32*>(buf) = sdlnet_hton(v);
	return buf + sizeof(Uint32);
}

inline Uint8* _deserialize_(Uint32& v, Uint8* buf) {
	v = sdlnet_ntoh(*reinterpret_cast<Uint32*>(buf));
	return buf + sizeof(Uint32);
}

inline Uint8* _serialize_(float& v, Uint8* buf) {
	static_assert(sizeof(float) == 4, "No es un float");
	return _serialize_(reinterpret_cast<Uint32&>(v), buf);
}
inline Uint8* _deserialize_(float& v, Uint8* buf) {
	static_assert(sizeof(float) == 4, "No es un float");
	return _deserialize_(reinterpret_cast<Uint32&>(v), buf);
}
struct Message {
	msgId_type id;
	//_m_TOWER_CLICKED
	struct {
		Entity* tower;
	}tower_clicked_data;

	//_m_SHOW_UPGRADE_TOWER_MENU
	struct {
		int cLevel;
		twrId tId;
		Vector2D pos;

	}show_upgrade_twr_menu_data;

	//_m_ADD_TEXT
	struct {
		string txt;
		SDL_Color color;
		Vector2D pos;
		Vector2D scale;
		int time;
	}add_text_data;
	// _m_ABLEBUTTONS
	struct {
		hdlrId_type buttonId;
		bool isAble;
	}able_buttons_data;

	//_m_ADD_TOWER
	struct
	{
		twrId towerId;
		Vector2D pos;
		Height height;

	} add_tower_data;

	//_m_ANIM_CREATE
	struct {
		grpId idGrp;
		gameTextures tex;
		Vector2D scale;
		Vector2D pos;
		vector<Vector2D> route;
		int frameInit;
		int frameEnd;
		int animSpeed;
		int rows;
		int cols;
		int width;
		int height;
		int iterationsToDelete;
	}anim_create;



	// _m_DRAG
	struct {
		twrId towerId;
	}drag_data;

	// _m_START_GAME
	struct
	{
		//nivel 
		int money;
		//nivel
		unsigned int level;
		NetMap* netmap;
	}start_game_data;

	// _m_OVER_GAME
	struct
	{
		// No hab�a mensaje de game over, lo dejo, igual tenemos q quitarlo
	}over_game;

	//_m_ENEMY_BOOK
	struct
	{
		int n;
	}start_enemy_book;
	//_m_RETURN_ENTITY
	struct {
		Entity* ent;
	}return_entity;

	struct {
		Entity* enemy;
	}change_route;

    // _m_TOWERS_TO_ATTACK
    struct {
		std::vector<Entity*> towers;
	} towers_to_attack;
	// _m_TOWER_TO_BLIND
	struct {
		Entity* e;		
		float damage;
	} tower_to_blind;
	// _m_ENTITY_TO_ATTACK
	struct {
		Entity* src;
		Entity* e;
		float damage;
		hdlrId targetId;
	} entity_to_attack;
	// _m_TOWER_TO_ATTACK
	struct {
		Entity* e;
		float damage;
	} tower_to_attack;
	//_m_SHIELD_NEXUS
	struct {
		int shield;
		int explosionDmg;
		bool explodes;
	}shield_data;
	//_m_ATTACK_NEXUS
	struct {
		int damage;
	}nexus_attack_data;
	//_m_DECREASE_SPEED
	struct {
		float slowPercentage;
		Entity* e;
	}decrease_speed;
	//_m_RESET_SPEED
	struct {
		float speed;
	}reset_speed;

	// _m_UPGRADE_TOWER
	struct {
		twrId towerId;
	}upgrade_tower;

	// _m_PAUSE
	struct {
		bool onPause;
	}start_pause;

	struct{
		int lvl;
	}upgrade_nexus;

	//_m_ADD_RECT
	struct {
		Entity* rect;
		rectId id;
	}rect_data;

	struct {
		SDL_Rect* offset;
	}offset_context;
  
	struct {
		int money;
	}money_data;

	
};

#endif // !ECS_H_