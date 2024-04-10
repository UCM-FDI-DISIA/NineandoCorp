#include "iconComponent.h"
#include "../ecs/Manager.h"

void IconComponent::addIcon(Entity* e, iconId id) {
	icon i;
	i.ent_ = e;
	i.id_ = id;
	icons_.push_back(i);
}

void IconComponent::removeIcon(iconId id) {
	int i = 0;
	while (i != icons_.size() && icons_[i].id_ != id) {
		i++;
	}
	if (i != icons_.size()) {
		mngr_->setAlive(icons_[i].ent_, false);
		icons_.erase(find(icons_.begin(), icons_.end(), icons_[i]));
	}
}

bool IconComponent::hasIcon(iconId id) {
	int i = 0;
	while (i != icons_.size() && icons_[i].id_ != id) {
		i++;
	}
	if (i == icons_.size())return false;
	else return true;
}

icon IconComponent::getIcon(iconId id) {
	int i = 0;
	while (i != icons_.size() && icons_[i].id_ != id) {
		i++;
	}
	if (i == icons_.size())return icon();
	else return icons_[i];
}