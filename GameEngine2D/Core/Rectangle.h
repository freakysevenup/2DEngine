#pragma once

class Rectangle
{
public:
	Rectangle(float posX, float posY, float width, float height) :
		m_posX(posX),
		m_posY(posY),
		m_width(width),
		m_height(height) { }
	~Rectangle() { }

	inline float GetWidth() { return m_width; }
	inline float GetHeight() { return m_height; }
	inline float GetX() { return m_posX; }
	inline float GetY() { return m_posY; }

private:
	float m_posX, m_posY, m_width, m_height;
};