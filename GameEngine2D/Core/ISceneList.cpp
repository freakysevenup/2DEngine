#include "ISceneList.h"
#include "IScene.h"
#include "IGame.h"


IScene * ISceneList::Next()
{
	IScene * currentScene = GetCurrentScene();
	if (currentScene->Next() != NO_LOADED_SCENE)
	{
		m_currentSceneIndex = currentScene->Next();
	}
	return GetCurrentScene();
}

IScene * ISceneList::Previous()
{
	IScene * currentScene = GetCurrentScene();
	if (currentScene->Previous() != NO_LOADED_SCENE)
	{
		m_currentSceneIndex = currentScene->Previous();
	}
	return GetCurrentScene();
}

IScene * ISceneList::GetCurrentScene()
{
	if (m_currentSceneIndex == NO_LOADED_SCENE)
	{
		return nullptr;
	}
	return m_scenes[m_currentSceneIndex];
}

void ISceneList::SetScene(int nextScene)
{
	m_currentSceneIndex = nextScene;
}

void ISceneList::AddScene(IScene * newScene)
{
	newScene->SetSceneIndex(m_scenes.size());
	m_scenes.push_back(newScene);
	newScene->Initialize();
	newScene->SetParent(m_game);
}

void ISceneList::Destroy()
{
	for (auto & scene : m_scenes)
	{
		scene->Dispose();
	}
	m_scenes.resize(0);
	m_currentSceneIndex = NO_LOADED_SCENE;
}
