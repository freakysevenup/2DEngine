
#pragma once
#include <SDL2\SDL.h>
#include <string>
#include "..\Core\InputManager.h"
#include <glm\glm.hpp>
using namespace glm;


/// <summary>
/// An enum for the window to be either invisible, fullscreen and/or borderless.
/// </summary>
enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

/// <summary>
/// The Display class is the window of the game. This is where eveything will be rendered to.
/// </summary>
class Display
{
public:
	Display() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="Display"/> class.
	/// </summary>
	/// <param name="name">The name of the window.</param>
	/// <param name="screenWidth">Width of the screen.</param>
	/// <param name="screenHeight">Height of the screen.</param>
	/// <param name="windowFlags">The window flags using <see cref='WindowFlags'/>.</param>
	Display(const std::string& name, const int& screenWidth, const int& screenHeight, unsigned int windowFlags);
	/// <summary>
	/// Finalizes an instance of the <see cref="Display"/> class.
	/// </summary>
	~Display();

	void ClearScreen(float r = 0.0f, float g = 0.0f, float b = 1.0f, float a = 1.0f);
	/// <summary>
	/// Swaps the buffers.
	/// </summary>
	void SwapBuffers();
	
	/// <summary>
	/// Determines whether this window is closed.
	/// </summary>
	/// <returns>If the window is closed.</returns>
	inline bool IsClosed() const { return m_isClosed; }
	/// <summary>
	/// Gets the width of the screen.
	/// </summary>
	/// <returns>THe screen width.</returns>
	inline const int GetScreenWidth() const { return m_screenWidth; }
	/// <summary>
	/// Gets the height of the screen.
	/// </summary>
	/// <returns>The screen height.</returns>
	inline const int GetScreenHeight() const { return m_screenHeight; }
	/// <summary>
	/// Gets the aspect ratio of the screen.
	/// </summary>
	/// <returns>The screen's aspect ratio.</returns>
	inline const float GetAspectRatio() const { return (float)m_screenWidth / (float)m_screenHeight; }
	/// <summary>
	/// Gets the center position of the window.
	/// </summary>
	/// <returns>The center point of the window.</returns>
	inline const vec2 GetCenter() const { return vec2((float)m_screenWidth / 2.0f, (float)m_screenHeight / 2.0f); }
	/// <summary>
	/// Gets the name of the screen.
	/// </summary>
	/// <returns>The name of the window.</returns>
	inline const std::string GetScreenName() const { return m_screenName; }
	/// <summary>
	/// Gets the window.
	/// </summary>
	/// <returns>A pointer to the <see cref='SDL_Window'/>.</returns>
	inline SDL_Window* GetWindow() const { return m_window; }

	/// <summary>
	/// Gets the input manager.
	/// </summary>
	/// <returns>A copy of the Inout Manager object.</returns>
	InputManager* GetInput() { return &m_input; }

	/// <summary>
	/// Sets the width of the screen.
	/// </summary>
	/// <param name="screenWidth">Width of the screen.</param>
	void SetScreenWidth(int screenWidth);
	/// <summary>
	/// Sets the height of the screen.
	/// </summary>
	/// <param name="screenHeight">Height of the screen.</param>
	void SetScreenHeight(int screenHeight);

private:
	/// <summary>
	/// The pointer to the SDL_Window.
	/// </summary>
	SDL_Window* m_window = nullptr;
	/// <summary>
	/// The OpenGL context in the window.
	/// </summary>
	SDL_GLContext m_glContext;
	/// <summary>
	/// The input manager.
	/// </summary>
	InputManager m_input;
	/// <summary>
	/// If the window is closed.
	/// </summary>
	bool m_isClosed = false;
	/// <summary>
	/// The screen width.
	/// </summary>
	int m_screenWidth = 0;
	/// <summary>
	/// The screen height.
	/// </summary>
	int m_screenHeight = 0;
	/// <summary>
	/// The window's name.
	/// </summary>
	std::string m_screenName = "";
};

