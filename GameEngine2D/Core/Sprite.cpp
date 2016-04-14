#include "Sprite.h"
#include "Vertex.h"
#include "TextureResources.h"

Sprite::Sprite(const glm::vec2& pos, const glm::vec2& scale, const std::string& filePath) :
m_position(pos),
m_scale(scale)
{
	m_texture = TextureResources::GetTexture(filePath);

	if (m_VBO == 0)
	{
		glGenBuffers(1, &m_VBO);
	}

	Vertex vertexData[6];

	//first Triangle of the square
	vertexData[0].SetPosition(m_position.x + m_scale.x, m_position.y + m_scale.y);
	vertexData[0].SetUV(1.0f, 1.0f);

	vertexData[1].SetPosition(m_position.x, m_position.y + m_scale.y);
	vertexData[1].SetUV(0.0f, 1.0f);

	vertexData[2].SetPosition(m_position.x, m_position.y);
	vertexData[2].SetUV(0.0f, 0.0f);

	//second Triangle of the square
	vertexData[3].SetPosition(m_position.x, m_position.y);
	vertexData[3].SetUV(0.0f, 0.0f);

	vertexData[4].SetPosition(m_position.x + m_scale.x, m_position.y);
	vertexData[4].SetUV(1.0f, 0.0f);

	vertexData[5].SetPosition(m_position.x + m_scale.x, m_position.y + m_scale.y);
	vertexData[5].SetUV(1.0f, 1.0f);


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