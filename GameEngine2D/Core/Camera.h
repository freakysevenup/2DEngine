#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
using namespace glm;

class Camera
{
public:
	Camera() :
		m_width(500),
		m_height(500),
		m_matrixNeedsUpdate(true),
		m_position(vec2(0.0f)),
		m_viewMatrix(mat4(1.0f)),
		m_orthoMatrix(mat4(1.0f)),
		m_scale(vec2(1.0f))
	{
	}
	~Camera() { }

	void Init(int screenWidth, int screenHeight);
	void Update();
	vec2 ConvertScreenToWorld(const vec2& screenCoords);
	bool CullFromView(const vec2& position, const vec2& dimensions);

	inline vec2 GetPosition() const { return m_position; }
	inline vec2 GetScale() const { return m_scale; }
	inline mat4 GetViewMatrix() const { return m_viewMatrix; }

	void SetPosition(const vec2& newPosition) { m_position = newPosition; }
	void SetScale(const vec2& newScale) { m_scale = newScale; }

private:
	int m_width, m_height;
	vec2 m_position;
	vec2 m_scale;
	mat4 m_viewMatrix, m_orthoMatrix;
	bool m_matrixNeedsUpdate;
};

