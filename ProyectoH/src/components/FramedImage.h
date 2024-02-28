#pragma once
#ifndef FRAMEDIMAGE_H_
#define FRAMEDIMAGE_H_

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"

struct FramedImage : public Component {
private:
	int currentFrame;
	float startTime, currentTime;
	int frameRate;
	int frameColumns, frameRows;
	int frameWidth, frameHeight;
public:
	static const cmpId id = cmpId::_FRAMEDIMAGE;
	// Constructor
	//IMPORTANTE: cambiar los strings de referencia al json
	FramedImage(int frameColumns = 1, int frameRows = 1, int frameWidth = 0, int frameHeight = 0, int currentFrame = 0, int frameRate = 0) :
		frameColumns(frameColumns), frameRows(frameRows), frameWidth(frameWidth), frameHeight(frameHeight), currentTime(0), currentFrame(currentFrame), frameRate(frameRate), startTime(0){};
	
	// Changes the current frame
	void updateCurrentFrame();
	// Returns texture Source Rect
	SDL_Rect getSrcRect();

	void setCurrentFrame(int newFrame) { currentFrame = newFrame; }
};

#endif