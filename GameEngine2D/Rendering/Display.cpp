#include "Display.h"
#include <glew\glew.h>
#include <assert.h>

Display::Display(const std::string& name, const int& screenWidth, const int& screenHeight, unsigned int windowFlags) : 
m_input(this),
m_screenWidth(screenWidth),
m_screenHeight(screenHeight),
m_screenName(name)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//Error handle
		assert(0 != 0);
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (windowFlags & INVISIBLE)
	{
		flags |= SDL_WINDOW_HIDDEN;
	}
	else if (windowFlags & FULLSCREEN)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	else if (windowFlags & BORDERLESS)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}

	m_window = SDL_CreateWindow(m_screenName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, flags);
	if (m_window == nullptr)
	{
		//Error handle
	}
	m_glContext = SDL_GL_CreateContext(m_window);

	SDL_GL_SetSwapInterval(1);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(err));
	}

}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::update(GUIEngine* guiEngine)
{
	SDL_Event e;
	if (m_input.Update(e))
	{
		m_isClosed = true;
	}
}

void Display::clearScreen(float r /* = 0.0f */, float g /* = 0.0f */, float b /* = 1.0f */, float a /* = 1.0f */)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}
