#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <glcore/glcore.h>

Camera::Camera(CameraSpec& spec)
	:m_CameraSpec(spec)
{
	m_VectorUP = { 0,1,0 };
	m_VectorForward = { 0,0,-1 };
	Update();
}

void Camera::ChangeViewport(uint32_t width, uint32_t height)
{
	this->m_CameraSpec.viewport = { (float)width,(float)height };
}

void Camera::Update()
{

	m_View = glm::rotate(glm::mat4(1.0f), glm::radians(this->m_Rotation.x), { 1,0,0 });
	m_View *= glm::rotate(glm::mat4(1.0f), glm::radians(this->m_Rotation.y), { 0,1,0 });
	m_View *= glm::rotate(glm::mat4(1.0f), glm::radians(this->m_Rotation.z), { 0,0,1 });
	m_View *= glm::lookAt(m_Position, m_Position + m_VectorForward, m_VectorUP);

	m_Projection = glm::perspective(
		glm::radians(m_CameraSpec.fov),
		(float)m_CameraSpec.viewport.width / (float)m_CameraSpec.viewport.height,
		m_CameraSpec.Near,
		m_CameraSpec.Far);
}

void Camera::Move(glm::vec3& dir)
{
	this->m_Position += dir;
	Update();
}

void Camera::Rotate(glm::vec3& rot)
{
	this->m_Rotation += rot;
	Update();
}

void Camera::Upload(uint32_t programID, std::string_view uProjection, std::string_view uView)
{
	glUseProgram(programID);
	uint32_t MatrixID = glGetAttribLocation(programID, uProjection.data());
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(m_Projection));
	MatrixID = glGetAttribLocation(programID, uView.data());
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(m_View));
}
