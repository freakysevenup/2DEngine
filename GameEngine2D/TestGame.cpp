#include "TestGame.h"
#include <SDL2\SDL_events.h>

void TestGame::run()
{
	// set up 


	// call update
	update();
}

void TestGame::processInput()
{
	SDL_Event eve;
	if (m_input->Update(eve))
	{
		m_state = EXIT;
	}
}

void TestGame::update()
{
	// if game is running,
	// refresh window, check input and call draw
	while (m_state == RUNNING)
	{
		m_window->swapBuffers();
		m_window->clearScreen(1.0f, 0.0f, 0.0f);
		processInput();

		draw();
	}
}

void TestGame::draw()
{
	// draw stuff
	update();
}
