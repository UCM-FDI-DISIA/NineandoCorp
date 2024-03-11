#include "FireComponent.h"

FireComponent::FireComponent(Transform* tr, Entity* target, int damage, float speed) :
	tr_(tr), target_(target), damage_(damage), speed_(speed) {}