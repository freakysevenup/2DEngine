#include "Sprite.h"
#include "Vertex.h"

Sprite::Sprite(const vec2& pos, const vec2& scale, const std::string& filePath) :
m_position(pos),
m_scale(scale)
{
	m_tResources = new TextureResources();
	m_texture = *m_tResources->Get(filePath);

	if (m_VBO == 0)
	{
		glGenBuffers(1, &m_VBO);
	}

	Vertex vertexData[6];

	//first Triangle of the square
	vertexData[0].setPosition(m_position.x + m_scale.x, m_position.y + m_scale.y);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(m_position.x, m_position.y + m_scale.y);
	vertexData[1].setUV(0.0f, 1.0f);

	vertexData[2].setPosition(m_position.x, m_position.y);
	vertexData[2].setUV(0.0f, 0.0f);

	//second Triangle of the square
	vertexData[3].setPosition(m_position.x, m_position.y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(m_position.x + m_scale.x, m_position.y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(m_position.x + m_scale.x, m_position.y + m_scale.y);
	vertexData[5].setUV(1.0f, 1.0f);


	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Sprite::~Sprite()
{
	if (m_VBO != 0)
	{
		glDeleteBuffers(1, &m_VBO);
	}
	delete m_tResources;
}

void Sprite::Draw()
{
	glBindTexture(GL_TEXTURE_2D, m_texture.m_id);

	//bind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	//Draw the 6 vertices to the screen
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Disable the vertex attribute array. This is not optional
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}