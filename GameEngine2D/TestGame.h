#pragma once
#include "Rendering\Display.h"


class TestGame
{
public:
	TestGame()
	{
		init();
	}

	~TestGame() {}

	void run();

private:

	void init();
	void update();
	void draw();

	Display * m_window;
};

