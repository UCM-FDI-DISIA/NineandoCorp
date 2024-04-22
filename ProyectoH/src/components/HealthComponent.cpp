#include "HealthComponent.h"

HealthComponent::HealthComponent(float l) : maxHealth_(l), baseHealth_(l) { };


void
HealthComponent::initComponent() {
	// Añadir mas cosas de init 
	currentHealth_ = maxHealth_;
}

void
HealthComponent::addHealth(float health) {
	currentHealth_ += health;
}

//Devuelve si muere o no;
bool
HealthComponent::subtractHealth(float health) {
	currentHealth_ -= health;
	if (currentHealth_ <= 0) {
		//std::cout << "muerto" << std::endl;

		mngr_->setAlive(ent_, false);
		return true;
	}
	return false;
}

void
HealthComponent::resetHealth() {
	currentHealth_ = maxHealth_;
}