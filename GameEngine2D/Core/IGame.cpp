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

	ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_INFO, "Game Exited...");
	SDL_Quit();
	exit(0);
}

bool IGame::Init()
{
	InitSystems();
	OnInit();

	if (m_window == nullptr)
	{
		m_window = new Display("DEFAULT", 500, 500, 0);
	}

	AddScene();

	m_currentScene = m_sceneList->GetCurrentScene();
	m_currentScene->OnEntry();
	m_currentScene->SetRunning();
	return true;
}

bool IGame::InitSystems()
{

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
			ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_INFO, "Switching to Next Scene...");
			m_currentScene->OnExit();
			m_currentScene = m_sceneList->Next();
			if (m_currentScene)
			{
				m_currentScene->SetRunning();
				m_currentScene->OnEntry();
			}
			break;
		case SceneState::CHANGE_PREVIOUS:
			ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_INFO, "Switching to Previous Scene...");
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
	m_window = new Display(title, width, height, flags);
	m_screenWidth = width;
	m_screenHeight = height;
	m_fps = fps;
	m_title = title;
	m_flags = flags;
	ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_INFO, "Window Created...");
}