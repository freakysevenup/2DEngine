#include <SDL2/SDL.h>
#include "FPSLimiter.h"

void FPSLimiter::Init(float maxFPS)
{
	SetMaxFPS(maxFPS);
}

void FPSLimiter::SetMaxFPS(float maxFPS)
{
	m_maxFPS = maxFPS;
}

void FPSLimiter::Begin()
{
	m_startTicks = SDL_GetTicks();
}

float FPSLimiter::End()
{
	CalculateFPS();

	float frameTicks = SDL_GetTicks() - m_startTicks;

	// limit the fps to the max fps
	if (1000.0f / m_maxFPS > frameTicks)
	{
		SDL_Delay(1000.0f / m_maxFPS - frameTicks);
	}

	return m_fps;
}

void FPSLimiter::CalculateFPS()
{
	// Kind of like a Global Variable, making a variable inside a method static means
	// it will hold its value even after the variable should have lost scope.

	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks;

	currentTicks = SDL_GetTicks();

	m_frameTime = currentTicks - prevTicks;

	// using a circular buffer here so we never need to reallocate memory to a buffer
	// we average out the FPS using this buffer
	frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

	prevTicks = currentTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		m_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		m_fps = 60.0f;
	}
}