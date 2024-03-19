#include "ShieldComponent.h"

ShieldComponent::ShieldComponent(float l) : maxHealth_(l), baseHealth_(l){ };


void
ShieldComponent::initComponent() {
	// Añadir mas cosas de init 
	currentHealth_ = maxHealth_;
	imgShield_ = nullptr;
}

void
ShieldComponent::addShield(float health) {
	currentHealth_ += health;
}

//Devuelve si muere o no;
bool
ShieldComponent::subtractShield(float health) {
	currentHealth_ -= health;
	//std::cout << currentHealth_ << std::endl;
	if (currentHealth_ <= 0) {
		//std::cout << "muerto" << std::endl;
		
		return true;
	}
	return false;
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


