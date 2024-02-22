#pragma once
#ifndef ECS_H_
#define ECS_H_

#include "../checkML.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLNetUtils.h"

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

	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

using hdlrId_type = int;
enum hdlrId : hdlrId_type { 
	_hdlr_DRAG_AND_DROP,
	_hdlr_BUTTON,
	
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
	// do not remove this
	_LAST_SYS_ID
};
constexpr sysId_type maxSystemId = _LAST_SYS_ID;

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_ROUND_START, //
	_m_ROUND_OVER,
	_m_SHOOT,
	_m_GAMEOVER,
	_m_GAMESTART,
	_m_PAUSE,
	_m_RESUME,
	_m_START_GAME
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
	// _m_COLLISION_ASTEROIDBULLET
	struct {
		Entity* a;
		Entity* b;
	} collision_asteroidbullet_data;
	// _m_GAMEOVER
	struct {
		unsigned char n;
	} winner_data;
	// _m_SHOOT
	struct {
		Vector2D pos;
		Vector2D vel;
		double width;
		double height;
		bool isEnemy;
	} gun_data;
	struct {
		float posX;
		float posY;
		float rotation;
		bool shooted;
		unsigned char winner;

		inline Uint8* serialize(Uint8* buf) {
			buf = _serialize_(posX, buf);
			buf = _serialize_(posY, buf);
			buf = _serialize_(rotation, buf);
			buf = _serialize_(reinterpret_cast<Uint32&>(shooted), buf);
			buf = _serialize_(reinterpret_cast<Uint32&>(winner), buf);
			return buf;
		}
		inline Uint8* deserialize(Uint8* buf) {
			buf = _deserialize_(posX, buf);
			buf = _deserialize_(posY, buf);
			buf = _deserialize_(rotation, buf);
			buf = _deserialize_(reinterpret_cast<Uint32&>(shooted), buf);
			buf = _deserialize_(reinterpret_cast<Uint32&>(winner), buf);
			this->winner = (unsigned char)winner;
			this->shooted = (bool)shooted;
			return buf;
		}
	} package_data;
	// _m_COLLISION_FIGHTERBULLET
	struct {
		bool isEnemy;
	} collision_fighterbullet_data;
	
	// _m_START_GAME
	struct 
	{
		//nivel 
	}start_game_data;


	// Poned el nombre pishitas
	struct {
		std::string name; 
		std::string enemyName; 
	} multiplayer_start_data;

};
#endif // !ECS_H_