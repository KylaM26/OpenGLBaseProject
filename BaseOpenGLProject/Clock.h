#pragma once

class Clock {
public:
	float deltaTime;
	virtual void Initialize() = 0;
	virtual void StartFrame() = 0;
	virtual void EndFrame() = 0;
};