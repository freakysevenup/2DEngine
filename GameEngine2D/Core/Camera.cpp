#include "Camera.h"

void Camera::Init(int screenWidth, int screenHeight)
{
	m_width = screenWidth;
	m_height = screenHeight;
	m_orthoMatrix = ortho(0.0f, float(m_width), 0.0f, float(m_height));
}

void Camera::Update()
{
	if (m_matrixNeedsUpdate)
	{
		// Translate the Camera
		vec3 translatedCamera(-m_position.x + m_width / 2.0f, -m_position.y + m_height / 2.0f, 0.0f);
		m_viewMatrix = translate(m_orthoMatrix, translatedCamera);

		// Scale the Camera
		vec3 scaledCamera(m_scale.x, m_scale.y, 0.0f);
		m_viewMatrix = scale(mat4(1.0f), scaledCamera) * m_viewMatrix;
		m_matrixNeedsUpdate = false;
	}
}

vec2 Camera::ConvertScreenToWorld(const vec2& screenCoords)
{
	vec2 temp = screenCoords;
	// Invert the y axis
	temp.y = m_height - temp.y;
	// Put the center at zero
	temp -= vec2(m_width / 2.0f, m_height / 2.0f);
	// Scale the coordinates
	temp /= m_scale;
	// Translate the position
	temp += m_position;
	return temp;
}

bool Camera::CullFromView(const vec2& position, const vec2& dimensions)
{
	glm::vec2 scaledScreenDimensions = glm::vec2(m_width, m_height) / m_scale;

	// The minimum distance before a collision occurs
	const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;

	// The maximum distance before a collision occurs
	const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

	// Center position of the parameters
	glm::vec2 centerPosition = position + dimensions / 2.0f;

	// Center Position of the camera
	glm::vec2 centerCameraPos = m_position;

	// Vector from the parameters to the camera
	glm::vec2 distVec = centerPosition - centerCameraPos;

	//Get the depth of the collision
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	// if either of the depths are > 0 we are colliding
	if (xDepth > 0 && yDepth > 0)
	{
		// There was a collision 
		return true;
	}
	return false;
}
