#include "MainGame.h"
#include <SDL2\SDL.h>
#include ".\Core\TextureResources.h"

const b2Vec2 GRAVITY = b2Vec2(0.0f, -9.80f);

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
	m_world = new b2World(GRAVITY);
	m_spritebatch.Init();
	m_shaderProgram = new Shader();
	m_shaderProgram->Init("Assets/Shaders/basicShader.vertGLSL", "Assets/Shaders/basicShader.fragGLSL");

	m_player = new PlayerTest();
	m_player->SetPosition(glm::vec2(0.0f, 0.0f));
	m_player->SetTexture(TextureResources::GetTexture("Assets/Textures/pirate.png"));

	m_cam.Init(m_window->GetScreenWidth(), m_window->GetScreenHeight());
	m_cam.SetPosition(glm::vec2(m_player->GetPosition().x + m_player->GetWidth() / 2.0f, m_player->GetPosition().y + m_player->GetHeight() / 2.0f));
	m_cam.SetScale(glm::vec2(1.0f / 4.0f));
}

void MainGame::OnExit()
{
	
}

void MainGame::Render()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	m_shaderProgram->Begin();
	glActiveTexture(GL_TEXTURE0);

	m_shaderProgram->SetUniformiARB("mySampler", 0);
	m_shaderProgram->SetUniformMatrix4fvARB("P", m_cam.GetViewMatrix());

	m_spritebatch.Begin();

	// Draw stuff under here

	m_player->Draw(m_spritebatch);

	// Draw stuff above here

	m_spritebatch.End();
	m_spritebatch.Render();
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
