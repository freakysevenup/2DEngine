#include "PlayerTest.h"
#include "Core\Rectangle.h"


PlayerTest::PlayerTest() {}
PlayerTest::~PlayerTest() {}

void PlayerTest::Draw(SpriteBatch& spriteBatch)
{
	Rectangle destRect(m_position.x, m_position.y, m_texture.m_width, m_texture.m_height);

	Rectangle UV_RECT(0.0f, 0.0f, 1.0f, 1.0f);
	float DEPTH = 0.0f;

	spriteBatch.Draw(destRect, UV_RECT, m_texture.m_id, DEPTH, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}