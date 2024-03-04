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

void
HealthComponent::subtractHealth(float health) {
	currentHealth_ -= health;
	std::cout << currentHealth_ << std::endl;
	if (currentHealth_ <= 0) {
		std::cout << "muerto" << std::endl;
		mngr_->setAlive(ent_, false);
	}
}

void
HealthComponent::resetHealth() {
	currentHealth_ = maxHealth_;
}

void 
HealthComponent::setHealth(float health) {
	currentHealth_ = health;
}

void 
HealthComponent::setMaxHealth(float health) {
	maxHealth_ = health;
}