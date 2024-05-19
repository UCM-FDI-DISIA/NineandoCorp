#pragma once
#include "..//ecs/Component.h"

class NexusComponent : public Component
{
public:
	static const cmpId id = cmpId::_NEXUS;

	NexusComponent();

	~NexusComponent();
	bool isMaxLevel() const { return isMaxLevel_; }

protected:
	bool isMaxLevel_ = false;
};

