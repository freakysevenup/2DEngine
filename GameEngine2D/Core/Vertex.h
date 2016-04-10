#pragma once
#include <glm\glm.hpp>
using namespace glm;

class Vertex
{
public:

	Vertex(vec2 position, vec2 textureCoords) :
		m_position(position),
		m_texCoords(textureCoords) { }
	Vertex(vec2 position, vec2 textureCoords, vec4 colour) :
		m_position(position),
		m_texCoords(textureCoords),
		m_colour(colour) { }
	~Vertex() { }

private:
	vec4 m_colour;
	vec2 m_position;
	vec2 m_texCoords;
};