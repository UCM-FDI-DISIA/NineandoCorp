#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include <SDL.h>

struct Transform : public Component
{
private:
	Vector2D* position;
	float rotation;
	//float speed;
	Vector2D* scale;
	Vector2D* velocity;

public:
	static const cmpId id = cmpId::_TRANSFORM;

	// Constructor
	Transform() : Component(), position(new Vector2D(0, 0)), rotation(0), scale(new Vector2D(100, 100)), velocity(new Vector2D(0, 0)) {};
	// Destructor
	virtual ~Transform() { delete position; delete scale; rotation = 0; delete velocity; };

	// Returns position
	inline Vector2D* getPosition() { return position; };
	// Returns rotation
	inline float getRotation() { return rotation; };
	// Returns scale
	inline Vector2D* getScale() { return scale; };
	// Returns velocity
	inline Vector2D* getVelocity() { return velocity; };

	// Returns position X
	float getX();
	// Returns position Y
	float getY();
	// Returns width
	float getWidth();
	// Returns height
	float getHeight();
	// Returns velocity X
	float getVelX();
	// Returns velocity Y
	float getVelY();
	// Returns a SDL_Rect with Transform properties
	SDL_Rect getRect();

	// Sets position
	inline void setPosition(const Vector2D& p) { *position = p; };
	// Sets rotation
	inline void setRotation(float r) { rotation = r; };
	// Sets scale
	inline void setScale(const Vector2D& s) { *scale = s; };
	// Sets velocity
	inline void setVelocity(const Vector2D& v) { *velocity = v; };

	// Sets position X
	void setX(float x);
	// Sets position Y
	void setY(float y);
	// Sets width
	void setWidth(float w);
	// Sets height
	void setHeight(float h);
	// Sets velocity X
	void setVelX(float velx);
	// Sets velocity Y
	void setVelY(float vely);

	// Adds inserted value to rotation
	void addRotation(float rot);

	// Updates position based on velocity and deltaTime
	void translate();
};
#endif