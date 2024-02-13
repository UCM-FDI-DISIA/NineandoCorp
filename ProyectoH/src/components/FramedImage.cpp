#include "FramedImage.h"
#include "../game/Game.h"

#ifdef Version_1_0
// Changes the current frame
void FramedImage::update() {
	updateCurrentFrame();
}

// Renders the current frame
void FramedImage::render() {
	SDL_Rect dest = build_sdlrect(*(tr_->getPosition()),
		tr_->getWidth(),
		tr_->getHeight());

	

	tex_->render(getSrcRect(), dest);
}
#endif

void FramedImage::updateCurrentFrame() {
	if (currentTime - startTime >= (1.0 / frameRate)) {
		++currentFrame;
		startTime = currentTime;
	}
	currentTime += game().getDeltaTime();
}

SDL_Rect FramedImage::getSrcRect() {
	return build_sdlrect(
		(currentFrame % frameColumns) * frameWidth,
		((currentFrame / frameColumns) % frameRows) * frameHeight,
		frameWidth,
		frameHeight);
}