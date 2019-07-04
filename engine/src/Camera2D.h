
#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Camera class for 2D games
class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	//sets up the orthographic matrix and screen dimensions
	void init(int t_screenWidth, int t_screenHeight);

	//updates the camera matrix if needed
	void update();

	glm::vec2 convertScreenToWorld(glm::vec2 t_screenCoords);

	bool isBoxInView(const glm::vec2& t_position, const glm::vec2& t_dimensions);

	void offsetPosition(const glm::vec2& t_offset) { m_position += t_offset; m_needsMatrixUpdate = true; }
	void offsetScale(float t_offset) { m_scale += t_offset; if (m_scale < 0.001f) m_scale = 0.001f; m_needsMatrixUpdate = true; }

	//setters
	void setPosition(const glm::vec2& t_newPosition) { m_position = t_newPosition; m_needsMatrixUpdate = true; }
	void setScale(float t_newScale) { m_scale = t_newScale; m_needsMatrixUpdate = true; }

	//getters
	const glm::vec2& getPosition() const { return m_position; }
	float getScale() const { return m_scale; }
	const glm::mat4& getCameraMatrix() const { return m_cameraMatrix; }
	float getAspectRatio() const { return (float)m_screenWidth / (float)m_screenHeight; }

private:
	int m_screenWidth, m_screenHeight;
	bool m_needsMatrixUpdate;
	float m_scale;
	glm::vec2 m_position;
	glm::mat4 m_cameraMatrix;
	glm::mat4 m_orthoMatrix;
};

#endif // CAMERA_2D_H
