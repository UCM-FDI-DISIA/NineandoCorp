#pragma once
#ifndef ECS_H_
#define ECS_H_

#include "../checkML.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLNetUtils.h"
#include <vector>

class Entity;
class Manager;

using uint8_t = unsigned char;

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

	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

using hdlrId_type = int;
enum hdlrId : hdlrId_type { 
	_hdlr_DRAG_AND_DROP,
	_hdlr_SUBMENU,
	_hdlr_LOW_TOWERS,
	_hdlr_ENEMIES,
	//botones de las escenas
	_hdlr_BUTTON_MAIN,
	_hdlr_BUTTON_LVLSEL,
	_hdlr_BUTTON_PLAY,
	
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
	_grp_HUD_DRAG_AND_DROP,
	
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
	_sys_BUTTON,

	// do not remove this
	_LAST_SYS_ID
};
constexpr sysId_type maxSystemId = _LAST_SYS_ID;

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_ROUND_START, //
	_m_ROUND_OVER,
	_m_SHOOT,
	_m_TOWERS_TO_ATTACK,
	_m_ENTITY_TO_ATTACK,
	_m_ATTACK_NEXUS,
	_m_TOWER_TO_ATTACK,
	_m_SHIELD_NEXUS,
	_m_GAMEOVER,
	_m_GAMESTART,
	_m_PAUSE,
	_m_RESUME,
	_m_START_GAME,
	_m_LEVEL_SELECTOR,
	_m_UPGRADE_NEXUS,
	_m_UPGRADE_TOWER,
	_m_BACK_TO_MAINMENU, 
	_m_TEXT_MESSAGE
};

using twrId_type = uint8_t;
enum twrId : twrId_type {
	_twr_BULLET,
	_twr_CRISTAL,
	_twr_SLIME,
	_twr_DIEGO,
	_twr_FENIX,
	_twr_DIRT,
	_twr_POWER,
};

// Correspondant text to each state
enum stateText {
	nexus_level, sttTxtSize
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
	// _m_START_GAME
	struct
	{
		//nivel 
	}start_game_data;

    // _m_TOWERS_TO_ATTACK
    struct {
		std::vector<Entity*> towers;
	} towers_to_attack;
	// _m_ENTITY_TO_ATTACK
	struct {
		Entity* e;
		float damage;
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

	// _m_UPGRADE_TOWER
	struct {
		twrId_type towerId;
		int lvl;
	}upgrade_tower;

	//_m_TEXT_MESSAGE
	struct {
		Entity* ent;
		stateText text;
	}text_message;

	// _m_UPGRADE_NEXUS
	struct {
		int lvl;
	}upgrade_nexus;
};

#endif // !ECS_H_