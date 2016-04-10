#pragma once
#include <memory>
#include "Display.h"
#include "InputManager.h"
#include "ISceneList.h"
class IScene;


class IGame
{
public:
	IGame() :
		m_sceneList(nullptr),
		m_currentScene(nullptr),
		m_isRunning(false),
		m_fps(0.0f),
		m_screenWidth(1920),
		m_screenHeight(1080)
	{
		m_sceneList = std::make_unique<ISceneList>(this);
	}

	virtual~IGame() {}

	void Run();
	void ExitGame();
	void SetWindowProperties(const std::string title = "Default title", int width = 1920, int height = 1080, int flags = 0, float fps = 60.0f);

	virtual void OnInit() = 0;
	virtual void AddScene() = 0;
	virtual void OnExit() = 0;
	const float GetFPS() const { return m_fps; }
	InputManager GetInputManager() { return m_inputManager; }

protected:
	bool Init();
	bool InitSystems();
	virtual void Update();
	virtual void Render();

	Display * m_window;
	InputManager m_inputManager;
	std::unique_ptr<ISceneList> m_sceneList;
	IScene * m_currentScene;
	bool m_isRunning;
	int m_screenWidth, m_screenHeight;
	float m_fps;
	std::string m_title;
	int m_flags;
};

