#include "Image.h"

#ifdef Version_1_0

// Gets a pointer to the Transform
void Image::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

// Draws the Texture on screen
void Image::render() {
	SDL_Rect dest = build_sdlrect(*(tr_->getPosition()),
		tr_->getWidth(),
		tr_->getHeight());
	tex_->render(dest, tr_->getRotation());
}

#endif