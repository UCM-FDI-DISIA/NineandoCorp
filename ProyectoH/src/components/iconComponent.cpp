#include "iconComponent.h"
#include "../ecs/Manager.h"
#include "RenderComponent.h"

void IconComponent::addIcon(iconId id) {
	Entity* icono = mngr_->addEntity(_grp_ICONS);
	gameTextures text;
	switch (id) {
		case _BLINDED:
			text = blindedIcon;
			break;
		case _HEALED:
				text = hpIcon;
				break;
		case _POWERUP:
			text = powerIcon;
			break;
		case _PARALIZED:
			text = lightningIcon;
			break;
		default:
			break;
	}
	mngr_->addComponent<RenderComponent>(icono, text);
	Transform* tr = mngr_->addComponent<Transform>(icono);
	Transform* targetTR = mngr_->getComponent<Transform>(ent_);
	tr->setPosition(*(targetTR->getPosition()) + Vector2D(sdlutils().intConst().at("IconOffset") * icons_.size(), 0));
	tr->setScale(*(targetTR->getScale()) / 4);
	icon i;
	i.ent_ = icono;
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