#pragma once

#ifndef IMAGE_H_
#define IMAGE_H_

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Entity.h"

#ifdef Version_1_0

class Image : public Component {
public:
	static const cmpId id = cmpId::_IMAGE;
	// Constructor
	Image(Texture* tex) : //
		tr_(nullptr), //
		tex_(tex) {
	}
	// Destructor
	virtual ~Image() { tex_ = nullptr; tr_ = nullptr; }
	// Gets a pointer to the Transform
	void initComponent() override;
	// Draws the Texture on screen
	virtual void render() override;

protected:
	Transform* tr_;
	Texture* tex_;
};

#endif
#endif
