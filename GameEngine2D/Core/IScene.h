#pragma once
#include <string>
#include "SceneNode.h"

#define NO_LOADED_SCENE -1

class IGame;

enum class SceneState
{
	NONE,
	RUNNING,
	EXIT,
	CHANGE_NEXT,
	CHANGE_PREVIOUS
};

class IScene
{
public:
	friend class ISceneList;
	IScene() :
		m_sceneIndex(-1),
		m_currentState(SceneState::NONE),
		m_game(nullptr) {}
	virtual ~IScene() {}

	virtual int Next() const = 0;
	virtual int Previous() const = 0;
	virtual void Initialize() const = 0;
	virtual void Dispose() const = 0;
	virtual void OnEntry() const = 0;
	virtual void OnExit() const = 0;
	virtual void Render() const = 0;
	virtual void Update() const = 0;
	virtual void ProcessInput() const = 0;

	inline int GetSceneIndex() const { return m_sceneIndex; }
	inline SceneState GetState() const { return m_currentState; }
	inline std::string GetSceneName() const { return m_sceneName; }
	inline SceneNode * GetRoot() const { return m_root; }

	void SetParent(IGame * game) { m_game = game; }
	void SetRunning() { m_currentState = SceneState::RUNNING; }
	void SetSceneIndex(int index) { m_sceneIndex = index; }
	void SetSceneName(const std::string& name) { m_sceneName = name; }

protected:
	int m_sceneIndex;
	SceneState m_currentState;
	IGame * m_game;
	SceneNode * m_root;
	std::string m_sceneName;
};

