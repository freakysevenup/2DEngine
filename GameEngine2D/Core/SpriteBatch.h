#pragma once
#include "Vertex.h"
#include <vector>
#include <glew\glew.h>
#include <glm\glm.hpp>
using namespace glm;

class Glyph
{
public:

	Glyph() {}
	Glyph(const vec4& destRect, const vec4& uvRect, GLuint TextureID, float zLayer, const vec4&colour);
	Glyph(const vec4& destRect, const vec4& uvRect, GLuint TextureID, float zLayer, const vec4&colour, float angle);

	Vertex topLeft_;
	Vertex bottomLeft_;
	Vertex topRight_;
	Vertex bottomRight_;

	GLuint texture_;
	float depth_;
	float angle_;

private:

	vec2 RotatePoint(vec2 point, float angle);
};

class RenderBatch
{
public:

	RenderBatch(GLuint offSet, GLuint numVertices, GLuint textureID) :
		offSet_(offSet),
		numVertices_(numVertices),
		textureID_(textureID) { }

	GLuint offSet_, numVertices_, textureID_;

};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();
};

