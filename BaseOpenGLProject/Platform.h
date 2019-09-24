#pragma once

#include "Clock.h"

enum {
#define KEY(name, str) KEY_##name,
#include "KeyboardKeylist.inc"
KEY_MAX
};

class Platform {
protected:
	virtual void InitializePixelStuff() = 0;
	float windowWidth, windowHeight;
public:
	bool quit;
	bool keypad[KEY_MAX];
	Clock* clock;

	Platform(Clock* platformClock) : clock(platformClock) { clock->deltaTime = platformClock->deltaTime; }
	void SetQuit(bool q) { quit = q; }
	void SetWindowWidthAndHeight(float width, float height) { windowWidth = width, windowHeight = height;  }
	float GetWindowWidth() { return windowWidth; };
	float GetWindowHeight() { return windowHeight; };
	virtual ~Platform() { }
};