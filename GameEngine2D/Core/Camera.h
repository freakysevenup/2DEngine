#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	Camera() :
		m_width(500),
		m_height(500),
		m_matrixNeedsUpdate(true),
		m_position(glm::vec2(0.0f)),
		m_viewMatrix(glm::mat4(1.0f)),
		m_orthoMatrix(glm::mat4(1.0f)),
		m_scale(glm::vec2(1.0f))
	{
	}
	~Camera() { }

	void Init(int screenWidth, int screenHeight);
	void Update();
	glm::vec2 ConvertScreenToWorld(const glm::vec2& screenCoords);
	bool CullFromView(const glm::vec2& position, const glm::vec2& dimensions);

	inline glm::vec2 GetPosition() const { return m_position; }
	inline glm::vec2 GetScale() const { return m_scale; }
	inline glm::mat4 GetViewMatrix() const { return m_viewMatrix; }

	void SetPosition(const glm::vec2& newPosition) { m_position = newPosition; m_matrixNeedsUpdate = true; }
	void SetScale(const glm::vec2& newScale) { m_scale = newScale; m_matrixNeedsUpdate = true; }

private:
	int m_width, m_height;
	glm::vec2 m_position;
	glm::vec2 m_scale;
	glm::mat4 m_viewMatrix, m_orthoMatrix;
	bool m_matrixNeedsUpdate;
};

