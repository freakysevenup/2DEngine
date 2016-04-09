#pragma once
#include "Rendering\Display.h"
#include "Core\InputManager.h"

enum GameState
{
	RUNNING,
	PAUSED,
	EXIT
};

class TestGame
{
public:
	TestGame(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int flags)
	{
		m_window = new Display(windowTitle, windowWidth, windowHeight, flags);
		m_state = RUNNING;
		m_input = new InputManager();
	}

	~TestGame() 
	{
		delete m_window;
		delete m_input;
	}

	void run();

private:

	void processInput();
	void update();
	void draw();

	Display * m_window;
	InputManager * m_input;
	GameState m_state;

};

