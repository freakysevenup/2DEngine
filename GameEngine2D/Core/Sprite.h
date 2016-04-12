#pragma once
#include "Texture.h"
#include "TextureResources.h"
#include <glew\glew.h>
#include <string>
#include <glm\glm.hpp>
using namespace glm;

class Sprite
{
public:
	Sprite(const vec2& pos, const vec2& scale, const std::string& filePath);
	~Sprite();

	void Draw();
private:
	vec2 m_position;
	vec2 m_scale;
	GLuint m_VBO;
	Texture m_texture;
	TextureResources * m_tResources;
};

