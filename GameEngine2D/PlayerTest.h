#pragma once
#include ".\Core\SpriteBatch.h"
#include ".\Core\Texture.h"
#include <glm\glm.hpp>

class PlayerTest
{
public:
	PlayerTest();
	~PlayerTest();

	void Draw(SpriteBatch& spriteBatch);
	void SetTexture(const Texture& texture) { m_texture = texture; m_textureWidth = texture.m_width; m_textureHeight = texture.m_height; }
	void SetPosition(glm::vec2& pos) { m_position = pos; }
	inline glm::vec2& GetPosition() { return m_position; }
	inline GLint & GetWidth() { return m_textureWidth; }
	inline GLint & GetHeight() { return m_textureHeight; }

private:
	Texture m_texture;
	GLint m_textureWidth;
	GLint m_textureHeight;
	glm::vec2 m_position;
};

