#pragma once
#include "ColourRGB8.h"
#include <glm\glm.hpp>
using namespace glm;

struct Position
{
	vec2 p;
};

struct TexCoords
{
	vec2 t;
};

struct Colour
{
	vec4 c;
};

class Vertex
{
public:

	Position v_position;
	TexCoords v_texCoords;
	Colour v_colour;

	void setPosition(float x, float y) 
	{
		v_position.p = vec2(x, y);
	}
	void setPosition(const vec2& param) 
	{
		v_position.p = param;
	}

	void setColor(float r, float g, float b, float a)
	{
		v_colour.c = vec4(r, g, b, a);
	}
	void setColor(const ColourRGB8& colour) 
	{
		v_colour.c = colour.m_colour;
	}
	void setColor(const vec4& colour)
	{
		v_colour.c = colour;
	}

	void setUV(float u, float v)
	{
		v_texCoords.t = vec2(u, v);
	}
	void setUV(const vec2& param) 
	{
		v_texCoords.t = param;
	}
};