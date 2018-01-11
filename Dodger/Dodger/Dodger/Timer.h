#pragma once
#include <SDL.h>
class Timer
{
public:
	Timer();
	
	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;

	bool mPaused;
	bool mStarted;
};

