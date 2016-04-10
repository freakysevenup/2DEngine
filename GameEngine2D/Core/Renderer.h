#pragma once


class Renderer
{
public:
	Renderer();
	virtual~Renderer();

	virtual void render() = 0;

};

