#pragma once
#ifndef FRAMEDIMAGE_H_
#define FRAMEDIMAGE_H_

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"

struct FramedImage : public Component {
private:
	int currentFrame;
	float startTime, currentTime;
	const int frameRate;
	const int frameColumns, frameRows;
	const int frameWidth, frameHeight;
public:
	// Constructor
	//IMPORTANTE: cambiar los strings de referencia al json
	FramedImage();
		/*currentFrame(0), startTime(SDL_GetTicks() / 1000.0), currentTime(startTime),
		frameRate(sdlutils().intConst().at("asteroidAnimFrameRate")),
		frameColumns(sdlutils().intConst().at("asteroidFrameColumns")),
		frameRows(sdlutils().intConst().at("asteroidFrameRows")),
		frameWidth(sdlutils().intConst().at("asteroidFrameWidth")),
		frameHeight(sdlutils().intConst().at("asteroidFrameHeight"))*/
	
	// Changes the current frame
	void updateCurrentFrame();
	// Returns texture Source Rect
	SDL_Rect getSrcRect();
};

#endif