#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class IconComponent:public Component
{
private:
	bool hasIcon_;
	Entity* icon_;
	cmpId iconType_;
public:
	static const cmpId id = cmpId::_ICON;

	IconComponent(cmpId iconType) : hasIcon_(false), iconType_(iconType), icon_(nullptr) {};

	Entity* getIcon() { return icon_; }
	cmpId getIconType() { return iconType_; }

	bool hasIcon() { return hasIcon_; }
	void setHasIcon(bool hasIcon) { hasIcon_ = hasIcon; }
	void setIcon(Entity* icon) { icon_ = icon; }

};

