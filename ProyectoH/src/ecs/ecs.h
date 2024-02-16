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
	_IMAGE,
	_DeAcceleration,
	_Health,
	_FIGHTERCTRL,
	_GUN,
	_SHOWATOPPOSITESIDE,
	_GENERATIONS,
	_FOLLOW,
	_DISABLEONEXIT,
	_BULLET,
	// ... (compoment ids)

	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

using hdlrId_type = int;
enum hdlrId : hdlrId_type { 
	_hdlr_FIGHTER,
	_hdlr_ENEMY_FIGHTER,
	
	// do not remove this
	_LAST_HDLR_ID };
constexpr hdlrId_type maxHdlrId = _LAST_HDLR_ID;

using grpId_type = int;
enum grpId : grpId_type {
	_grp_GENERAL,
	_grp_ASTEROIDS,
	_grp_BULLETS,
	_grp_ENEMY_BULLETS,
	
	// do not remove this
	_LAST_GRP_ID
};
using tileId_type = int;
enum tileId : tileId_type {
	_idPRADERA,
	_idLAGOS,
	_idBORDELAGOS,
	_idMONTANA,
	_idCAMINOS
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
	_sys_ASTEROIDS,
	_sys_MULTIPLAYER,
	_sys_SERVER,
	_sys_CLIENT,
	_sys_BULLET,
	_sys_FIGHTER,
	_sys_COLLISIONS,
	_sys_RENDER,

	// do not remove this
	_LAST_SYS_ID
};
constexpr sysId_type maxSystemId = _LAST_SYS_ID;

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_ROUND_START, //
	_m_ROUND_OVER,
	_m_COLLISION_ASTEROIDBULLET,
	_m_COLLISION_FIGHTERASTEROID,
	_m_COLLISION_BULLETBULLET,
	_m_ASTEROIDS_EXTINCTION,
	_m_SHOOT,
	_m_GAMEOVER,
	_m_GAMEOVER_MULTIPLAYER,
	_m_GAMESTART,
	_m_PAUSE,
	_m_RESUME,
	_m_MULTIPLAYER_START,
	_m_RECEIVE_PACKAGE,
	_m_SEND_PACKAGE,
	_m_MULTIPLAYERACTIVE
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

	struct {
		std::string name; 
		std::string enemyName; 
	} multiplayer_start_data;

};
#endif // !ECS_H_