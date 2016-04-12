#pragma once
#include "Vertex.h"
#include <vector>
#include <glew\glew.h>
#include <glm\glm.hpp>
using namespace glm;

enum VBO
{
	POSITION,
	COLOUR,
	TEXCOORDS,
	NUM_VBOS
};

enum GlyphSort
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph
{
public:

	Glyph() {}
	Glyph(
		const vec4& destRect, 
		const vec4& uvRect, 
		GLuint TextureID, 
		float zLayer, 
		const vec4&colour);

	Glyph(
		const vec4& destRect, 
		const vec4& uvRect, 
		GLuint TextureID, 
		float zLayer, 
		const vec4&colour, 
		float angle);

	Vertex topLeft_;
	Vertex bottomLeft_;
	Vertex topRight_;
	Vertex bottomRight_;

	GLuint texture_;
	float zLayer_;
	float angle_;

private:

	vec2 RotatePoint(vec2 point, float angle);
};

class RenderBatch
{
public:

	RenderBatch(
		GLuint offSet, 
		GLuint numVertices, 
		GLuint textureID) :
		offSet_(offSet),
		numVertices_(numVertices),
		textureID_(textureID) { }

	GLuint offSet_, numVertices_, textureID_;

};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch() { }

	void Begin(GlyphSort sortType = GlyphSort::TEXTURE);
	void End();

	void Draw(
		const vec4& destRect, 
		const vec4& uvRect, 
		GLuint textureID, 
		float zLayer, 
		const vec4& colour);

	void Draw(
		const vec4& destRect, 
		const vec4& uvRect, 
		GLuint textureID, 
		float zLayer, 
		const vec4& colour, 
		float angle);

	void Draw(
		const vec4& destRect, 
		const vec4& uvRect, 
		GLuint textureID, 
		float zLayer, 
		const vec4& colour, 
		const vec2& direction);

	void Render();

private:

	void CreateRenderBatches();
	void SortGlyphs();

	static bool CompareFrontToBack(Glyph * a, Glyph * b);
	static bool CompareBackToFront(Glyph * a, Glyph * b);
	static bool CompareTexture(Glyph * a, Glyph * b);

	GLuint m_VBO[NUM_VBOS], m_VAO;
	GlyphSort m_sortType;

	std::vector<Glyph> m_glyphs;
	std::vector<Glyph *> m_glyphPointers;
	std::vector<RenderBatch> m_renderBatches;
};
