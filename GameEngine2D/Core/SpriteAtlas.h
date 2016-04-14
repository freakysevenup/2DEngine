#pragma once
#include <vector>
#include "Texture.h"
#include "Rectangle.h"
#include <glm\glm.hpp>

class SpriteAtlas
{
public:
	SpriteAtlas() {}
	SpriteAtlas(const Texture& texture, const glm::vec2& dimensions) :
		m_texture(texture),
		m_width((int)dimensions.x),
		m_height((int)dimensions.y)
	{

	}
	~SpriteAtlas() { }

	inline Rectangle GetTexCoords(int index)
	{
		int xTile = index % m_width;
		int yTile = index / m_height;

		Rectangle texCoords(
			float(xTile / m_width),
			float(yTile / m_height),
			float(1.0f / m_width),
			float(1.0f / m_height));
		return texCoords;
	}

	inline Texture& GetTexture() { return m_texture; }

private:
	Texture m_texture;
	int m_width, m_height;
};