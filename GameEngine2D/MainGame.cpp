#include "MainGame.h"
#include <SDL2\SDL.h>

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
	delete m_spritebatch;
	delete m_textureLoader;
}

void MainGame::OnEntry()
{
	m_textureLoader = new TextureResources();
	m_tempTexture = *m_textureLoader->Load("./Assets/Textures/temp.png");

	m_spritebatch = new SpriteBatch();
	m_shaderProgram = new Shader();
	m_shaderProgram->Init("./Assets/Shaders/basicShader.vertGLSL", "./Assets/Shaders/basicShader.fragGLSL");

	m_cam.Init(1920, 1080);
	m_cam.SetScale(vec2(32.0f, 32.0f));
}

void MainGame::OnExit()
{
	// Reset variables here that should be zeroed out if you leave the scene
}

void MainGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shaderProgram->SetUniformiARB("mySampler", 0);
	m_shaderProgram->SetUniformMatrix4fvARB("P", m_cam.GetViewMatrix());

	m_shaderProgram->Begin();
	m_spritebatch->Begin();

	// Draw stuff in here

	m_spritebatch->End();

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
