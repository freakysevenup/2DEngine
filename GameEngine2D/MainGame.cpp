#include "MainGame.h"
#include <SDL2\SDL.h>
#include ".\Core\TextureResources.h"

int MainGame::Next() const
{
	return NO_LOADED_SCENE;
}

int MainGame::Previous() const
{
	return NO_LOADED_SCENE;
}

void MainGame::Initialize()
{
	
}

void MainGame::Dispose()
{
}

void MainGame::OnEntry()
{

	m_spritebatch.Init();
	m_shaderProgram = new Shader();
	m_shaderProgram->Init("./Assets/Shaders/basicShader.vertGLSL", "./Assets/Shaders/basicShader.fragGLSL");

	m_player = new PlayerTest();
	m_player->SetPosition(glm::vec2(0.0f, 0.0f));

	m_cam.Init(m_window->GetScreenWidth(), m_window->GetScreenHeight());
	m_cam.SetScale(glm::vec2(2.0f, 2.0f));
}

void MainGame::OnExit()
{
	// Reset variables here that should be zeroed out if you leave the scene
}

void MainGame::Render()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shaderProgram->SetUniformiARB("mySampler", 0);
	m_shaderProgram->SetUniformMatrix4fvARB("P", m_cam.GetViewMatrix());

	m_shaderProgram->Begin();

	// Draw code goes here

	m_spritebatch.Begin();

	// Draw stuff in here

	m_player->Draw(m_spritebatch, TextureResources::GetTexture("./Assets/Textures/pirate.png").m_id);

	m_spritebatch.End();

	m_spritebatch.Render();

	m_counter += 0.001f;
}

void MainGame::Update()
{
	m_cam.Update();
}

void MainGame::ProcessInput()
{
	SDL_Event e;
	m_game->GetInputManager().Update(e);
}
