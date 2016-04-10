#pragma once
#include <memory>
#include "Core\IGame.h"
#include "MainGame.h"

enum GameState
{
	RUNNING,
	PAUSED,
	EXIT
};

class TestGame : public IGame
{
public:

	TestGame() :
	m_mainGame(nullptr) {}
	~TestGame() 
	{}

	virtual void OnInit() override;
	virtual void AddScene() override;
	virtual void OnExit() override;

private:

	std::unique_ptr<MainGame> m_mainGame;

};

