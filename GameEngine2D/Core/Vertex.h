#pragma once
#include "ColourRGB8.h"
#include <glm\glm.hpp>

struct Position
{
	glm::vec2 p;
};

struct TexCoords
{
	glm::vec2 t;
};

struct Colour
{
	glm::vec4 c;
};

class Vertex
{
public:

	Position v_position;
	TexCoords v_texCoords;
	Colour v_colour;

	void SetPosition(float x, float y) 
	{
		v_position.p = glm::vec2(x, y);
	}
	void SetPosition(const glm::vec2& param)
	{
		v_position.p = param;
	}

	void SetColour(float r, float g, float b, float a)
	{
		v_colour.c = glm::vec4(r, g, b, a);
	}
	void SetColour(const ColourRGB8& colour) 
	{
		v_colour.c = colour.m_colour;
	}
	void SetColour(const glm::vec4& colour)
	{
		v_colour.c = colour;
	}

	void SetUV(float u, float v)
	{
		v_texCoords.t = glm::vec2(u, v);
	}
	void SetUV(const glm::vec2& param)
	{
		v_texCoords.t = param;
	}
};