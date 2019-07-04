#include "Camera2D.h"

Camera2D::Camera2D() : 
	m_position(0.0f, 0.0f),
	m_cameraMatrix(1.0f),
	m_orthoMatrix(1.0f),
	m_scale(1.0f),
	m_needsMatrixUpdate(true),
	m_screenWidth(500),
	m_screenHeight(500)
{
}

Camera2D::~Camera2D()
{
}

void Camera2D::init(int t_screenWidth, int t_screenHeight) 
{
	m_screenWidth = t_screenWidth;
	m_screenHeight = t_screenHeight;
	m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
}

//updates the camera matrix if needed
void Camera2D::update() 
{
	//Only update if our position or scale have changed
	if (m_needsMatrixUpdate) 
	{
		//Camera Translation
		glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
		m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

		//Camera Scale
		glm::vec3 scale(m_scale, m_scale, 0.0f);
		m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

		m_needsMatrixUpdate = false;
	}
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 t_screenCoords) 
{
	// Invert Y direction
	t_screenCoords.y = m_screenHeight - t_screenCoords.y;
	// Make it so that 0 is the center
	t_screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
	// Scale the coordinates
	t_screenCoords /= m_scale;
	// Translate with the camera position
	t_screenCoords += m_position;
	return t_screenCoords;
}

// Simple AABB test to see if a box is in the camera view
bool Camera2D::isBoxInView(const glm::vec2& t_position, const glm::vec2& t_dimensions)
{
	glm::vec2 scaledScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight) / (m_scale);

	// The minimum distance before a collision occurs
	const float MIN_DISTANCE_X = t_dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
	const float MIN_DISTANCE_Y = t_dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

	// Center position of the parameters
	glm::vec2 centerPos = t_position + t_dimensions / 2.0f;
	// Center position of the camera
	glm::vec2 centerCameraPos = m_position;
	// Vector from the input to the camera
	glm::vec2 distVec = centerPos - centerCameraPos;

	// Get the depth of the collision
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	// If both the depths are > 0, then we collided
	if (xDepth > 0 && yDepth > 0) 
	{
		// There was a collision
		return true;
	}
	return false;
}
