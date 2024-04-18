#pragma once
#include "../ecs/Component.h"
class LockComponent : public Component
{
public:
	static const cmpId id = cmpId::_LOCK;

	LockComponent(bool b) : isLocked_(b) {}
	
	inline bool isLocked() const { return isLocked_; }

	inline void lock() { isLocked_ = true; }

	inline void unlock() { isLocked_ = false; }

private:	

	bool isLocked_;

};

