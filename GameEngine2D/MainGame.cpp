#include "MainGame.h"
#include <SDL2/SDL.h>

int MainGame::Next() const
{
	return NO_LOADED_SCENE;
}

int MainGame::Previous() const
{
	return NO_LOADED_SCENE;
}

void MainGame::Initialize() const
{

}

void MainGame::Dispose() const
{

}

void MainGame::OnEntry() const
{

}

void MainGame::OnExit() const
{

}

void MainGame::Render() const
{

}

void MainGame::Update() const
{

}

void MainGame::ProcessInput() const
{
	SDL_Event e;
	m_game->GetInputManager().Update(e);
}
