#include "Transform.h"
#include "../game/Game.h"

// Individual members of Vector2D Getters and Setters 

// Returns position X
float Transform::getX() { return position->getX(); }

// Returns position Y
float Transform::getY() { return position->getY(); }

// Returns width
float Transform::getWidth() { return scale->getX(); }

// Returns height
float Transform::getHeight() { return scale->getY(); }

// Returns velocity X
float Transform::getVelX() { return velocity->getX(); }

// Returns velocity Y
float Transform::getVelY() { return velocity->getY(); }

// Returns a SDL_Rect with Transform properties
SDL_Rect Transform::getRect() { return build_sdlrect(position->getX(), position->getY(), scale->getX(), scale->getY()); };

// Sets position X
void Transform::setX(float x) {position->setX(x); };

// Sets position Y
void Transform::setY(float y) { position->setY(y); };

// Sets width
void Transform::setWidth(float w) { scale->setX(w); };

// Sets height
void Transform::setHeight(float h) { scale->setY(h); };

// Sets velocity X
void Transform::setVelX(float velx) { velocity->setX(velx); };

// Sets velocity Y
void Transform::setVelY(float vely) { velocity->setY(vely); };

// Adds inserted value to rotation
void Transform::addRotation(float rot) { rotation += rot; };

// Updates position based on velocity and deltaTime
void Transform::translate() {
	*position = *position + (*velocity * game().getDeltaTime());
};