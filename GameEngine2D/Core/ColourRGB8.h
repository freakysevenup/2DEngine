#pragma once
#include <glm\glm.hpp>
using namespace glm;

enum COLOUR_SWATCH
{
	RED,
	DARK_RED,
	ORANGE,
	BROWN,
	YELLOW,
	LIGHT_BROWN,
	GREEN,
	DARK_GREEN,
	BLUE,
	DARK_BLUE,
	PURPLE,
	DARK_PURPLE,
	CYAN,
	MAGENTA,
	WHITE,
	GREY,
	BLACK
};

struct ColourRGB8
{
	ColourRGB8(float r, float g, float b, float a = 1.0f)
	{
		r == NULL ? m_colour.r = 0.0f : m_colour.r = r;
		g == NULL ? m_colour.g = 0.0f : m_colour.g = g;
		b == NULL ? m_colour.b = 0.0f : m_colour.b = b;
		a == NULL ? m_colour.a = 0.0f : m_colour.a = a;
	}
	ColourRGB8(vec4 colour = vec4(0.0f, 0.0f, 0.0f, 1.0f)) :
		m_colour(colour) { }
	ColourRGB8(COLOUR_SWATCH colour) :
		m_colour(SetColour(colour)) { }
	~ColourRGB8() {}

	inline vec4 GetColour() const { return m_colour; }

	void SetColour(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
	{
		m_colour = vec4(r, g, b, a);
	}

	void SetColour(vec4 colour = vec4(0.0f, 0.0f, 0.0f, 1.0f))
	{
		m_colour = colour;
	}

	vec4 SetColour(COLOUR_SWATCH colour)
	{
		switch (colour)
		{
		case RED:
			return m_colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		case DARK_RED:
			return m_colour = vec4(0.4f, 0.0f, 0.0f, 1.0f);
			break;
		case ORANGE:
			return m_colour = vec4(1.0f, 0.5f, 0.0f, 1.0f);
			break;
		case BROWN:
			return m_colour = vec4(0.4f, 0.2f, 0.0f, 1.0f);
			break;
		case YELLOW:
			return m_colour = vec4(1.0f, 1.0f, 0.0f, 1.0f);
			break;
		case LIGHT_BROWN:
			return m_colour = vec4(0.4f, 0.4f, 0.0f, 1.0f);
			break;
		case GREEN:
			return m_colour = vec4(0.0f, 1.0f, 0.0f, 1.0f);
			break;
		case DARK_GREEN:
			return m_colour = vec4(0.0f, 0.4f, 0.0f, 1.0f);
			break;
		case BLUE:
			return m_colour = vec4(0.0f, 0.0f, 1.0f, 1.0f);
			break;
		case DARK_BLUE:
			return m_colour = vec4(0.0f, 0.0f, 0.4f, 1.0f);
			break;
		case PURPLE:
			return m_colour = vec4(0.5f, 0.0f, 1.0f, 1.0f);
			break;
		case DARK_PURPLE:
			return m_colour = vec4(0.4f, 0.0f, 0.4f, 1.0f);
			break;
		case CYAN:
			return m_colour = vec4(0.0f, 1.0f, 1.0f, 1.0f);
			break;
		case MAGENTA:
			return m_colour = vec4(1.0f, 0.0f, 0.5f, 1.0f);
			break;
		case GREY:
			return m_colour = vec4(0.5f, 0.5f, 0.5f, 1.0f);
			break;
		case BLACK:
			return m_colour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
			break;
		case WHITE:
			return m_colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}
	}

	vec4 m_colour;
};

