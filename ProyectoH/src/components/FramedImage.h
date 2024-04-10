#pragma once
#ifndef FRAMEDIMAGE_H_
#define FRAMEDIMAGE_H_

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"

struct FramedImage : public Component {
private:
	int currentFrame;
	int startFrame, lastFrame;
	float startTime, currentTime;
	int frameRate;
	int frameColumns, frameRows;
	int frameWidth, frameHeight;
	int iterations;
public:
	static const cmpId id = cmpId::_FRAMEDIMAGE;
	// Constructor
	//IMPORTANTE: cambiar los strings de referencia al json
	FramedImage(int frameColumns = 1, int frameRows = 1, int frameWidth = 0, int frameHeight = 0, int currentFrame = 0, int frameRate = 0, int lastFrame = 1) :
		frameColumns(frameColumns), frameRows(frameRows), frameWidth(frameWidth), frameHeight(frameHeight), currentTime(0), currentFrame(currentFrame), frameRate(frameRate), startTime(0), startFrame(currentFrame), lastFrame(lastFrame), iterations(0){};
	
	// Changes the current frame
	void updateCurrentFrame();
	int getIters() const { return iterations; };
	// Returns texture Source Rect
	SDL_Rect getSrcRect();

	void setCurrentFrame(int newFrame) { currentFrame = newFrame; }
	int getCurrentFrame() { return currentFrame; }
	inline void setFrame(int x_, int y_) {
		currentFrame = x_;
		lastFrame = y_;
	}
};

#endif