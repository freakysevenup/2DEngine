#include "TestGame.h"


void TestGame::run()
{
	// set up 


	// call update
	update();
}

void TestGame::init()
{
	m_window = new Display("First Window", 500, 500, 0);
}

void TestGame::update()
{
	// if game is running,
	// refresh window, check input and call draw
	while (true)
	{
		m_window->swapBuffers();
		m_window->clearScreen(1.0f, 0.0f, 0.0f);

		draw();
	}
}

void TestGame::draw()
{
	// draw stuff
	update();
}
