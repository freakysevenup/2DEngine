#pragma once
#include ".\Core\SpriteBatch.h"
#include <glm\glm.hpp>

class PlayerTest
{
public:
	PlayerTest();
	~PlayerTest();

	void Draw(SpriteBatch& spriteBatch, GLuint textureID);
	void SetPosition(glm::vec2& pos) { m_position = pos; }

private:
	GLuint m_textureID;
	glm::vec2 m_position;
};

