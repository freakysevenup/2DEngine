#include "SpriteBatch.h"
#include <algorithm>

Glyph::Glyph(
	Rectangle& destRect,
	Rectangle& uvRect,
	GLuint textureID,
	float zLayer,
	const glm::vec4&colour) :
	texture_(textureID), zLayer_(zLayer)
{
	topLeft_.SetColour(colour);
	topLeft_.SetPosition(destRect.GetX(), destRect.GetY() + destRect.GetHeight());
	topLeft_.SetUV(uvRect.GetX(), uvRect.GetY() + uvRect.GetHeight());

	bottomLeft_.SetColour(colour);
	bottomLeft_.SetPosition(destRect.GetX(), destRect.GetY());
	bottomLeft_.SetUV(uvRect.GetX(), uvRect.GetY());

	bottomRight_.SetColour(colour);
	bottomRight_.SetPosition(destRect.GetX() + destRect.GetWidth(), destRect.GetY());
	bottomRight_.SetUV(uvRect.GetX() + uvRect.GetWidth(), uvRect.GetY());

	topRight_.SetColour(colour);
	topRight_.SetPosition(destRect.GetX() + destRect.GetWidth(), destRect.GetY() + destRect.GetHeight());
	topRight_.SetUV(uvRect.GetX() + uvRect.GetWidth(), uvRect.GetY() + uvRect.GetHeight());
}

Glyph::Glyph(
	Rectangle& destRect,
	Rectangle& uvRect,
	GLuint textureID,
	float zLayer,
	const glm::vec4&colour,
	float angle) :
	texture_(textureID), zLayer_(zLayer)
{
	glm::vec2 halfDimensions(destRect.GetWidth() / 2.0f, destRect.GetHeight() / 2.0f);

	// Get points centered at origin
	glm::vec2 tl(-halfDimensions.x, halfDimensions.y);
	glm::vec2 bl(-halfDimensions.x, -halfDimensions.y);
	glm::vec2 br(halfDimensions.x, -halfDimensions.y);
	glm::vec2 tr(halfDimensions.x, halfDimensions.y);

	// Rotate the points
	tl = RotatePoint(tl, angle) + halfDimensions;
	bl = RotatePoint(bl, angle) + halfDimensions;
	br = RotatePoint(br, angle) + halfDimensions;
	tr = RotatePoint(tr, angle) + halfDimensions;

	topLeft_.SetColour(colour);
	topLeft_.SetPosition(destRect.GetX() + tl.x, destRect.GetY() + tl.y);
	topLeft_.SetUV(uvRect.GetX(), uvRect.GetY() + uvRect.GetHeight());

	bottomLeft_.SetColour(colour);
	bottomLeft_.SetPosition(destRect.GetX() + bl.x, destRect.GetY() + bl.y);
	bottomLeft_.SetUV(uvRect.GetX(), uvRect.GetY());

	bottomRight_.SetColour(colour);
	bottomRight_.SetPosition(destRect.GetX() + br.x, destRect.GetY() + br.y);
	bottomRight_.SetUV(uvRect.GetX() + uvRect.GetWidth(), uvRect.GetY());

	topRight_.SetColour(colour);
	topRight_.SetPosition(destRect.GetX() + tr.x, destRect.GetY() + tr.y);
	topRight_.SetUV(uvRect.GetX() + uvRect.GetWidth(), uvRect.GetY() + uvRect.GetHeight());
	angle_ = angle;
}

glm::vec2 Glyph::RotatePoint(glm::vec2 point, float angle)
{
	return glm::vec2(point.x * cos(angle) - point.y * sin(angle),
		point.x * sin(angle) + point.y * cos(angle));
}


void SpriteBatch::Init()
{
	CreateVertexArray();
}

void SpriteBatch::CreateVertexArray()
{
	// Generate the VAO if it isn't already generated
	if (m_VAO == 0)
	{
		glGenVertexArrays(1, &m_VAO);
	}

	// Bind the VAO. All subsequent openGL calls will modify it's state
	glBindVertexArray(m_VAO);

	// Generate the VBO if it isn't already generated
	if (m_VBO == 0)
	{
		glGenBuffers(1, &m_VBO);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	//tell openGL that we want to use the first
	//attribute array. We only need one array right
	//now since we are oly using position
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, v_position));

	//This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, v_colour));

	//This is the UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, v_texCoords));

	glBindVertexArray(0);
}

void SpriteBatch::Begin(GlyphSort sortType /* = GlyphSort::TEXTURE */)
{
	m_sortType = sortType;
	m_renderBatches.clear();
	m_glyphs.clear();
}

void SpriteBatch::End()
{
	// Set the size of the _glyphpointers vector to be the size of the _glyphs vector
	m_glyphPointers.resize(m_glyphs.size());

	// Point to each of the _glyphPointers to each of the _glyphs
	// so we can sort through them faster
	for (unsigned int i = 0; i < m_glyphs.size(); i++)
	{
		m_glyphPointers[i] = &m_glyphs[i];
	}

	SortGlyphs();
	CreateRenderBatches();
}

void SpriteBatch::Draw(
	Rectangle& destRect,
	Rectangle& uvRect,
	GLuint textureID,
	float zLayer,
	const glm::vec4& colour)
{
	m_glyphs.emplace_back(destRect, uvRect, textureID, zLayer, colour);
}

void SpriteBatch::Draw(
	Rectangle& destRect,
	Rectangle& uvRect,
	GLuint textureID,
	float zLayer,
	const glm::vec4& colour,
	float angle)
{
	m_glyphs.emplace_back(destRect, uvRect, textureID, zLayer, colour, angle);
}

void SpriteBatch::Draw(
	Rectangle& destRect,
	Rectangle& uvRect,
	GLuint textureID,
	float zLayer,
	const glm::vec4& colour,
	const glm::vec2& direction)
{
	const glm::vec2 rightVector(1.0f, 0.0f);

	float angle = acos(dot(rightVector, direction));
	if (direction.y < 0.0f)
	{
		angle = -angle;
	}

	m_glyphs.emplace_back(destRect, uvRect, textureID, zLayer, colour, angle);
}

void SpriteBatch::Render()
{
	glBindVertexArray(m_VAO);

	for (unsigned int i = 0; i < m_renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].textureID_);
		glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offSet_, m_renderBatches[i].numVertices_);
	}

	glBindVertexArray(0);
}

void SpriteBatch::CreateRenderBatches()
{
	// This will store all the vertices that we need to upload
	std::vector<Vertex> vertices;

	//Resize the buffer to the exact size we need so we can treat
	// it like an array
	vertices.resize(m_glyphPointers.size() * 6);

	if (m_glyphPointers.empty())
	{
		return;
	}

	int offset = 0; // current offset
	int cv = 0; // Current Vertex

	// Add the first batch
	m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture_);
	vertices[cv++] = m_glyphPointers[0]->topLeft_;
	vertices[cv++] = m_glyphPointers[0]->bottomLeft_;
	vertices[cv++] = m_glyphPointers[0]->bottomRight_;
	vertices[cv++] = m_glyphPointers[0]->bottomRight_;
	vertices[cv++] = m_glyphPointers[0]->topRight_;
	vertices[cv++] = m_glyphPointers[0]->topLeft_;
	offset += 6;

	// Add all the rest of the glyphs
	for (unsigned int cg = 1; cg < m_glyphPointers.size(); cg++)
	{
		// Check if this glyph can be part of the current batch
		if (m_glyphPointers[cg]->texture_ != m_glyphPointers[cg - 1]->texture_)
		{
			// make a new batch
			m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->texture_);
		}
		else
		{
			//If it's part of the current batch, just increase numVertices
			m_renderBatches.back().numVertices_ += 6;
		}
		vertices[cv++] = m_glyphPointers[cg]->topLeft_;
		vertices[cv++] = m_glyphPointers[cg]->bottomLeft_;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight_;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight_;
		vertices[cv++] = m_glyphPointers[cg]->topRight_;
		vertices[cv++] = m_glyphPointers[cg]->topLeft_;
		offset += 6;
	}

	// Bind our VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Orphan the buffer to save time in processing 
	// (tell the computer you don't want to wait for it to clear 
	// the data before writing to it again, essentially just throw it away and give me a new one)
	// This makes things faster
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	//upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::SortGlyphs()
{
	switch (m_sortType)
	{
	case GlyphSort::TEXTURE:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), CompareTexture);
		break;
	case GlyphSort::BACK_TO_FRONT:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), CompareBackToFront);
		break;
	case GlyphSort::FRONT_TO_BACK:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), CompareFrontToBack);
		break;
	}
}

bool SpriteBatch::CompareFrontToBack(Glyph * a, Glyph * b)
{
	return (a->zLayer_ < b->zLayer_);
}

bool SpriteBatch::CompareBackToFront(Glyph * a, Glyph * b)
{
	return (a->zLayer_ > b->zLayer_);
}

bool SpriteBatch::CompareTexture(Glyph * a, Glyph * b)
{
	return (a->texture_ < b->texture_);
}
