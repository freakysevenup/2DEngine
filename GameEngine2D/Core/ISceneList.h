#pragma once
#include <vector>

class IGame;
class IScene;

class ISceneList
{
public:
	ISceneList(IGame * game) :
		m_currentSceneIndex(-1),
		m_game(game) {}
	~ISceneList()
	{
		Destroy();
	}

	IScene * Next();
	IScene * Previous();
	IScene * GetCurrentScene();

	void SetScene(int nextScene);
	void AddScene(IScene * newScene);
	void Destroy();

protected:
	std::vector<IScene *> m_scenes;
	int m_currentSceneIndex;
	IGame * m_game;
};

