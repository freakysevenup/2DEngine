#pragma once
#include "Vertex.h"
#include <vector>
#include <glew\glew.h>
#include "Rectangle.h"
#include <glm\glm.hpp>

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
		Rectangle& destRect,
		Rectangle& uvRect,
		GLuint TextureID, 
		float zLayer, 
		const glm::vec4&colour);

	Glyph(
		Rectangle& destRect,
		Rectangle& uvRect,
		GLuint TextureID, 
		float zLayer, 
		const glm::vec4&colour,
		float angle);

	Vertex topLeft_;
	Vertex bottomLeft_;
	Vertex topRight_;
	Vertex bottomRight_;

	GLuint texture_;
	float zLayer_;
	float angle_;

private:

	glm::vec2 RotatePoint(glm::vec2 point, float angle);
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
	SpriteBatch() :
	m_VBO(0),
	m_VAO(0) { }
	~SpriteBatch() { }

	void Begin(GlyphSort sortType = GlyphSort::TEXTURE);
	void End();
	void Init();
	void CreateVertexArray();

	void Draw(
		Rectangle& destRect,
		Rectangle& uvRect,
		GLuint textureID, 
		float zLayer, 
		const glm::vec4& colour);

	void Draw(
		Rectangle& destRect,
		Rectangle& uvRect,
		GLuint textureID, 
		float zLayer, 
		const glm::vec4& colour,
		float angle);

	void Draw(
		Rectangle& destRect,
		Rectangle& uvRect,
		GLuint textureID, 
		float zLayer, 
		const glm::vec4& colour,
		const glm::vec2& direction);

	void Render();

private:

	void CreateRenderBatches();
	void SortGlyphs();

	static bool CompareFrontToBack(Glyph * a, Glyph * b);
	static bool CompareBackToFront(Glyph * a, Glyph * b);
	static bool CompareTexture(Glyph * a, Glyph * b);

	GLuint m_VBO, m_VAO;
	GlyphSort m_sortType;

	std::vector<Glyph> m_glyphs;
	std::vector<Glyph *> m_glyphPointers;
	std::vector<RenderBatch> m_renderBatches;
};

