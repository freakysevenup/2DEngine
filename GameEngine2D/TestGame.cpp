#include ".\Core\ISceneList.h"

#include "TestGame.h"

void TestGame::OnInit()
{

}

void TestGame::AddScene()
{
	m_mainGame = std::make_unique<MainGame>();
	m_sceneList->AddScene(m_mainGame.get());
	m_sceneList->SetScene(m_mainGame->GetSceneIndex());
}

void TestGame::OnExit()
{

}
