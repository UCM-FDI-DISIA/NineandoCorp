#include "FramedImage.h"
#include "../game/Game.h"



void FramedImage::updateCurrentFrame() {
	if (currentTime - startTime >= (1.0 / frameRate)) {
		++currentFrame;
		if (currentFrame > lastFrame) {
			currentFrame = startFrame;
			iterations++;
		}			
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

Vector2D FramedImage::getSize() {
	return Vector2D(frameWidth, frameHeight);
}