#pragma once
class FPSLimiter
{
public:
	FPSLimiter() {}
	void Init(float maxFPS);
	void SetMaxFPS(float maxFPS);
	void Begin();

	// Will return the current FPS
	float End();

private:
	void CalculateFPS();
	float m_maxFPS, m_frameTime, m_fps;
	unsigned int m_startTicks;
};

