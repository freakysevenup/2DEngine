#pragma once
#include "Texture.h"
#include <glew\glew.h>
#include <string>
#include <glm\glm.hpp>

class Sprite
{
public:
	Sprite(const glm::vec2& pos, const glm::vec2& scale, const std::string& filePath);
	~Sprite();

	void Draw();
private:
	glm::vec2 m_position;
	glm::vec2 m_scale;
	GLuint m_VBO;
	Texture m_texture;
};

