#include "PlayerTest.h"
#include "Core\Rectangle.h"


PlayerTest::PlayerTest() {}
PlayerTest::~PlayerTest() {}

void PlayerTest::Draw(SpriteBatch& spriteBatch, GLuint textureID)
{
	m_textureID = textureID;

	Rectangle destRect(m_position.x, m_position.y, 60.0f, 60.0f);

	Rectangle UV_RECT(0.0f, 0.0f, 1.0f, 1.0f);
	float DEPTH = 0.0f;

	spriteBatch.Draw(destRect, UV_RECT, textureID, DEPTH, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}