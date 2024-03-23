#include "MeteorologySystem.h"

#include "../ecs/Manager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"

MeteorologySystem::MeteorologySystem() {

}
MeteorologySystem::~MeteorologySystem() {

}


void MeteorologySystem::initSystem() {

}

void  MeteorologySystem::receive(const Message& m) {
	switch (m.id) {
	default:
		break;
	}
}


void MeteorologySystem::update() {
	
}
