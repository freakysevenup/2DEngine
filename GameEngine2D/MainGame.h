#pragma once
#include ".\Core\IScene.h"
#include ".\Core\IGame.h"

class MainGame : public IScene
{
public:
	MainGame()
	{

	}

	~MainGame()
	{

	}

	virtual int Next() const override;
	virtual int Previous() const override;
	virtual void Initialize() const override;
	virtual void Dispose() const override;
	virtual void OnEntry() const override;
	virtual void OnExit() const override;
	virtual void Render() const override;
	virtual void Update() const override;
	virtual void ProcessInput() const override;
};

