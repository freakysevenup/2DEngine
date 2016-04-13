#pragma once
#include ".\Core\IScene.h"
#include ".\Core\IGame.h"
#include ".\Core\Camera.h"
#include ".\Core\Spritebatch.h"
#include ".\Core\Texture.h"
#include ".\Core\Shader.h"
#include "PlayerTest.h"
#include <Box2D\Box2D.h>


class MainGame : public IScene
{
public:
	MainGame(Display * display) :
		m_window(display)
	{

	}

	~MainGame()
	{

	}

	virtual int Next() const override;
	virtual int Previous() const override;
	virtual void Initialize() override;
	virtual void Dispose() override;
	virtual void OnEntry() override;
	virtual void OnExit() override;
	virtual void Render() override;
	virtual void Update() override;
	virtual void ProcessInput() override;

	Camera m_cam;
	SpriteBatch m_spritebatch;
	Shader * m_shaderProgram;
	float m_counter = 0.0f;
	PlayerTest * m_player;
	Display * m_window;
	b2World * m_world;
};

