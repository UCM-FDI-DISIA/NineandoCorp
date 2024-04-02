#include "ShieldComponent.h"

ShieldComponent::ShieldComponent(float l) : maxHealth_(l), baseHealth_(l), imgShield_(nullptr) { };


void
ShieldComponent::initComponent() {
	// Añadir mas cosas de init 
	currentHealth_ = maxHealth_;
}

void
ShieldComponent::addShield(float health) {
	currentHealth_ += health;
}

void
ShieldComponent::subtractShield(float health) {
	currentHealth_ -= health;
}

void
ShieldComponent::resetShield() {
	currentHealth_ = maxHealth_;
}

void
ShieldComponent::setShield(float health) {
	currentHealth_ = health;
}

void
ShieldComponent::setMaxShield(float health) {
	maxHealth_ = health;
}


