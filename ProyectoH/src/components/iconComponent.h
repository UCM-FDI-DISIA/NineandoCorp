#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include <vector>

struct icon {
	Entity* ent_;
	iconId id_;

	inline bool operator==(const icon& r) {
		return ent_ == r.ent_ && id_ == r.id_;
	}
};

class IconComponent:public Component
{
private:
	vector<icon> icons_;
public:
	static const cmpId id = cmpId::_ICON;

	IconComponent() : icons_() {};

	virtual ~IconComponent() { removeAllIcons(); }

	vector<icon> getIcons() { return icons_; }

	bool hasIcon(iconId id);
	void addIcon(iconId id);
	void removeIcon(iconId id);
	void removeAllIcons();

	icon getIcon(iconId id);
};

