#include "IGame.h"
#include "IScene.h"
#include "ErrorLog.h"
#include "FPSLimiter.h"
#include <glew/glew.h>

void IGame::Run()
{
	if (!Init())
	{
		return;
	}

	m_isRunning = true;

	while (m_isRunning)
	{
		FPSLimiter fpsLimiter;
		fpsLimiter.SetMaxFPS(60.0f);
		fpsLimiter.Begin();

		SDL_Event e;
		m_inputManager.Update(e);

		Update();

		if (m_isRunning)
		{
			Render();
			m_fps = fpsLimiter.End();
			m_window->ClearScreen(1.0f, 0.0f, 0.0f, 1.0f);
			m_window->SwapBuffers();
		}
	}
}

void IGame::ExitGame()
{
	m_currentScene->OnExit();

	if (m_sceneList)
	{
		m_sceneList->Destroy();
		m_sceneList.reset();
	}

	m_isRunning = false;
}

bool IGame::Init()
{
	InitSystems();
	OnInit();
	AddScene();

	m_currentScene = m_sceneList->GetCurrentScene();
	m_currentScene->OnEntry();
	m_currentScene->SetRunning();
	return true;
}

bool IGame::InitSystems()
{
	m_window = new Display(m_title, m_screenWidth, m_screenHeight, m_flags);
	return true;
}

void IGame::Update()
{
	if (m_currentScene)
	{
		switch (m_currentScene->GetState())
		{
		case SceneState::RUNNING:
			m_currentScene->Update();
			break;
		case SceneState::CHANGE_NEXT:
			m_currentScene->OnExit();
			m_currentScene = m_sceneList->Next();
			if (m_currentScene)
			{
				m_currentScene->SetRunning();
				m_currentScene->OnEntry();
			}
			break;
		case SceneState::CHANGE_PREVIOUS:
			m_currentScene->OnExit();
			m_currentScene = m_sceneList->Previous();
			if (m_currentScene)
			{
				m_currentScene->SetRunning();
				m_currentScene->OnEntry();
			}
			break;
		case SceneState::EXIT:
			ExitGame();
			break;
		default:
			break;
		}
	}
	else
	{
		ExitGame();
	}
}

void IGame::Render()
{
	glViewport(0, 0, m_window->GetScreenWidth(), m_window->GetScreenHeight());
	if (m_currentScene && m_currentScene->GetState() == SceneState::RUNNING)
	{
		m_currentScene->Render();
	}
}

void IGame::SetWindowProperties(const std::string title/* = "Default title"*/, int width/*  = 1920*/, int height/*  = 1080*/, int flags/*  = 0*/, float fps/*  = 60.0f*/)
{
	m_screenWidth = width;
	m_screenHeight = height;
	m_fps = fps;
	m_title = title;
	m_flags = flags;
}